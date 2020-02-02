//String.h
#pragma once
#include "Vector.h"

class String
  : public Vector<char>
{
public:
  using Vector<char>::Vector;
  String(const char*);

  using Vector<char>::operator=;
  String& operator=(const char*);

  using Vector<char>::operator+=;
  String& operator+=(const char*);

  using Vector<char>::operator+;
  String operator+(const char*);

  using Vector<char>::operator==;
  bool operator==(const char*);

  using Vector<char>::operator!=;
  bool operator!=(const char*);

  using Vector<char>::add;
  void add(const char*);

  using Vector<char>::insert;
  void insert(size_t, const char*);

  using Vector<char>::remove;
  void remove(const char*);

  using Vector<char>::find;
  size_t find(const char*);

  using Vector<char>::findAll;
  Vector<size_t> findAll(const char*);

  using Vector<char>::replace;
  void replace(const char*, const char*);
  void replace(const char*, const std::string&);
  void replace(const std::string&, const char*);
};