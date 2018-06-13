#include <string>
#include <vector>
#include <utility>

#include "datrie_dictionary.hpp"
#include "IDictionary.hpp"

DatrieDictionary::DatrieDictionary() :
      base_(std::vector<int>(1, 1)),
      check_(std::vector<int>()),
      tail_(std::vector<char>())
{}

bool DatrieDictionary::exists(const std::string& w)
{
  int m;
  int n = 0;
  int t = 0;

  for (int i = 0; i < w.size(); ++i)
  {
    //now search in tail
    if (base_[n] < 0)
    {
      while (i < w.size())
      {
        if (-base_[n] + t >= tail_.size() || tail_[-base_[n] + t] != w[i])
          return false;
        ++i;
        ++t;
      }
      if (tail_[-base_[n] + t] != '#')
        return false;
      return true;
    }

    m = base_[n] + w[i] - 96;
    if (m >= check_.size())
      return false;
    if (check_[m] != n)
      return false;

    n = m;
  }
  return false;
}


