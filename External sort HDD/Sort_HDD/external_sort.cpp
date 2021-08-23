#include "external_sort.h"
#include "system_config.h"
#include "files.h"
#include "messages.h"

#include <execution>
#include <future>
#include <string>
#include <fstream>
#include <stack>

#ifdef _DEBUG
#include <thread>
#endif

const std::unordered_map<SortError, const char*>  errorMessages =
{
    {SortError::SrcFileNotExist, message::srcFileNotExist},
    {SortError::SrcFileEmpty, message::srcFileEmpty},
    {SortError::SrcFileTooBig, message::srcFileTooBig},
    {SortError::SrcFileReadError, message::srcFileReadError},
    {SortError::DstFileCreateError, message::dstFileCreateError},
    {SortError::DstFileWriteError, message::dstFileWriteError},
    {SortError::Unknown, message::unknownError},
};

static std::string srcParentPath;
static const char* kHelpFilename = "sort_help_file_";
static const char* kHelpFilenameExt = ".bin";
static int kGlobalHelpFileCounter = 0;

SortError split_file_into_helpfiles(const char* filepath, std::stack<std::string>& splitFiles);
SortError merge_files(const char* filepath1, const char* filepath2, const char* resultFilepath, size_t memoryDivider);
SortError remove_help_files();
std::string generate_help_file_name();

SortError external_sort(const char* src, const char* dst)
{
    //extract parent path for help files
    extract_parent_path(src, srcParentPath);

    //Phase I. Split files into separate sorted files size of available RAM
    std::stack<std::string> splitFiles;
    auto error = split_file_into_helpfiles(src, splitFiles);

    if(error != SortError::Success)
    {
        remove_help_files();
        return error;
    }

    //Phase II. Merge splited files into bigger ones. Then merge bigger files and so on recursively.
    std::stack<std::string> mergeStack = std::move(splitFiles);
    std::stack<std::string> tmpStack;

    std::vector<std::future<SortError>> merge_futures;

    while(mergeStack.size() > 1)
    {
        //this prevents from using max available RAM
        //each thread will use a correspondent part of RAM
        size_t memoryDivider = mergeStack.size() / 2;

        //take 2 help files from stack and merge them
        while(mergeStack.size() > 1)
        {
            auto resultFile = generate_help_file_name();

            tmpStack.emplace(resultFile);

            auto helpFile1 = mergeStack.top();
            mergeStack.pop();

            auto helpFile2 = mergeStack.top();
            mergeStack.pop();

            //parallel merge of pairs of files 
            auto merge_future = std::async(std::launch::async, [helpFile1, helpFile2, resultFile, memoryDivider]
                {
                    auto error = merge_files(helpFile1.c_str(), helpFile2.c_str(), resultFile.c_str(), memoryDivider);

                    remove_file(helpFile1.c_str());
                    remove_file(helpFile2.c_str());

                    return error;
                });
            merge_futures.push_back(std::move(merge_future));
        }

        //wait for merging of the current layer
        for(auto& merge_future : merge_futures)
        {
            if(merge_future.valid())
            {
                auto e = merge_future.get();
                if(e != SortError::Success)
                {
                    error = e;
                }
            }
        }

        if(error != SortError::Success)
        {
            break;
        }

        //add the last help file to a new stack if previous stack had odd number of files
        const bool isOneFileLeft = !mergeStack.empty();
        if(isOneFileLeft)
        {
            tmpStack.emplace(std::move(mergeStack.top()));
            mergeStack.pop();
        }

        std::swap(tmpStack, mergeStack);
    }

    auto fileError = rename_file(mergeStack.top().c_str(), dst);

    if(fileError != FileError::Success)
    {
        error = SortError::Unknown;//TODO
    }

    remove_help_files();

    return error;
}

SortError split_file_into_helpfiles(const char* filepath, std::stack<std::string>& splitFiles)
{
    ExistFile srcFile;
    auto error = open_file(srcFile, filepath);

    if(error != FileError::Success)
    {
        return SortError::Unknown;//TODO
    }

    //reserve two half size buffers of available RAM
    const auto bufferSizeInBytes = system_config::ramMaxSize / 2;
    std::vector<int> buffer1(bufferSizeInBytes / sizeof(int));
    std::vector<int> buffer2(bufferSizeInBytes / sizeof(int));

    auto* fileBufferPtr = &buffer1;
    auto* sortBufferPtr = &buffer2;

    std::future<FileError> sort_future;

    while(srcFile.good())
    {
        //read file
        auto fileBufferRawPtr = reinterpret_cast<char*>(fileBufferPtr->data());
        error = read_from_file(srcFile, fileBufferRawPtr, bufferSizeInBytes);

        //check reading errors
        if(error != FileError::Success)
        {
            srcFile.close();
            return SortError::Unknown;//TODO
        }

        //get read bytes count
        auto readByteCount = srcFile.gcount();

        std::swap(fileBufferPtr, sortBufferPtr);

        //if sorting task has already been run then wait for it
        if(sort_future.valid())
        {
            error = sort_future.get();

            //check errors while sorting
            if(error != FileError::Success)
            {
                srcFile.close();
                return SortError::Unknown;//TODO
            }
        }

        if(readByteCount > 0)
        {
            //run sorting task and continue to read source file
            sort_future = std::async(std::launch::async, [sortBufferPtr, readByteCount, &splitFiles]
                {
                    //parallel sort
                    const auto fourByteCount = readByteCount / sizeof(int);
                    std::sort(std::execution::par_unseq, sortBufferPtr->begin(), sortBufferPtr->begin() + fourByteCount);

                    //store filename to stack
                    auto resultFile = generate_help_file_name();
                    splitFiles.push(resultFile);
                    auto bufferRawPtr = reinterpret_cast<char*>(sortBufferPtr->data());

                    //store buffer to disk
                    return storeBufferToFile(resultFile.c_str(), bufferRawPtr, readByteCount);
                });
        }
    }

    srcFile.close();

    return SortError::Success;
}

SortError merge_files(const char* filepath1, const char* filepath2, const char* resultFilepath, size_t memoryDivider)
{
    ExistFile file[2];
    auto error = open_file(file[0], filepath1);

    if(error != FileError::Success)
    {
        return SortError::Unknown;//TODO
    }

    error = open_file(file[1], filepath2);

    if(error != FileError::Success)
    {
        return SortError::Unknown;//TODO
    }

    NewFile resultFile;
    error = create_file(resultFile, resultFilepath);

    if(error != FileError::Success)
    {
        return SortError::Unknown;//TODO
    }

    auto closeFiles = [file = file, &resultFile]
    {
        file[0].close();
        file[1].close();
        resultFile.close();
    };

    //available RAM size
    const auto ramMaxSize = system_config::ramMaxSize / memoryDivider;

    //reserve two quater size buffers of available RAM
    const auto bufferSizeInBytes = ramMaxSize / 4;
    std::vector<int> buffer[2];
    buffer[0].resize(bufferSizeInBytes / sizeof(int));
    buffer[1].resize(bufferSizeInBytes / sizeof(int));

    //reserve result buffer equals to two previous buffers
    const auto resultBufferSizeInBytes = ramMaxSize / 2;
    std::vector<int> resultBuffer(resultBufferSizeInBytes / sizeof(int));

    //start iterate through the files
    std::int64_t index[2] = { 0 };
    std::int64_t bufferSize[2] = { 0 };
    std::int64_t resultIndex = 0;
    std::int64_t resultBufferSize = 0;

    while(true)
    {
        for(size_t i = 0; i < 2; ++i)
        {
            if(index[i] == bufferSize[i])
            {
                if(file[i].eof())
                {
                    continue;
                }

                index[i] = 0;
                auto rawPtr = reinterpret_cast<char*>(buffer[i].data());
                error = read_from_file(file[i], rawPtr, bufferSizeInBytes);

                if(error != FileError::Success)
                {
                    closeFiles();
                    return SortError::Unknown; //TODO
                }

                bufferSize[i] = file[i].gcount() / sizeof(int);

                if(bufferSize[i] == 0)
                {
                    index[i] = -1;
                }
            }
        }

        const bool allFilesEOF = index[0] == -1 && index[1] == -1;
        if(allFilesEOF)
        {
            break;
        }

        while(index[0] < bufferSize[0] && index[1] < bufferSize[1])
        {
            int resultNumber = 0;

            //compare between two value from both buffers
            if(index[0] != -1 && index[1] != -1)
            {
                if(buffer[0][index[0]] < buffer[1][index[1]])
                {
                    resultNumber = buffer[0][index[0]];
                    ++index[0];
                }
                else
                {
                    resultNumber = buffer[1][index[1]];
                    ++index[1];
                }
            }
            //second buffer is empty, work with first
            else if(index[0] != -1)
            {
                resultNumber = buffer[0][index[0]];
                ++index[0];
            }
            //first buffer is empty, work with second
            else
            {
                resultNumber = buffer[1][index[1]];
                ++index[1];
            }

            resultBuffer[resultIndex++] = resultNumber;

            //result buffer is full
            const bool needFlushToFile = resultIndex == resultBuffer.size();
            if(needFlushToFile)
            {
                resultIndex = 0;
                auto rawPtr = reinterpret_cast<char*>(resultBuffer.data());
                error = write_to_file(resultFile, rawPtr, resultBuffer.size() * sizeof(int));

                if(error != FileError::Success)
                {
                    closeFiles();
                    return SortError::Unknown; //TODO
                }
            }
        }
    }

    //result buffer is not empty
    const bool needFlushToFile = resultIndex > 0;
    if(resultIndex > 0)
    {
        auto fileBufferRawPtr = reinterpret_cast<char*>(resultBuffer.data());
        error = write_to_file(resultFile, fileBufferRawPtr, resultIndex * sizeof(int));
        resultIndex = 0;

        if(error != FileError::Success)
        {
            closeFiles();
            return SortError::Unknown; //TODO
        }
    }

    closeFiles();

    return error == FileError::Success ? SortError::Success : SortError::Unknown; //TODO
}

SortError remove_help_files()
{
    //store counter
    const auto fileCount = kGlobalHelpFileCounter;

    //reset counter for generator
    kGlobalHelpFileCounter = 0;

    //remove help files
    for(size_t i = 0; i < fileCount; i++)
    {
        remove_file(generate_help_file_name().c_str());
    }

    //reset counter again for system
    kGlobalHelpFileCounter = 0;

    return SortError::Success;
}

std::string generate_help_file_name()
{
    std::string filename(srcParentPath);
    if(!srcParentPath.empty())
    {
        filename.append("\\");
    }
    filename.append(kHelpFilename);
    filename.append(std::to_string(kGlobalHelpFileCounter++));
    filename.append(kHelpFilenameExt);
    return filename;
}