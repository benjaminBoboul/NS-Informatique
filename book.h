#ifndef BOOK_H_
#define BOOK_H_

#include <stdbool.h>

typedef struct Book *IBook;
IBook bookNew(const char *title);
void bookDelete(IBook this);
const char *bookTitle(IBook this);

#endif /* BOOK_H_ */
