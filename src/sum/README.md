# sum benchmark
Different ways to calculate the sum of all elements of a vector: scalaar, and with different boost.SIMD mechanisms.

Code is compiled with different Intel SIMD instruction set support, and performance is validated using the 
Google benchmark framework. Hot/cold cache scenarios are also compared to test memory transfer rate.
