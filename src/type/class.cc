/**
 ** \file type/class.cc
 ** \brief Implementation for type/class.hh.
 */

#include <iostream>
#include <ostream>

#include <misc/indent.hh>
#include <type/class.hh>

namespace type
{
  Class::Class (const Class* super)
    : Type ()
    , id_ (fresh_id ())
    , super_ (super)
    , subclasses_ ()
  {}


  const Type*
  Class::attr_type(const misc::symbol& key) const
  {
  // FIXME: Some code was deleted here.
  }

  const Method*
  Class::meth_type(const misc::symbol& key) const
  {
  // FIXME: Some code was deleted here.
  }

  // FIXME: Some code was deleted here (Find common super class).

  // FIXME: Some code was deleted here (Super class soundness test).

  // FIXME: Some code was deleted here (Print).

  // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Class).

  const Class&
  Class::object_instance()
  {
  // FIXME: Some code was deleted here.
  }

  unsigned Class::fresh_id()
  {
  // FIXME: Some code was deleted here.
  }

} // namespace type
