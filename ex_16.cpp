
#include <iostream>

// thx to Georg Fritzsche
// http://stackoverflow.com/questions/2978259/programmatically-create-static-arrays-at-compile-time-in-c
template <unsigned... args>
struct ArrayHolder
{
  static const unsigned char data[sizeof...(args)];
};

template <unsigned... args>
const unsigned char ArrayHolder<args...>::data[sizeof...(args)] = { args... };

template <size_t N, template<size_t> class F, unsigned... args>
struct generate_array_impl
{
  typedef typename generate_array_impl<N - 1, F, F<N>::value, args...>::result result;
};

template<template<size_t> class F, unsigned... args>
struct generate_array_impl<0, F, args...>
{
  typedef ArrayHolder<F<0>::value, args...> result;
};

template <size_t N, template<size_t> class F>
struct generate_array
{
  typedef typename generate_array_impl<N - 1, F>::result result;
};

template <size_t index>
struct MetaFunc
{
  enum { value = (('a' <= index && index <= 'z') ? -(index - 'z') + 'a'
		  : ('A' <= index && index <= 'Z') ? -(index - 'Z') + 'A' 
		  : index ) };
};

int main(int argc, char *argv[])
{
  const size_t count = 256;
  typedef generate_array<count, MetaFunc>::result A;

  if (*++argv)
    {
      const char *str(*argv);
      while (*str)
	std::cout << static_cast<char>(A::data[*str++]);
      std::cout << std::endl;
    }
}
