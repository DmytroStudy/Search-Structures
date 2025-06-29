#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "WBTree.h"
#include "RBTree.h"
#include "HashTable.h"

long long generateRandomId() {
    // Collect a 30-bit random number from two rand() calls
    long long high = rand() & 0x7FFF;  // 15 bit
    long long low  = rand() & 0x7FFF;  // other 15 bit
    long long result = (high << 15) | low; // unite two 15 bits

    return result % 2147483647; // max int value
}

int WBTreeRandomTest(int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    WBTree tree;
    WBcreate(&tree);

    for (int i = 0; i < N; i++) {
        int op = rand() % 3; // 0 - insert, 1 - search, 2 - delete
        int randomId = generateRandomId();
        if (op == 0) {
            WBinsert(&tree, randomId);
        }else if (op == 1) {
            WBsearch(&tree, randomId);
        }else if (op == 2) {
            WBdelete(&tree, randomId);
        }
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d random operations in WBTree: %.6f seconds\n", N, time_spent);

    return 0;
}

int RBTreeRandomTest(int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    RBTree tree;
    RBcreate(&tree);

    for (int i = 0; i < N; i++) {
        int op = rand() % 3; // 0 - insert, 1 - search, 2 - delete
        int randomId = generateRandomId();
        if (op == 0) {
            RBinsert(&tree, randomId);
        }else if (op == 1) {
            RBsearch(&tree, randomId);
        }else if (op == 2) {
            RBdelete(&tree, randomId);
        }
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d random operations in RBTree: %.6f seconds\n", N, time_spent);

    return 0;
}

int HashTableRandomTest(int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    HashTable table;
    HTcreate(&table, N/10);

    for (int i = 0; i < N; i++) {
        int op = rand() % 3; // 0 - insert, 1 - search, 2 - delete
        int randomId = generateRandomId();
        if (op == 0) {
            HTinsert(&table, randomId);
        }else if (op == 1) {
            HTsearch(&table, randomId);
        }else if (op == 2) {
            HTdelete(&table, randomId);
        }
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d random operations in HashTable: %.6f seconds\n", N, time_spent);

    return 0;
}


int WBTreeInsertTest(WBTree *tree, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        WBinsert(tree, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d insert operations in WBTree: %.6f seconds\n", N, time_spent);

    return 0;
}

int WBTreeSearchTest(WBTree *tree, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        WBsearch(tree, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d search operations in WBTree: %.6f seconds\n", N, time_spent);

    return 0;
}

int WBTreeDeleteTest(WBTree *tree, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        WBdelete(tree, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d delete operations in WBTree: %.6f seconds\n", N, time_spent);

    return 0;
}


int RBTreeInsertTest(RBTree *tree, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);  // Получаем частоту таймера
    QueryPerformanceCounter(&start);   // Начало измерения

    srand(GetTickCount());  // Инициализация генератора

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        RBinsert(tree, randomId);
    }

    QueryPerformanceCounter(&end);  // Конец измерения

    // Расчёт времени в секундах
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d insert operations in RBTree: %.6f seconds\n", N, time_spent);

    return 0;
}

int RBTreeSearchTest(RBTree *tree, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        RBsearch(tree, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d search operations in RBTree: %.6f seconds\n", N, time_spent);

    return 0;
}

int RBTreeDeleteTest(RBTree *tree, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        RBdelete(tree, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d delete operations in RBTree: %.6f seconds\n", N, time_spent);

    return 0;
}


int HashTableInsertTest(HashTable *table, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        HTinsert(table, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d insert operations in HashTable: %.6f seconds\n", N, time_spent);

    return 0;
}

int HashTableSearchTest(HashTable *table, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        HTsearch(table, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d search operations in HashTable: %.6f seconds\n", N, time_spent);

    return 0;
}

int HashTableDeleteTest(HashTable *table, int N) {
    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    srand(GetTickCount());

    for (int i = 0; i < N; i++) {
        int randomId = generateRandomId();
        HTdelete(table, randomId);
    }

    QueryPerformanceCounter(&end);
    double time_spent = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Time spent on %d delete operations in HashTable: %.6f seconds\n", N, time_spent);

    return 0;
}


int main() {

    // Insert -> Search -> Delete test
    for (int N = 1000; N <= 100000000; N *= 10) {
        WBTree WBtree;
        WBcreate(&WBtree);
        WBTreeInsertTest(&WBtree, N);
        WBTreeSearchTest(&WBtree, N);
        WBTreeDeleteTest(&WBtree, N);
        printf("\n");

        RBTree RBtree;
        RBcreate(&RBtree);
        RBTreeInsertTest(&RBtree, N);
        RBTreeSearchTest(&RBtree, N);
        RBTreeDeleteTest(&RBtree, N);
        printf("\n");


        HashTable table;
        HTcreate(&table, N/10);
        HashTableInsertTest(&table, N);
        HashTableSearchTest(&table, N);
        HashTableDeleteTest(&table, N);
        printf("\n");
    }

    // Random operations test
    for (int N = 1000; N < 1000000000; N *= 10) {
        WBTreeRandomTest(N);
        RBTreeRandomTest(N);;
        HashTableRandomTest(N);
        printf("\n");
    }

    /* Also it can print all nodes of each tree
    WBprint(&WBtree, 2147483647);
    RBprint(&RBtree, 2147483647);
    HTprint(&table, 2147483647);
    */
}
