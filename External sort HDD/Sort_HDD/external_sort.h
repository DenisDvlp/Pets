#pragma once
#include <unordered_map>

enum class SortError : char
{
    Success,
    SrcFileNotExist,
    SrcFileEmpty,
    SrcFileTooBig,
    SrcFileReadError,
    DstFileCreateError,
    DstFileWriteError,
    Unknown,
};

extern const std::unordered_map<SortError, const char*>  errorMessages;

SortError external_sort(const char* src, const char* dst);
