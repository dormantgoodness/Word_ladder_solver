# Word Ladder Generator  

This project implements a **Word Ladder Generator** in C. A *word ladder* is a sequence of words where each word differs from the previous one by exactly one letter. The goal is to transform a given start word into a final word using the shortest possible sequence of valid dictionary words.  

The project includes:  
- Core data structures (`WordNode`, `LadderNode`) for representing ladders and lists of ladders.  
- A breadth-first search (BFS) algorithm to find the shortest word ladder.  
- Utility functions for word handling, binary search, ladder copying, and memory management.  
- Built-in test functions for verifying correctness of core components.  
- A simple command-line interface for interactive use.  

---

## Features  
- Load words of a given length from a dictionary file.  
- Automatically build an array of valid words.  
- User-friendly prompts for selecting the start and final words.  
- Random word selection if too many invalid inputs are entered.  
- BFS-based algorithm ensures the **shortest ladder** is found.  
- Memory-safe (supports `valgrind` testing).  
- Built-in testing mode (`-t` flag) for verifying functionality.  

---

## Build & Run  

```bash
make build      # compile the program
```
```bash
make run        # run the program interactively
```
```bash
make run_test   # run built-in unit tests
```
```bash
make run_redirect   # run with redirected input from testing.txt
```
```bash
make valgrind   # run with Valgrind for memory check
```

---

## Example Usage
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

---

## Requirements
- GCC compiler 
- Make
- (Optional) Valgrind for memory testing


