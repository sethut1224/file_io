#include "file_reader.hpp"

FileReader::FileReader(const char *path, std::ios_base::openmode mode)
    : file_path_{path}
{
    stream_.open(file_path_, mode);
}

void FileReader::file_read(std::string& buf)
{
    // read_entire(buf);
    read_line_by_line(buf);
}

void FileReader::read_entire(std::string& buf)
{
    stream_.seekg(0, std::ios::end);
    size_t file_size = stream_.tellg();
    stream_.seekg(0, std::ios::beg);

    buf.resize(file_size);
    stream_.read(&buf[0], file_size);
}

void FileReader::read_line_by_line(std::string& buf)
{
    std::string s;
    while(getline(stream_,s))
    {   
        buf.append(s);
    }
}

const bool FileReader::is_ok() const
{
    return stream_.is_open() && stream_.good();
}
