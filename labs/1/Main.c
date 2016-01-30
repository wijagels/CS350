#include "Main.h"

int main(int argc, char **argv, char *envp[]) {
    char* usage = "Usage: %s [-u] [-g] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>]\n[-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n";
    char* optstring = "ugn:m:M:s:i:o:c:";
    optionstruct init = {
        0, 100, 1, 1000000, 0, "", "", ""
    };
    for(int i=1;i<argc;i++) {
        //printf("%s\n", argv[i]);
    }
    for(char** env = envp;*env != 0;env++) {
        //printf("%s\n", *env);
    }
    optionstruct parameters = init;
    char opt;
    /*
     * For each of the flags provided, add them to the struct
     * Runtime is the size of argv-1
     */
    while((opt = getopt(argc, argv, optstring)) != -1) {
        switch(opt) {
            case 'u':
                printf(usage, argv[0]);
                break;
            case 'g':
                if(DEBUG) printf("g: enabled");
                parameters.g = 1;
                break;
            case 'n':
                if(DEBUG) printf("n: %s\n", optarg);
                parameters.num = atoi(optarg);
                break;
            case 'm':
                if(DEBUG) printf("m: %s\n", optarg);
                parameters.min = atoi(optarg);
                break;
            case 'M':
                if(DEBUG) printf("M: %s\n", optarg);
                parameters.max = atoi(optarg);
                break;
            case 's':
                if(DEBUG) printf("s: %s\n", optarg);
                parameters.seed = strtoul(optarg, NULL, 10);
                break;
            case 'i':
                if(DEBUG) printf("i: %s\n", optarg);
                parameters.input = optarg;
                break;
            case 'o':
                if(DEBUG) printf("o: %s\n", optarg);
                parameters.output = optarg;
                break;
            case 'c':
                if(DEBUG) printf("c: %s\n", optarg);
                parameters.countfile = optarg;
                break;
            default:
                fprintf(stderr, usage, argv[0]);
                exit(1);
                break;
        }
    }
    if(parameters.g) {
        generate(parameters);
    }
    else {
        FILE* ostream = stdout;
        FILE* istream = stdin;
        FILE* countstream = stdout;
        if(strlen(parameters.output) > 1) {
            ostream = fopen(parameters.output, "w");
            if(!ostream) {
                perror("fopen failed");
                exit(1);
            }
        }
        if(strlen(parameters.input) > 1) {
            istream = fopen(parameters.input, "r");
            if(!istream) {
                perror("fopen failed");
                exit(1);
            }
        }
        if(strlen(parameters.countfile) > 1) {
            countstream = fopen(parameters.countfile, "w");
            if(!countstream) {
                perror("fopen failed");
                exit(1);
            }
        }
        sorted(parameters, istream, ostream, countstream);
    }
}

