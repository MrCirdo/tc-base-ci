/**
 ** \file misc/file-library.cc
 ** \brief Implements misc::file_library.
 */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <stdexcept>
#include <iostream>
#include <misc/contract.hh>
#include <misc/file-library.hh>

namespace misc
{

  void
  file_library::push_cwd()
  {
    // Store the working directory
    char cwd[MAXPATHLEN + 1];

    if (nullptr == getcwd(cwd, MAXPATHLEN + 1))
      throw std::runtime_error("working directory name too long");

    push_current_directory(cwd);
  }


  file_library::file_library()
  {
    push_cwd();
  }

  file_library::file_library(path p)
  {
    push_cwd();
    // Then only process given path.
    search_path_.push_back(p);
  }

  void
  file_library::append_dir_list(std::string path_list)
  {
    std::string::size_type pos;

    while ((pos = path_list.find(':')) != std::string::npos)
      {
        append_dir(path_list.substr(0, pos));
        path_list.erase(0, pos + 1);
      }
    append_dir(path_list);
  }


  path
  file_library::ensure_absolute_path(path p) const
  {
    if (p.absolute_get())
      return p;
    else
      return current_directory_get() + p;
  }

  void
  file_library::append_dir(path p)
  {
    search_path_.push_back(ensure_absolute_path(p));
  }

  void
  file_library::prepend_dir(path p)
  {
    search_path_.push_front(ensure_absolute_path(p));
  }

  void
  file_library::push_current_directory(path p)
  {
    // Ensure that path is absolute.
    if (!p.absolute_get())
      p = this->current_directory_get() + p;

    current_directory_.push_front(p);
  }

  void
  file_library::pop_current_directory()
  {
    precondition(!current_directory_.empty());

    current_directory_.pop_front();
  }

  path
  file_library::current_directory_get() const
  {
    precondition(!current_directory_.empty());

    return *current_directory_.begin();
  }


  path
  file_library::find_file(const std::string& file)
  {
    // Split file in two components, basename and basedir.
    path directory = basedir(file);
    std::string filename = basename(file);


    if (directory.absolute_get())
      {
        // If file is absolute, just check that it exists.
        if (!file_exists(file))
          return path();
      }
    else
      {
        // Does the file can be found in current directory?
        if (find_in_directory(current_directory_get(), file))
          return basedir(current_directory_get() + file);

        directory = find_in_search_path(directory, filename);
      }

    return directory;
  }

  bool
  file_library::find_in_directory(const path& dir,
                                  const std::string& file) const
  {
    return file_exists(dir + file);
  }

  path
  file_library::find_in_search_path(const path& relative_path,
                                    const std::string& filename) const
  {
    path checked_dir;

    // Otherwise start scanning the search path.
    for (const path& p : search_path_)
      {
        if (p.absolute_get())
          checked_dir = p;
        else
          checked_dir = current_directory_get() + p;

        checked_dir += relative_path;

        if (find_in_directory(checked_dir, filename))
          return checked_dir;
      }

    // File not found in search path.
    return path();
  }

  std::ostream&
  file_library::dump(std::ostream& ostr) const
  {
    ostr << ".";
    for (const path& p : search_path_)
      ostr << ":" << p;
    return ostr;
  }

  std::string
  basename(const std::string& file)
  {
    std::string::size_type pos;

    if ((pos = file.rfind('/')) != std::string::npos)
      return file.substr(pos + 1);
    else
      return file;
  }

  path
  basedir(const std::string& file)
  {
    std::string::size_type pos;

    if ((pos = file.rfind('/')) != std::string::npos)
      return file.substr(0, pos);
    else
      return path();
  }

  bool
  file_exists(const std::string& file)
  {
    struct stat buf;

    return 0 == stat(file.c_str(), &buf);
  }
}
