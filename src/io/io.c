/**
 * @file io.c
 * @author Stack1
 * @brief
 * @version 1.0
 * @date 31-01-2025
 *
 * Copyright (c) Simone Staccone
 *
 */
#include "io.h"

void _write_seq_file()
{
    int ret, i;
    FILE *fp;
    char *blank = " ";

    fp = fopen(DEFAULT_SEQ_FILE_NAME, "r");
    if (fp == NULL)
    {
        if (errno != ENOENT)
        {
            fprintf(stdout, RED "\tUnexpected error returned while opening the file %s\n" RESET, DEFAULT_SEQ_FILE_NAME);
            fprintf(stdout, RED "\tErrno returned %s\n" RESET, strerror(errno));
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        fprintf(stdout, "\tCreating sequence.txt file\t\t" GREEN "[OK]" RESET "\n");
    }
    else
    {
        fprintf(stdout, "\tOpening sequence.txt file\t\t" GREEN "[OK]" RESET "\n");
    }

    fp = fopen(DEFAULT_SEQ_FILE_NAME, "w");
    if (fp == NULL)
    {
        if (errno == EINVAL)
        {
            fprintf(stdout, RED "\tInvalid mode flags used to open the file %s\n" RESET, DEFAULT_SEQ_FILE_NAME);
            fprintf(stdout, RED "\tErrno returned %s\n" RESET, strerror(errno));
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        else if (errno == ENOENT)
        {
            fprintf(stdout, RED "\tDirectory or file %s does not exist\n" RESET, DEFAULT_SEQ_FILE_NAME);
            fprintf(stdout, RED "\tErrno returned %s\n" RESET, strerror(errno));
            fclose(fp);
            exit(EXIT_FAILURE);
        }
        else
        {
            fprintf(stdout, RED "\tUnexpected error returned while opening the file %s\n" RESET, DEFAULT_SEQ_FILE_NAME);
            fprintf(stdout, RED "\tErrno returned %s\n" RESET, strerror(errno));
            fclose(fp);
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < BUFF_SIZE * 3; i++)
    {
        ret = fprintf(fp, "%d", i);
        if (ret == 0)
        {
            break;
        }

        if (ret == -1)
        {
            fprintf(stdout, "\tElements written on file: %d\t\t" GREEN "[FAIL]" RESET "\n",i);
            fprintf(stdout, RED "\t\"write_seq_file\": Error writing number %d on file %s\n" RESET, i, DEFAULT_SEQ_FILE_NAME);
            exit(EXIT_FAILURE);
        }
        ret = fwrite(blank, sizeof(char), 1, fp);
        if (ret == -1)
        {
            fprintf(stdout, "\tElements written on file: %d\t\t" GREEN "[FAIL]" RESET "\n",i);
            fprintf(stdout, RED "\t\"write_seq_file\": Error writing blank space after number %d on file %s\n" RESET, i, DEFAULT_SEQ_FILE_NAME);
            exit(EXIT_FAILURE);
        }
    }

    fclose(fp);

    fprintf(stdout, "\tElements written on file: %d\t\t" GREEN "[OK]" RESET "\n",i);
}

/**
 * @brief Function used to read from file the sequence to use.
 *
 * @param file_name The string representing the name of the file to open
 * (or NULL if the file is the standard config/sequence.txt file)
 * @return A pointer to a memory area containing the sequence.
 */
int *seq_file_read(char *file_name)
{
    int ret, i, max_size, resized;
    FILE *fp;
    int *sequence;
    int *tmp;
    char local_file_name[256];

    max_size = 0; // Counter used to see if realloc needed
    resized = 0;  // Variable holding the information about how many times the vector has been resized

    if (file_name == NULL)
    {
        fprintf(stdout, "[INFO]\tReading sequence from standard file sequence.txt\n");
        strncpy(local_file_name, DEFAULT_SEQ_FILE_NAME, (strlen(DEFAULT_SEQ_FILE_NAME) + 1) * sizeof(char));
        fprintf(stdout, "[INFO]\tGenerating sequence ...\n");
        _write_seq_file();
        fprintf(stdout, GREEN "\tSequence successfully generated and written on file!\n" RESET);
    }
    else
    {
        fprintf(stdout, "[INFO]\tReading sequence from %s file\n", file_name);

        // Check to automatically set the base dir of the file if it isn't inserted by the user
        if (strncmp(file_name, DEFAULT_SUFFIX_DIR, strlen(DEFAULT_SUFFIX_DIR)) != 0)
        {
            sprintf(local_file_name, "%s%s", DEFAULT_SUFFIX_DIR, file_name);
        }
    }
    printf("%s\n",local_file_name);

    sequence = (int *)malloc(sizeof(int) * BUFF_SIZE);
    if (sequence == NULL)
    {
        fprintf(stdout, RED "\tError allocating memory for sequence array in function \"seq_file_read\" \n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "\tMemory correctly initialized for sequence\n");

    fp = fopen(local_file_name, "r");
    if (fp == NULL)
    {
        fprintf(stdout, "\tFile %s open \t\t\t" RED "[FAIL]" RESET "\n", local_file_name);

        if (errno == EINVAL)
        {
            fprintf(stdout, RED "\tInvalid mode flags used to open the file %s\n" RESET, local_file_name);
        }
        else if (errno == ENOENT)
        {
            fprintf(stdout, RED "\tDirectory or file %s does not exist\n" RESET, local_file_name);
        }
        else
        {
            fprintf(stdout, RED "\tUnexpected error returned while opening the file %s\n" RESET, local_file_name);
        }

        fprintf(stdout, RED "\tErrno returned %s\n" RESET, strerror(errno));

        fclose(fp);
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "\tFile %s open \t\t\t" GREEN "[OK]" RESET "\n", local_file_name);

    ret = 1;
    i = 0;

    while (ret != 0)
    {
        ret = fscanf(fp, "%d", &sequence[i]);
        if (ret == -1)
        {
            return NULL;
        }
        max_size++;
        if (max_size == BUFF_SIZE)
        {
            resized++;
            tmp = (int *)realloc(sequence, sizeof(int) * BUFF_SIZE * (resized + 1));

            if (tmp == NULL)
            {
                fprintf(stdout, YELLOW "\tWarning: Impossible to read thw whole .txt file, it's either too large or memory is not available at this time. Read %d elements.\n" RESET, i + 1);
                fprintf(stdout, RED "\tError resizing memory! The resize index is %d. The function called was \"seq_file_read\" \n" RESET, i + 1);
                return sequence;
            }
            else
            {
                sequence = tmp; // Realloc OK, save new pointer value
            }

            max_size = 0;
        }

        i++;
    }

    fclose(fp);

    return sequence;
}
