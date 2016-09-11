add_executable(
  scalar_sum scalar_sum.cpp
)
add_executable(
  simd_sum simd_sum.cpp
)

target_link_libraries(
  scalar_sum
  ${BENCHMARK_LIBRARY}
  -lrt
  -lpthread
)

target_link_libraries(
  simd_sum
  ${BENCHMARK_LIBRARY}
  -lrt
  -lpthread
)
