# Berlekamp-Massey
## Outline
- [Overview](#overview)
- [Algorithm](#algorithm)
- [Getting Started](#getting-started)
- [References](#references)

## Overview
This is a C implementation of the Berlekamp-Massey algorithm used to find linear recurrence in sequences. The aim of this repository is to have a clear implementation of the algorithm and have some verbose documentation explaining the algorithm


## Algorithm
#### Introduction
The algorithm has multiple steps and has been proven to work in different papers. My implementation is based on the guide present in [[1]](#trivialize) and tries to be as clear as possible, not trying to be efficient but understandable.

#### Problem description
Our reference problem is to find the coefficients $C = [c_1,c_1.c_2,c_3,...,c_d]$ that correctly finds a linear recurrence between the elements of the  sequence $S = [s_0,s_1,s_2,s_3,...,s_n]$. So we want to find a set $C$ so that $s_{d+1} = s_0 \cdot c_d + s_1 \cdot c_{d-1} + ... + s_d \cdot c_0$. 

Therefore we can define:
$s_i = \sum_{j=1}^d{c_j \cdot s_{i-j}}$ &emsp;$\forall i \geq d$

#### Examples
Here is reported a list of examples, fell free to add your personal ones to help gaining a better understanding of the problem.
##### Fibonacci
A typical example of a linear recurrence is Fibonacci, $F_n = F_{n-1} + F_{n-2}$
$$
\begin{cases} 
s_i = s_{i-1} + s_{i-2} \\
s_0 = 1 \\
s_1 = 1
\end{cases}
$$
In this example $S = [1,1,2,3,5,8,13,21,...]$ and $C = [1,1]$ 
##### Growing sequence

##### Trailing zeros

##### Single trailing zero


### Nomenclature

### Algorithm iterations

### Conclusions

## Getting Started
To compile and run the code just use the provided Makefile with one of the two possible options:
- ```make all```: standard compilation. 
- ```make debug```: compilation in which the program will output some debug information about the values at each iteration of the algorithm. [3]

To run the program just run ```./berlekamp_massey <file_name>.txt```. In particular if no file name is specified (running just ```./berlekamp_massy```) than a standard file called **`sequence.txt`** populated by a random ordered sequence of 1024 elements. Each time the program is runned a new sequence will be generated, so the file will be overwritten. 

If a file name is specified make sure to place a file with the same name in the `Berlekamp-Massey/config/` directory, having written inside the sequence to process formatted as numbers spaced by a blank character (Eg. {2 3 5 1 4}). The sequence will be treated as an array of float numbers. 

In the configuration directory are present test_*.txt files used to test the correctness of the implementation. Those test were written according to the examples present in [[1]](#trivialize).

## References
 <a id="trivialize">[1]</a> Trivialize Berlekamp-Massey : https://mzhang2021.github.io/cp-blog/berlekamp-massey/
<a id="2">[2]</a> MASSEY, James. Shift-register synthesis and BCH decoding. IEEE transactions on Information Theory, 1969, 15.1: 122-127. 
<a id="3">[3]</a> Algebraic Coding Theory, Elwyn R Berlekamp (UC Berkeley), Non-Series Books. May 2015 
