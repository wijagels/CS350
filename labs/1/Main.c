#include "Main.h"

int main(int argc, char **argv, char *envp[]) {
    const char* usage = "Usage: %s [-u] [-g] [-n <num-integers>] [-m <min-int>] [-M <max-int>] [-s <seed>]\n[-i <input-file-name>] [-o <output-file-name>] [-c <count-file-name>]\n";
    const char* optstring = "ugn:m:M:s:i:o:c:";
    // Set the defaults
    optionstruct parameters = {
        0, 100, 1, 255, 0, "", "", ""
    };
    char opt;
    /*
     * For each of the flags provided, add them to the struct
     * Runtime is argc-1
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
                if(DEBUG) fprintf(stderr, "n: %s\n", optarg);
                if(!sscanf(optarg, "%d", &parameters.num)) {
                    perror("sscanf failed");
                    exit(1);
                }
                break;
            case 'm':
                if(DEBUG) fprintf(stderr, "m: %s\n", optarg);
                if(!sscanf(optarg, "%d", &parameters.min)) {
                    perror("sscanf failed");
                    exit(1);
                }
                break;
            case 'M':
                if(DEBUG) fprintf(stderr, "M: %s\n", optarg);
                if(!sscanf(optarg, "%d", &parameters.max)) {
                    perror("sscanf failed");
                    exit(1);
                }
                break;
            case 's':
                if(DEBUG) fprintf(stderr, "s: %s\n", optarg);
                parameters.seed = strtoul(optarg, NULL, 10);
                break;
            case 'i':
                if(DEBUG) fprintf(stderr, "i: %s\n", optarg);
                parameters.input = optarg;
                break;
            case 'o':
                if(DEBUG) fprintf(stderr, "o: %s\n", optarg);
                parameters.output = optarg;
                break;
            case 'c':
                if(DEBUG) fprintf(stderr, "c: %s\n", optarg);
                parameters.countfile = optarg;
                break;
            default:
                fprintf(stderr, usage, argv[0]);
                exit(1);
                break;
        }
    }
    if(parameters.max < parameters.min) {
        fprintf(stderr, "%d < %d\n", parameters.max, parameters.min);
        exit(1);
    }
    if(parameters.max > 1000000) {
        fprintf(stderr, "max too large\n");
        exit(1);
    }
    if(parameters.min < 1) {
        fprintf(stderr, "min too small\n");
        exit(1);
    }

    if(parameters.g) {
        FILE* ostream = stdout;
        if(strlen(parameters.output)) {
            ostream = fopen(parameters.output, "w");
            if(!ostream) {
                perror("fopen failed");
                exit(1);
            }
        }
        generate(parameters, ostream);
        fclose(ostream);
    }
    else {
        FILE* ostream = stdout;
        FILE* istream = stdin;
        FILE* countstream = stdout;
        if(strlen(parameters.output)) {
            ostream = fopen(parameters.output, "w");
            if(!ostream) {
                perror("fopen failed");
                exit(1);
            }
        }
        if(strlen(parameters.input)) {
            istream = fopen(parameters.input, "r");
            if(!istream) {
                perror("fopen failed");
                exit(1);
            }
        }
        if(strlen(parameters.countfile)) {
            countstream = fopen(parameters.countfile, "w");
            if(!countstream) {
                perror("fopen failed");
                exit(1);
            }
        }
        settimer();
        sorted(parameters, istream, ostream, countstream);
        fprintf(stderr, "Elapsed time: %f sec\n", (float)endtimer()/1000000);
        fclose(istream);
        fclose(ostream);
        fclose(countstream);
    }
    return 0;
}

