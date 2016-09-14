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
#include <boost/simd/memory/allocator.hpp>


typedef std::vector<double, boost::simd::allocator<double>> DoubleVector;


void
multiply_add(const DoubleVector &a, 
	     const DoubleVector &b, 
	     const DoubleVector &c,
	     DoubleVector &res)
{
  constexpr int cardinalDouble = boost::simd::cardinal_of<boost::simd::pack<double>>();
  const size_t arraySize = a.size();

  for (size_t i = 0 ; i < arraySize ; i += cardinalDouble) {
    boost::simd::pack<double>(res.data() + i) = boost::simd::pack<double>(a.data() + i) +
      (boost::simd::pack<double>(b.data() + i) * boost::simd::pack<double>(c.data() + i));
  }
}


static void 
BM_MultiplyAdd(benchmark::State& state) 
{
  DoubleVector a(state.range(0));
  DoubleVector b(state.range(0));
  DoubleVector c(state.range(0));
  DoubleVector res(state.range(0));
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
