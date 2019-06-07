# NS-Informatique

### Introduction

Le langage C autorise une modularité poussée grâce à l'approche suivante. Pour un module `book`, on déclare `IBook` dans le fichier d'en-tête `book.h`... 

```c
typedef struct Book *IBook;
```

... et `struct Book` dans `book.c` : 

```c
struct Book {
        char *title;
        etc...
};
```

Pour utiliser le module `book`, un programme library par exemple, inclut le fichier d'en-tête `book.h`, le mode d'emploi du module qui contient les signatures des fonctions. Il sait qu'`IBook` est un type pointeur de `struct Book` mais ne sait pas de quels champs `struct Book` est composé. Il lui est donc interdit d'accéder à ces champs.... 

```
Dereferencing pointer to incomplete type
```

 ...et c'est bien le but recherché (cf. `private` de Java). Pour manipuler un objet `book`, il est donc contraint de n'utiliser que les fonctions prévues par `book.h` : 

```c
IBook bookNew(const char *title);
void bookDelete(IBook this);
const char *bookTitle(IBook this);
```

Le fichier `book.c` est le seul à avoir accès à `struct Book` et il définit les fonctions listées par `book.h`, par exemple, l'équivalent d'un constructeur : 

```c
IBook bookNew(const char *title) {
        IBook this = calloc(1, sizeof(struct Book));
        this->title = strdup(title);
        etc...
        return this;
}
```

La fonction `bookDelete` récupère avec `free` la mémoire allouée par `calloc` et `strdup`. 

```c
void bookDelete(IBook this) {
        free(this->title);
        free(this);
}
```

La fonction `bookTitle` retourne le titre (`const` rend cette chaîne non modifiable) : 

```c
const char *bookTitle(IBook this) {
        return this->title;
}
```

NB : les fonctions présentes dans `book.c` n'ont pas toutes vocation à avoir leur signature dans `book.h` ; certaines ne relèvent que de la "cuisine interne" de `book.c`. Dans ce cas, non seulement on ne met pas leur signature dans `book.h` mais en plus on les déclare static, ce qui renforce leur côté "privé". 

### Travail à faire

On fournit le code de départ sous forme de zip d'un dossier projet C Library, directement importable dans eclipse mais l'utilisation d'eclipse n'est pas imposée. Une fois dézippé, on peut considérer le dossier Library comme un dossier ordinaire.

Réaliser un module `bookArray`, donc composé des fichiers `bookArray.h` et `bookArray.c` en utilisant cette approche. Ce module fournit les services d'un tableau de taille variable :

```c
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
```

Initialement, un `bookArray` ne contient rien mais a une capacité de stockage de 10. On peut stoker plus de 10 `books`, une fonction `grow` interne fait croître le capacité de stockage de 10 au fur et à mesure des besoins.

### Développement guidé par les tests 

On utilise une méthode de développement guidé par des tests unitaires. Les tests sont fournis. Ils sont écrits sous forme de fonctions du fichier `bookArrayTest.c`. Les fonctions du module de test appellent des fonctions du module testé (`bookArray.c`) et vérifient que leur comportement est bien celui attendu. Les fonctions de vérification sont fournies sous forme de code source (module `CuTest`).

Les tests ne sont pas exhaustifs,
 * donc quand tous les tests passent OK, cela ne prouve pas l'absence de bugs (défauts dans le comportement).
 * En revanche, quand un test ne passe pas OK, cela prouve la présence d'un bug. 

### Compiler 

Pour compiler, on a besoin d'un compilateur C, d'une ligne de commandes et d'un éditeur de texte. Le compilateur C gcc est disponible sous `Linux`, `MacOSX` et `Windows`. Le dossier de la commande `gcc` doit être listé dans la variable d'environnement `PATH`. Si tous les fichiers sont dans le même dossier, il suffit de passer les commandes suivantes : 

```bash
gcc -c book.c
gcc -c bookArray.c
gcc -c CuTest.c
gcc -c bookArrayTest.c
gcc -o Library.exe book.o bookArray.o CuTest.o bookArrayTest.o
```

Les quatre premières compilent séparément les fichiers `.c` ce qui produit les fichiers `.o` de même nom. Les warnings relatifs à `CuTest` ne doivent pas inquiéter : 

```
..\tests\CuTest.c:274:15: warning: unknown conversion type character 'l' in format [-Wformat=]
  sprintf(buf, "expected <%lld> but was <%lld>", expected, actual);
               ^
..\tests\CuTest.c:274:15: warning: unknown conversion type character 'l' in format [-Wformat=]
..\tests\CuTest.c:274:15: warning: too many arguments for format [-Wformat-extra-args]
```

La dernière commande rassemble les fichiers compilés et produit l'exécutable de test Library. L'extension `.exe` est propre à `Windows` ; elle n'est pas nécessaire sous `Unix`. 

L'exécution se fait en tapant le nom de l'exécutable :

`./Library` sous Unix
`Library.exe` sous Windows

En cas de défaut de l'objet testé, le programme de test affiche la valeur attendue et la valeur trouvée ainsi que la ligne à laquelle le défaut a été constaté : 

```
..F.F...

There were 2 failures:
1) testNewInit: ..\tests\bookArrayTest.c:64: expected <0> but was <-1>
2) testIndexOf: ..\tests\bookArrayTest.c:86: expected <2> but was <1>

!!!FAILURES!!!
Runs: 8 Passes: 6 Fails: 2
```

 Si un élément n'est pas rangé à la bonne place, les valeurs attendue et trouvée seront des adresses : 

```
.....FFF

There were 3 failures:
1) testInsert: ..\tests\bookArrayTest.c:105: expected pointer <0x0000000003098A60> but was <0x0000000003098A20>
2) testRemove: ..\tests\bookArrayTest.c:125: expected pointer <0x0000000003098A40> but was <0x0000000003098C40>
3) testSet: ..\tests\bookArrayTest.c:153: expected pointer <0x0000000003098C00> but was <0x0000000003098C60>

!!!FAILURES!!!
Runs: 8 Passes: 5 Fails: 3
```

Il se peut aussi qu'on n'accède pas à une adresse autorisée. Dans ce cas, le programme de test s'interrompt brutalement parfois sans diagnostic... Il faut alors tenter de cerner la source du problème en réduisant la taille du programme en mettant certaines parties en commentaires. On ne garde que testGrow pour voir si l'arrêt intempestif se produit.

```c
int main() {
        CuSuite *suite = CuSuiteNew();
        CuString *output = CuStringNew();
//      SUITE_ADD_TEST(suite, testNew);
//      SUITE_ADD_TEST(suite, testAppend);
        SUITE_ADD_TEST(suite, testGrow);
//      SUITE_ADD_TEST(suite, testInsert);
//      SUITE_ADD_TEST(suite, testRemove);
//      SUITE_ADD_TEST(suite, testSet);
        CuSuiteRun(suite);
        CuSuiteSummary(suite, output);
        CuSuiteDetails(suite, output);
        printf("%s\n", output->buffer);
}
```

 De la même façon on ne garde que les `bookaAppend` pour voir si le problème se révèle pendant cette phase ou lors des `bookaGet`. 

```c
static void testGrow(CuTest *tc) {
        IBook book;
        int i;
        before();
        books = bookaNew();
        for (i=0; i<30; i++)
                bookaAppend(books, book1);
//      int res = bookaSize(books);
//      CuAssertIntEquals(tc, 30, res);
//      for (i=0; i<30; i++) {
//              book = bookaGet(books, i);
//              CuAssertPtrEquals(tc, book1, book);
//      }
        after();
}
```

 Le problème vient typiquement :
 * d'un pointeur non initialisé ;
 * d'un dépassement des limites d'un tableau ;
 * d'un accès à un bloc mémoire après sa récupération par `free`.

 Une autre technique fait appel à la fonction `assert`. 
 On peut aussi utiliser un IDE comme Eclipse IDE for C/C++ Developers mais il faut quand même installer gcc à part. 

### Évaluation

Le livrable est un zip du fichier `bookArray.c` avec les deux noms dedans :

Un module original pour chaque binôme ! L'évaluation tiendra compte :

1. de la capacité à travailler en C ;
1. du respect de l'approche modulaire poussée ;
1. du résultat obtenu nombre de tests OK ;
1. de la qualité du code :
   - code auto-documenté (c'est-à-dire sans avoir à le commenter)
   - lignes courtes : un seul appel de fonction par ligne ;
   - lisibilité : indentation, noms significatifs, concision, ...
   - efficacité : absence de calculs inutiles, ...
