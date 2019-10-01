/*
 Student Name: Tiffany Montgomery
 Date: 4/4/18

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf

/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
    HashTableEntry* entryptr = (HashTableEntry*)malloc(sizeof(HashTableEntry)); //allocate memory for the hash table entry
    if (entryptr == NULL) return NULL; //if malloc fails return NULL pointer
    
    //initialize hash table entry values
    entryptr->key = key;
    entryptr->value = value;
    entryptr ->next = NULL;
    return entryptr; //return a pointer to the entry
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/

static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
    unsigned int ind = hashTable->hash(key); //get the bucket index
    HashTableEntry* entryptr = hashTable->buckets[ind]; //get a pointer to the head of the bucket the item is in
    
    while(entryptr){ //while entryptr is not NULL
        if (entryptr-> key == key){
            return entryptr;
        }
        entryptr = entryptr -> next;
    }
    return NULL; //return null pointer if the entry does not exist
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  newTable->buckets = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*));

  // As the new buckets are empty, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

void destroyHashTable(HashTable* hashTable) {
    
    //check to see if the hash table has been created
    while(hashTable != NULL){
        
        //iterate through each bucket and destroy each element
        for (int i = 0; i < hashTable -> num_buckets; i++){
            HashTableEntry* entryptr = hashTable ->buckets[i];
            while(entryptr && entryptr->next){
                hashTable -> buckets[i] = entryptr ->next;
                ///Ummm I'm not waling the list here..... find someway to test this
                if(entryptr ->value) free(entryptr ->value);
                free(entryptr);
            }
        }
        free(hashTable -> buckets); //free pointer to bucket array
        free(hashTable); //free hash table struct
        break;
    }
}

void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
    HashTableEntry* entryptr;
    if ((entryptr = findItem(hashTable, key))){
        void* temp = entryptr -> value;
        entryptr -> value = value;
        return temp;
    }
    entryptr = createHashTableEntry(key, value);
    if(entryptr == NULL) return NULL;
    int ind = hashTable -> hash(key);
    entryptr -> next = hashTable -> buckets[ind];
    
    hashTable -> buckets[ind] = entryptr;
    return NULL;

}

void* getItem(HashTable* hashTable, unsigned int key) {
    HashTableEntry* entryptr;
    entryptr = findItem(hashTable, key);
    if(entryptr == NULL) return NULL;
    return entryptr -> value;
}

void* removeItem(HashTable* hashTable, unsigned int key) {
    unsigned int ind = hashTable -> hash(key);
    HashTableEntry* entryptr = hashTable -> buckets[ind];
    if(entryptr == NULL) return NULL;
    if(entryptr -> key == key){
        hashTable -> buckets[ind] = entryptr -> next;
        void* val = entryptr ->value;
        free(entryptr);
        return val;
    }
    while(entryptr->next){
        if(entryptr->next->key == key){
            HashTableEntry* temp = entryptr ->next;
            entryptr -> next = entryptr ->next->next;
            void* val = temp -> value;
            free(entryptr);
            return val;
        }
        entryptr = entryptr ->next;
    }
    return NULL;

}

void deleteItem(HashTable* hashTable, unsigned int key) {
    unsigned int ind = hashTable -> hash(key);
    HashTableEntry* entryptr = hashTable -> buckets[ind];
    if(entryptr && entryptr -> key == key){
        hashTable -> buckets[ind] = entryptr -> next;
        if(entryptr -> value) free(entryptr ->value);
        free(entryptr);
    }
    while(entryptr && entryptr->next){
        if(entryptr->next->key == key){
            HashTableEntry* temp = entryptr ->next;
            entryptr -> next = entryptr ->next->next;
            if(entryptr -> value) free(temp -> value);
            free(entryptr);
        }
        entryptr = entryptr ->next;
    }

}
