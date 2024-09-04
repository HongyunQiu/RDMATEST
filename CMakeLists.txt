cmake_minimum_required(VERSION 3.10)
project(rdma_test C)

set(CMAKE_C_STANDARD 11)

# 添加额外的库查找路径
list(APPEND CMAKE_PREFIX_PATH "/usr/lib" "/usr/local/lib")

# 查找必要的库
find_library(IBVERBS_LIB ibverbs)
find_library(RDMACM_LIB rdmacm)

# 如果找不到库，给出错误信息
if(NOT IBVERBS_LIB)
    message(FATAL_ERROR "ibverbs library not found. Please install libibverbs-dev.")
endif()

if(NOT RDMACM_LIB)
    message(FATAL_ERROR "rdmacm library not found. Please install librdmacm-dev.")
endif()

# 添加可执行文件
add_executable(rdma_test rdma_test.c)

# 链接库
target_link_libraries(rdma_test ${IBVERBS_LIB} ${RDMACM_LIB})

# 添加包含目录
target_include_directories(rdma_test PRIVATE /usr/include/infiniband)

# 设置编译选项
target_compile_options(rdma_test PRIVATE -Wall -Wextra -pedantic)

# 安装目标
install(TARGETS rdma_test DESTINATION bin)
