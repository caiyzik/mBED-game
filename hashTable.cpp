#include "hashTable.h"
#include <iostream>


HashTable::HashTable(HashFunction hashFunction, unsigned int numBuckets){
	// The hash table has to contain at least one bucket. Exit gracefully if
  	// this condition is not met.
  	if (numBuckets==0) {
    	std::cout << "Hash table has to contain at least 1 bucket..." << std::endl;
    	//exit(1); //WHAT IS THE PROPER EXCEPTION? C++ DOESN'T USE EXIT
  	}

  	// Initialize the components of the new HashTable struct.
  	this->hash = hashFunction;
  	this->num_buckets = numBuckets;
  	this->buckets = new HashTableEntry*[this->num_buckets]; //why do the heads of the buckets need to be dynamically allocated?

  // As the new buckets are empty, init each bucket as NULL.
  	unsigned int i;
  	for (i=0; i<this->num_buckets; ++i) {
    	this->buckets[i] = NULL;
  	}

}

HashTable::~HashTable(){

        //iterate through each bucket and destroy each element
        for (int i = 0; i < this-> num_buckets; i++){
            HashTableEntry* entryptr;
            while(this -> buckets[i]){ //while there is at least one element in the list
                entryptr = this -> buckets[i];
                this -> buckets[i] = entryptr -> next; //increment the head pointer
                //so entry pointer is private
                if (entryptr) delete entryptr; //free the hashtable entry, destructor will delete the value
            }
        }
        delete[] this -> buckets; //free pointer to bucket array
        //free(hashTable); //free hash table struct
}

HashTable::HashTableEntry* HashTable::findItem(unsigned int key){ //should this be implemented inside the class if I want it to be static
	unsigned int ind = hash(key); //get the bucket index
    HashTableEntry* entryptr = buckets[ind]; //get a pointer to the head of the bucket the item is in
    
    while(entryptr){ //while entryptr is not NULL
        if (entryptr-> key == key){
            return entryptr;
        }
        entryptr = entryptr -> next;
    }
    return NULL; //return null pointer if the entry does not exist
}

void* HashTable::insertItem(unsigned int key, void* value) {
    HashTableEntry* entryptr;
    if ((entryptr = findItem(key))){ //if the key is in the hash table
        void* temp = entryptr -> value;
        entryptr -> value = value;
        return temp;
    }
    
    //create entry if key is not in hash table
    entryptr = new HashTableEntry(key, value, NULL); 
    if(entryptr == NULL) return NULL;
    int ind = hash(key);
    
    //insert entry at the head of the linked list
    entryptr -> next = buckets[ind];
    buckets[ind] = entryptr;
    return NULL;

}

void* HashTable::getItem(unsigned int key) {
    HashTableEntry* entryptr;
    entryptr = findItem(key);
    if(entryptr == NULL) return NULL;
    if (entryptr -> value) return entryptr -> value;  //return value at key if key is present in the table
    return NULL;
}

void* HashTable::removeItem(unsigned int key) {
    unsigned int ind = hash(key);
    HashTableEntry* entryptr = buckets[ind];
    if(entryptr == NULL) return NULL; //check if list is empty
    
    //if the item to be removed is at the end of the list
    if(entryptr -> key == key){ //find the key
        buckets[ind] = entryptr -> next; //increment the head pointer
        void* val = entryptr ->value; //store value
        delete entryptr;
        return val;
    }
    
    //if item to be removed is in the middle of the list or at the end of the list
    while(entryptr->next){
        if(entryptr->next->key == key){ //check to see if the next entry matches the key
            HashTableEntry* temp = entryptr ->next;
            entryptr -> next = entryptr ->next->next; //increment entryptr
            void* val = temp -> value;
            delete temp;
            return val;
        }
        entryptr = entryptr ->next;
    }
    return NULL;

}

void HashTable::deleteItem(unsigned int key) {
    unsigned int ind = hash(key);
    HashTableEntry* entryptr = buckets[ind];
    
    //if first item matches the key
    if(entryptr && entryptr -> key == key){
        buckets[ind] = entryptr -> next;
        if(entryptr -> value) delete entryptr ->value; //if the entry still contains a value
        delete entryptr;
    }
    
    //if key is in the middle of or at the end of the list
    while(entryptr && entryptr->next){
        if(entryptr->next->key == key){
            HashTableEntry* temp = entryptr ->next; 
            entryptr -> next = entryptr ->next->next; //increment entryptr
            if(entryptr -> value) delete temp -> value; //if the entry still contains a value
            delete temp;
        }
        entryptr = entryptr ->next;
    }

}
int main(){

}