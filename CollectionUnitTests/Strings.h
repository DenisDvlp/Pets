#pragma once
#include <string>
#include "SizeBase.h"
#include "Container.h"

typedef std::string CString;

template<typename T>
class CSizeBase;
/*
class CStrings: public List<CString>
{
public:

  static const CString delimiter;
  template<typename Container>
  static CStrings split(Container container, CString delimiter);
  static CStrings split(const char * text, CString delimiter);

  CStrings();
  CStrings(CString string);

  using List<CString>::add;
  using List<CString>::insert;
  void    add   (const char * text);
  void    insert(const char * text, int index);

  CString text();
  CString delimitedText(CString delimiter);
  void    text(CString string, CString delimiter = "\n");
  CSizeBase<int> drawingSize();

protected:

  template<typename Container>
  static void splitHelper(Container &container, UsedContainer &containerDst, const CString &delimiter);
  static void splitHelper(CString &string, UsedContainer &containerDst, const CString &delimiter);
  template<typename Container>
  static void delimitedTextHelper(Container &container, CString &delimiter);

};

////////////////impementation////////////////

template<typename Container>
inline CStrings CStrings::split(Container container, CString delimiter)
{
  CStrings strings;
  splitHelper(container, strings.m_items, delimiter);
  return strings;
}

template<typename Container>
void CStrings::splitHelper(Container &container, UsedContainer &containerDst, const CString &delimiter)
{
  for (Container::iterator it = container.begin(); it != container.end(); it++)
  {
    splitHelper(*it, containerDest, delimiter);
  }
}

template<typename Container>
void CStrings::delimitedTextHelper(Container & container, CString & delimiter)
{
  CString string;
  if (size())
  {
    for (UsedContainer::iterator it = m_items.begin(); it != m_items.end(); it++)
    {
      string.append(*it).append(delimiter);
    }
    string = string.substr(0, string.size() - delimiter.size());
  }
  return string;
}*/
