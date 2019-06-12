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

/*
 * bookaNew
 * @return IBookArray
 */
IBookArray bookaNew() {
    IBookArray this = calloc(1, sizeof(struct BookArray));
    this->next = NULL;
    return this;
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
    if (this->books[BOOK_ARRAY_DEFAULT_SIZE-1 ]!=NULL) {
        if (this->next==NULL) grow(this);
        bookaAppend(this->next, book);
    } else {
        for (int i = 0; i < BOOK_ARRAY_DEFAULT_SIZE; ++i) {
            if (this->books[i] == NULL) {
                this->books[i] = book;
                break;
            }
        }
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
    for(int i=0;i<bookaSize(this);i++){
        if(this->books[i]==book){
            indexOfBook = i;
            break;
        }
    }
    return indexOfBook;
}

/*
 * bookaInsertAt
 */
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

/*
 * bookaRemoveAt
 */
void bookaRemoveAt(IBookArray this, int i) {
    if(i>=BOOK_ARRAY_DEFAULT_SIZE && this->next != NULL) {
        bookaRemoveAt(this, BOOK_ARRAY_DEFAULT_SIZE - i);
    } else if (i < BOOK_ARRAY_DEFAULT_SIZE) {
        if (this->books[i+1] != NULL) {
            this->books[i] = this->books[i+1];
            bookaRemoveAt(this ,i+1);
        } else {this->books[i] = NULL;}
    }

}

/*
 * bookaRemoveLast
 */
void bookaRemoveLast(IBookArray this) {
    int quantityOfBooks = bookaSize(this);
    bookaRemoveAt(this, quantityOfBooks-1);
}

/*
 * bookaSet
 */
void bookaSet(IBookArray this, int i, IBook book) {
    if (i >= BOOK_ARRAY_DEFAULT_SIZE) {
        if (this->next == NULL) grow(this);
        bookaSet(this->next, i - BOOK_ARRAY_DEFAULT_SIZE, book);
    } else { this->books[i] = book; }
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
