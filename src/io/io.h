/**
 * @file io.h
 * @author Stack1
 * @brief 
 * @version 0.1
 * @date 31-01-2025
 * 
 * 
 */
#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define DEFAULT_SEQ_FILE_NAME "../config/sequence.txt"
#define DEFAULT_SUFFIX_DIR "../config/" 
#define BUFF_SIZE 1024 //This is the size of the buffer used to read numbers from file, it is dynamically reallocated only after max size is reached to avoid continuos malloc calls 

#define RESET       "\033[0m"
#define BLACK       "\033[30m"              /* Black        */
#define RED         "\033[31m"              /* Red          */
#define GREEN       "\033[32m"              /* Green        */
#define YELLOW      "\033[33m"              /* Yellow       */
#define BLUE        "\033[34m"              /* Blue         */
#define MAGENTA     "\033[35m"              /* Magenta      */
#define CYAN        "\033[36m"              /* Cyan         */
#define WHITE       "\033[37m"              /* White        */
#define BOLDBLACK   "\033[1m\033[30m"       /* Bold Black   */
#define BOLDRED     "\033[1m\033[31m"       /* Bold Red     */
#define BOLDGREEN   "\033[1m\033[32m"       /* Bold Green   */
#define BOLDYELLOW  "\033[1m\033[33m"       /* Bold Yellow  */
#define BOLDBLUE    "\033[1m\033[34m"       /* Bold Blue    */
#define BOLDMAGENTA "\033[1m\033[35m"       /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"       /* Bold Cyan    */
#define BOLDWHITE   "\033[1m\033[37m"       /* Bold White   */

int *seq_file_read(char *file_name);

#endif