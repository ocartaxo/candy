# Candy Crush (Backtracking approach)

An implementation of the [Candy Crush](https://king.com/game/candycrush) game using the backtracking approach and the pseudo-random numbers, which play the role of colors, to generate the board.

## Getting Started

If you haven't an IDE installed on your pc, you can compile the code through the terminal using the ``gcc candy.cpp`` command in the code directory. And to run, use ``./a.out``.

To start playing you must type:

* ``N`` - The board dimension (5 <= N <= 20).
* ``D`` - The maximum amount of color on the board (3 <= D <= 8).
* ``S`` - Seed for generation of pseudo-random numbers, any integer value.

To generate the board. To move a cell from the board, you must type:

* ``source row``
* ``source column``
* ``target row``
* ``target column``

### Prerequisites

If you are using Windows, you need to have [MinGW](http://www.mingw.org/wiki/HOWTO_Install_the_MinGW_GCC_Compiler_Suite) installed on your PC.

## Running

Maybe you don't remember how to compile/run a program in C++ (or don't know, no problems). So, let me remind you:

``g++ candy.cpp -o candy.exe(or -o candy.out if are using a SO based in linux)``
Then
``./candy.exe``

Or you can just do

``g++ candy.cpp`` and then ``./a.exe``
