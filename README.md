# DS_WordSearch
RPI CSCI-1200, Fall 2009/Spring 2017, Homework 6 - Inverse Word Search Recursion <br />
By Erebuxy

## Usage
```shell
<input_filename> one_solution
<input_filename> all_solutions
```

## Improvements/Optimizations
* Sort word list and banned word list by string length before recursion.
* Only place the first word at the upper-left side of the board.
* Do not rotate the first word under some circumstances (such as word length equals column number when placing horizontally).
* Do not rotate a letter.

## Performance
Complied with `-O3` optimization, run on Intel Core-i7 6700k / Windows subsystem for Linux

Command | # of Solutions | Runtime
--- | :---: | ---: |
`puzzle1.txt all_solutions` | 8 | 0.014s
`puzzle2.txt all_solutions` | 4 | 0.014s
`puzzle3.txt all_solutions` | 8 | 0.014s
`puzzle4.txt all_solutions` | 4 | 0.013s
`puzzle5.txt all_solutions` | 100 | 0.013s
`puzzle6.txt all_solutions` | 208 | 0.012s
`puzzle7.txt all_solutions` | 1 | 0.037s
`puzzle8.txt all_solutions` | 4 | 0.323s
