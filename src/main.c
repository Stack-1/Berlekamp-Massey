#include "io/io.h"


int main(int argc, char **argv){
    int ret;
    char *file_name;
    sequence *seq;

    printf("[INFO]\tBerlekamp-Massey algorithm for linear recurrences\n");
    printf("\tVersion 0.1\n");
    printf("\tCopyright (c) 2025 Simone Staccone, Tor Vergata University, Rome\n");
    printf("\tAuthor: Stack1\n");
    puts("");

    seq = (sequence *)malloc(sizeof(sequence));
    if(seq == NULL){
        // TDO: Handle error
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

    ret = seq_file_read(seq,file_name);
    if(ret != 0){
        fprintf(stdout,RED "[ERROR] Error encountered while leading sequence elements\n" RESET);
        exit(EXIT_FAILURE);
    }


    return 0;
}