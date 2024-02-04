#ifndef __FILE_IO_HPP__
#define __FILE_IO_HPP__

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>

// #define READ_LINE_BY_LINE

namespace fs = std::filesystem;

void copy(const fs::path &from, const fs::path &to, fs::copy_options options = fs::copy_options::none)
{
    fs::copy(from, to, options);
}

void remove_all(const fs::path &path)
{
    std::error_code err;
    fs::remove_all(path);
    std::runtime_error(err.message());
}

void remove(const fs::path &path)
{
    std::error_code err;
    fs::remove(path, err);
    std::runtime_error(err.message());
}

void create_directories(const fs::path &path)
{
    fs::create_directories(path);
}

std::filesystem::file_time_type last_write_time(const fs::path &path)
{
    return fs::last_write_time(path);
}

uint64_t size(const fs::path &path)
{
    return fs::file_size(path);
}

bool exist(const fs::path &path)
{
    return fs::exists(path);
}

const fs::path current_path(const fs::path &path)
{
    return fs::current_path();
}

const fs::path absolute_path(const fs::path &path)
{
    return fs::absolute(path);
}

const fs::path canonical_path(const fs::path &path)
{
    return fs::canonical(path);
}

void list_up(const fs::path &path, bool recursive = true)
{   
    if(recursive)
    {
        for(auto& e : fs::recursive_directory_iterator(path))
        {
            std::cout<<e.path()<<std::endl;
        }
    }

    else
    {
        for (auto &e : fs::directory_iterator(path))
        {
            std::cout<<e.path()<<std::endl;

        }
    }
}

class FileIO
{
private:
    std::ofstream ostream_;
    std::ifstream istream_;

    fs::path ostream_path_;
    fs::path istream_path_;

public:
    FileIO() = default;

    void open_input_stream(const char *path, const std::ios_base::openmode mode = std::ios_base::in)
    {
        if (istream_.is_open())
            istream_.close();
        istream_.open(path, mode);
        istream_path_ = fs::path(path);
    }

    void open_output_stream(const char *path, const std::ios_base::openmode mode = std::ios_base::out)
    {
        if (ostream_.is_open())
            ostream_.close();
        ostream_.open(path, mode);
        ostream_path_ = fs::path(path);
    }

    const bool input_stream_ok() const
    {
        return istream_.is_open() && istream_.good();
    }

    const bool output_stream_ok() const
    {
        return ostream_.is_open() && ostream_.good();
    }

    void read(std::string &buf)
    {
        #ifdef READ_LINE_BY_LINE
            read_line_by_line();
        #else
            read_entire(buf);
        #endif
    };

    void write(const std::string &buf)
    {
        ostream_.write(buf.c_str(), buf.size());
    };

    void read_entire(std::string &buf)
    {
        istream_.seekg(0, std::ios::end);
        size_t file_size = istream_.tellg();
        istream_.seekg(0, std::ios::beg);

        buf.resize(file_size);
        istream_.read(&buf[0], file_size);
    }

    void read_line_by_line(std::string &buf)
    {
        std::string s;
        while (getline(istream_, s))
        {
            buf.append(s);
        }
    }

    void copy(const fs::path &from, const fs::path &to, fs::copy_options options = fs::copy_options::none)
    {
        fs::copy(from, to, options);
    }

    void rm(const fs::path &path)
    {
        std::error_code err;
        fs::remove_all(path);
        std::runtime_error(err.message());
    }

    void rmdir(const fs::path &path)
    {
        std::error_code err;
        fs::remove(path, err);
        std::runtime_error(err.message());
    }

    void mkdir(const fs::path &path)
    {
        fs::create_directories(path);
    }

    std::filesystem::file_time_type last_write_time(const fs::path &path)
    {
        return fs::last_write_time(path);
    }

    uint64_t size(const fs::path &path)
    {
        return fs::file_size(path);
    }

    bool exist(const fs::path &path)
    {
        return fs::exists(path);
    }

    const fs::path current_path(const fs::path &path)
    {
        return fs::current_path();
    }

    const fs::path absolute_path(const fs::path &path)
    {
        return fs::absolute(path);
    }

    const fs::path canonical_path(const fs::path &path)
    {
        return fs::canonical(path);
    }

    void recursive_traversal(const fs::path &path)
    {
        for (auto &e : fs::recursive_directory_iterator(path))
        {
            std::cout << e.path() << std::endl;
        }
    }
};

#endif
