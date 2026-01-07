#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void burn_cpu() {
    // 增加循环次数，让 CPU 多算一会儿，少打一会儿字
    // 这样能减少“抢麦”导致的乱码
    volatile int i;
    for (i = 0; i < 50000000; i++) {} 
}


int main(int argc, char *argv[]) {
    int pid_A, pid_B;

    // 创建子进程 A
    pid_A = fork();
    if (pid_A == 0) {
        settickets(10); // A 只有 10 张票 (穷人)
        while(1) {
            burn_cpu();
            // 打印红色的 A
            printf("\x1b[31mA\x1b[0m"); 
        }
    }

    // 创建子进程 B
    pid_B = fork();
    if (pid_B == 0) {
        settickets(100); // B 有 100 张票 (富人)
        while(1) {
            burn_cpu();
            // 打印绿色的 B
            printf("\x1b[32mB\x1b[0m"); 
        }
    }

    // 父进程等待
    wait(0);
    wait(0);
    exit(0);
}