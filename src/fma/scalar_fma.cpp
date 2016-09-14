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


void
multiply_add(const std::vector<double> &a, 
	     const std::vector<double> &b, 
	     const std::vector<double> &c,
	     std::vector<double> &res)
{
  const size_t length = a.size();
  for (size_t i = 0; i < length; ++i) {
    res[i] = a[i] + (b[i] * c[i]);
  }
}


static void 
BM_MultiplyAdd(benchmark::State& state) 
{
  std::vector<double> a(state.range(0));
  std::vector<double> b(state.range(0));
  std::vector<double> c(state.range(0));
  std::vector<double> res(state.range(0));
  std::iota(a.begin(), a.end(), 0);
  std::iota(b.begin(), b.end(), 0);
  std::iota(c.begin(), c.end(), 0);
  res.reserve(a.size());

  while (state.KeepRunning()) {
    multiply_add(a, b, c, res);
  }

  // Prevent compiler optimizations
  std::stringstream ss;
  ss << res[0];
  state.SetLabel(ss.str());
}

BENCHMARK(BM_MultiplyAdd)->Range(8, 8 << 20);

BENCHMARK_MAIN()
