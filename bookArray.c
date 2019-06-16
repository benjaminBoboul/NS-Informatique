#include <assert.h>
#include "bookArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define IS_EMPTY == NULL
#define BOOK_ARRAY_SIZE 10

/*
 * BookArray
 */
struct BookArray {
    IBook books[BOOK_ARRAY_SIZE];
    struct BookArray *next;
};

/*
 * bookaNew
 * @return IBookArray
 */
IBookArray bookaNew() {
    return calloc(1, sizeof(struct BookArray)); // return allocated memory's pointer
}

/*
 * bookaDelete
 */
void bookaDelete(IBookArray this) {
    if (this->next != NULL) bookaDelete(this->next);
    free(this);
}

/*
 * bookaAppend
 */
void bookaAppend(IBookArray this, IBook book) {
    int lastItemInCurrentArray = BOOK_ARRAY_SIZE - 1;
    if (this->books[lastItemInCurrentArray] IS_EMPTY) {
        for (int i = 0; i < BOOK_ARRAY_SIZE; ++i) {
            if (this->books[i] IS_EMPTY) {
                this->books[i] = book;
                break;
            }
        }
    } else {
        if (this->next IS_EMPTY) grow(this);
        bookaAppend(this->next, book);
    }
}

/*
 * bookaGet
 */
IBook bookaGet(IBookArray this, int i) {
    IBook book;
    if (i >= BOOK_ARRAY_SIZE) {
        if (this->next IS_EMPTY) book = NULL;
        else book = bookaGet(this->next, i - BOOK_ARRAY_SIZE);
    } else {
        book = this->books[i];
    }
    return book;
}

/*
 * bookaIndexOf
 */
int bookaIndexOf(IBookArray this, IBook book) {
    signed int temporaryIndexOfBookInNextArray = -1, indexOfBook = -1;
    for (int i = 0; i < bookaSize(this); i++) {
        if (this->books[i] == book) {
            indexOfBook = i;
            break;
        }
    }
    // if the book isn't found in the current array and the pointer lead to another structure.
    if (indexOfBook == -1 && this->next != NULL)
        temporaryIndexOfBookInNextArray = bookaIndexOf(this->next, book);
    // if the next structure found the book, else
    return temporaryIndexOfBookInNextArray != -1 ?
        BOOK_ARRAY_SIZE + temporaryIndexOfBookInNextArray :
        indexOfBook;
}

/*
 * bookaInsertAt
 */
void bookaInsertAt(IBookArray this, int i, IBook book) {
    if (i >= BOOK_ARRAY_SIZE) {
        if (this->next IS_EMPTY) grow(this);
        bookaInsertAt(this->next, i - BOOK_ARRAY_SIZE, book);
    } else {
        if (this->books[i] != NULL) bookaInsertAt(this, i + 1, this->books[i]);
        this->books[i] = book;
    }
}

/*
 * bookaRemoveAt
 */
void bookaRemoveAt(IBookArray this, int i) {
    if (i < BOOK_ARRAY_SIZE || this->next IS_EMPTY) {
        if (i < BOOK_ARRAY_SIZE) {
            if (this->books[i + 1] IS_EMPTY) { this->books[i] = NULL; }
            else {
                this->books[i] = this->books[i + 1];
                bookaRemoveAt(this, i + 1);
            }
        }
    } else {
        bookaRemoveAt(this, BOOK_ARRAY_SIZE - i);
    }
}

/*
 * bookaRemoveLast
 */
void bookaRemoveLast(IBookArray this) {
    int quantityOfBooks = bookaSize(this);
    bookaRemoveAt(this, quantityOfBooks - 1);
}

/*
 * bookaSet
 */
void bookaSet(IBookArray this, int i, IBook book) {
    if (i >= BOOK_ARRAY_SIZE) {
        if (this->next IS_EMPTY) grow(this);
        bookaSet(this->next, i - BOOK_ARRAY_SIZE, book);
    } else { this->books[i] = book; }
}

/*
 * bookaSize
 */
int bookaSize(IBookArray this) {
    unsigned int sizeOfTotalBookArray = 0;
    if (this->next IS_EMPTY) while (this->books[sizeOfTotalBookArray] != NULL) sizeOfTotalBookArray++;
    else sizeOfTotalBookArray = BOOK_ARRAY_SIZE + bookaSize(this->next);
    return sizeOfTotalBookArray;
}

/*
 * grow
 */
void grow(IBookArray this) {
    this->next = bookaNew();
}
