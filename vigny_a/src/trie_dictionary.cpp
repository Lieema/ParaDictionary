#include <string>
#include <vector>
#include <utility>
#include <iostream>

#include "IDictionary.hpp"
#include "trie_dictionary.hpp"

TrieDictionary::Trie::Trie() :
    num_children_(0),
    word_(""),
    parent_(nullptr),
    children_(std::vector<TrieDictionary::Trie*>(26, nullptr)),
    eow_(false)
{}

TrieDictionary::Trie::~Trie()
{}

bool TrieDictionary::Trie::exists(const std::string& w)
{
  TrieDictionary::Trie* t = this;

  for (int i = 0; i < w.size(); ++i)
  {
    if (t->children_[w[i] - 97] == nullptr)
      return false;
    t = t->children_[w[i] - 97];
  }
  return t->eow_;
}

void TrieDictionary::Trie::insert(const std::string& w)
{
  TrieDictionary::Trie* t = this;
  std::string word = "";

  for (int i = 0; i < w.size(); ++i)
  {
    word.push_back(w[i]);
    if (t->children_[w[i] - 97] == nullptr)
    {
      t->children_[w[i] - 97] = new TrieDictionary::Trie();
      t->num_children_ += 1;
      t->children_[w[i] - 97]->word_ = word;
      t->children_[w[i] - 97]->parent_ = t;
    }
    t = t->children_[w[i] - 97];
  }
  t->eow_ = true;
}

void TrieDictionary::Trie::erase(const std::string& w)
{
  TrieDictionary::Trie* t = this;
  TrieDictionary::Trie* last_word = nullptr;
  char c;

  for (int i = 0; i < w.size(); ++i)
  {
    if (t->children_[w[i] - 97] == nullptr)
      return;
    t = t->children_[w[i] - 97];
  }

  t->eow_ = false;

  if (t->num_children_ == 0)
  {
    while (!t->eow_ && t->parent_ != nullptr)
    {
      std::cout << t->word_ << std::endl;
      last_word = t->parent_;
      delete t;
      t = last_word;
      c = t->word_.back();
    }
    t->num_children_ -= 1;
    t->children_[c - 97] = nullptr;
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
