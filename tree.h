#include <stdbool.h>
#include "model.h"

#ifndef TREE_H
#define TREE_H

/**
 * A binary tree node.
 * 
 * @param value the value of this node.
 * @param left the left child if exists or NULL.
 * @param right the right child if exists or NULL.
 */
typedef struct _Tree {
    WeatherRow value;
    struct _Tree *left;
    struct _Tree *right;
} Tree;

/**
 * Create a new node containing the given value.
 * 
 * @param value the value of the new node.
 * @return a pointer to the newly created node.
 */
Tree *createNode(WeatherRow value);

/**
 * Executes the given callback to each node using infix path.
 * @param tree the tree to visit.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEachInfix(Tree *tree, Callback callback, bool reversed);

/**
 * Print the given tree using prefix path.
 * 
 * @param tree the tree to visit.
 */
void printPrefix(Tree *tree);

/**
 * Print the given tree using postfix path.
 * 
 * @param tree the tree to visit.
 */
void printPostfix(Tree *tree);

/**
 * Print the given tree using infix path.
 * 
 * @param tree the tree to visit.
 */
void printInfix(Tree *tree);

/**
 * Check if the given tree is empty.
 * 
 * @param tree the tree to test.
 * @return true if the tree is NULL, false otherwise.
*/
bool isEmpty(Tree *tree);

/**
 * Check if the given tree is a leaf.
 * 
 * @param tree the tree to test.
 * @return true if the tree have neither right or left child.
 * @see hasLeft, hasRight
 */
bool isLeaf(Tree *tree);

/**
 * Check if the given tree has a left child.
 * 
 * @param tree the tree to test.
 * @return true if tree->left is NULL.
 */
bool hasLeft(Tree *tree);

/**
 * Check if the given tree has a right child.
 * 
 * @param tree the tree to test.
 * @return true if tree->right is NULL.
 */
bool hasRight(Tree *tree);

/**
 * Set the left child of the given tree.
 * 
 * @param tree the tree to modify.
 * @param value the value of the left child.
 * @note exits if the tree already has a left child.
 * @see addRight, removeLeft
 */
void addLeft(Tree *tree, WeatherRow value);

/**
 * Set the right child of the given tree.
 * 
 * @param tree the tree to modify.
 * @param value the value of the right child.
 * @note exits if the tree already has a right child.
 * @see addLeft, removeRight
 */
void addRight(Tree *tree, WeatherRow value);

/**
 * Set the root value of the given tree.
 * 
 * @param tree the tree to change its value.
 * @param value the root value.
 * @return this tree, mutated, or a newly created one if tree was NULL.
 */
Tree *setRoot(Tree *tree, WeatherRow value);

/**
 * Remove the left child of this tree.
 * 
 * @param tree the parent of the child to remove.
 * @see removeRight, addLeft
 */
void removeLeft(Tree *tree);

/**
 * Remove the right child of this tree.
 * 
 * @param tree the parent of the child to remove.
 * @see removeLeft, addRight
 */
void removeRight(Tree *tree);

/**
 * Count the leaves of the given tree.
 * 
 * @param tree the tree to visit.
 * @return the leaf count of the given tree.
 * @see isLeaf
 */
int leafCount(Tree *tree);

/**
 * Get the height of the tree.
 * 
 * @param tree the tree to get the height from.
 */
int height(Tree *tree);

/**
 * Check if the given BST contains the given value.
 * 
 * @param tree the BST to search in.
 * @param value the value to search.
 * @return true if the tree contains value.
 */
bool containsBST(Tree *tree, WeatherRow value, Comparator comparator);

/**
 * Remove the given value from the given BST.
 * 
 * @param tree the BST to remove from.
 * @param value the value to remove.
 * @return the new root of the given BST.
 */
Tree *removeValue(Tree *tree, WeatherRow value, Comparator comparator);

/**
 * Insert the given value while still satsifying the BST criteria.
 * 
 * @param tree the BST to insert into.
 * @param value the value to insert.
 * @return the new root of the given BST.
 */
Tree *insertBST(Tree *tree, WeatherRow value, Comparator comparator);

/**
 * Check if the given tree is a BST.
 * 
 * @param tree the BST to check.
 * @return true if the given tree satsifies the BST criteria.
 */
bool isBST(Tree *tree, Comparator comparator);

#endif