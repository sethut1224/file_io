#include "filesystem_utils.hpp"

namespace filesystem_utils
{
    void copy(const fs::path &from, const fs::path &to, fs::copy_options options)
    {
        fs::copy(from, to, options);
    }

    void remove_all(const fs::path &path)
    {
        uintmax_t n = fs::remove_all(path);
        std::cout << "Delete " << n << " files or directories" << std::endl;
    }

    void remove(const fs::path &path)
    {
        uintmax_t n =fs::remove(path);
        std::cout << "Delete " << n << " files or directories" << std::endl;
    }

    void create_directories(const fs::path &path)
    {
        fs::create_directories(path);
    }

    const std::filesystem::file_time_type last_write_time(const fs::path &path)
    {
        return fs::last_write_time(path);
    }

    const std::uintmax_t size(const fs::path &path)
    {
        return fs::file_size(path);
    }

    const bool exists(const fs::path &path)
    {
        return fs::exists(path);
    }

    const fs::path current_path()
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

    void list_up(const fs::path &path, bool recursive)
    {
        if (recursive)
        {
            for (auto &e : fs::recursive_directory_iterator(path))
            {
                std::cout << e.path() << std::endl;
            }
        }
        else
        {
            for (auto &e : fs::directory_iterator(path))
            {
                std::cout << e.path() << std::endl;
            }
        }
    }
}
