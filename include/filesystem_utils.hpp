#ifndef __FILESYSTEM_UTILS_HPP__
#define __FILESYSTEM_UTILS_HPP__

#include <fstream>
#include <filesystem>
#include <iostream>
#include <cmath>

// #define READ_LINE_BY_LINE

namespace fs = std::filesystem;

namespace filesystem_utils
{
    struct HumanReadable
    {
        std::uintmax_t size{};

    private:
        friend std::ostream &operator<<(std::ostream &os, HumanReadable hr)
        {
            int o{};
            double unit = hr.size;
            while(unit >= 1024)
            {
                ++o;
                unit /= 1024;
            }
            os << std::ceil(unit * 10.) / 10. << "BKMGTPE"[o];
            
            return o ? os << "B (" << hr.size << ')' : os;
        }
    };

    /// \param[in] copy_options : update_exisitng,
    ///                           overwirte_exisiting,
    ///                           recursive,
    ///                           directories_only
    ///                         ...
    void copy(const fs::path &from, const fs::path &to, fs::copy_options options = fs::copy_options::none);

    void remove_all(const fs::path &path);
    void remove(const fs::path &path);

    void create_directories(const fs::path &path);

    const std::filesystem::file_time_type last_write_time(const fs::path &path);
    const std::uintmax_t size(const fs::path &path);
    const bool exists(const fs::path &path);

    const fs::path current_path();
    const fs::path absolute_path(const fs::path &path);
    const fs::path canonical_path(const fs::path &path);

    void list_up(const fs::path &path, bool recursive = true);
}
#endif
