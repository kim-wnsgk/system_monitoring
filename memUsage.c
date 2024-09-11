#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned long total;
    unsigned long free;
    unsigned long available;
    unsigned long buffers;
    unsigned long cached;
} MemoryUsage;

// 메모리 사용량을 파싱하는 함수
void parse_memory_usage(MemoryUsage *mem_usage) {
    FILE *fp = fopen("/proc/meminfo", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/meminfo");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strncmp(buffer, "MemTotal:", 9) == 0) {
            sscanf(buffer + 9, "%lu", &mem_usage->total);
        } else if (strncmp(buffer, "MemFree:", 8) == 0) {
            sscanf(buffer + 8, "%lu", &mem_usage->free);
        } else if (strncmp(buffer, "MemAvailable:", 13) == 0) {
            sscanf(buffer + 13, "%lu", &mem_usage->available);
        } else if (strncmp(buffer, "Buffers:", 8) == 0) {
            sscanf(buffer + 8, "%lu", &mem_usage->buffers);
        } else if (strncmp(buffer, "Cached:", 7) == 0) {
            sscanf(buffer + 7, "%lu", &mem_usage->cached);
        }
    }

    fclose(fp);
}

int main() {
    MemoryUsage mem_usage = {0};

    // 메모리 사용량 수집
    parse_memory_usage(&mem_usage);

    // 메모리 사용 정보 출력
    printf("Total Memory: %lu KB\n", mem_usage.total);
    printf("Free Memory: %lu KB\n", mem_usage.free);
    printf("Available Memory: %lu KB\n", mem_usage.available);
    printf("Buffers: %lu KB\n", mem_usage.buffers);
    printf("Cached: %lu KB\n", mem_usage.cached);

    return 0;
}

