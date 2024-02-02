#include "file_writer.hpp"

FileWriter::FileWriter(const char *path, std::ios_base::openmode mode)
    : file_path_{path}
{
    stream_.open(file_path_, mode);
}

const bool FileWriter::is_ok() const
{
    return stream_.is_open() && stream_.good();
}

void FileWriter::file_write(const std::string &str)
{
    stream_.write(str.c_str(), str.size());
}
