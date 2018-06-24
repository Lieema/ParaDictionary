#include <future>
#include <mutex>

#include "async_trie_dictionary.hpp"

AsyncTrieDictionary::AsyncTrieDictionary() :
  trie_(TrieDictionary()),
  is_search(false)
{}

void AsyncTrieDictionary::init(const std::vector<std::string>& word_list)
{
  trie_.init(word_list);
}

std::future<result_t> AsyncTrieDictionary::search(const std::string& w) const
{
  if (!is_search)
  {
    is_search = true;
    mutex_.lock();
  }

  std::promise<result_t> p;
  p.set_value(trie_.search(w));
  return p.get_future();
}

std::future<void> AsyncTrieDictionary::insert(const std::string& w)
{
  if (is_search)
    mutex_.unlock();

  std::lock_guard l(mutex_);

  is_search = false;

  std::promise<void> p;
  trie_.insert(w);
  p.set_value();
  return p.get_future();
}

std::future<void> AsyncTrieDictionary::erase(const std::string& w)
{
  if (is_search)
    mutex_.unlock();

  std::lock_guard l(mutex_);

  is_search = false;

  std::promise<void> p;
  trie_.erase(w);
  p.set_value();
  return p.get_future();
}
