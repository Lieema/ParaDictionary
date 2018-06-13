#pragma once

#include <string>
#include <vector>
#include <utility>

#include "IDictionary.hpp"

//Double array trie implementation
//characters are a = 1, b = 2, ..., z = 26 and # = 0
//# is a separator used in the tail
class DatrieDictionary : public IDictionary
{
  public:
    DatrieDictionary();
    //Returns true if w is in the dictionary
    bool exists(const std::string& w);

    void init(const std::vector<std::string>& word_list);

    result_t search(const std::string& w) const;
    void insert(const std::string& w);
    void erase(const std::string& w);

  private:
    std::vector<int> base_;
    std::vector<int> check_;
    std::vector<char> tail_;
};
