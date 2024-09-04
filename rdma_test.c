#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <infiniband/verbs.h>
#include <rdma/rdma_cma.h>
#include <arpa/inet.h>

#define MAX_BUFFER_SIZE 1024

struct rdma_context {
    struct ibv_context *ctx;
    struct ibv_pd *pd;
    struct ibv_cq *cq;
    struct ibv_qp *qp;
    struct ibv_mr *mr;
    char *buffer;
};

static void die(const char *reason)
{
    fprintf(stderr, "Error: %s\n", reason);
    exit(EXIT_FAILURE);
}

static void init_rdma_context(struct rdma_context *ctx)
{
    printf("DEBUG: Entering init_rdma_context\n");

    // 获取设备列表
    int num_devices;
    struct ibv_device **dev_list = ibv_get_device_list(&num_devices);
    if (!dev_list) {
        die("Failed to get IB devices list");
    }
    printf("DEBUG: Found %d IB devices\n", num_devices);

    if (num_devices == 0) {
        die("No IB devices found");
    }

    // 使用第一个设备
    ctx->ctx = ibv_open_device(dev_list[0]);
    if (!ctx->ctx) {
        die("Failed to open IB device");
    }
    printf("DEBUG: Opened IB device successfully\n");

    // 分配保护域
    ctx->pd = ibv_alloc_pd(ctx->ctx);
    if (!ctx->pd) {
        die("Failed to allocate PD");
    }
    printf("DEBUG: Allocated protection domain successfully\n");

    // 创建完成队列
    ctx->cq = ibv_create_cq(ctx->ctx, 10, NULL, NULL, 0);
    if (!ctx->cq) {
        die("Failed to create CQ");
    }
    printf("DEBUG: Created completion queue successfully\n");

    // 分配缓冲区
    ctx->buffer = malloc(MAX_BUFFER_SIZE);
    if (!ctx->buffer) {
        die("Failed to allocate buffer");
    }
    printf("DEBUG: Allocated buffer successfully\n");

    // 注册内存区域
    ctx->mr = ibv_reg_mr(ctx->pd, ctx->buffer, MAX_BUFFER_SIZE, IBV_ACCESS_LOCAL_WRITE | IBV_ACCESS_REMOTE_WRITE);
    if (!ctx->mr) {
        die("Failed to register MR");
    }
    printf("DEBUG: Registered memory region successfully\n");

    ibv_free_device_list(dev_list);
    printf("DEBUG: RDMA context initialization complete\n");
}

static void cleanup_rdma_context(struct rdma_context *ctx)
{
    printf("DEBUG: Entering cleanup_rdma_context\n");
    if (ctx->mr) {
        ibv_dereg_mr(ctx->mr);
        printf("DEBUG: Deregistered memory region\n");
    }
    if (ctx->buffer) {
        free(ctx->buffer);
        printf("DEBUG: Freed buffer\n");
    }
    if (ctx->qp) {
        ibv_destroy_qp(ctx->qp);
        printf("DEBUG: Destroyed queue pair\n");
    }
    if (ctx->cq) {
        ibv_destroy_cq(ctx->cq);
        printf("DEBUG: Destroyed completion queue\n");
    }
    if (ctx->pd) {
        ibv_dealloc_pd(ctx->pd);
        printf("DEBUG: Deallocated protection domain\n");
    }
    if (ctx->ctx) {
        ibv_close_device(ctx->ctx);
        printf("DEBUG: Closed IB device\n");
    }
    printf("DEBUG: RDMA context cleanup complete\n");
}

// 服务器端代码
void server(const char *port)
{
    printf("DEBUG: Starting RDMA server on port %s\n", port);
    struct rdma_context ctx = {};
    init_rdma_context(&ctx);

    // 这里添加服务器特定的RDMA连接和通信代码
    printf("DEBUG: Server is ready. Waiting for client connection...\n");
    // 模拟等待连接
    sleep(10);

    cleanup_rdma_context(&ctx);
    printf("DEBUG: Server shutting down\n");
}

// 客户端代码
void client(const char *server_ip, const char *port)
{
    printf("DEBUG: Connecting to RDMA server at %s:%s\n", server_ip, port);
    struct rdma_context ctx = {};
    init_rdma_context(&ctx);

    // 这里添加客户端特定的RDMA连接和通信代码
    printf("DEBUG: Client is ready. Attempting to connect to server...\n");
    // 模拟连接过程
    sleep(5);

    cleanup_rdma_context(&ctx);
    printf("DEBUG: Client shutting down\n");
}

int main(int argc, char *argv[])
{
    printf("DEBUG: Program started with %d arguments\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("DEBUG: argv[%d] = %s\n", i, argv[i]);
    }

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <s|c> <port> [server_ip]\n", argv[0]);
        fprintf(stderr, "  s: run as server\n");
        fprintf(stderr, "  c: run as client\n");
        exit(1);
    }

    if (strcmp(argv[1], "s") == 0) {
        server(argv[2]);
    } else if (strcmp(argv[1], "c") == 0) {
        if (argc != 4) {
            fprintf(stderr, "Client mode requires server IP address\n");
            exit(1);
        }
        client(argv[3], argv[2]);
    } else {
        fprintf(stderr, "Invalid mode. Use 's' for server or 'c' for client.\n");
        exit(1);
    }

    printf("DEBUG: Program exiting normally\n");
    return 0;
}
