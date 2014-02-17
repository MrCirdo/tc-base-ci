/**
 ** \file parse/tiger-parser.hh
 ** \brief Declaration of parse::TigerParser.
 */

#ifndef PARSE_TIGER_PARSER_HH
# define PARSE_TIGER_PARSER_HH

# include <memory>
# include <map>
# include <stack>
# include <common.hh>
# include <misc/error.hh>
# include <misc/path.hh>
# include <misc/file-library.hh>
# include <parse/parsetiger.hh>
# include <parse/tweast.hh>

// Announce to Bison the lexing function it must use.
// Unfortunately, SWIG 1.3.28 cannot parse this declaration.
#ifndef SWIG
  YY_DECL_ ();
#endif

namespace parse
{

  /// Conduct the scanner and the parser.
  class TigerParser
  {
  public:
    /// The parsed object is either a file, represented by the filename
    /// or a Tweast.
    typedef misc::variant<std::string, Tweast*> input_type;

    TigerParser(const misc::file_library& lib = misc::file_library());

    virtual ~TigerParser();

    friend class parser;
    // SWIG can't parse this declaration either!
#ifndef SWIG
    friend YY_DECL_(::);
#endif

    /// Parse the Tiger file \a name.
    ast_type parse_file(const std::string& name);
    /// Parse the Tweast \a s.  Extensions are enabled.
    ast_type parse(Tweast& s);
    /// Parse the string \a s.  Extensions are automatically disabled.
    ast_type parse(const std::string& s);

    /// Parse a Tiger prelude, return the list of decs.
    ast::DecsList* parse_import(const std::string& name,
                                const location& loc);

    /// Return the error status of the parsing.
    const misc::error& error_get() const;

    /// The default prelude.
    const char* prelude() const;

    /// Set the scanner traces.
    TigerParser& scan_trace(bool b = true);

    /// Set the parser traces.
    TigerParser& parse_trace(bool b = true);


    /// Enable syntax extensions.
    TigerParser& enable_extensions(bool b = true);

  private:
    /// \name Handling the scanner.
    /// \{
    /// The scanner.
    std::unique_ptr<yyFlexLexer> scanner_;

    /// Verbose scanning?
    bool scan_trace_p_;

    /// The list of open files, and the location of their request.
    std::map<std::string, location> open_files_;
    /// \}

    /// \name Running the parse.
    /// \{
    /// Parse a Tiger program, return the AST.
    ast_type parse_();

    /// Parse a Tweast. \a extensions temporarily enable or disable
    /// extensions for the string parsing. This method is used to factor
    /// code between parse (Tweast) and parse (const std::string))
    ast_type parse_input(Tweast& input, bool extensions);

    /// Parse a Tiger prelude \a f, return the list of decs.
    ast::DecsList* parse_prelude(const std::string& f);

  public:
    /// The result of the parse.
    ast_type ast_;
    /// Parsing errors handler.
    misc::error error_;
    /// Verbose parsing?
    bool parse_trace_p_;
    /// \}

    /// The location requesting the import.
    location location_;
    /// The source to parse.
    input_type input_;
    /// The file library for imports.
    misc::file_library library_;
    /// Allow language extensions (reserved identifiers, new keywords)?
    bool enable_extensions_p_;
  };

}

#endif // !PARSE_TIGER_PARSER_HH