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
#include <sys/stat.h>
#include <sys/wait.h>

void signal_handler(int sig);
int numprocs;

int main(int argc, char** argv) {
    /* Initialization */
    signal(SIGUSR1, signal_handler);
    numprocs = atoi(argv[1]);
    if(0 > numprocs || numprocs > 32) {
        printf("Invalid argument.  Exiting\n");
        exit(1);
    }
    int ogprocs = numprocs;
    int shmid;
    key_t key;
    int *shm;
    key = 1738;
    umask(0);// Needed for reasons
    mknod("lab3pipe", S_IFIFO | 0666, 0);
    shmid = shmget(key, numprocs * sizeof(int), IPC_CREAT | 0666);
    if(shmid < 0) {
        perror("shmget");
        exit(1);
    }
    shm = shmat(shmid, NULL, 0);
    if(shm == (int*) -1) {
        perror("shmat");
        exit(1);
    }
    memset(shm, 0, numprocs * sizeof(pid_t));
    /* End init */
    if(numprocs == 1) {
        // Special case, skip all the normal stuff.
        printf("ALIVE: Level %d process with pid=%d, child of ppid=%d.\n",
                numprocs, getpid(), getppid());
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
        if(remove("lab3pipe")) perror("remove");
        kill(getpid(), SIGUSR1);
    }
    while(numprocs > 0) {
        if(numprocs == ogprocs) {
            printf("ALIVE: Level %d process with pid=%d, child of ppid=%d.\n",
                    numprocs, getpid(), getppid());
            shm[0] = getpid();
        }
        int fd[2];
        pipe(fd);
        int np = numprocs-1;
        write(fd[WRITE], &np, sizeof(int));
        close(fd[WRITE]);
        if(fork() == 0) {
            read(fd[READ], &numprocs, sizeof(int));
            close(fd[READ]);
            printf("ALIVE: Level %d process with pid=%d, child of ppid=%d.\n",
                    numprocs, getpid(), getppid());
            shm[ogprocs-numprocs] = getpid();
            if(numprocs <= 1) {
                int l3p = open("lab3pipe", O_WRONLY);
                char *buf = "KillMePls";
                write(l3p, buf, 10);
                close(l3p);
                pause();
            }
        }
        else if(numprocs == ogprocs)
            break;
        else
            pause();
    }
    int l3p = open("lab3pipe", O_RDONLY);
    char buf[10];
    read(l3p, buf, 10);
    close(l3p);
    pid_t me = getpid();
    for(int i = 0;i < ogprocs;i++) {
        if(shm[i] != me) {
            kill(shm[i], SIGUSR1);
            wait(NULL); // Wait to kill the n-1th process
            while(i != 1 && kill(shm[i], 0) != -1); // Voodoo magic
        }
    }
    // Cleanup
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    if(remove("lab3pipe")) perror("remove");
    kill(getpid(), SIGUSR1); // Kill self
}

void signal_handler(int sig) {
    printf("EXITING: Level %d process with pid=%d, child of ppid=%d, with signal=%d.\n",
            numprocs, getpid(), getppid(), sig);
    exit(0);
}
