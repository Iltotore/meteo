#include <stdbool.h>
#include "model.h"

#ifndef tree
#define tree

/**
 * A binary tree node.
 * 
 * @param value the value of this node.
 * @param left the left child if exists or NULL.
 * @param right the right child if exists or NULL.
 */
typedef struct _Node {
    WeatherRow value;
    struct _Node *left;
    struct _Node *right;
} Node;

/**
 * Create a new node containing the given value.
 * 
 * @param value the value of the new node.
 * @return a pointer to the newly created node.
 */
Node *createNode(WeatherRow value);

/**
 * Executes the given callback to each node using infix path.
 * @param node the tree to visit.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEachInfix(Node *node, Callback callback, bool reversed);

/**
 * Print the given tree using prefix path.
 * 
 * @param node the tree to visit.
 */
void printPrefix(Node *node);

/**
 * Print the given tree using postfix path.
 * 
 * @param node the tree to visit.
 */
void printPostfix(Node *node);

/**
 * Print the given tree using infix path.
 * 
 * @param node the tree to visit.
 */
void printInfix(Node *node);

/**
 * Check if the given node is empty.
 * 
 * @param node the node to test.
 * @return true if the node is NULL, false otherwise.
*/
bool isEmpty(Node *node);

/**
 * Check if the given node is a leaf.
 * 
 * @param node the node to test.
 * @return true if the node have neither right or left child.
 * @see hasLeft, hasRight
 */
bool isLeaf(Node *node);

/**
 * Check if the given node has a left child.
 * 
 * @param node the node to test.
 * @return true if node->left is NULL.
 */
bool hasLeft(Node *node);

/**
 * Check if the given node has a right child.
 * 
 * @param node the node to test.
 * @return true if node->right is NULL.
 */
bool hasRight(Node *node);

/**
 * Set the left child of the given node.
 * 
 * @param node the node to modify.
 * @param value the value of the left child.
 * @note exits if the node already has a left child.
 * @see addRight, removeLeft
 */
void addLeft(Node *node, WeatherRow value);

/**
 * Set the right child of the given node.
 * 
 * @param node the node to modify.
 * @param value the value of the right child.
 * @note exits if the node already has a right child.
 * @see addLeft, removeRight
 */
void addRight(Node *node, WeatherRow value);

/**
 * Set the root value of the given tree.
 * 
 * @param node the node to change its value.
 * @param value the root value.
 * @return this node, mutated, or a newly created one if node was NULL.
 */
Node *setRoot(Node *node, WeatherRow value);

/**
 * Remove the left child of this node.
 * 
 * @param node the parent of the child to remove.
 * @see removeRight, addLeft
 */
void removeLeft(Node *node);

/**
 * Remove the right child of this node.
 * 
 * @param node the parent of the child to remove.
 * @see removeLeft, addRight
 */
void removeRight(Node *node);

/**
 * Count the leaves of the given tree.
 * 
 * @param node the tree to visit.
 * @return the leaf count of the given tree.
 * @see isLeaf
 */
int leafCount(Node *node);

/**
 * Get the height of the tree.
 * 
 * @param node the tree to get the height from.
 */
int height(Node *node);

/**
 * Check if the given BST contains the given value.
 * 
 * @param node the BST to search in.
 * @param value the value to search.
 * @return true if the tree contains value.
 */
bool containsABR(Node *node, WeatherRow value, Comparator comparator);

/**
 * Remove the given value from the given BST.
 * 
 * @param node the BST to remove from.
 * @param value the value to remove.
 * @return the new root of the given BST.
 */
Node *removeValue(Node *node, WeatherRow value, Comparator comparator);

/**
 * Insert the given value while still satsifying the BST criteria.
 * 
 * @param node the BST to insert into.
 * @param value the value to insert.
 * @return the new root of the given BST.
 */
Node *insertABR(Node *node, WeatherRow value, Comparator comparator);

/**
 * Check if the given tree is a BST.
 * 
 * @param node the BST to check.
 * @return true if the given tree satsifies the BST criteria.
 */
bool isABR(Node *node, Comparator comparator);

#endif