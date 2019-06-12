#include <assert.h>
#include "bookArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BOOK_ARRAY_DEFAULT_SIZE 10

struct BookArray {
    IBook books[BOOK_ARRAY_DEFAULT_SIZE];
    struct BookArray *next;
};

IBookArray bookaNew() {
    IBookArray this = calloc(1, sizeof(struct BookArray));
    this->next = NULL;
    return this;
}

/*
 * bookaDelete
 */
void bookaDelete(IBookArray this) {
    free(this);
}

/*
 * bookaAppend
 */
void bookaAppend(IBookArray this, IBook book) {
    /*unsigned int indexOfInsertedBook = 0;
    for (int i = 0; i < BOOK_ARRAY_DEFAULT_SIZE; ++i) {
        if (this->books[i] == NULL) this->books[i] = book; break;
    }*/
    for(int i = 0; i < BOOK_ARRAY_DEFAULT_SIZE;i++){
        if(this->books[i] == NULL && i<=9){
            this->books[i] = book;
            break;
        }else{
            grow(this);
            for (int j=bookaSize(this) - 10;j < bookaSize(this);j++){
                if(this->books[j] != NULL){
                    this->books[j] = book;
                    break;
                }
            }
        }*/
    }
}

/*
 * bookaGet
 */
IBook bookaGet(IBookArray this, int i) {
    if (i >= BOOK_ARRAY_DEFAULT_SIZE && this->next != NULL)
        return bookaGet(this->next, i-BOOK_ARRAY_DEFAULT_SIZE);
    else return this->books[i];
}

/*
 * bookaIndexOf
 */
int bookaIndexOf(IBookArray this, IBook book) {
    signed int indexOfBook = -1;
    return indexOfBook;
}

void bookaInsertAt(IBookArray this, int i, IBook book) {
    IBook old_book;
    if (i >= BOOK_ARRAY_DEFAULT_SIZE) {
        if (this->next == NULL) grow(this);
        bookaInsertAt(this->next, i - BOOK_ARRAY_DEFAULT_SIZE, book);
    } else if (this->books[i] != NULL) {
        old_book = this->books[i];
        this->books[i] = book;
        bookaInsertAt(this, i + 1, old_book);
    } else {
        this->books[i] = book;
    }
}

void bookaRemoveAt(IBookArray this, int i) {
}

void bookaRemoveLast(IBookArray this) {
}

void bookaSet(IBookArray this, int i, IBook book) {
}

int bookaSize(IBookArray this) {
    unsigned int sizeOfTotalBookArray = 0;
    if (this->next != NULL) return BOOK_ARRAY_DEFAULT_SIZE + bookaSize(this->next);
    else while(this->books[sizeOfTotalBookArray] != NULL) sizeOfTotalBookArray++;
    return sizeOfTotalBookArray;
}

void grow(IBookArray this) {
    this->next = bookaNew();
}
