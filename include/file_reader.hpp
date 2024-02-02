#ifndef __FILE_READER_HPP__
#define __FILE_READER_HPP__

#include <fstream>
#include <string>
#include <time_utils.hpp>


class FileReader
{
private:
    std::string file_path_;
    std::ifstream stream_;

public:
    FileReader() = default;
    FileReader(const char *path, std::ios_base::openmode mode = std::ios_base::in);

    void file_read(std::string& buf);
    void read_entire(std::string& buf);
    void read_line_by_line(std::string& buf);

    const bool is_ok() const;

};

#endif