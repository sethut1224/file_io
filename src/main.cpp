#include "file_io.hpp"
#include "filesystem_utils.hpp"

#define TEXT_FILE1 "/home/taeho/file_io/text_file1.txt" // write 를 통해 생성할 파일 경로
#define TEXT_FILE2 "/home/taeho/file_io/text_file2.txt" // TEXT_FILE1 의 copy 버전 및 remove 대상 파일 경로

int main()
{
    /// open, write, read
    {
        FileIO fio;
        fs::path first(TEXT_FILE1);

        fio.open_output_stream(first);
        if (fio.output_stream_ok())
        {
            std::string write_buf("insert \nthis \ncontent");
            fio.write(write_buf);
            std::cout << "[write text_file1.txt]" << std::endl;
            std::cout << write_buf << std::endl;
        }
        // fio.close_output_stream();

        fio.open_input_stream(first);
        if (fio.input_stream_ok())
        {
            std::string read_buf;
            fio.read(read_buf);
            fio.close_input_stream();
            std::cout << "[read text_file1.txt]" << std::endl;
            std::cout << read_buf << "\n"
                      << std::endl;
        }
        // fio.close_input_stream();
    }

    /// copy, remove, exists, size
    {
        FileIO fio;
        fs::path first(TEXT_FILE1);
        fs::path second(TEXT_FILE2);

        std::cout << "[before copy, text_file2 exists?] : " << std::boolalpha << filesystem_utils::exists(second) << std::endl;
        filesystem_utils::copy(first, second);
        std::cout << "Copy()" << std::endl;
        std::cout << "[after copy, text_file2 exists?] : " << std::boolalpha << filesystem_utils::exists(second) << std::endl;

        // std::cout << "\n[text_file1 and text_file2  size] : " << filesystem_utils::HumanReadable{filesystem_utils::size(first)}
        // <<","<<filesystem_utils::HumanReadable{filesystem_utils::size(second)}<<std::endl;

        filesystem_utils::remove(second);
        std::cout << "Remove()" << std::endl;
        std::cout << "[after remove, text_file2.txt exists?] : " << std::boolalpha << filesystem_utils::exists(second) << "\n"
                  << std::endl;
    }

    /// current_path, canonical_path, list_up
    {
        fs::path current_path = filesystem_utils::current_path();
        std::cout << "[current_path] : " << current_path << std::endl;
        std::cout << "[current path absolute] : " << filesystem_utils::absolute_path(current_path) << std::endl;
        std::cout << "[current directory list up]" << std::endl;
        filesystem_utils::list_up(current_path, false);
    }
}
