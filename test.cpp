// Uncomment the next line to use precompiled headers
#include "pch.h"
#include <iostream>
#include <list>
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue

// Test that a collection is empty when created.
// Prior to calling this (and all other TEST_F defined methods),
//  CollectionTest::StartUp is called.
// Following this method (and all other TEST_F defined methods),
//  CollectionTest::TearDown is called
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer 
TEST_F(CollectionTest, AlwaysFail)
{
    FAIL();
}*/

// TODO: Create a test to verify adding a single value to an empty collection //////////////////////////////////////////////////////////////////
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    // ADD the element to the collection
    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty()); // Verify that the collection received an entry and is not empty

    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1); // Verify the collection size is one since we added only one entry
}

// TODO: Create a test to verify adding five values to collection //////////////////////////////////////////////////////////////////////////////
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    // if empty, the size must be 0
    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    // ADD the elements to the collection
    add_entries(5);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty()); // Verify that the collection received an entry and is not empty

    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5); // Verify the collection size is five
}

// TODO: Create a test to verify that max size is greater than or equal to size for 0, 1, 5, 10 entries ///////////////////////////////////////
TEST_F(CollectionTest, MaxSizeGreaterThanEqualToEntrySize)
{
    int max = collection->max_size();  // identify and store maximum size of the collection
    ASSERT_TRUE(collection->empty());  // Verify the collection is empty

    std::list<int> entry_list = {0,1,4,5}; // list of integers to test the collection size

    // FOR loop to iterate the list and add entries for testing
    for (int i : entry_list)
    {
        add_entries(i); // add the entries from the list, 0+1+4+5 = 10

        ASSERT_EQ(collection->size(), i); // Test that the collection size is equal to the total number of entries
        ASSERT_TRUE(max >= collection->size()); // Verify the max size of the colleciton is greater than or equal to the number of entries
    }
}

// TODO: Create a test to verify that capacity is greater than or equal to size for 0, 1, 5, 10 entries ///////////////////////////////////////
TEST_F(CollectionTest, CapacityGreaterThanEqualEntrySize)
{
    ASSERT_TRUE(collection->empty());  // Verify the collection is empty

    std::list<int> entry_list = { 0,1,4,5 }; // list of integers to test the collection size

    // FOR loop to iterate the list and add entries for testing
    for (int i : entry_list)
    {
        add_entries(i); // add the entries from the list, 0+1+4+5 = 10

        ASSERT_EQ(collection->size(), i); // Test that the collection size is equal to the total number of entries
        ASSERT_TRUE(collection->capacity() >= collection->size()); // Verify the capactiy of the colleciton is greater than or equal to the number of entries
    }
}

// TODO: Create a test to verify resizing increases the collection ////////////////////////////////////////////////////////////////////////////
TEST_F(CollectionTest, DidResizeIncrease)
{
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    collection->resize(5); // resize the vector for testing

    ASSERT_EQ(collection->size(), 5); // Verify the test resized the collection size to 5

}

// TODO: Create a test to verify resizing decreases the collection ////////////////////////////////////////////////////////////////////////////
TEST_F(CollectionTest, DidResizeDecreaseSize)
{
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    add_entries(3); // Add entries for resize test

    EXPECT_FALSE(collection->empty()); // Verify the collection is not empty

    //EXPECT_EQ(collection->size(), 3); // Verify the size is 3

    collection->resize(1); // Resize the collection for testing

    ASSERT_EQ(collection->size(), 1); // Verify the resizing changed the size to 1
}

// TODO: Create a test to verify resizing decreases the collection to zero ///////////////////////////////////////////////////////////////////
TEST_F(CollectionTest, DidResizeDecreaseToZero)
{
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    add_entries(3); // Add entries for resize test

    EXPECT_FALSE(collection->empty()); // Verify the collection is not empty

    EXPECT_EQ(collection->size(), 3); // Verify the size is 3

    collection->resize(0); // Resize the collection for testing

    ASSERT_EQ(collection->size(), 0); // Verify the resizing changed the size to zero
}

// TODO: Create a test to verify clear erases the collection /////////////////////////////////////////////////////////////////////////////////
TEST_F(CollectionTest, DidClearEraseCollection)
{

    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    add_entries(3); // Add entries for test

    EXPECT_FALSE(collection->empty()); // Verify the collection is not empty

    EXPECT_EQ(collection->size(), 3); // Verify the size is 3

    collection->clear(); // Clear the collection

    ASSERT_TRUE(collection->empty()); // Verify the collection is empty

    ASSERT_EQ(collection->size(), 0); // If the collection is empty, Verify the size is zero
}

// TODO: Create a test to verify erase(begin,end) erases the collection//////////////////////////////////////////////////////////////////////////
TEST_F(CollectionTest, VerifyErase)
{
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    add_entries(3); // Add entries for test

    EXPECT_FALSE(collection->empty()); // Verify the collection is not empty

    EXPECT_EQ(collection->size(), 3); // Verify the size is 3

    collection->erase(collection->begin(), collection->end()); // erase the collection beginning to end

    ASSERT_TRUE(collection->empty()); // Verify the collection is empty

    ASSERT_EQ(collection->size(), 0); // If the collection is empty, Verify the size is zero
}

// TODO: Create a test to verify reserve increases the capacity but not the size of the collection////////////////////////////////////////////
TEST_F(CollectionTest, DidReserveIncreaseCapacityButNotSize)
{
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    EXPECT_EQ(collection->capacity(), 0); // Verify Capacity is Zero

    collection->reserve(5); // Reserve 5 spots in the capacity

    ASSERT_TRUE(collection->empty()); // Verify the collection is empty

    ASSERT_EQ(collection->size(), 0); // If the collection is empty, Verify the size is zero

    ASSERT_GT(collection->capacity(), collection->size()); // Verify the capacity is greater than the size
}

// TODO: Create a test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds///////////////////////
// NOTE: This is a negative test
TEST_F(CollectionTest, OutOfRangeExceptionThrow)
{
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    ASSERT_THROW(collection->at(5), std::out_of_range); // Verify the exception is thrown
}

// TODO: Create 2 unit tests of your own to test something on the collection - do 1 positive & 1 negative//////////////////////////////////////

TEST_F(CollectionTest, AssignValuesToCollection)
{
    EXPECT_TRUE(collection->empty()); // Verify the collection is empty

    EXPECT_EQ(collection->size(), 0); // Verify the size is zero

    collection->assign(1, 1);  // assign a value to the collection
     
    ASSERT_FALSE(collection->empty()); // Verify the collection is not empty

    ASSERT_EQ(collection->size(), 1); // verify the size is 1

    ASSERT_EQ(collection->at(0), 1); // verify the value in the first position is 1
}

TEST_F(CollectionTest, LengthErrorExceptionThrow)
{
    ASSERT_THROW(collection->reserve(-2), std::length_error); // Verify an error is received for negative capacity
}