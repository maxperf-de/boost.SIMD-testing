add_executable(
  scalar_sum scalar_sum.cpp
)

target_link_libraries(
  scalar_sum
  ${BENCHMARK_LIBRARY}
  -lrt
  -lpthread
)
