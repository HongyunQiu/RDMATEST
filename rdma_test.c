#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <infiniband/verbs.h>
#include <rdma/rdma_cma.h>

// 服务器端代码
void server() {
    printf("Hello World from RDMA server!\n");
    // 初始化RDMA设备
    // 创建QP(Queue Pair)
    // 等待客户端连接
    // 执行RDMA操作
    // 清理资源
}

// 客户端代码
void client() {
    printf("Hello World from RDMA client!\n");
    // 初始化RDMA设备
    // 连接到服务器
    // 执行RDMA操作
    // 清理资源
}

int main(int argc, char *argv[]) {
    printf("Hello World from RDMA test program!\n");
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <s|c>\n", argv[0]);
        fprintf(stderr, "  s: run as server\n");
        fprintf(stderr, "  c: run as client\n");
        exit(1);
    }

    if (strcmp(argv[1], "s") == 0) {
        server();
    } else if (strcmp(argv[1], "c") == 0) {
        client();
    } else {
        fprintf(stderr, "Invalid argument. Use 's' for server or 'c' for client.\n");
        exit(1);
    }

    return 0;
}
