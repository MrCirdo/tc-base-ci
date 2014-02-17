/**
 ** \file misc/path.hh
 ** \brief path: represents an absolute path in the filesystem
 */

#ifndef MISC_PATH_HH
# define MISC_PATH_HH

# include <string>
# include <list>

namespace misc
{
  /** \brief Helper for handling paths
   **/
  class path
  {
  public:
    /// \name Constructors.
    /// \{

    path();

    /// Init object with \a p.
    path(std::string p);

    /// Init object with \a p.
    /// Useful when passing char[], e.g., when using literal C strings.
    path(const char* p);

    /// \}

    /// \name Operations on path.
    /// \{
#ifdef SWIG
    %rename(assign) operator=(const path& rhs);
#endif
    path& operator=(const path& rhs);
    path& operator+=(const path& rhs);
    path operator+(const std::string& rhs) const;
    bool operator==(const path& rhs) const;

    /// \}

    /// \name Printing and converting.
    /// \{
#ifdef SWIG
    %rename(__str__) operator std::string() const;
#endif
    operator std::string() const;
    std::ostream& dump(std::ostream& ostr) const;

    /// \}

    /// Whether is an absolute path.
    bool absolute_get() const;
    /// Whether is empty.
    bool empty() const;

  private:
    /// path is represented with a list of directories.
    typedef std::list<std::string> path_type;

    /// Append a single directory \a dir.
    void append_dir(std::string dir);

    /// Init object with path \a p.
    void init(std::string p);

    /// Represented path.
    path_type path_;

    /// "absolute" flag.
    bool absolute_;
  };

  std::ostream&
  operator<<(std::ostream& ostr, const path& p);
}

# include <misc/path.hxx>

#endif // !MISC_PATH_HH
