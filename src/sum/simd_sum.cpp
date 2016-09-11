#include <stdint.h>

#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <utility>
#include <numeric>

#include "benchmark/benchmark.h"

#if defined(__GNUC__)
# define BENCHMARK_NOINLINE __attribute__((noinline))
#else
# define BENCHMARK_NOINLINE
#endif

#include <boost/simd/pack.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/sum.hpp>

int
vectorsum(std::vector<int> &array)
{
  constexpr int cardinalInteger = boost::simd::cardinal_of<boost::simd::pack<int>>();
  const size_t arraySize = array.size();

  boost::simd::pack<int> sumPack{0};
  for (size_t i = 0 ; i < arraySize ; i += cardinalInteger) {
    sumPack += boost::simd::pack<int>(array.data() + i);
  }

  return boost::simd::sum(sumPack);
}


static void 
BM_Vectorsum(benchmark::State& state) 
{
  int sum = 0;
  std::vector<int> array(state.range(0));
  std::iota(array.begin(), array.end(), 0);

  while (state.KeepRunning()) {
    sum += vectorsum(array);
  }

  // Prevent compiler optimizations
  std::stringstream ss;
  ss << sum;
  state.SetLabel(ss.str());
}

BENCHMARK(BM_Vectorsum)->Range(8, 8 << 10);

BENCHMARK_MAIN()
