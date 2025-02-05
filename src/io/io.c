/**
 * @file io.c
 * @author Stack1
 * @brief
 * @version 0.1
 * @date 31-01-2025
 *
 * Copyright (c) Simone Staccone, Tor Vergata University, Rome
 *
 */
#include "io.h"

void _random_generate(float *polynomial, int size)
{
    int i;
    srand(time(NULL)); // Initialization, should only be called once.

    for (i = 0; i < size; i++)
    {
        polynomial[i] = (float)(rand() % 100);
    }
}

void _write_seq_file(float *polynomial)
{
    int ret, i;
    FILE *fp;
    char *blank = " ";

    fp = fopen(DEFAULT_SEQ_FILE_NAME, "r");
    if (fp == NULL)
    {
        if (errno != ENOENT)
        {
            fprintf(stdout, RED "\tUnexpected error returned while opening the file %s" RESET "\n", DEFAULT_SEQ_FILE_NAME);
            fprintf(stdout, RED "\tErrno returned %s" RESET "\n", strerror(errno));
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "\tCreate file sequence.txt\t\t" GREEN "[OK]" RESET "\n");
    }

    fp = fopen(DEFAULT_SEQ_FILE_NAME, "w");
    if (fp == NULL)
    {
        fprintf(stdout, "\tOpen file sequence.txt\t\t\t" RED "[FAIL]" RESET "\n");

        if (errno == EINVAL)
        {
            fprintf(stdout, RED "\tInvalid mode flags used to open the file %s" RESET "\n", DEFAULT_SEQ_FILE_NAME);
        }
        else if (errno == ENOENT)
        {
            fprintf(stdout, RED "\tDirectory or file %s does not exist" RESET "\n", DEFAULT_SEQ_FILE_NAME);
        }
        else
        {
            fprintf(stdout, RED "\tUnexpected error returned while opening the file %s" RESET "\n", DEFAULT_SEQ_FILE_NAME);
        }
        fprintf(stdout, RED "\tErrno returned %s" RESET "\n", strerror(errno));
        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "\tOpen file sequence.txt\t\t\t" GREEN "[OK]" RESET "\n");

    _random_generate(polynomial, BUFF_SIZE);

    for (i = 0; i < BUFF_SIZE; i++)
    {
        ret = fprintf(fp, "%f", polynomial[i]);
        if (ret == 0)
        {
            break;
        }

        if (ret == -1)
        {
            fprintf(stdout, "\tElements written on file: %d\t\t" GREEN "[FAIL]" RESET "\n", i);
            fprintf(stdout, RED "\t\"write_seq_file\": Error writing number %d on file %s" RESET "\n", i, DEFAULT_SEQ_FILE_NAME);
            exit(EXIT_FAILURE);
        }
        ret = fwrite(blank, sizeof(char), 1, fp);
        if (ret == -1)
        {
            fprintf(stdout, "\tElements written on file: %d\t\t" GREEN "[FAIL]" RESET "\n", i);
            fprintf(stdout, RED "\t\"write_seq_file\": Error writing blank space after number %d on file %s" RESET "\n", i, DEFAULT_SEQ_FILE_NAME);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);

    fprintf(stdout, "\tElements written on file: %d\t\t" GREEN "[OK]" RESET "\n", i);
}

/**
 * @brief Function used to read from file the polynomial to use.
 *
 * @param file_name The string representing the name of the file to open
 * (or NULL if the file is the standard config/sequence.txt file)
 * @return The size of the polynomial read from file.
 */
int seq_file_read(polynomial *seq, char *file_name)
{
    int ret, i, max_size, resized;
    FILE *fp;
    float *tmp;
    char local_file_name[256];

    max_size = 0; // Counter used to see if realloc needed
    resized = 0;  // Variable holding the information about how many times the vector has been resized

    fprintf(stdout, "[INFO]\tReading polynomial from file ...\n");

    seq->data = (float *)malloc(sizeof(float) * BUFF_SIZE);
    if (seq->data == NULL)
    {
        fprintf(stdout, "\tInitialize memory\t\t\t" GREEN "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for polynomial array in function \"seq_file_read\" \n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "\tInitialize memory\t\t\t" GREEN "[OK]" RESET "\n");

    if (file_name == NULL)
    {
        strncpy(local_file_name, DEFAULT_SEQ_FILE_NAME, (strlen(DEFAULT_SEQ_FILE_NAME) + 1) * sizeof(char));
        _write_seq_file(seq->data);
        fprintf(stdout, GREEN "\tSequence successfully generated and written on file!" RESET "\n");
    }
    else
    {
        fprintf(stdout, "[INFO]\tReading polynomial from %s file\n", file_name);

        // Check to automatically set the base dir of the file if it isn't inserted by the user
        if (strncmp(file_name, DEFAULT_SUFFIX_DIR, strlen(DEFAULT_SUFFIX_DIR)) != 0)
        {
            sprintf(local_file_name, "%s%s", DEFAULT_SUFFIX_DIR, file_name);
        }
    }

    fp = fopen(local_file_name, "r");
    if (fp == NULL)
    {
        fprintf(stdout, "\tFile %s open \t\t" RED "[FAIL]" RESET "\n", local_file_name);

        if (errno == EINVAL)
        {
            fprintf(stdout, RED "\tInvalid mode flags used to open the file %s" RESET "\n", local_file_name);
        }
        else if (errno == ENOENT)
        {
            fprintf(stdout, RED "\tDirectory or file %s does not exist" RESET "\n", local_file_name);
        }
        else
        {
            fprintf(stdout, RED "\tUnexpected error returned while opening the file %s" RESET "\n", local_file_name);
        }

        fprintf(stdout, RED "\tErrno returned %s" RESET "\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "[INFO]\tLoading data from file ...\n");

    if (strlen(local_file_name) < 21) // Magic number used to format output in the fastest way (not the best)
    {
        fprintf(stdout, "\tFile %s open \t\t" GREEN "[OK]" RESET "\n", local_file_name);
    }
    else
    {
        fprintf(stdout, "\tFile %s open \t" GREEN "[OK]" RESET "\n", local_file_name);
    }

    ret = 1;
    i = 0;

    while (ret != 0)
    {
        ret = fscanf(fp, "%f", &seq->data[i]);

        if (ret == EOF)
        {
            if (errno == 0)
            {
                i--; // Resize to correct length the final vector
                break;
            }
            fprintf(stdout, RED "\tError loading data from file %s" RESET "\n", local_file_name);
            fprintf(stdout, RED "\tErrno returned %d: %s" RESET "\n", errno, strerror(errno));
            return -1;
        }

        max_size++;

        if (max_size == BUFF_SIZE)
        {
            resized++;
            tmp = (float *)realloc(seq->data, sizeof(float) * BUFF_SIZE * (resized + 1));

            if (tmp == NULL)
            {
                fprintf(stdout, YELLOW "\tWarning: Impossible to read thw whole .txt file, it's either too large or memory is not available at this time. Read %d elements." RESET "\n", i + 1);
                fprintf(stdout, RED "\tError resizing memory! The resize index is %d. The function called was \"seq_file_read\" " RESET "\n", i + 1);
                seq->size = i + 1;
                break;
            }
            else
            {
                seq->data = tmp; // Realloc OK, save new pointer value
            }

            max_size = 0;
        }

        i++;
    }

    fclose(fp);

    fprintf(stdout, "\tLoad polynomial of size %d\t\t" GREEN "[OK]" RESET "\n", i + 1);

    seq->size = i + 1;
    seq->mem_size = BUFF_SIZE * (resized + 1);

    fprintf(stdout, GREEN "\tSequence successfully loaded into memory" RESET "\n");

    return 0;
}
