#include "Strings.h"
/*
const CString CStrings::delimiter = "\n";

CStrings CStrings::split(const char * text, CString delimiter)
{
  CStrings strings;
  splitHelper(CString(text), strings.m_items, delimiter);
  return strings;
}

CStrings::CStrings()
{}

CStrings::CStrings(CString string)
{
  splitHelper(string, m_items, delimiter);
}

void CStrings::splitHelper(CString &string, UsedContainer &containerDst, const CString &delimiter)
{
  int prev = 0;
  int delSize = delimiter.size();
  int strSize = string.size();
  int pos = string.find(delimiter, 0);
  if (delSize)
  {
    while (pos >= 0)
    {
      int sz = pos - prev;
      containerDst.push_back(std::move(string.substr(prev, sz)));
      prev = pos + delSize;
      pos = string.find(delimiter, prev);
    }
  }
  if (prev <= strSize)
  {
    containerDst.push_back(std::move(string.substr(prev, strSize - prev)));
  }
}

void CStrings::add(const char * text)
{
  insertHelper(CString(text), m_items, m_items.size());
}

void CStrings::insert(const char * text, int index)
{
  insertHelper(CString(text), m_items, index);
}

CString CStrings::text()
{
  return delimitedText("\n");
}

CString CStrings::delimitedText(CString delimiter)
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
}

void CStrings::text(CString string, CString delimiter /* = "\n" *//*)
{
  m_items.clear();
  splitHelper(string, m_items, delimiter);
}

CSizeBase<int> CStrings::drawingSize()
{
  int width = 0;
  for (UsedContainer::iterator it = m_items.begin(); it != m_items.end(); it++)
  {
    if (width < int(it->size()))
    {
      width = it->size();
    }
  }
  return CSizeBase<int>(width, m_items.size());
}
*/