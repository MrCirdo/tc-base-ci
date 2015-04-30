/**
 ** \file tree/fragment.hxx
 ** \brief Inline methods for tree/fragment.hh.
 **/

#ifndef TREE_FRAGMENT_HXX
# define TREE_FRAGMENT_HXX

# include <temp/temp.hh>
# include <tree/fwd.hh>
# include <tree/fragment.hh>
# include <temp/label.hh>

namespace tree
{

  inline std::ostream&
  operator<<(std::ostream& o, const Fragment& f)
  {
    return f.dump(o);
  }


  /*--------------------.
  | DataFrag: strings.  |
  `--------------------*/

  inline
  DataFrag::DataFrag(const temp::Label& label, const std::string& data)
    : label_(label)
    , data_(data)
  {}

  inline temp::Label
  DataFrag::label_get() const
  {
    return label_;
  }

  inline const std::string&
  DataFrag::data_get() const
  {
    return data_;
  }


  /*-----------------------.
  | ProcFrag: procedures.  |
  `-----------------------*/

  inline
  ProcFrag::ProcFrag(const temp::Label& label,
                     const misc::symbol& name,
                     const rStm& body,
                     const frame::Frame* frame)
    : label_(label)
    , name_(name)
    , body_(body)
    , frame_(frame)
    , save_fp_(temp::Temp())
  {}

  inline
  ProcFrag::~ProcFrag()
  {
    delete frame_;
  }


  inline temp::Label
  ProcFrag::label_get() const
  {
    return label_;
  }

  inline const misc::symbol&
  ProcFrag::name_get() const
  {
    return name_;
  }

  inline rStm
  ProcFrag::body_get() const
  {
    return body_;
  }

  inline void
  ProcFrag::body_set(const rStm& body)
  {
    body_ = body;
  }

  inline const frame::Frame&
  ProcFrag::frame_get() const
  {
    return *frame_;
  }


} /* namespace tree */

#endif // !TREE_FRAGMENT_HXX
