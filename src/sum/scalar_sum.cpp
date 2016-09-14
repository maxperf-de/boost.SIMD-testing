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


int
vectorsum(const std::vector<int> &array)
{
  int sum = 0;
  for (const int &elem: array) {
    sum += elem;
  }

  return sum;
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

BENCHMARK(BM_Vectorsum)->Range(8, 8 << 20);

BENCHMARK_MAIN()
