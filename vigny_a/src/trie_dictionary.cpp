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


result_t TrieDictionary::Trie::search(const std::string& w)
{
  std::vector<int> currentRow( w.length() + 1);
  std::iota(std::begin(currentRow), std::end(currentRow), 0);
  result_t current_min;
  for (auto node : children_)
  	searchRecursive(node, node.word_.back, w, currentRow, &current_min)
  return current_min;
}


void TrieDictionary::Trie::searchRecursive(Trie node, char letter
	, const std::string& word, std::vector<int> previous, result_t& min)
{
  int columns = word.length() + 1;
  std::vector<int> currentRow(1);
  currentRow.push_back(previous[0] + 1);
  for (int column = 1; column < columns; ++column)) 
  {
     int insertCost = currenRow[column - 1] + 1;
     int deleteCost = previous[column] + 1;
     int replaceCost;
     if (word[column - 1] != letter)
	     replaceCost = previous[column - 1] + 1;
     else
	     replaceCost = previous[column - 1];
     currentRow.push_back(std::min(std::min(inserCost, deleteCost), replaceCost));
  }

  if (currentRow.back < std::get<1>(min))
	  min = std::make_pair(node.word_, currentRow.back);

  for (auto children : node.children_)
	  searchRecursive(children, children.word_.back, word, currentRow, min);
  
}
