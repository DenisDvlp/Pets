#include "files.h"
#include "system_config.h"

#include <filesystem>

namespace fs = std::filesystem;

FileError open_file(std::ifstream& file, const char* filepath)
{
    if(!filepath || *filepath == 0)
    {
        return FileError::EmptyPath;
    }

    const auto path = fs::path(filepath);

    if(!fs::exists(path))
    {
        return FileError::NotExist;
    }

    const auto fileSize = fs::file_size(path);

    if(fileSize == 0)
    {
        return FileError::Empty;
    }

    if(fileSize > system_config::fileMaxSize)
    {
        return FileError::TooBig;
    }

    file = std::ifstream(path, std::ios::binary);

    if(file.fail())
    {
        file.close();
        return FileError::OpenError;
    }

    return FileError::Success;
}


FileError create_file(std::ofstream& file, const char* filepath, bool rewrite)
{
    if(!filepath || *filepath == 0)
    {
        return FileError::EmptyPath;
    }

    const auto path = fs::path(filepath);

    if(!fs::exists(path) && !rewrite)
    {
        return FileError::AlreadyExists;
    }

    file = std::ofstream(path, std::ios::binary);

    if(file.fail())
    {
        file.close();
        return FileError::CreateError;
    }

    return FileError::Success;
}

FileError read_from_file(std::ifstream& file, char* buffer, size_t size)
{
    file.read(buffer, size);

    if(file.fail() && !file.eof())
    {
        return FileError::ReadError;
    }

    return FileError::Success;
}

FileError write_to_file(std::ofstream& file, const char* buffer, size_t size)
{
    file.write(buffer, size);

    if(file.fail())
    {
        return FileError::WriteError;
    }

    return FileError::Success;
}

FileError storeBufferToFile(const char* filepath, const char* buffer, size_t size)
{
    NewFile file;

    auto error = create_file(file, filepath);

    if(error == FileError::Success)
    {
        error = write_to_file(file, buffer, size);
    }

    file.close();

    return error;
}

FileError remove_file(const char* filepath)
{
    if(!filepath || *filepath == 0)
    {
        return FileError::EmptyPath;
    }

    const auto path = fs::path(filepath);

    if(!fs::exists(path))
    {
        return FileError::NotExist;
    }

    if(!fs::remove(path))
    {
        return FileError::RemoveError;
    }

    return FileError::Success;
}

FileError rename_file(const char* oldFilepath, const char* newFilepath)
{
    if(!oldFilepath || *oldFilepath == 0 || !newFilepath || *newFilepath == 0)
    {
        return FileError::EmptyPath;
    }

    const auto oldPath = fs::path(oldFilepath);

    if(!fs::exists(oldPath))
    {
        return FileError::NotExist;
    }

    const auto newPath = fs::path(newFilepath);

    std::error_code code;
    fs::rename(oldPath, newPath, code);

    if(code)
    {
        return FileError::RenameError;
    }

    return FileError::Success;
}

FileError extract_parent_path(const char* filepath, std::string& parentPath)
{
    if(!filepath)
    {
        return FileError::EmptyPath;
    }

    parentPath = fs::path(filepath).parent_path().u8string();

    return FileError::Success;
}

#ifdef _DEBUG
void generate_file(const char* file)
{
    const auto filepath = fs::path(file);

    if(!fs::exists(filepath))
    {
        std::srand(std::chrono::high_resolution_clock::now().time_since_epoch().count());

        auto file = std::ofstream(filepath, std::ofstream::binary);

        std::vector<size_t> buffer(system_config::ramMaxSize / sizeof(size_t));

        size_t blockCount = system_config::fileMaxSize / 4 / buffer.size() / sizeof(size_t);
        for(size_t i = 0; i < blockCount; ++i)
        {
            for(auto& element : buffer)
            {
                element =
                    static_cast<size_t>(std::rand()) << 48 |
                    static_cast<size_t>(std::rand()) << 36 |
                    static_cast<size_t>(std::rand()) << 16 |
                    static_cast<size_t>(std::rand());
            }
            file.write((char*)buffer.data(), buffer.size() * sizeof(size_t));
            file.flush();
        }
        file.close();
    }
}
#endif