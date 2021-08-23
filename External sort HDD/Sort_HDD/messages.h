#pragma once

namespace message
{
static const char* const help =
"This program sorts the content from a source file and save the result in a destination file\n\n"
"Sort_HDD.exe [source filepath] [destination filepath]\n\n"
"The content of the source file reads as an array of 4-byte integers. The destination file replaces if exists.\n\n"
"Example: sort_hdd.exe srcFile.bin dstFile.bin\n";

static const char* const srcFileNotExist =
"Source file does not exist.\n";

static const char* const srcFileEmpty =
"Source file is empty.\n";

static const char* const srcFileTooBig =
"Source file is too big.\n";

static const char* const srcFileReadError =
"Unable to read source file.\n";

static const char* const dstFileCreateError =
"Unable to create destination file.\n";

static const char* const dstFileWriteError =
"Unable to read destination file.\n";

static const char* const unknownError =
"Unknown error has occured.\n";
}
