/**
 ** \file parse/tiger-parser.cc
 ** \brief Implementation of parse::TigerParser.
 */

#include <cstdlib>
#include <fstream>
#include <parse/tiger-parser.hh>
#include <parse/scantiger.hh>
#include <parse/parsetiger.hh>

namespace parse
{

  // FIXME: Some code was deleted here (Ctor).

  // FIXME: Some code was deleted here (Dtor).

  /// Set the scanner traces.
  TigerParser&
  TigerParser::scan_trace(bool b)
  {
    scan_trace_p_ = b;
    return *this;
  }

  /// Set the parser traces.
  TigerParser&
  TigerParser::parse_trace(bool b)
  {
    parse_trace_p_ = b;
    return *this;
  }

  /// Enable object extensions.
  TigerParser&
  TigerParser::enable_object_extensions(bool b)
  {
    enable_object_extensions_p_ = b;
    return *this;
  }

  /// Enable syntax extensions.
  TigerParser&
  TigerParser::enable_extensions(bool b)
  {
    enable_extensions_p_ = b;
    return *this;
  }

  /// Parse a Tiger file or string.
  ast_type
  TigerParser::parse_()
  {
    std::string* fn = boost::get<std::string>(&input_);

    /* The (address of) the string behind the symbol FILENAME is
       guaranteed to remain valid even after the symbol has been
       destroyed, so we can safely pass `&filename.name_get()' to
       `location_.initialize()'.  As for other symbols, the
       corresponding string will be deallocated at the end of the
       program.  */
    misc::symbol filename(fn == nullptr ? ""
                          : *fn == "-" ? "standard input"
                          : *fn);
    location_.initialize(&filename.name_get());

    std::istream* in;
    if (fn == nullptr)
      // Parse a Tweast.
      in = new std::stringstream(boost::get<Tweast*>(input_)->input_get());
    else if (*fn == "-")
      // Parse from the standard input.
      in = &std::cin;
    else
      {
        // Parse from a file.
        in = new std::ifstream(*fn);
        if (in->fail())
          {
            delete in;
            error_ << misc::error::failure
                   << program_name
                   << ": cannot open `" << filename << "': "
                   << strerror(errno) << std::endl
                   << &misc::error::exit;
          }
      }

  // FIXME: Some code was deleted here (Initialize the scanner and parser, then parse and close).
    ast_type res = ast_;
    ast_ = static_cast <ast::Exp*>(nullptr);

    if (fn == nullptr || *fn != "-")
      delete in;

    return res;
  }

  /*---------------.
  | Parse a file.  |
  `---------------*/

  ast_type
  TigerParser::parse_file(const std::string& name)
  {
    if (parse_trace_p_)
      std::cerr << "Parsing file: " << name << std::endl;
    input_ = name;
    return parse_();
  }

  /*----------------.
  | Parse a Tweast. |
  `----------------*/

  ast_type
  TigerParser::parse_input(Tweast& s, bool extensions)
  {
    std::swap(extensions, enable_extensions_p_);
    // Merge all aggregated Tweasts into a single one.
    s.flatten();
  // FIXME: Some code was deleted here.
  }

  ast_type
  TigerParser::parse(Tweast& s)
  {
    return parse_input(s, true);
  }

  /*-----------------.
  | Parse a string.  |
  `-----------------*/

  ast_type
  TigerParser::parse(const std::string& s)
  {
    Tweast in(s);
    return parse_input(in, false);
  }

  /*-----------------------.
  | Parse a Tiger import.  |
  `-----------------------*/

  ast::DecsList*
  TigerParser::parse_import(const std::string& name, const location& loc)
  {
    // Try to find directory containing the file to import.
    misc::path directory_path = library_.find_file(name);

    if (directory_path.empty())
      {
        error_ << misc::error::failure
               << loc << ": "
               << name << ": file not found." << std::endl;
        return nullptr;
      }

    // Complete path of file (directory + filename).
    misc::path absolute_path = directory_path + misc::basename(name);

    // Detect recursive inclusion.
    if (open_files_.find(absolute_path) != open_files_.end())
      {
        error_ << misc::error::failure
               << loc << ": " << name
               << ": recursive inclusion." << std::endl
               << open_files_[absolute_path]
               << ": initial inclusion was here." << std::endl;
        return nullptr;
      }

    library_.push_current_directory(directory_path);
    open_files_[absolute_path] = loc;
    // Save the inputs, and reset them.
    input_type saved_input = input_;
    location saved_location = location_;
    // Parse the imported file.
    ast::DecsList* res = nullptr;
    try
      {
        res = parse_file(absolute_path);
      }
    catch (boost::bad_get& e)
      {
        error_ << misc::error::parse
               << absolute_path << ": imported from " << loc
               << ": syntax error, unexpected exp, expecting decs."
               << std::endl;
        error_.exit();
      }
    // Set the inputs back to their original values.
    input_ = saved_input;
    location_ = saved_location;

    open_files_.erase(absolute_path);
    library_.pop_current_directory();
    return res;
  }

  const misc::error&
  TigerParser::error_get() const
  {
    return error_;
  }

}
