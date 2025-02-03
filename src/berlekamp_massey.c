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

void _print_poly(polynomial *p)
{
    for (int i = 0; i < p->size; i++)
    {
        printf("%d ", p->data[i]);
    }
    puts("");
}

/**
 * @brief
 *
 * @param s Sequence
 * @param c Polynomial coefficients
 * @param i Element of the sequence that we are processing
 * @return The evaluation of the polynomial c using the sequence s
 */
int _evaluate_poly(polynomial *s, polynomial *c, int i)
{
    int val, j;

    val = 0;

    if (j >= c->size)
    {
        fprintf(stdout, RED "\tInvalid argument passed to \"_evaluate_poly\", j (%d) is grater than C polynomial grade (%d)" RESET "\n", j, c->size);
        exit(EXIT_FAILURE);
    }

    for (j = 0; j < c->size; j++)
    {
        val += (c->data[j] * s->data[i - j]);
    }

    return val;
}

int _set_start(polynomial *s)
{
    int i;

    i = 0;

    while (i < s->size && s->data[i] == 0)
    {
        i++;
    }

    return i;
}

// void _update_poly(polynomial *c, int delta, int last_fail)
// {
// }

/**
 * @brief
 *
 * @param s
 * @param c
 * @param index
 * @return
 */
int _cmp_c_s(polynomial *s, polynomial *c, int index)
{
    int delta;

    delta = 0;

    if (c->data[index] == -1)
    {
        // Empty set, populate c polynomial
        c->data[index] = s->data[index];
    }
    else
    {
        delta = s->data[index] - _evaluate_poly(s, c, index);
    }
    return delta;
}

/**
 * @brief
 *
 * @param s
 */
void berlekamp_massey(polynomial *s)
{
    int i, delta, last_delta, last_index, start_index;
    polynomial *c;

    //_print_poly(s);

    fprintf(stdout, "[INFO]\tStarting Berlekamp-Massey algorithm ...\n");

    // Initialize memory
    c = (polynomial *)malloc(sizeof(polynomial));
    if (c == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for the linear recurrence polynomial C data structure" RESET "\n");
        exit(EXIT_FAILURE);
    }

    c->data = (int *)malloc(sizeof(int) * (s->mem_size));
    if (c->data == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for C polynomial" RESET "\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "\tMemory and metadata initialization \t" GREEN "[OK]" RESET "\n");

    // Initialize C poly metadata
    c->size = 0;
    c->mem_size = s->mem_size;

    // Initialize guess to an empty set (-1 is the end of the set)
    c->data[0] = -1;

    // Initialize algorithm metadata
    last_delta = -1;
    last_index = -1;

    start_index = _set_start(s);

    printf("Start index: %d\n", start_index);

    // Initialize C polynomial with the right length init status
    if (start_index == 0)
    {
        // Initialize C with the first element of S(x)
        c->data[0] = s->data[0];
        c->size = 1;
    }
    else
    {
        // Insert a set of zeros
        for (i = 0; i < start_index; i++)
        {
            c->data[i] = 0;
            c->size++;
        }
    }

    _print_poly(c);

    // for (i = 0; i < s->size; i++)
    // {
    //     delta = _cmp_c_s(s, c, i);
    //     if (delta == 0)
    //     {
    //         // Linear recurrence matches
    //         continue;
    //     }
    //     else
    //     {
    //     }
    // }
}