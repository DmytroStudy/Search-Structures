#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct HashNode{
    int id;
}HashNode;

typedef struct HashTable {
    HashNode* arr;
    int size;
    int prime;
    int amount; // object's amount
}HashTable;

int isPrime(int num);

int getPrime(int size);

void HTcreate(HashTable *table, int size);


int hash1(HashTable* table, int id);

int hash2(HashTable* table, int id);


HashNode* HTsearch(HashTable* table, int id);

void HTinsert(HashTable *table, int id);

void HTdelete(HashTable *table, int id);

void HTprint(HashTable *hash);

#endif
