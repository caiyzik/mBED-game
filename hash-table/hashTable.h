#pragma once

typedef unsigned int (*HashFunction)(unsigned int key);

class HashTable{
	
	private:

		class HashTableEntry{
			public:
			unsigned int key;
			void* value;
			HashTableEntry* next; 
			
			HashTableEntry(unsigned int key, void* value, HashTableEntry *next){
				this->key = key;
				this->value = value;
				this->next = nullptr;
			};

			//the hashtable class will get rid of the "pointer to the entry itself"
			//what if value is an array?
			~HashTableEntry(){
				//if (value){delete value;}
			}; 

		};

	private: 
		HashTableEntry** buckets;
		HashFunction hash;
		unsigned int num_buckets;
		static HashTableEntry* createHashTableEntry(unsigned int, void*); //unneeded?
		HashTableEntry* findItem(unsigned int); //why does it need to be static?

	public: 
		HashTable(HashFunction, unsigned int ); //constructor, createHashTable
		~HashTable();
		void* insertItem(unsigned int, void*);
		void* getItem(unsigned int);
		void* removeItem(unsigned int);
		void deleteItem(unsigned int);

		
};