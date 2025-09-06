/*-------------------------------------------
Project: Find the Shortest Word Ladder - A program that tries to find the shortest bridge between one 
word and another
Author: Dominic Aidoo
------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next;
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

/*
Function that takes in a filename and the size of the word. It tries to find the number of words in the
file that have the same size as wordSize and returns it
*/
int countWordsOfLength(char* filename, int wordSize) { 
    
    FILE* file = fopen(filename, "r");
    // returns -1 if file cannot open
    if (!file) {
        return -1;
    }

    int count = 0; 
    char word[100];
    // loop to read words from file
    while (fscanf(file, "%99s", word) == 1) {
        // checks if word has the correct length
        if (strlen(word) == wordSize) {
            count ++;
        }
    }
    fclose(file);

    return count;
}

/*
Function that takes no parameters and tests the countWordsOfLength() function. It returns true if the
tests passed and false if they fail
*/
bool test_countWordsOfLength() {
    int count = countWordsOfLength("testing.txt", 3);
    // checks if function call matches expected value
    if (count != 17) {
        printf("Expected values does not match the actual values - Test failed");
        return false;
    }

    count = countWordsOfLength("hello.txt", 2);
    // checks if function call matches expected value
    if (count != -1 ) {
        printf("Expected values does not match the actual values - Test failed");
        return false;
    }

    return true;
}

/*
Function that takes in a filename, array of words, word size and number of words. It finds words that 
are exactly word size long and and fills the array words with it. It returns true if the number of words
in the array matches numWords and false otherwise
*/
bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    
    FILE* file = fopen(filename, "r");
    // returns false if file cannot open
    if (!file) {
        return false;
    }

    int count = 0;
    char buffer[100];

    // loop to read words from the file
    while (fscanf(file, "%99s", buffer) == 1) {
        if (strlen(buffer) == wordSize) {
            strcpy(words[count], buffer);
            count ++;
        }
    }

    fclose(file);

    // returns true if count is same as expected which is numWords
    if (count == numWords) {
        return true;
    }
    
    return false;
}   

/*
Function that takes in an array of words, a word to look for, a lower bound and higher bound. It uses 
binary search to look for the word in the words array and returns the index of that word in the array
or -1 if it does not find it
*/
int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    
    // loop that keeps running until word is found(binary search)
    while (loInd <= hiInd) {
        int midInd = loInd + (hiInd - loInd) / 2;
        int cmp = strcmp(words[midInd], aWord);

        // finds word and returns index
        if (cmp == 0) {
            return midInd;
        }
        // increases lower bound
        else if (cmp < 0) {
            loInd = midInd + 1;
        }
        // decreases higher bound
        else {
            hiInd = midInd - 1;
        }
    }
    return -1;  //did not find word
}

/*
Function that takes no parameters and tests the findWord() function. It returns true if the
tests passed and false if they fail
*/
bool test_findWord() {
    char* words[] = {"aim", "air", "are", "bar", "bye", "car", "cry", "dab", "dad",
    "ego", "egg"};
    int index = findWord(words, "bar", 0, 10);
    // returns false if function call does not match expected result
    if (index != 3) {
        printf("Expected value does not match actual value");
        return false;
    }

    index = findWord(words, "arm", 0, 10);
    // returns false if function call does not match expected result
    if (index != -1) {
        printf("Expected value does not match actual value");
        return false;
    } 

    return true;
}

/*
Function that takes in an array of words, and number of words and frees the memory taking by the words
array. It returns void
*/
void freeWords(char** words, int numWords) {
    
    // loops through the words array and frees the memory at each index
    for (int i = 0; i < numWords; ++i) {
        free(words[i]);
    }
    free(words);
}

/*
Function that takes in a ladder and a new word as parameters. It inserts the new word at the front of the
ladder. It returns void
*/
void insertWordAtFront(WordNode** ladder, char* newWord) {
    
    WordNode* newNode = (WordNode*)malloc(sizeof(WordNode)); //creates memory for the new word
    
    newNode -> myWord = newWord;
    newNode -> next = *ladder;
    *ladder = newNode; // makes the new node the head of the ladder
}

/*
Function that takes no parameters and tests the insertWordAtFront() function. It returns true if the
tests passed and false if they fail
*/
bool test_insertWordAtFront() {
    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, "cat");
    // returns false if function call does not match expected result
    if (strcmp(ladder -> myWord, "cat") != 0) {
        printf("Test failed");
        return false;
    }

    insertWordAtFront(&ladder, "dog");
    // returns false if function call does not match expected result
    if (strcmp(ladder -> myWord, "dog") != 0) {
        printf("Test failed");
        return false;
    }

    return true;
}

/*
Function that takes in a ladder as a parameter and gets the height of the ladder. It returns the height 
of the ladder
*/
int getLadderHeight(WordNode* ladder) {
    
    int height = 0;
    // loops through the ladder until null and counts the number of words in the ladder
    while (ladder != NULL) {
        height ++;
        ladder = ladder -> next;
    }

    return height;
}


/*
Function that takes in a ladder as a parameter. It frees all the memory allocated in the ladder. It 
returns void
*/
void freeLadder(WordNode* ladder) {
    
    WordNode* current = ladder;
    // loops through ladder and frees up each space 
    while (current != NULL) {
        WordNode* temp = current -> next;
        free(current);
        current = temp;
    }
}

/*
Function that takes no parameters and tests the getLadderHeight() function. It returns true if the
tests passed and false if they fail
*/
bool test_getLadderHeight() {
    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, "word1");
    insertWordAtFront(&ladder, "word2");

    if (getLadderHeight(ladder) != 2) {
        // returns false if function call does not match expected result
        printf("Expected value does not match actual value");
        freeLadder(ladder);
        return false;
    }

    freeLadder(ladder);
    return true;
}

/*
Function that takes in a ladder as a parameter. It allocates new space for each word in the ladder and 
creates a copy of the ladder. it returns the copied ladder
*/
WordNode* copyLadder(WordNode* ladder) {

    WordNode* newLadder = malloc(sizeof(WordNode)); //creates memory for new ladder
    newLadder -> myWord = ladder -> myWord;
    newLadder -> next = NULL;
    WordNode* current = ladder -> next;
    WordNode* newCurrent = newLadder;

    // loops through old ladder and copies the contents over to the new ladder
    while (current != NULL) {
        WordNode* newNode = malloc(sizeof(WordNode));
        newNode -> myWord = current -> myWord;
        newNode -> next = NULL;
        newCurrent -> next = newNode;
        newCurrent = newNode;
        current = current -> next;
    }

    return newLadder;
}

/*
Function that takes no parameters and tests the copyLadder() function. It returns true if the
tests passed and false if they fail
*/
bool test_copyLadder() {
    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, "copy");
    WordNode* copiedLadder = copyLadder(ladder);
    // returns false if function call does not match expected result
    if (strcmp(copiedLadder -> myWord, "copy") != 0) {
        printf("Test failed");
        return false;
    }

    return true;
}



/*
Function that takes in a list of ladders and a new ladder as parameters. It inserts the new ladder to the
back of the list of ladders. It returns void
*/
void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    
    LadderNode* newNode = (LadderNode*)malloc(sizeof(LadderNode)); // creates space for ladder
    newNode -> topWord = newLadder;
    newNode -> next = NULL;
    
    // inserts list if list is empty
    if (*list == NULL) {
        *list = newNode;
        return;
    }
    
    LadderNode* current = *list;
    // finds last list 
    while (current -> next != NULL) {
        current = current -> next;
    }

    current -> next = newNode; // makes the next list the new node
}

/*
Function that takes no parameters and tests the insertLadderAtBack() function. It returns true if the
tests passed and false if they fail
*/
bool test_insertLadderAtBack() {
    LadderNode* list = NULL;
    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, "word1");
    insertLadderAtBack(&list, ladder);
    // returns true if function call matches expected result and false otherwise
    if (list != NULL && strcmp(list -> topWord -> myWord, "word1") == 0) {
        return true;
    }
    else {
        printf("Test failed!");
        return false;
    }
}

/*
Function that takes in a list of ladders as a parameters. It removes the first ladder and returns it
*/
WordNode* popLadderFromFront(LadderNode** list) {

    LadderNode* head = *list;
    WordNode* ladder = head -> topWord;
    *list = head -> next; //sets the list to the next
    free(head); // frees memory at the old list head

    return ladder;
}

/*
Function that takes no parameters and tests the popLadderFromFront() function. It returns true if the
tests passed and false if they fail
*/
bool test_popLadderFromFront() {
    LadderNode* list = NULL;
    WordNode* ladder = NULL;
    insertWordAtFront(&ladder, "first");
    insertLadderAtBack(&list, ladder);

    WordNode* poppedLadder = popLadderFromFront(&list);
    // returns false if function call does not match expected result
    if (strcmp(poppedLadder -> myWord, "first") != 0) {
        printf("Test failed");
        return false;
    }
    freeLadder(poppedLadder);
    // checks if list is empty
    if (list != NULL) {
        printf("Test failed");
        return false;
    }

    return true;
}

/*
Function that takes in a list of ladders. It frees the space taken by each ladder. It returns void
*/
void freeLadderList(LadderNode* myList) {
    
    // loops over the list and frees the memory at each ladder
    while (myList != NULL) {
        LadderNode* nextLadder = myList -> next;
        freeLadder(myList -> topWord);
        free(myList);
        myList = nextLadder;
    }
}

/*
Function that takes in an array of words, a word that has been used in the previous ladder, number of 
words, size of word, the starting word and the final word. It finds the shortest ladder and returns a
pointer to it
*/
WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {

    LadderNode* myList = NULL;
    WordNode* myLadder = NULL;
    insertWordAtFront(&myLadder, startWord);
    insertLadderAtBack(&myList, myLadder);
    // loops over the words and checks if the start word and word at the index are the same
    for (int usedIndex = 0; usedIndex < numWords; ++usedIndex) {
        // checks if the start word and word at the index are the same
        if (strcmp(words[usedIndex], startWord) == 0) {
            usedWord[usedIndex] = true;
            break;
        }
    }

    //loops through list until shortest ladder is found
    while (myList) {
        WordNode* currentLadder = popLadderFromFront(&myList);
        char* currentWord = currentLadder -> myWord;

        // loop to generate neighbors of current word
        for (int neighIndex = 0; neighIndex < wordSize; ++neighIndex) {
            char origChar = currentWord[neighIndex];
            char tempWord[wordSize + 1];
            strcpy(tempWord, currentWord);
            // loops over letters of the alphabet
            for (char letter = 'a'; letter <= 'z'; ++letter) {
                if (letter == origChar) {
                    continue;
                }
                tempWord[neighIndex] = letter;
                int wordIndex = findWord(words, tempWord, 0, numWords - 1);

                if (wordIndex != -1 && !usedWord[wordIndex]) {
                    // checks if final word has been found
                    if (strcmp(tempWord, finalWord) == 0) {
                        insertWordAtFront(&currentLadder, finalWord);
                        freeLadderList(myList);
                        return currentLadder;
                    }

                    WordNode* newLadder = copyLadder(currentLadder);
                    insertWordAtFront(&newLadder, words[wordIndex]);
                    insertLadderAtBack(&myList, newLadder);
                    usedWord[wordIndex] = true;
                }
            }
            tempWord[neighIndex] = origChar;
        }
        freeLadder(currentLadder);
    }
     
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}

/*
Function that has no parameters and calls all the tests for the 
functions and returns void
*/
void callTests() {
    printf("Testing countWordsOfLength()...\n");
    // tests number of words in a file of a particular size
    if (test_countWordsOfLength()) {
        printf("All tests PASSED!\n");
    }
    else {
        printf("test FAILED\n");
    }

    printf("Testing findWord()...\n");
    // tests finding a word in an array
    if (test_findWord()) {
        printf("All tests PASSED!\n");
    }
    else {
        printf("test FAILED\n");
    }

    printf("Testing insertWordAtFront()...\n");
    // tests inputting a word at the front of a ladder
    if (test_insertWordAtFront()) {
        printf("All tests PASSED!\n");
    }
    else {
        printf("test FAILED\n");
    }

    printf("Testing getLadderHeight()...\n");
    // tests getting the height of a ladder
    if (test_getLadderHeight()) {
        printf("All tests PASSED!\n");
    }
    else {
        printf("test FAILED\n");
    }

    printf("Testing copyLadder()...\n");
    // tests if a ladder has been copied correctly
    if (test_copyLadder()) {
        printf("All tests PASSED!\n");
    }
    else {
        printf("test FAILED\n");
    }

    printf("Testing insertLadderAtBack()...\n");
    // tests inputting a ladder at the end of a list
    if (test_insertLadderAtBack()) {
        printf("All tests PASSED!\n");
    }
    else {
        printf("test FAILED\n");
    }

    printf("Testing popLadderFromFront()...\n");
    // tests removing the first ladder in the list
    if (test_popLadderFromFront()) {
        printf("All tests PASSED!\n");
    }
    else {
        printf("test FAILED\n");
    }
}


int main(int argc, char* argv[]) {
    srand((int)time(0));

    bool testMode = false;
    // checks second argument of command line
    if (argc >= 2 && strcmp(argv[1], "-t") == 0) {
        testMode = true;
    }

    // checks if test mode is turned on
    if (testMode == true) {
        callTests();
        return 0;
    }
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
