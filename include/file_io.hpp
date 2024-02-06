#ifndef __FILE_IO_HPP__
#define __FILE_IO_HPP__

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

// #define READ_LINE_BY_LINE

namespace fs = std::filesystem;

class FileIO
{
public:
    std::ofstream ostream_;
    std::ifstream istream_;

    fs::path ostream_path_;
    fs::path istream_path_;

public:
    FileIO() = default;

    void open_input_stream(const fs::path &path, std::ios_base::openmode mode = std::ios_base::in);
    void open_input_stream(const char *path, std::ios_base::openmode mode = std::ios_base::in);
    void open_output_stream(const fs::path &path, std::ios_base::openmode mode = std::ios_base::out);
    void open_output_stream(const char *path, std::ios_base::openmode mode = std::ios_base::out);

    void close_input_stream();
    void close_output_stream();

    const bool access_same_file() const;
    const bool input_stream_ok() const;
    const bool output_stream_ok() const;

    void read(std::string &buf);
    void read_entire(std::string &buf);
    void read_line_by_line(std::string &buf);
    void write(const std::string &buf);
};

#endif
