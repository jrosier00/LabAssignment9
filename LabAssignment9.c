#include <stdlib.h>
#include <stdio.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

// HashType
struct HashType
{
    struct RecordType* head; // head of the chain (linked list)
};

// hash function
int hash(int x, int hashSz)
{
    return x % hashSz;
}

// initialize the hash table
struct HashType* createHashTable(int hashSz)
{
    struct HashType* hashTable = (struct HashType*) malloc(sizeof(struct HashType) * hashSz);
    if (hashTable == NULL)
    {
        printf("Cannot allocate memory\n");
        exit(-1);
    }
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        hashTable[i].head = NULL;
    }
    return hashTable;
}

// insert records into the hash table
void insertRecord(struct HashType* hashTable, struct RecordType* record, int hashSz)
{
    int index = hash(record->id, hashSz);
    record->next = hashTable[index].head;
    hashTable[index].head = record;
}

// display records in the hash structure
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;
    struct RecordType* record;
    for (i=0; i<hashSz; ++i)
    {
        if (pHashArray[i].head != NULL)
        {
            printf("Index %d -> ", i);
            for (record = pHashArray[i].head; record != NULL; record = record->next)
            {
                printf("%d, %c, %d -> ", record->id, record->name, record->order);
            }
            printf("NULL\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // create the hash table
    int hashSz = recordSz; // we'll use the size of the input array as the size of our hash table for simplicity
    struct HashType* hashTable = createHashTable(hashSz);

    // insert all the records into the hash table
    int i;
    for (i = 0; i < recordSz; ++i)
    {
        insertRecord(hashTable, &pRecords[i], hashSz);
    }

    // display the hash table
    displayRecordsInHash(hashTable, hashSz);
    return 0;
}
