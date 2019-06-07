#include "book.h"
#include <stdlib.h>
#include <string.h>

struct Book {
	char *title;
};

IBook bookNew(const char *title) {
	IBook this = calloc(1, sizeof(struct Book));
	this->title = strdup(title);
    // (*this).title eqv
	return this;
}

void bookDelete(IBook this) {
	free(this->title);
	free(this);
}

const char *bookTitle(IBook this) {
	return this->title;
}
