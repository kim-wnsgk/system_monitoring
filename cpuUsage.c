#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// CPU 사용량 구조체
typedef struct {
    unsigned long user;
    unsigned long nice;
    unsigned long system;
    unsigned long idle;
    unsigned long iowait;
    unsigned long irq;
    unsigned long softirq;
} CpuUsage;

// CPU 사용량을 파싱하는 함수
void parse_cpu_usage(CpuUsage *usage) {
    FILE *fp = fopen("/proc/stat", "r");
    if (fp == NULL) {
        perror("Failed to open /proc/stat");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), fp);  // 첫 번째 줄에 CPU 데이터가 있음

    sscanf(buffer, "cpu %lu %lu %lu %lu %lu %lu %lu", 
           &usage->user, &usage->nice, &usage->system, 
           &usage->idle, &usage->iowait, &usage->irq, &usage->softirq);

    fclose(fp);
}

// CPU 사용률을 계산하는 함수
double calculate_cpu_usage(CpuUsage *prev, CpuUsage *curr) {
    unsigned long prev_idle = prev->idle + prev->iowait;
    unsigned long curr_idle = curr->idle + curr->iowait;

    unsigned long prev_non_idle = prev->user + prev->nice + prev->system + prev->irq + prev->softirq;
    unsigned long curr_non_idle = curr->user + curr->nice + curr->system + curr->irq + curr->softirq;

    unsigned long prev_total = prev_idle + prev_non_idle;
    unsigned long curr_total = curr_idle + curr_non_idle;

    unsigned long total_diff = curr_total - prev_total;
    unsigned long idle_diff = curr_idle - prev_idle;

    return (double)(total_diff - idle_diff) / total_diff * 100.0;
}

int main() {
    CpuUsage prev_usage = {0}, curr_usage = {0};

    // 초기 CPU 사용량 수집
    parse_cpu_usage(&prev_usage);
    sleep(1);  // 1초 대기 후

    // 현재 CPU 사용량 수집
    parse_cpu_usage(&curr_usage);

    // CPU 사용률 계산
    double cpu_usage = calculate_cpu_usage(&prev_usage, &curr_usage);
    printf("CPU Usage: %.2f%%\n", cpu_usage);

    return 0;
}

