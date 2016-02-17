#include "Main.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
    const char* usage = "%s [-u] [-N <num-levels>] [-M <num-children>] [-p] [-s <sleep-time]";
    const char* optstring = "uN:M:ps:k";
    optionstruct parameters = {
        0, 1, 0, 0
    };
    char opt;
    while((opt = getopt(argc, argv, optstring)) != -1) {
        switch(opt) {
            case 'u':
                fprintf(stderr, usage, argv[0]);
                exit(0);
                break;
            case 'N':
                parameters.levels = atoi(optarg)-1;
                if(parameters.levels < -1 || parameters.levels > 4) {
                    fprintf(stderr, "Invalid value for -N");
                    exit(1);
                }
                break;
            case 'M':
                parameters.children = atoi(optarg);
                if(parameters.children < 1 || parameters.children > 4) {
                    fprintf(stderr, "Invalid value for -M");
                    exit(1);
                }
                break;
            case 'p':
                if(parameters.sleep) {
                    fprintf(stderr, "Can't specify -s and -p");
                    exit(1);
                }
                parameters.pause = 1;
                break;
            case 's':
                if(parameters.pause) {
                    fprintf(stderr, "Can't specify -s and -p");
                    exit(1);
                }
                parameters.sleep = optarg;
                break;
            case 'k':
                parameters.levels++;
                break;
            default:
                fprintf(stderr, usage, argv[0]);
                exit(1);
                break;
        }
    }
    if(parameters.levels < 1)
        parameters.levels = 0;
    fprintf(stdout, "ALIVE: Level %d process with pid=%d, child of ppid=%d.\n",
            parameters.levels, getpid(), getppid());
    if(!parameters.sleep)
        parameters.sleep = "1";
    if(parameters.levels < 1) {
        fprintf(stdout, "EXITING: Level %d process with pid=%d, child of ppid=%d.\n",
                parameters.levels, getpid(), getppid());
        exit(0);
    }
    tree(parameters, argv);
}

void tree(optionstruct parameters, char **argv) {
    pid_t pid = 0;
    for(int i = 0;i < parameters.children;i++) {
        pid = fork();
        if(pid == 0) break;
    }
    if(pid < 0) {
        fprintf(stderr, "Fork failed");
        exit(1);
    }
    if(pid == 0) {
        parameters.levels--;
        fprintf(stdout, "ALIVE: Level %d process with pid=%d, child of ppid=%d.\n",
                parameters.levels, getpid(), getppid());
        if(parameters.levels <= 0) {
            if(parameters.pause)
                pause();
            else if(parameters.sleep)
                sleep(atoi(parameters.sleep));
            fprintf(stdout, "EXITING: Level %d process with pid=%d, child of ppid=%d.\n",
                    parameters.levels, getpid(), getppid());
            exit(0);
        }
        char lvls[3];
        lvls[0] = parameters.levels + 48;
        lvls[1] = '\0';
        char chld[3];
        chld[0] = parameters.children + 48;
        chld[1] = '\0';
        if(parameters.pause) {
            char* opts[] = {argv[0], "-N", lvls, "-M", chld, "-p", "-k", NULL};
            execve(argv[0], opts, NULL);
        }
        else {
            char* opts[] = {argv[0], "-N", lvls, "-M", chld, "-s", parameters.sleep, "-k", NULL};
            execve(argv[0], opts, NULL);
        }
        fprintf(stdout, "EXITING: Level %d process with pid=%d, child of ppid=%d.\n",
                parameters.levels, getpid(), getppid());
        exit(0);
    }
    else {
        wait(NULL);
        fprintf(stdout, "EXITING: Level %d process with pid=%d, child of ppid=%d.\n",
                parameters.levels, getpid(), getppid());
    }
}
