add_executable(
  scalar_fma scalar_fma.cpp
)
add_executable(
  simd_fma simd_fma.cpp
)

target_link_libraries(
  scalar_fma
  ${BENCHMARK_LIBRARY}
  -lrt
  -lpthread
)

target_link_libraries(
  simd_fma
  ${BENCHMARK_LIBRARY}
  -lrt
  -lpthread
)
