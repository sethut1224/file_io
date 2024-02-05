#include "file_io.hpp"

void FileIO::open_input_stream(const char *path, std::ios_base::openmode mode)
{
    if (istream_.is_open())
        close_input_stream();
    istream_.open(path, mode);
    istream_path_ = fs::path(path);
}

void FileIO::open_output_stream(const char *path, std::ios_base::openmode mode)
{
    if (ostream_.is_open())
        close_output_stream();
    ostream_.open(path, mode);
    ostream_path_ = fs::path(path);
}

void FileIO::open_input_stream(const fs::path& path, std::ios_base::openmode mode)
{
    open_input_stream(path.c_str(), mode);
}

void FileIO::open_output_stream(const fs::path& path, std::ios_base::openmode mode)
{
    open_output_stream(path.c_str(), mode);
}

void FileIO::close_output_stream()
{
    ostream_path_ = "";
    ostream_.close();
}

void FileIO::close_input_stream()
{
    istream_path_ = "";
    istream_.close();
}

const bool FileIO::access_same_file() const
{
    return ostream_path_ == istream_path_;
}

const bool FileIO::input_stream_ok() const
{
    return istream_.is_open() && istream_.good();
}

const bool FileIO::output_stream_ok() const
{
    return ostream_.is_open() && ostream_.good();
}

void FileIO::read(std::string &buf)
{   
    if(access_same_file())
    {
        close_output_stream();
    }
    #ifdef READ_LINE_BY_LINE
        read_line_by_line();
    #else
        read_entire(buf);
    #endif
};

void FileIO::read_entire(std::string &buf)
{
    istream_.seekg(0, std::ios::end);
    size_t file_size = istream_.tellg();
    istream_.seekg(0, std::ios::beg);

    buf.resize(file_size);
    istream_.read(&buf[0], file_size);
}

void FileIO::read_line_by_line(std::string &buf)
{
    std::string s;
    while (getline(istream_, s))
    {
        buf.append(s);
    }
}

void FileIO::write(const std::string &buf)
{
    ostream_.write(buf.c_str(), buf.size());
};

