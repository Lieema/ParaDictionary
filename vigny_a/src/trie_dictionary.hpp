#pragma once

#include <string>
#include <vector>
#include <utility>

#include "IDictionary.hpp"

//Trie implementation
class TrieDictionary : public IDictionary
{
  public:
    TrieDictionary();
    //returns true if w is in the dictionary
    bool exists(const std::string& w);

    void init(const std::vector<std::string>& word_list);

    result_t search(const std::string& w) const;
    void insert(const std::string& w);
    void erase(const std::string& w);

    //Trie class implementation
  class Trie
  {
    public:
      Trie();
      Trie(const char& key);
      ~Trie();
    
      bool exists(const std::string& w);

      result_t search(const std::string& w);
      void insert(const std::string& w);
      void erase(const std::string& w);

    private:
      int num_children_;
      const std::string& word_;
      Trie* parent_;
      std::vector<*Trie> children_;
      bool eow_;
  };

  private:
    Trie *root;
};
