#include <gtest/gtest.h>
#include "BinaryTree/BSTNode.h"
#include "BinaryTree/TreeMap.h"

// Test the copy constructor of BSTNode
TEST(BSTNodeTest, CopyConstructor) {
    BSTNode<int> original(10); // Create root node with data = 10
    original.setLeft(new BSTNode<int>(5)); // Add left child with data = 5
    original.setRight(new BSTNode<int>(15)); // Add right child with data = 15

    BSTNode<int> copy(original); // Use the copy constructor

    // Assertions
    ASSERT_EQ(copy.getItem(), 10); // Check the root node data
    ASSERT_EQ(copy.getLeft()->getItem(), 5); // Check left child data
    ASSERT_EQ(copy.getRight()->getItem(), 15); // Check right child data
}

// Test to ensure that insert and retrieve operations work as expected
TEST(TreeMapTest, InsertAndRetrieve) {
    TreeMap<int, std::string> map;
    ASSERT_NO_THROW({
                        map.put(1, "One");
                        auto result = map.get(1);
                        ASSERT_EQ(result, "One") << "The value for key 1 should be 'One'.";
                    });
}

// Test the assignment operator of BSTNode
TEST(BSTNodeTest, AssignmentOperator) {
    BSTNode<int> original(10); // Create root node with data = 10
    original.setLeft(new BSTNode<int>(5)); // Add left child with data = 5
    original.setRight(new BSTNode<int>(15)); // Add right child with data = 15

    BSTNode<int> copy; // Create an empty node
    copy = original; // Use the assignment operator

    // Assertions
    ASSERT_EQ(copy.getItem(), 10); // Check the root node data
    ASSERT_EQ(copy.getLeft()->getItem(), 5); // Check left child data
    ASSERT_EQ(copy.getRight()->getItem(), 15); // Check right child data
}

// Test the count method of BSTNode
TEST(BSTNodeTest, Count) {
    BSTNode<int> root(10); // Root node
    root.add(5);           // Add left child
    root.add(15);          // Add right child
    root.add(3);           // Add left-left child
    root.add(7);           // Add left-right child

    // Assertions
    ASSERT_EQ(root.count(), 5); // Ensure the total count is correct
}

// Test adding and retrieving elements
TEST(BSTNodeTest, AddAndRetrieve) {
    BSTNode<int> root(10); // Root node
    root.add(5);           // Add left child
    root.add(15);          // Add right child

    // Assertions
    ASSERT_EQ(root.getLeft()->getItem(), 5); // Check left child data
    ASSERT_EQ(root.getRight()->getItem(), 15); // Check right child data
}

// Test basic operations of TreeMap
TEST(TreeMapTest, BasicOperations) {
    TreeMap<int, std::string> map;
    map.put(1, "One");
    ASSERT_EQ(map.size(), 1);
    ASSERT_EQ(map.get(1), "One");

    map.put(2, "Two");
    ASSERT_EQ(map.size(), 2);
    ASSERT_EQ(map.get(2), "Two");

    map.removeKey(1);
    ASSERT_EQ(map.size(), 1);
    ASSERT_FALSE(map.containsKey(1));
}

// Test TreeMap keySet method
TEST(TreeMapTest, KeySet) {
    TreeMap<int, std::string> map;
    map.put(1, "One");
    map.put(2, "Two");
    map.put(3, "Three");

    std::vector<int> keys = map.keySet();

    // Assertions
    ASSERT_EQ(keys.size(), 3);
    ASSERT_EQ(keys[0], 1);
    ASSERT_EQ(keys[1], 2);
    ASSERT_EQ(keys[2], 3);
}

// Test TreeMap operator[]
TEST(TreeMapTest, OperatorBracket) {
    TreeMap<int, std::string> map;
    map[1] = "One";
    map[2] = "Two";

    // Assertions
    ASSERT_EQ(map.get(1), "One");
    ASSERT_EQ(map.get(2), "Two");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}