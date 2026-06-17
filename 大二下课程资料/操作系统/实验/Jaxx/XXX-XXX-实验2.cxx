#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>

// 共享数据结构，生产者&消费者之间传输数据
typedef struct {
    pid_t pid;//写入数据的进程pid
    union {
        int num;
        char ch;
    } value; // 0=整数, 1=字母
    int flag;  //标志 0=整数, 1=字母
} ShareData;

enum { SEM_EMPTY = 0, SEM_FULL = 1, SEM_MUTEX = 2 };//信号量编号 0=空 ，1=满， 2=互斥


// start P/V 操作的宏
struct sembuf P_empty = {SEM_EMPTY, -1, 0};
struct sembuf V_empty = {SEM_EMPTY,  1, 0};
struct sembuf P_full  = {SEM_FULL,  -1, 0};
struct sembuf V_full  = {SEM_FULL,   1, 0};
struct sembuf P_mutex = {SEM_MUTEX, -1, 0};
struct sembuf V_mutex = {SEM_MUTEX,  1, 0};
// end P/V 操作的宏

int main() {

    int sem_id = semget(IPC_PRIVATE, 3, IPC_CREAT | 0666);//创建三个信号量：空，满，互斥
    if (sem_id < 0) { perror("semget"); exit(1); }//判断是否获取失败，如是结束运行
    //start 初始化信号量
    semctl(sem_id, SEM_EMPTY, SETVAL, 1);
    semctl(sem_id, SEM_FULL,  SETVAL, 0);
    semctl(sem_id, SEM_MUTEX, SETVAL, 1);
    //end 初始化信号量

    int shm_id = shmget(IPC_PRIVATE, sizeof(ShareData), IPC_CREAT | 0666);//创建共享内存，大小为一个ShareData的大小
    if (shm_id < 0) { perror("shmget"); exit(1); }//判断是否创建共享内存失败，如是结束运行
    ShareData *shdata = static_cast<ShareData*>(shmat(shm_id, NULL, 0));//将内存地址映射到进程地址空间
    if (shdata == (void*)-1) { perror("shmat"); exit(1); }//判断是否映射失败，如是结束运行

    // start 生产者 a 进程
    if (fork() == 0) {
        for (int i = 0; i < 10000; i++) {//循环10000次
            semop(sem_id, &P_empty, 1);//等待空槽位
            semop(sem_id, &P_mutex, 1);//进入临界区
            shdata->pid = getpid();//写入进程pid
            shdata->value.num = i;//写入value值
            shdata->flag = 0;   //标志类型为整数
            semop(sem_id, &V_mutex, 1);//推出临界区
            semop(sem_id, &V_full, 1);//增加槽位
        }
        _exit(0);//退出子进程
    }
    // end 生产者 a 进程:

    // start 生产者 b进程
    if (fork() == 0) {
        for (char c = 'A'; c <= 'Z'; c++) {
            semop(sem_id, &P_empty, 1);//等待空槽位
            semop(sem_id, &P_mutex, 1);//进入临界区
            shdata->pid = getpid();//写入进程pid
            shdata->value.ch = c;   //写入value值
            shdata->flag = 1;   //标志类型为字元
            semop(sem_id, &V_mutex, 1);//退出临界区
            semop(sem_id, &V_full, 1);//增加槽位
        }
        _exit(0); //退出子进程
    }
    //end 生产者 b进程

    // start消费者 c（写入 a.out）
    if (fork() == 0) {
        FILE *fa = fopen("a.out", "w");// 打开文件用于写入
        if (fa == NULL) {//如果打开失败，报错结束
            perror("fopen a.out");
            exit(1);
        }
        int count = 0;
        while (count < 10000) {
            semop(sem_id, &P_full, 1);//等待满槽位
            semop(sem_id, &P_mutex, 1);//进入临界区
            if (shdata->flag == 0) {// 如果是整数类型，则写入文件
                fprintf(fa, "pid=%d, num=%d\n", shdata->pid, shdata->value.num);
                count++;
                semop(sem_id, &V_mutex, 1);//退出临界区
                semop(sem_id, &V_empty, 1);//增加空槽位
            } else {
                // 非目标类型，释放并重试
                semop(sem_id, &V_mutex, 1);
                semop(sem_id, &V_full, 1);
            }
        }
        fclose(fa);
        _exit(0);
    }
    //end 消费者 c

    // 消费者 d （写入 b.out）
    if (fork() == 0) {

        FILE *fb = fopen("b.out", "w");// 打开文件用于写入
        if (fb == NULL) {//如果打开失败，报错结束
            perror("fopen b.out");
            exit(1);
        }
        int count = 0;
        while (count < 26) {
            semop(sem_id, &P_full, 1);//等待满槽位
            semop(sem_id, &P_mutex, 1);//进入临界区
            if (shdata->flag == 1) {// 如果是char类型，则写入文件
                fprintf(fb, "pid=%d, ch=%c\n", shdata->pid, shdata->value.ch);
                count++;
                semop(sem_id, &V_mutex, 1);//退出临界区
                semop(sem_id, &V_empty, 1);//增加空槽位
            } else {
                // 非目标类型，释放并重试
                semop(sem_id, &V_mutex, 1);
                semop(sem_id, &V_full, 1);
            }
        }
        fclose(fb);
        _exit(0);
    }
    // end 消费者 d

    for (int i = 0; i < 4; i++) wait(NULL);// 父进程等待所有子进程

    //start 解除映射并删除共享内存、信号量
    shmdt(shdata);
    shmctl(shm_id, IPC_RMID, NULL);
    semctl(sem_id, 0, IPC_RMID);
    //end 解除映射并删除共享内存、信号量

    return 0;
}
