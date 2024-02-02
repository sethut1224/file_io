#ifndef __FILE_WRITER_HPP__
#define __FILE_WRITER_HPP__

#include <fstream>
#include <string>
#include <sstream>
#include <time_utils.hpp>

class FileWriter
{
private:
    std::string file_path_;
    std::ofstream stream_;

public:
    FileWriter() = default;
    FileWriter(const char *path, std::ios_base::openmode mode = std::ios_base::out);

    void file_write(const std::string &str);
    const bool is_ok() const;
    
};

#endif