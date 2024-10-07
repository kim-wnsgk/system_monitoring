#include <stdio.h>
#include <stdlib.h>

int main() {
    // 리눅스 시스템의 경우 /proc/cpuinfo 파일을 읽어 CPU 정보를 가져올 수 있습니다.
    FILE *cpuInfo = fopen("/proc/cpuinfo", "r");
    if (cpuInfo == NULL) {
        printf("Error opening /proc/cpuinfo\n");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), cpuInfo) != NULL) {
        printf("%s", buffer);
    }

    fclose(cpuInfo);
    return 0;
}