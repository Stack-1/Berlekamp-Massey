#include "io/io.h"
#include "berlekamp_massey.h"


int main(int argc, char **argv){
    int ret;
    char *file_name;
    polynomial *s;

    printf("[INFO]\tBerlekamp-Massey algorithm for linear recurrences\n");
    printf("\tVersion 0.1\n");
    printf("\tCopyright (s) 2025 Simone Staccone, Tor Vergata University, Rome\n");
    printf("\tAuthor: Stack1\n");
    puts("");

    s = (polynomial *)malloc(sizeof(polynomial));
    if(s == NULL){
        fprintf(stdout, RED "[ERROR]\tError allocating memory for C polynomial data structure" RESET "\n");
        exit(EXIT_FAILURE);
    }

    
    switch(argc){
        case 1:
            // Default config
            file_name = NULL;
            break;
        case 2:
            // File name as argv[1]
            file_name = argv[1];
            break;
        default:
            // Too many arguments
            fprintf(stdout, RED "[ERROR] Too many arguments: program should be called as ,/<prog> <file_name>\n" RESET);
            exit(EXIT_FAILURE);
            break;
    }

    ret = seq_file_read(s,file_name);
    if(ret != 0){
        fprintf(stdout,RED "[ERROR] Error encountered while leading polynomial elements\n" RESET);
        exit(EXIT_FAILURE);
    }

    berlekamp_massey(s);

    return 0;
}