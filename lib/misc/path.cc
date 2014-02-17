/**
 ** \file misc/path.cc
 ** \brief path: implements file misc/path.hh
 */

#include <iostream>
#include <misc/contract.hh>
#include <misc/path.hh>

namespace misc
{
  path::path()
    : path("")
  {}

  path::path(std::string p)
  {
    absolute_ = p[0] == '/';

    std::string::size_type pos;
    while ((pos = p.find("/")) != std::string::npos)
      {
        std::string dir = p.substr(0, pos);
        p.erase(0, pos + 1);

        this->append_dir(dir);
      }

    this->append_dir(p);
  }

  path::path(const char* p)
    : path(std::string(p))
  {}

  path&
  path::operator=(const path& rhs)
  {
    absolute_ = rhs.absolute_;
    path_ = rhs.path_;
    return *this;
  }

  path&
  path::operator+=(const path& rhs)
  {
    for (const std::string& dir : rhs.path_)
      this->append_dir(dir);
    return *this;
  }

  path
  path::operator+(const std::string& rhs) const
  {
    path ret = *this;

    return ret += rhs;
  }

  path::operator std::string() const
  {
    std::string path_str;
    for (const std::string& dir : path_)
      {
        path_str += '/';
        path_str += dir;
      }

    // Erase the initial / if needed.
    if (!absolute_)
      path_str.erase(0, 1);

    return path_str;
  }

  bool
  path::operator==(const path& rhs) const
  {
    return path_ == rhs.path_;
  }

  std::ostream&
  path::dump(std::ostream& ostr) const
  {
    ostr << this->operator std::string();
    return ostr;
  }

  void
  path::append_dir(std::string dir)
  {
    precondition(dir.find('/') == std::string::npos);

    if (dir != "" && dir != ".")
      {
        if (dir == "..")
          {
            if (path_.empty() || *path_.rbegin() == "..")
              path_.push_back("..");
            else
              path_.pop_back();
          }
        else
          {
            path_.push_back(dir);
          }
      }
  }

}
