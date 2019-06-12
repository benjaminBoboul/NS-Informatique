#include "bookArray.h"
#include "CuTest.h"
#include <stdio.h>
#include <stdlib.h>

static const char *titles[3] = {
	"Vingt mille lieues sous les mers.",
	"De la Terre à la Lune.",
	"Le tour du monde en 80 jours."
};

IBook book1, book2, book3;
IBookArray books;

static void before() {
	book1 = bookNew(titles[0]);
	book2 = bookNew(titles[1]);
	book3 = bookNew(titles[2]);
}

static void after() {
	bookDelete(book1);
	bookDelete(book2);
	bookDelete(book3);
	bookaDelete(books);
}

static void testNew(CuTest *tc) {
	before();
	books = bookaNew();
	int res = bookaSize(books);
	CuAssertIntEquals(tc, 0, res);
	res = bookaIndexOf(books, NULL);
	CuAssertIntEquals(tc, -1, res);
	res = bookaIndexOf(books, book1);
	CuAssertIntEquals(tc, -1, res);
	after();
}

static void testAppend(CuTest *tc) {
	IBook book;
	before();
	books = bookaNew();
	bookaAppend(books, book1);
	bookaAppend(books, book2);
	bookaAppend(books, book3);
	int res = bookaSize(books);
	CuAssertIntEquals(tc, 3, res);
	book = bookaGet(books, 0);
	CuAssertPtrEquals(tc, book1, book);
	book = bookaGet(books, 1);
	CuAssertPtrEquals(tc, book2, book);
	book = bookaGet(books, 2);
	CuAssertPtrEquals(tc, book3, book);
	after();
}

static void testGrow(CuTest *tc) {
	IBook book;
	int i;
	before();
	books = bookaNew();
	for (i=0; i<30; i++)
        bookaAppend(books, book1);
    int res = bookaSize(books);
	CuAssertIntEquals(tc, 30, res);
	for (i=0; i<30; i++) {
		book = bookaGet(books, i);
		CuAssertPtrEquals(tc, book1, book);
	}
	after();
}

static void testInsert(CuTest *tc) {
	int res;
	before();
	books = bookaNew();
	bookaInsertAt(books, 0, book1); // 1
	bookaInsertAt(books, 0, book2); // 2 1
	bookaInsertAt(books, 1, book3); // 2 3 1
	res = bookaIndexOf(books, book1);
	CuAssertIntEquals(tc, 2, res);
	res = bookaIndexOf(books, book2);
	CuAssertIntEquals(tc, 0, res);
	res = bookaIndexOf(books, book3);
	CuAssertIntEquals(tc, 1, res);
	after();
}

static void testRemove(CuTest *tc) {
	int res;
	IBook book;
	before();
	books = bookaNew();
	bookaInsertAt(books, 0, book1); // 1
	bookaInsertAt(books, 0, book2); // 2 1
	bookaInsertAt(books, 1, book3); // 2 3 1
	bookaRemoveAt(books, 1);		// 2 1
	res = bookaSize(books);
	CuAssertIntEquals(tc, 2, res);
	book = bookaGet(books, 0);
	CuAssertPtrEquals(tc, book2, book);
	book = bookaGet(books, 1);
	CuAssertPtrEquals(tc, book1, book);
	bookaRemoveAt(books, 1);		// 2
	res = bookaSize(books);
	CuAssertIntEquals(tc, 1, res);
	book = bookaGet(books, 0);
	CuAssertPtrEquals(tc, book2, book);
	bookaRemoveAt(books, 0);		// <vide>
	res = bookaSize(books);
	CuAssertIntEquals(tc, 0, res);
	after();
}

static void testRemoveLast(CuTest *tc) {
	IBook book;
	before();
	books = bookaNew();
	bookaAppend(books, book1);
	bookaAppend(books, book2);
	bookaAppend(books, book3);
	// remove
	bookaRemoveLast(books);		// 3
	int res = bookaSize(books);
	CuAssertIntEquals(tc, 2, res);
	book = bookaGet(books, 0);
	CuAssertPtrEquals(tc, book1, book);
	book = bookaGet(books, 1);
	CuAssertPtrEquals(tc, book2, book);
	bookaRemoveLast(books);		// 2
	res = bookaSize(books);
	CuAssertIntEquals(tc, 1, res);
	book = bookaGet(books, 0);
	CuAssertPtrEquals(tc, book1, book);
	bookaRemoveLast(books);		// 1
	res = bookaSize(books);
	CuAssertIntEquals(tc, 0, res);
	after();
}

static void testSet(CuTest *tc) {
	int res;
	IBook book;
	before();
	books = bookaNew();
	bookaInsertAt(books, 0, book1); // 1
	bookaInsertAt(books, 0, book2); // 2 1
	bookaInsertAt(books, 1, book3); // 2 3 1
	bookaSet(books, 0, book1);		// 1 3 1
	bookaSet(books, 1, book2);		// 1 2 1
	bookaSet(books, 2, book3);		// 1 2 3
	res = bookaSize(books);
	CuAssertIntEquals(tc, 3, res);
	book = bookaGet(books, 0);
	CuAssertPtrEquals(tc, book1, book);
	book = bookaGet(books, 1);
	CuAssertPtrEquals(tc, book2, book);
	book = bookaGet(books, 2);
	CuAssertPtrEquals(tc, book3, book);
	after();
}

int main() {
	CuSuite *suite = CuSuiteNew();
	CuString *output = CuStringNew();
	SUITE_ADD_TEST(suite, testNew);
	SUITE_ADD_TEST(suite, testAppend);
	/*SUITE_ADD_TEST(suite, testGrow);
	SUITE_ADD_TEST(suite, testInsert);
	SUITE_ADD_TEST(suite, testRemove);
	SUITE_ADD_TEST(suite, testRemoveLast);
	SUITE_ADD_TEST(suite, testSet);*/
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}
