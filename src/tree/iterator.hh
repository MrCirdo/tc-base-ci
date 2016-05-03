/**
 ** \file tree/iterator.hh
 ** \brief Intermediate representation: iterator.hh
 **/

#pragma once

#include <list>

#include <tree/tree.hh>

namespace tree
{

  class Iterator
  {
  public:

    Iterator(const rTree& entry);

    void first();

    bool is_ok() const;

    rTree tree_get() const; // 'const' means 'iterator cannot move'

    void next();

  private:

    rTree entry_;
    std::list<rTree> list_;
  };

}

#include <tree/iterator.hxx>
