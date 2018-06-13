#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include "datrie_dictionary.hpp"
#include "IDictionary.hpp"

/*
 * m represents the value of index at base_ added to character value
 * and the index we're gonna look in check_
 *
 * n represents the index of base_ we're looking at
 *
 * t represents the index of tail_
 */

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

  //loop for each character of w
  for (int i = 0; i < w.size(); ++i)
  {
    //now search in tail
    if (base_[n] < 0)
    {
      //checks that each charcter of tail corresponds to w
      while (i < w.size())
      {
        if (-base_[n] + t >= tail_.size() || tail_[-base_[n] + t] != w[i])
          return false;
        ++i;
        ++t;
      }
      //check that the part in tail has size of w
      if (tail_[-base_[n] + t] != '#')
        return false;
      return true;
    }

    m = base_[n] + w[i] - 96;
    if (m >= check_.size() || check_[m] != n)
      return false;

    n = m;
  }
  return false;
}

void DatrieDictionary::insert(const std::string& w)
{
  int m;
  int n = 0;
  int t = 0;

  for (int i = 0; i < w.size(); ++i)
  {
    m = base_[n] + w[i] - 96;
    //case where double-array is empty or without collisions
    if (m >= check_.size() || check_[m] == 0)
    {
      //resize if needed
      if (m >= base_.size())
        base_.resize(m, 0);
      base_[m] = -tail_.size();

      //insert rest of the word into tail
      ++i;
      while (i < w.size())
      {
        tail_.push_back(w[i]);
        ++i;
      }

      //insert the delimiter (EOW)
      tail_.push_back('#');
      return;
    }
    n = m;
  }
}

int main()
{
  DatrieDictionary dt = DatrieDictionary();
  dt.insert("bachelor");
  std::cout << dt.exists("bachelor");
  return 0;
}
