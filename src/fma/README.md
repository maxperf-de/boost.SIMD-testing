# fma benchmark
Different ways to calculate vector-based r = a + (b * c), which can be accelerated as fused multiply-add.

Code is compiled with different Intel SIMD instruction set support, and performance is validated using the 
Google benchmark framework. Hot/cold cache scenarios are also compared to test memory transfer rate.
