#include "file_reader.hpp"
#include "file_writer.hpp"
#include <iostream>

bool validate_arguments(int argc, char *argv[])
{
    try
    {
        if (argc == 1)
        {
            throw std::runtime_error("file path is not passed by argument!");
        }
        else if (argc > 2)
        {
            throw std::runtime_error("more than 2 files are passed by argument!");
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "argument error : " << e.what() << std::endl;
        std::cout << "usage : " << argv[0] << " <file_path> " << std::endl;
        return false;
    }

    return true;
}

int main(int argc, char *argv[])
{
    if (!validate_arguments(argc, argv))
    {
        exit(-1);
    }

    const char *file_path = argv[1];
    struct timespec begin, end, res;

    // File Write
    // write user-defined string to the file passed as command line arguments
    {
        // FileWriter fw(file_path, std::ofstream::out | std::ofstream::app); //append mode
        FileWriter fw(file_path, std::ofstream::out); // writing starts from the beginning of the file
        if (!fw.is_ok())
        {
            std::cout << "can not open file! check the file path" << std::endl;
            return -1;
        }
        std::string s("insert \nthis \ncontent");

        clock_gettime(CLOCK_MONOTONIC, &begin);
        fw.file_write(s);
        clock_gettime(CLOCK_MONOTONIC, &end);

        std::cout << "[write file]" << std::endl;
        std::cout << s << std::endl;

        time_utils::sub(&end, &begin, &res);
        std::cout << "write elapse: " << time_utils::to_nsec(&res) << "ns\n\n" << std::endl;
    }

    // File Read
    // read the file passed as command line arguments
    {
        FileReader fr(file_path);
        if (!fr.is_ok())
        {
            std::cout << "file path : " << file_path << std::endl;
            std::cout << "can not open file! check the file path" << std::endl;
            return -1;
        }
        std::string buf;

        clock_gettime(CLOCK_MONOTONIC, &begin);
        fr.file_read(buf);
        clock_gettime(CLOCK_MONOTONIC, &end);

        std::cout << "[read file]" << std::endl;
        std::cout << buf << std::endl;

        time_utils::sub(&end, &begin, &res);
        std::cout << "read elapse: " << time_utils::to_nsec(&res) << "ns" << std::endl;
    }
}