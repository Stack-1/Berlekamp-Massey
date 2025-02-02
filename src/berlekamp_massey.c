/**
 * @file berlekamp_massey.c
 * @author Stack1
 * @brief 
 * @version 0.1
 * @date 02-02-2025
 * 
 * Copyright (c) Simone Staccone, Tor Vergata University, Rome
 * 
 */
#include "berlekamp_massey.h"


/**
 * @brief 
 * 
 * @param seq 
 */
void berlekamp_massey(sequence *seq){
    int *guess;

    guess = (int *)malloc(sizeof(int) * (seq->size + 1) );
    if(guess == NULL){
        fprintf(stdout, RED "\tError allocating memory for the linear recurrence guess" RESET "\n");
        exit(EXIT_FAILURE);
    }

    // Initialize guess to an empty set (-1 is the end of the set)
    guess[0] = -1;
    
}