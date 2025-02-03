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

void _poly_cpy(polynomial *p, polynomial *q)
{
    for (int i = 0; i < q->size; i++)
    {
        p->data[i] = q->data[i];
    }
    p->size = q->size;
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

    for (j = 0; j < c->size; j++)
    {
        val += (c->data[j] * s->data[i - j - 1]);
        printf("%d %d %d %d %d\n", i, j, val, c->data[j], s->data[i - j - 1]);
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
    int i, j, val, zeros, delta, last_delta, last_index, start_index;
    polynomial *c, *d;

    _print_poly(s);

    fprintf(stdout, "[INFO]\tStarting Berlekamp-Massey algorithm ...\n");

    // Initialize memory
    c = (polynomial *)malloc(sizeof(polynomial));
    if (c == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for the linear recurrence polynomial C data structure" RESET "\n");
        exit(EXIT_FAILURE);
    }

    d = (polynomial *)malloc(sizeof(polynomial));
    if (d == NULL)
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

    d->data = (int *)malloc(sizeof(int) * (s->mem_size));
    if (d->data == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for C polynomial" RESET "\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "\tMemory and metadata initialization \t" GREEN "[OK]" RESET "\n");

    // Initialize C poly metadata
    c->size = 0;
    c->mem_size = s->mem_size;
    d->size = 0;
    d->mem_size = c->mem_size;

    // Initialize guess to an empty set (-1 is the end of the set)
    c->data[0] = -1;

    // Initialize algorithm metadata
    last_delta = -1;
    last_index = -1;

    start_index = _set_start(s);

    printf("Start index: %d\n", start_index);

    // Set past memory
    last_delta = s->data[start_index];
    last_index = start_index;
    _poly_cpy(d, c);

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

    // _print_poly(c);
    printf("Initial D(x): ");
    _print_poly(d);
    // printf("%d %d\n",c->size, _evaluate_poly(s,c,c->size - 1));

    for (i = start_index + 1; i < s->size; i++)
    {
        delta = _cmp_c_s(s, c, i);
        printf("Delta: %d\n", delta);
        if (delta == 0)
        {
            // Linear recurrence matches
            continue;
        }
        else
        {
            printf("\n\n\n\n%d %d %d %d\n", last_index, delta, last_delta, delta / last_delta);

            // Step 1: Set d equal to that sequence

            // Step 2: Multiply sequence by -1
            for (j = 0; j < d->size; j++)
            {
                d->data[j] = -d->data[j];
            }

            printf("Debug 1 D(x): ");
            _print_poly(d);

            // Step 3: Insert 1 on the left
            for (j = d->size; j > 0; j--)
            {
                d->data[j] = d->data[j - 1];
            }
            d->data[0] = 1;
            d->size++;

            printf("Debug 2 D(x): ");
            _print_poly(d);

            // Step 4: Multiply the sequence by delta / d(f + 1)
            val = delta / last_delta;
            printf("Val: %d\n", val);
            for (j = 0; j < d->size; j++)
            {
                d->data[j] = d->data[j] * val;
            }

            printf("Debug 3 D(x): ");
            _print_poly(d);

            // Step 5: Insert i - f - 1 zeros on the left
            zeros = i - last_index - 1;
            if (zeros != 0)
            {
                d->size = d->size + zeros;

                for (j = d->size; j > zeros; j--)
                {
                    d->data[j-1] = d->data[j - zeros - 1];
                }
                _print_poly(d);

                for (j = 0; j < zeros; j++)
                {
                    d->data[j] = 0;
                }
            }

            printf("Debug 4 D(x): ");
            _print_poly(d);

            // Step 6: Sum d and c
            val = (c->size > d->size) ? c->size : d->size;
            for (j = 0; j < val; j++)
            {
                c->data[j] = c->data[j] + d->data[j];
            }
            c->size = val;

            printf("Debug 5 C(x): ");
            _print_poly(c);

            last_delta = delta;
            last_index = i;
        }
    }
}