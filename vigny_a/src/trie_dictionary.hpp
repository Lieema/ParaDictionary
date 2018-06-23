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
    TrieDictionary(const std::initializer_list<std::string>& init);
    ~TrieDictionary();
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
      ~Trie();
    
      bool exists(const std::string& w);

      result_t search(const std::string& w);
      void searchRecursive(Trie* node, char letter
		      , const std::string& word, std::vector<int> previous
		      ,result_t& min ,result_t curr);
      void insert(const std::string& w);
      void erase(const std::string& w);

    private:
      int num_children_;
      std::string word_;
      Trie* parent_;
      std::vector<Trie*> children_;
      bool eow_;
  };

  private:
    Trie *root;
};
