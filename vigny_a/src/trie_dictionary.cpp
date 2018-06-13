#include <string>
#include <vector>
#include <utility>

#include "IDictionary.hpp"
#include "trie_dictionary.hpp"

TrieDictionary::Trie::Trie() :
    key_('\0'), children_(std::vector<Trie>(),
    eow_(false))
{}

TrieDictionary::Trie::Trie(const char& key) :
    key_(key), children_(std::vector<Trie>(),
    eow_(false))
{}

bool TrieDictionary::Trie::exists(const std::string& w)
{
  Trie t = *this;
  for (int i = 0; i < w.size(); ++i)
  {
    for (auto 
  }
}
