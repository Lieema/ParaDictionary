#include <functional>
#include "tools.hpp"
#include "naive_dictionary.hpp"
#include "naive_async_dictionary.hpp"
#include "trie_dictionary.hpp"
#include "async_trie_dictionary.hpp"

#include <benchmark/benchmark.h>

constexpr int NQUERIES = 100;
constexpr int TRIE_NQUERIES = 100;

class BMScenario : public ::benchmark::Fixture
{
public:
  void SetUp(benchmark::State&)
    {
      if (!m_scenario)
      {
        auto wl = load_word_list();
        m_scenario = std::make_unique<Scenario>(wl, NQUERIES);
      }
    }

protected:
  static std::unique_ptr<Scenario> m_scenario;
};

class TrieBMScenario : public ::benchmark::Fixture
{
public:
  void SetUp(benchmark::State&)
    {
      if (!trie_m_scenario)
      {
        auto wl = load_word_list();
        trie_m_scenario = std::make_unique<Scenario>(wl, TRIE_NQUERIES);
      }
    }

protected:
  static std::unique_ptr<Scenario> trie_m_scenario;
};

std::unique_ptr<Scenario> BMScenario::m_scenario;
std::unique_ptr<Scenario> TrieBMScenario::trie_m_scenario;



BENCHMARK_DEFINE_F(BMScenario, Naive_NoAsync)(benchmark::State& st)
{
  naive_dictionary dic;
  m_scenario->prepare(dic);

  for (auto _ : st)
    m_scenario->execute(dic);

  st.SetItemsProcessed(st.iterations() * NQUERIES);
}

BENCHMARK_DEFINE_F(BMScenario, Naive_Async)(benchmark::State& st)
{
  naive_async_dictionary dic;
  m_scenario->prepare(dic);

  for (auto _ : st)
    m_scenario->execute(dic);

  st.SetItemsProcessed(st.iterations() * NQUERIES);
}

BENCHMARK_DEFINE_F(TrieBMScenario, Trie_NoAsync)(benchmark::State& st)
{
  TrieDictionary dic;
  trie_m_scenario->prepare(dic);

  for (auto _ : st)
    trie_m_scenario->execute(dic);

  st.SetItemsProcessed(st.iterations() * TRIE_NQUERIES);
}

BENCHMARK_DEFINE_F(TrieBMScenario, Trie_Async)(benchmark::State& st)
{
  AsyncTrieDictionary dic;
  trie_m_scenario->prepare(dic);

  for (auto _ : st)
    trie_m_scenario->execute(dic);

  st.SetItemsProcessed(st.iterations() * TRIE_NQUERIES);
}

BENCHMARK_REGISTER_F(BMScenario, Naive_NoAsync)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(BMScenario, Naive_Async)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(TrieBMScenario, Trie_NoAsync)->Unit(benchmark::kMillisecond);
BENCHMARK_REGISTER_F(TrieBMScenario, Trie_Async)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();
