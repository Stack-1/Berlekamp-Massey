/**
 * @file berlekamp_massey.c
 * @author Stack1
 * @brief File containing all the functions used to implement the
 * Berlekamp-Massey algorithm for real numbers base 10.
 *
 * @version 0.1
 * @date 02-02-2025
 *
 * Copyright (c) Simone Staccone, Tor Vergata University, Rome
 *
 */
#include "berlekamp_massey.h"

/**
 * @brief Debug function used to print a polynomial.
 *
 * @param p The data structure containing the polynomial to print
 */
void _print_poly(polynomial *p)
{
    for (int i = 0; i < p->size; i++)
    {
        printf("%.2f ", p->data[i]);
    }
    puts("");
}

/**
 * @brief Function that copies a polynomial coefficients into
 * another polynomial data structure, updating also the size
 * metadata.
 *
 * @param p Polynomial data structure to populate.
 * @param q Polynomial data structure to copy.
 */
void _poly_cpy(polynomial *p, polynomial *q)
{
    for (int i = 0; i < q->size; i++)
    {
        p->data[i] = q->data[i];
    }
    p->size = q->size;
}

/**
 * @brief Function that computes the value of the polynomial evaluated
 * using a specific sequence.
 *
 * @param s The data structure containing the sequence to use.
 * @param c The data structure containing the polynomial coefficients.
 * @param i Element of the sequence that we are processing.
 * @return The evaluation of the polynomial C(x) using the sequence s.
 */
float _evaluate_poly(polynomial *s, polynomial *c, int i)
{
    int j;
    float val = 0.0;

    for (j = 0; j < c->size; j++)
    {
        val += (c->data[j] * s->data[i - j - 1]);
    }

    return val;
}

/**
 * @brief Function to initialize C(x) according to the first
 * elements og the sequence. A single value if the first element
 * is not zero or a set of zeros (could also be random numbers)
 * equals to the length of the trailing zeros inside the sequence.
 *
 * @param s The data structure containing the sequence.
 * @return An integer representing the number of zero elements
 * stored in the beginning of the sequence.
 */
int _set_start(polynomial *s)
{
    int i;

    i = 0;

    while (i < s->size && s->data[i] == 0.0)
    {
        i++;
    }

    return i;
}

/**
 * @brief Function that returns the difference between the polynomial
 * S(x) evaluated with C(x) at the i-th grade and the value of the
 * i-th element of the sequence S(x).
 *
 * @param s The data structure containing the sequence to compare.
 * @param c The data structure containing the polynomial to evaluate.
 * @param index The grade off the polynomial.
 * @return A floating point representing the difference between
 * S(c_0,c_1,...,c_i) and S(i).
 */
float _cmp_c_s(polynomial *s, polynomial *c, int index)
{
    float delta;

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
 * @brief This is the main function of the algorithm. The purpose of this
 * function is to get the sequence and return the coefficients of a linear
 * polynomial representing the linear recurrence of the sequence. (For more
 * information about the algorithm check the README.md file.)
 *
 * @param s A data structure representing the sequence to be used.
 */
void berlekamp_massey(polynomial *s)
{
    int i, j, zeros, last_index, start_index;
    float val, delta, last_delta;
    polynomial *c, *d, *b;

#ifdef DEBUG
    printf("S(x): ");
    _print_poly(s);
#endif

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

    b = (polynomial *)malloc(sizeof(polynomial));
    if (b == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for the linear recurrence polynomial C data structure" RESET "\n");
        exit(EXIT_FAILURE);
    }

    c->data = (float *)malloc(sizeof(float) * (s->mem_size));
    if (c->data == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for C polynomial" RESET "\n");
        exit(EXIT_FAILURE);
    }

    d->data = (float *)malloc(sizeof(float) * (s->mem_size));
    if (d->data == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for C polynomial" RESET "\n");
        exit(EXIT_FAILURE);
    }

    b->data = (float *)malloc(sizeof(float) * (s->mem_size));
    if (b->data == NULL)
    {
        fprintf(stdout, "\tMemory and metadata initialization \t" RED "[FAIL]" RESET "\n");
        fprintf(stdout, RED "\tError allocating memory for C polynomial" RESET "\n");
        exit(EXIT_FAILURE);
    }

    // Initialize C polynomial metadata
    c->size = 0;
    c->mem_size = s->mem_size;
    d->size = 0;
    d->mem_size = c->mem_size;
    b->size = 0;
    b->mem_size = d->mem_size;

    fprintf(stdout, "\tMemory and metadata initialization \t" GREEN "[OK]" RESET "\n");

    // Find the first index of a non zero element
    start_index = _set_start(s);

    // Initialize C polynomial with the right length init status
    c->data[0] = 1;
    c->size++;
    last_delta = s->data[start_index];
    last_index = start_index;

    if (start_index > 0)
    {
        // Insert a set of zeros
        for (i = 0; i < start_index; i++)
        {
            c->data[i] = 0.0;
            c->size++;
        }
        last_delta = s->data[i];
    }

    fprintf(stdout, "\tAlgorithm initialization\t\t" GREEN "[OK]" RESET "\n");

#ifdef DEBUG
    printf("Initial B(x): ");
    _print_poly(b);
    printf("Initial D(x): ");
    _print_poly(d);
    printf("Initial C(x): ");
    _print_poly(c);
#endif
    // printf("%d %d\n",c->size, _evaluate_poly(s,c,c->size - 1));

    delta = 1;

    for (i = start_index + 1; i < s->size; i++)
    {
        delta = _cmp_c_s(s, c, i);
#ifdef DEBUG
        printf("Iteration %d\n", i);
        printf("Delta: %.2f\n", delta);
#endif

        if (delta == 0)
        {
            // Linear recurrence matches
            continue;
        }
        else
        {

            // Step 1: Set d equal to that sequence
            _poly_cpy(d, b);

#ifdef DEBUG
            printf("Debug 1 D(x): ");
            _print_poly(d);
#endif
            // Step 2: Multiply sequence by -1
            for (j = 0; j < d->size; j++)
            {
                d->data[j] = -d->data[j];
            }
#ifdef DEBUG
            printf("Debug 2 D(x): ");
            _print_poly(d);
#endif
            // Step 3: Insert 1 on the left
            for (j = d->size; j > 0; j--)
            {
                d->data[j] = d->data[j - 1];
            }
            d->data[0] = 1.0;
            d->size++;

#ifdef DEBUG
            printf("Debug 3 D(x): ");
            _print_poly(d);
#endif
            // Step 4: Multiply the sequence by delta / d(f + 1)
            val = delta / last_delta;
            for (j = 0; j < d->size; j++)
            {
                d->data[j] = d->data[j] * val;
            }
#ifdef DEBUG
            printf("Debug 4 D(x): ");
            _print_poly(d);
#endif
            // Step 5: Insert i - f - 1 zeros on the left
            zeros = i - last_index - 1;

            if (zeros != 0)
            {
                d->size = d->size + zeros;

                for (j = d->size; j > zeros; j--)
                {
                    d->data[j - 1] = d->data[j - zeros - 1];
                }
#ifdef DEBUG
                printf("Middle D(x): ");
                _print_poly(d);
#endif
                for (j = 0; j < zeros; j++)
                {
                    d->data[j] = 0;
                }
            }
#ifdef DEBUG
            printf("Debug 5 D(x): ");
            _print_poly(d);
#endif

            if (i - c->size >= last_index - b->size)
            {
                _poly_cpy(b, c);
                last_index = i;
                last_delta = delta;
            }

            // Step 6: Sum d and c
            val = (c->size > d->size) ? c->size : d->size;
            for (j = 0; j < val; j++)
            {
                c->data[j] = c->data[j] + d->data[j];
            }
            c->size = val;
#ifdef DEBUG
            printf("Debug 5 C(x): ");
            _print_poly(c);
#endif

#ifdef DEBUG
            printf("End of %i iteration B(x): ", i);
            _print_poly(b);
            printf("End of %i iteration D(x): ", i);
            _print_poly(d);
            printf("End of %i iteration C(x): ", i);
            _print_poly(c);
#endif
        }
    }
    fprintf(stdout, "\tAlgorithm termination\t\t\t" GREEN "[OK]" RESET "\n");

#ifdef DEBUG
    printf("C(x): ");
    _print_poly(c);
#endif


    _write_seq_file(s->data,"output.txt");


    fprintf(stdout, GREEN "\tLinear recurrence successfully computed!" RESET "\n");
}