#include "io/io.h"


int main(int argc, char **argv){
    char *file_name;

    printf("[INFO]\tBerlekamp-Massey algorithm for linear recurrences\n");
    printf("\tVersion 0.1\n");
    printf("\tCopyright (c) 2025 Simone Staccone, Tor Vergata University, Rome\n");
    printf("\tAuthor: Stack1\n");
    puts("");

    
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

    seq_file_read(file_name);

    return 0;
}