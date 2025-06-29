#include <stdio.h>
#include <stdlib.h>
#include "HashTable.h"


static const int primes[] = {
    5, 53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593,
    49157, 98317, 196613, 393241, 786433, 1572869, 3145739,
    6291469, 12582917, 25165843, 50331653, 100663319,
    201326611, 402653189, 805306457, 1610612741
};

void HTcreate(HashTable *HT, int size) {

    // finding nearest Prime number
    for (int i = 1; i < sizeof(primes)/sizeof(primes[0]); i++) {
        if (primes[i] >= size) {
            HT->size = primes[i];
            HT->prime = primes[i-1]; //for Hash2
            break;
        }
    }

    HT->amount = 0;
    HT->arr = (HashNode*)malloc(HT->size * sizeof(HashNode));

    // Setting -1 for each cell
    for (int i = 0; i < HT->size; i++) {
        HT->arr[i].id = -1;
    }
}

int hash1(HashTable* HT, int id) {
    return id % HT->size;
}

int hash2(HashTable* HT, int id) {
    return HT->prime - (id % HT->prime);
}


// Interactions with HashTable
HashNode* HTsearch(HashTable* HT, int id) {
    int H1 = hash1(HT, id);
    int H2 = hash2(HT, id);
    int startPosition = H1;
    int firstIteration = 0;
    int max_tries = HT->size * 2;
    int i = 0;

    while (i++ < max_tries && HT->arr[H1].id != -1) {

        // If found cell
        if (HT->arr[H1].id == id) {
            return &HT->arr[H1];

        // If came back to the beginning
        } else if (H1 == startPosition && firstIteration) {
            return NULL;

        // Going forward
        } else {
            H1 = (H1 + H2) % HT->size;
        }
        firstIteration = 1;
    }
    return NULL;
}

void HTinsert(HashTable *HT, int id) {

    if (id < 0) {
        return;
    }

    // If the entire table is filled
    if (HT->size <= 1.5 * HT->amount) {
        int new_size = HT->size * 1.5;

        // Finding nearest prime number
        for (int i = 0; i < sizeof(primes)/sizeof(primes[0]); i++) {
            if (primes[i] >= new_size) {
                new_size = primes[i];
                break;
            }
        }

        HashTable HT_new;
        HTcreate(&HT_new, new_size);
        HashNode* old_arr = HT->arr;
        int old_size = HT->size;

        // Rehashing old elements
        for (int i = 0; i < old_size; i++) {
            if (old_arr[i].id != -1) {
                HTinsert(&HT_new, HT->arr[i].id);
            }
        }

        free(old_arr);
        *HT = HT_new;
    }

    int H1 = hash1(HT, id);
    int H2 = hash2(HT, id);

    // Looking for empty space
    while (HT->arr[H1].id != -1 && HT->arr[H1].id != -2) {

        // Found duplicate
        if (HT->arr[H1].id == id) {
            return;
        }

        H1 = (H1 + H2) % HT->size;
    }

    HT->arr[H1].id = id;
    HT->amount++;
}

void HTdelete(HashTable *HT, int id) {
    HashNode *N1 = HTsearch(HT, id);

    if (N1 == NULL) {
        return;
    }

    N1->id = -2;
    HT->amount--;
}

void HTprint(HashTable *hash) {
    printf("HashTable:\n");
    for (int i = 0; i < hash->size; i++) {
        if (hash->arr[i].id > 0) {
            printf("%d, ", hash->arr[i].id);
        }
    }
    printf("\n");
}


/*
//Hashing functions
int isPrime(int num) {
    if (num < 2) return 0;
    if (num == 2 || num == 3) return 1;
    if (num % 2 == 0) return 0;

    for (int i = 3; i*i <= num; i += 2) {
        if (num % i == 0) return 0;
    }
    return 1;
}


int getPrime(int size) {
    for (int i = size - 1; i >= 2; i--) {
        if (isPrime(i)) return i;
    }
    return 2;
}
*/