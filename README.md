Word Ladder Generator

This project implements a Word Ladder Generator in C. A word ladder is a sequence of words where each word differs from the previous one by exactly one letter. The goal is to transform a given start word into a final word using the shortest possible sequence of valid dictionary words.

The project includes:

Core data structures (WordNode, LadderNode) for representing ladders and lists of ladders.

A breadth-first search (BFS) algorithm to find the shortest word ladder.

Utility functions for word handling, binary search, ladder copying, and memory management.

Built-in test functions for verifying correctness of core components.

A simple command-line interface for interactive use.

Features

Load words of a given length from a dictionary file.

Automatically build an array of valid words.

User-friendly prompts for selecting the start and final words.

Random word selection if too many invalid inputs are entered.

BFS-based algorithm ensures the shortest ladder is found.

Memory-safe (supports valgrind testing).

Built-in testing mode (-t flag) for verifying functionality.

Build & Run
Build the program
make build

Run the program
make run

Run with redirected input (for testing with a file)
make run_redirect

Run in test mode (executes all unit tests)
make run_test

Run with Valgrind (to check memory safety)
make valgrind

Example Usage
Welcome to the CS 211 Word Ladder Generator!

Enter the word size for the ladder: 3

This program will make the shortest possible
word ladder between two 3-letter words.

Enter filename for dictionary: testing.txt

Building array of 3-letter words... Done!

Setting the start 3-letter word...
  Enter a 3-letter word: cat

Setting the final 3-letter word...
  Enter a 3-letter word: dog

Shortest Word Ladder found!
        cat
        cot
        cog
        dog
Word Ladder height = 4

Testing

The program includes test functions for:

countWordsOfLength()

findWord()

insertWordAtFront()

getLadderHeight()

copyLadder()

insertLadderAtBack()

popLadderFromFront()

To run all tests:

./app.exe -t

Requirements

GCC compiler

Make

(Optional) Valgrind
 for memory testing

Notes

Dictionary file must exist and contain words of the specified length.

If the dictionary has fewer than 2 words of the given size, the program exits.

User must ensure input dictionary is sorted for findWord() (binary search) to work correctly.
