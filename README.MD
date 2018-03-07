# Candy Crush (Backtracking approach)

An implementation of the [Candy Crush](https://king.com/game/candycrush) game using the backtracking approach and the pseudo-random numbers, which play the role of colors, to generate the board.

## Getting Started

If you haven't an IDE installed on your pc, you can compile the code through the terminal using the ``gcc candy.cpp`` command in the code directory. And to run, use ``./a.out``.

To start playing you must type:

* ``N`` - The board dimension (5 <= N <= 20).
* ``D`` - The maximum amount of color on the board (3 <= D <= 8).
* ``S`` - Seed for generation of pseudo-random numbers, any integer value.


To generate the board. To move a cell from the board, you must type:

* ``the source row and column``.
* ``the target row and column``.

### Prerequisites

If you are using Windows, you need to have [MinGW](http://www.mingw.org/wiki/HOWTO_Install_the_MinGW_GCC_Compiler_Suite) installed on your PC.
