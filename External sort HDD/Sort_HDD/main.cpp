#include "messages.h"
#include "external_sort.h"
#include "files.h"

#include <chrono>
#include <iostream>


void main(int argc, const char** argv)
{

#ifdef _DEBUG
    const char* agrs[] = { "", "srcFile.bin", "dstFile.bin" };
    argc = 3;
    argv = agrs;
    generate_file(argv[1]);
#endif

    if(argc != 3)
    {
        std::cout << message::help;
        return;
    }

    //measure time
    namespace chn = std::chrono;
    const auto beforeSortTime = chn::high_resolution_clock::now();

    //sort
    const auto code = external_sort(argv[1], argv[2]);

    const auto afterSortTime = chn::high_resolution_clock::now();
    const auto duration = chn::duration_cast<chn::milliseconds>(afterSortTime - beforeSortTime).count();

    char outString[1024];
    sprintf_s(outString, sizeof(outString), "Operation has been completed in %lli ms\n", duration);
    std::cout << outString;

    switch(code)
    {
    case SortError::Success:
        break;
    default:
        std::cout << message::unknownError;
        break;
    }
}