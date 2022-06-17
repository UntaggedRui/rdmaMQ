add_executable(latency "${CMAKE_CURRENT_SOURCE_DIR}/latency/main.cc")
add_executable(throughput "${CMAKE_CURRENT_SOURCE_DIR}/throughput/main.cc")
target_link_libraries(latency rdmaMQ)
target_link_libraries(throughput rdmaMQ)