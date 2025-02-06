# Berlekamp-Massey
## Outline
- [Overview](#overview)
- [Algorithm](#algorithm)
- [Getting Started](#getting-started)
- [References](#references)

## Overview
This is a C implementation of the Berlekamp-Massey algorithm used to find linear recurrence in sequences. The aim of this repository is to have a clear implementation of the algorithm and have some verbose documentation explaining the algorithm


## Algorithm
The algorithm has multiple steps and has been proven to work in different papers. My implementation is based on the guide present in [[1]](#trivialize).
$S(x) = 1 + c_1 x + c_2 x^2 + ... + c_d x^d$


## Getting Started
To compile and run the code just use the provided Makefile with one of the two possible options:
- ```make all```: standard compilation. 
- ```make debug```: compilation in which the program will output some debug information about the values at each iteration of the algorithm. 

To run the program just run ```./berlekamp_massey <file_name>.txt```. In particular if no file name is specified (running just ```./berlekamp_massy```) than a standard file called **`sequence.txt`** populated by a random ordered sequence of 1024 elements. Each time the program is runned a new sequence will be generated, so the file will be overwritten. 

If a file name is specified make sure to place a file with the same name in the `Berlekamp-Massey/config/` directory, having written inside the sequence to process formatted as numbers spaced by a blank character (Eg. {2 3 5 1 4}). The sequence will be treated as an array of float numbers. 

In the configuration directory are present test_*.txt files used to test the correctness of the implementation. Those test were written according to the examples present in \[\[1\]\](#trivialize).

## References
<a id="trivialize">\[1\].</a> Trivialize Berlekamp-Massey : https://mzhang2021.github.io/cp-blog/berlekamp-massey/

<a id="2">\[2\].</a> MASSEY, James. Shift-register synthesis and BCH decoding. IEEE transactions on Information Theory, 1969, 15.1: 122-127. 

<a id="3">\[3\].</a> Algebraic Coding Theory, Elwyn R Berlekamp (UC Berkeley), Non-Series Books. May 2015 
