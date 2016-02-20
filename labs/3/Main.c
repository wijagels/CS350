#define _GNU_SOURCE
#define WRITE 1
#define READ 0
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/stat.h>

void signal_handler(int sig);
char numprocs;

int main(int argc, char** argv) {
    numprocs = atoi(argv[1]);
    char ogprocs = numprocs;
    int shmid;
    key_t key;
    pid_t *shm;
    key = 1738;
    mknod("lab3pipe", S_IFIFO, 0);
    shmid = shmget(key, numprocs * sizeof(pid_t), IPC_CREAT | 0666);
    if(shmid < 0) {
        perror("shmget");
        exit(1);
    }
    shm = shmat(shmid, NULL, 0);
    if(shm == (pid_t*) -1) {
        perror("shmat");
        exit(1);
    }
    memset(shm, 0, numprocs * sizeof(pid_t));
    shm[0] = getpid();
    numprocs--;
    if(fork() == 0) {
        printf("ALIVE: Level %d process with pid=%d, child of ppid=%d.\n",
                numprocs, getpid(), getppid());
        while(numprocs > 0) {
            int fd[2];
            pipe(fd);
            pid_t pid = fork();
            pid_t me = getpid();
            signal(SIGUSR1, signal_handler);
            if(pid == 0) {
                numprocs--;
                printf("ALIVE: Level %d process with pid=%d, child of ppid=%d.\n",
                        numprocs, getpid(), getppid());
                close(fd[READ]);
                write(fd[WRITE], &me, sizeof(pid_t));
                close(fd[WRITE]);
            }
            else {
                if(numprocs > 0) {
                    shmid = shmget(key, numprocs * sizeof(pid_t), 0666);
                    shm = shmat(shmid, NULL, 0);
                    pid_t k;
                    close(fd[WRITE]);
                    read(fd[READ], &k, sizeof(pid_t));
                    close(fd[READ]);
                    shm[ogprocs - numprocs] = k;
                    if(numprocs == 1) {
                        int l3p = open("lab3pipe", O_WRONLY);
                        char *buf = "hi";
                        write(l3p, buf, 10);
                        close(l3p);
                    }
                }
                pause();
                exit(0);
            }
        }
        pause();
    }
    else {
        //wait(NULL);
        int l3p = open("lab3pipe", O_RDONLY);
        char buf[10];
        int status = read(l3p, buf, 10);
        printf("%d - %s\n", status, buf);
        close(l3p);
        for(int i = 0;i <= numprocs;i++) {
            printf("%d\n", shm[i]);
            if(i)
                kill(shm[i], SIGUSR1);
        }
    }
}

void signal_handler(int sig) {
	//printf("Child reached signal handler: %d, signal: %d\n", getpid(), sig);
    printf("EXITING: Level %d process with pid=%d, child of ppid=%d.\n",
            numprocs, getpid(), getppid());

	exit(0);
}
