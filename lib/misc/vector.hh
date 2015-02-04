/**
 ** \file vector/vector.hh
 ** \brief Declaration of utils for vector
 */

#ifndef VECTOR_VECTOR_HH
# define VECTOR_VECTOR_HH

# include <iosfwd>
# include <vector>

namespace misc
{

  template<typename T>
  void back_append_and_move(std::vector<T>& res,
                            std::vector<T>&& to_append)
  {
    res.insert(res.end(),
               make_move_iterator(to_append.begin()),
               make_move_iterator(to_append.end()));
    to_append.clear();
  }

  template<typename T>
  void back_append_and_move(std::vector<T>& res,
                            std::vector<T>& to_append)
  {
    res.insert(res.end(),
               make_move_iterator(to_append.begin()),
               make_move_iterator(to_append.end()));
    to_append.clear();
  }

  template<typename T>
  void front_append_and_move(std::vector<T>& res,
                             std::vector<T>&& to_append)
  {
    res.insert(res.begin(),
               make_move_iterator(to_append.begin()),
               make_move_iterator(to_append.end()));
    to_append.clear();
  }

  template<typename T>
  void front_append_and_move(std::vector<T>& res,
                             std::vector<T>& to_append)
  {
    res.insert(res.begin(),
               make_move_iterator(to_append.begin()),
               make_move_iterator(to_append.end()));
    to_append.clear();
  }

  template<typename T, typename Iterator>
  void position_append_and_move(std::vector<T>& res,
                                Iterator res_iterator,
                                std::vector<T>&& to_append)
  {
    res.insert(res_iterator,
               make_move_iterator(to_append.begin()),
               make_move_iterator(to_append.end()));
    to_append.clear();
  }

  template<typename T, typename Iterator>
  void position_append_and_move(std::vector<T>& res,
                                Iterator res_iterator,
                                std::vector<T>& to_append)
  {
    res.insert(res_iterator,
               make_move_iterator(to_append.begin()),
               make_move_iterator(to_append.end()));
    to_append.clear();
  }
  
} // namespace vector

#endif // !VECTOR_VECTOR_HH
