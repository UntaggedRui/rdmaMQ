aux_source_directory(. DIR_RDMA_MQ)
add_library(rdmaMQ STATIC ${DIR_RDMA_MQ})
target_link_libraries(rdmaMQ  pthread ibverbs)