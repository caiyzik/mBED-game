#include "hashTable.h"
#include "gtest/gtest.h"
#include <iostream>

#define BUCKET_NUM  3

// Dummy value to store in hash table entry
// Please beware that any type of data (e.g. int, double, struct and etc.) can
// be stored in hash table for testing your hash table. Only the pointer to
// the data will be stored in the HashTableEntry.
struct HTItem {};

// Helper function for creating a lot of dummy values.
void make_items(HTItem* result[], unsigned n)
{
	// Populate the array with pointers to the dummy values.
	while(n--)
	{
		result[n] = (HTItem*) malloc(sizeof(HTItem));
	}
}

// A simple hash function that maps a positive number to an integer between 0~(BUCKET_NUM-1).
unsigned int hash(unsigned int key) {
  return key%BUCKET_NUM;
}

////////////////////////
// Initialization tests
////////////////////////
TEST(InitTest, CreateDeleteHashTable)
{
	HashTable* ht = new HashTable(hash, BUCKET_NUM);
	delete ht;
}


////////////////
// Access tests
////////////////
TEST(AccessTest, GetKey_TableEmpty)
{
  HashTable* ht = new HashTable(hash, BUCKET_NUM);

  // Test when table is empty.
  EXPECT_EQ(NULL, ht->getItem(0));
  EXPECT_EQ(NULL, ht->getItem(1));
  EXPECT_EQ(NULL, ht->getItem(2));

  // Test with index greater than the number of buckets.
  EXPECT_EQ(NULL, ht->getItem(10));

  delete ht;
}


TEST(AccessTest, GetSingleKey)
{
  HashTable* ht = new HashTable(hash, BUCKET_NUM);

  // Create a list of items to add to hash table.
	size_t num_items = 1;
	HTItem* m[num_items];
	make_items(m, num_items);

	// Insert one item into the hash table.
  ht->insertItem(0, m[0]);

	// Test if the correct value can be retrieved from hash table with its key.
  EXPECT_EQ(m[0], ht->getItem(0));

  delete ht;
}


TEST(AccessTest, GetKey_KeyNotPresent)
{
  HashTable* ht = new HashTable(hash, BUCKET_NUM);

  // Create a list of items to add to hash table.
	size_t num_items = 1;
	HTItem* m[num_items];
	make_items(m, num_items);

	// Insert one item into the hash table.
	ht->insertItem(0, m[0]);

	// Test if the hash table returns NULL when the key is not found.
  EXPECT_EQ(nullptr, ht->getItem(1));

  delete ht;
}


////////////////////////////
// Removal and delete tests
////////////////////////////
TEST(RemoveTest, SingleValidRemove)
{
  HashTable* ht = new HashTable(hash, BUCKET_NUM);

  // Create a list of items to add to hash table.
	size_t num_items = 1;
	HTItem* m[num_items];
	make_items(m, num_items);

	// Insert one item into the hash table.
	ht->insertItem(0, m[0]);

	// After removing an item with a specific key, the data stored in the
	// corresponding entry should be returned. If the key is not present in the
	// hash table, then NULL should be returned.
  void* data = ht->removeItem(0);

	// Since the key we want to remove is present in the hash table, the correct
	// data should be returned.
  EXPECT_EQ(m[0], data);

  delete ht;
}


TEST(RemoveTest, SingleInvalidRemove)
{
  HashTable* ht = new HashTable(hash, BUCKET_NUM);

	// When the hash table is empty, the remove funtion should still work.
  EXPECT_EQ(nullptr, ht->removeItem(1));

  delete ht;
}


///////////////////
// Insersion tests
///////////////////
TEST(InsertTest, InsertAsOverwrite)
{
  HashTable* ht = new HashTable(hash, BUCKET_NUM);

  // Create list of items to be added to the hash table.
  size_t num_items = 2;
  HTItem* m[num_items];
	make_items(m, num_items);

	// Only insert one item with key=0 into the hash table.
  ht->insertItem(0, m[0]);

	// When we are inserting a different value with the same key=0, the hash table
	// entry should hold the new value instead. In the test case, the hash table entry
	// corresponding to key=0 will hold m[1] and return m[0] as the return value.
  EXPECT_EQ(m[0], ht->insertItem(0, m[1]));

	// Now check if the new value m[1] has indeed been stored in hash table with
	// key=0.
  EXPECT_EQ(m[1], ht->getItem(0));

   delete ht;
}
