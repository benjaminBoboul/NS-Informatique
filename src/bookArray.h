#ifndef BOOKARRAY_H_
#define BOOKARRAY_H_

#include "book.h"

typedef struct BookArray *IBookArray;

IBookArray bookaNew();
void bookaDelete(IBookArray this);
void bookaAppend(IBookArray this, IBook book);
IBook bookaGet(IBookArray, int i);
int bookaIndexOf(IBookArray this, IBook book);
void bookaInsertAt(IBookArray this, int i, IBook book);
void bookaRemoveAt(IBookArray this, int i);
void bookaRemoveLast(IBookArray this);
void bookaSet(IBookArray this, int i, IBook book);
int bookaSize(IBookArray this);

#endif /* BOOKARRAY_H_ */
