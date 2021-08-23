#pragma once
#include <fstream>

enum class FileError : char
{
    Success,
    NotExist,
    AlreadyExists,
    Empty,
    TooBig,
    CreateError,
    OpenError,
    WriteError,
    ReadError,
    RemoveError,
    EmptyPath,
    RenameError,
    Unknown,
};

using NewFile = std::ofstream;
using ExistFile = std::ifstream;

FileError open_file(std::ifstream& file, const char* filepath);
FileError create_file(std::ofstream& file, const char* filepath, bool rewrite = true);
FileError read_from_file(std::ifstream& file, char* buffer, size_t size);
FileError write_to_file(std::ofstream& file, const char* buffer, size_t size);

FileError storeBufferToFile(const char* filepath, const char* buffer, size_t size);
FileError remove_file(const char* filepath);
FileError rename_file(const char* oldFilepath, const char* newFilepath);
FileError extract_parent_path(const char* filepath, std::string& parentPath);

#ifdef _DEBUG
void generate_file(const char* file);
#endif
