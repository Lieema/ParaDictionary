#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>
#include <queue>
#include <numeric>
#include <climits>

#include "IDictionary.hpp"
#include "trie_dictionary.hpp"
#include "tools.hpp"

TrieDictionary::Trie::Trie() :
    word_(""),
    parent_(nullptr),
    children_(std::vector<TrieDictionary::Trie*>(26, nullptr)),
    num_children_(std::vector<char>()),
    eow_(false)
{}

TrieDictionary::Trie::~Trie()
{}

bool TrieDictionary::Trie::exists(const std::string& w)
{
  TrieDictionary::Trie* t = this;

  for (size_t i = 0; i < w.size(); ++i)
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

  for (size_t i = 0; i < w.size(); ++i)
  {
    word.push_back(w[i]);
    if (t->children_[w[i] - 97] == nullptr)
    {
      t->children_[w[i] - 97] = new TrieDictionary::Trie();
      t->num_children_.push_back(w[i]);
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
  char c = ' ';

  for (size_t i = 0; i < w.size(); ++i)
  {
    if (t->children_[w[i] - 97] == nullptr)
      return;
    t = t->children_[w[i] - 97];
  }

  t->eow_ = false;

  if (t->num_children_.size() == 0)
  {
    while (!t->eow_ && t->parent_ != nullptr && t->num_children_.size() == 0)
    {
      last_word = t->parent_;
      c = t->word_.back();
      delete t;
      t = last_word;
      t->num_children_.erase(std::remove(t->num_children_.begin(),
            t->num_children_.end(), c), t->num_children_.end());
    }
    t->children_[c - 97] = nullptr;
  }
}


void TrieDictionary::Trie::searchRecursive(Trie* node, char letter
	, const std::string& word, std::vector<int> previous
	, result_t& min, result_t curr)
{ 
  int columns = word.length() + 1;
  std::vector<int> currentRow(0);
  currentRow.push_back(previous[0] + 1);
  int insertCost = 0;
  int deleteCost = 0;
  int replaceCost = 0;
  for (int column = 1; column < columns; ++column)
  {
     insertCost = currentRow[column - 1] + 1;
     deleteCost = previous[column] + 1;
     if (word[column - 1] != letter)
	     replaceCost = previous[column - 1] + 1;
     else
	     replaceCost = previous[column - 1];
     currentRow.push_back(std::min(std::min(insertCost, deleteCost), replaceCost));  
  }
  curr = std::make_pair(node->word_ , currentRow.back());
  if (curr.second < min.second && node->eow_)
	  min = curr;
  if (*std::min_element(currentRow.begin(), currentRow.end()) < min.second)
    for (auto c : node->num_children_)
	    searchRecursive(node->children_[c - 97],
          node->children_[c - 97]->word_.back(), word, currentRow, min, curr);
}


result_t TrieDictionary::Trie::search(const std::string& w)
{
  std::vector<int> currentRow( w.length() + 1);
  std::iota(std::begin(currentRow), std::end(currentRow), 0);
  result_t current_min = std::make_pair(w, INT_MAX);
  result_t curr = std::make_pair(w, 0);
  if (exists(w))
	  return std::make_pair(w, 0);
  for (auto c : this->num_children_)
    searchRecursive(children_[c - 97],
        children_[c - 97]->word_.back(), w, currentRow, current_min, curr);
  return current_min;
}

TrieDictionary::TrieDictionary() :
  root(new Trie())
{}

TrieDictionary::TrieDictionary(const std::initializer_list<std::string>& init) :
  root(new Trie())
{
  this->init(init);
}

TrieDictionary::~TrieDictionary()
{
  delete root;
}

bool TrieDictionary::exists(const std::string& w)
{
  return root->exists(w);
}

void TrieDictionary::init(const std::vector<std::string>& word_list)
{
  for (auto w : word_list)
    root->insert(w);
}

result_t TrieDictionary::search(const std::string& w) const
{
  return root->search(w);
}

void TrieDictionary::insert(const std::string& w)
{
  root->insert(w);
}

void TrieDictionary::erase(const std::string& w)
{
  root->erase(w);
}
