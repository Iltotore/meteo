#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "model.h"
#include "linkedlist.h"
#include "util.h"

/**
 * Create a new node containing the given value.
 * 
 * @param value the value of the new node.
 * @return a pointer to the newly created node.
 */
Node *createNode(WeatherRow value) {
    Node *node = safeMalloc(sizeof(Node));
    (node->value) = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Executes the given callback to each node using infix path.
 * @param node the tree to visit.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEachInfix(Node *node, Callback callback, bool reversed) {
    if(node != NULL) {
        forEachInfix(reversed ? node->right : node->left, callback, reversed);
        callback(node->value);
        forEachInfix(reversed ? node->left : node->right, callback, reversed);
    }
}

void printPrefixRec(Node *node) {
    if (node != NULL) {
        printf("%d ", node->value.id);
        printPrefixRec(node->left);
        printPrefixRec(node->right);
    }
}

/**
 * Print the given tree using prefix path.
 * 
 * @param node the tree to visit.
 */
void printPrefix(Node *node) {
    printPrefixRec(node);
    printf("\n");
}

void printPostfixRec(Node *node) {
    if (node != NULL) {
        printPostfixRec(node->left);
        printPostfixRec(node->right);
        printf("%d ", node->value.id);
    }
}

/**
 * Print the given tree using postfix path.
 * 
 * @param node the tree to visit.
 */
void printPostfix(Node *node) {
    printPostfixRec(node);
    printf("\n");
}

void printInfixRec(Node *node) {
    if (node != NULL) {
        printInfixRec(node->left);
        printf("%d ", node->value.id);
        printInfixRec(node->right);
    }
}

/**
 * Print the given tree using infix path.
 * 
 * @param node the tree to visit.
 */
void printInfix(Node *node) {
    printInfixRec(node);
    printf("\n");
}

/**
 * Check if the given node is empty.
 * 
 * @param node the node to test.
 * @return true if the node is NULL, false otherwise.
*/
bool isEmpty(Node *node) {
    return node == NULL;
}

/**
 * Check if the given node is a leaf.
 * 
 * @param node the node to test.
 * @return true if the node have neither right or left child.
 * @see hasLeft, hasRight
 */
bool isLeaf(Node *node) {
    return node != NULL && node->left == NULL && node->right == NULL;
}

/**
 * Check if the given node has a left child.
 * 
 * @param node the node to test.
 * @return true if node->left is NULL.
 */
bool hasLeft(Node *node) {
    return node->left != NULL;
}

/**
 * Check if the given node has a right child.
 * 
 * @param node the node to test.
 * @return true if node->right is NULL.
 */
bool hasRight(Node *node) {
    return node->right != NULL;
}

/**
 * Set the left child of the given node.
 * 
 * @param node the node to modify.
 * @param value the value of the left child.
 * @note exits if the node already has a left child.
 * @see addRight, removeLeft
 */
void addLeft(Node *node, WeatherRow value) {
    if (node->left != NULL) error("This node already has a left child!");
    node->left = createNode(value);
}

/**
 * Set the right child of the given node.
 * 
 * @param node the node to modify.
 * @param value the value of the right child.
 * @note exits if the node already has a right child.
 * @see addLeft, removeRight
 */
void addRight(Node *node, WeatherRow value) {
    if (node->right != NULL) error("This node already has a right child!");
    node->right = createNode(value);
}

/**
 * Set the root value of the given tree.
 * 
 * @param node the node to change its value.
 * @param value the root value.
 * @return this node, mutated, or a newly created one if node was NULL.
 */
Node *setRoot(Node *node, WeatherRow value) {
    if (node == NULL) return createNode(value);
    else {
        node->value = value;
        return node;
    }
}

void freeNode(Node *node) {
    if (node == NULL) return;
    freeNode(node->left);
    freeNode(node->right);
    safeFree(node);
}

/**
 * Remove the left child of this node.
 * 
 * @param node the parent of the child to remove.
 * @see removeRight, addLeft
 */
void removeLeft(Node *node) {
    freeNode(node->left);
    node->left = NULL;
}

/**
 * Remove the right child of this node.
 * 
 * @param node the parent of the child to remove.
 * @see removeLeft, addRight
 */
void removeRight(Node *node) {
    freeNode(node->right);
    node->right = NULL;
}

/**
 * Count the leaves of the given tree.
 * 
 * @param node the tree to visit.
 * @return the leaf count of the given tree.
 * @see isLeaf
 */
int leafCount(Node *node) {
    if (node == NULL) return 0;
    if (node->left == NULL && node->right == NULL) return 1;
    return leafCount(node->left) + leafCount(node->right);
}

/**
 * Get the height of the tree.
 * 
 * @param node the tree to get the height from.
 */
int height(Node *node) {
    if (node == NULL) return 0;
    else {
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

/**
 * Check if the given BST contains the given value.
 * 
 * @param node the BST to search in.
 * @param value the value to search.
 * @return true if the tree contains value.
 */
bool containsABR(Node *node, WeatherRow value, Comparator comparator) {
    if (node == NULL) return false;
    else {
        if (comparator(value, node->value) == Less) return containsABR(node->left, value, comparator);
        else if (comparator(value, node->value) == Greater) return containsABR(node->right, value, comparator);
        else return true;
    }
}

Node *popMax(Node *node, WeatherRow *max) {
    if (node == NULL) return NULL;
    else {
        *max = node->value;
        popMax(node->right, max);
        return node;
    }
}

/**
 * Remove the given value from the given BST.
 * 
 * @param node the BST to remove from.
 * @param value the value to remove.
 * @return the new root of the given BST.
 */
Node *removeValue(Node *node, WeatherRow value, Comparator comparator) {
    if (node == NULL) return NULL;
    else if (comparator(value, node->value) == Equal) {
        if (node->left == NULL) return node->right;
        else {
            WeatherRow max;
            Node *left = popMax(node->left, &max);
            left->right = node->right;
            return left;
        }
    } else if (comparator(value, node->value) == Less) {
        node->left = removeValue(node->left, value, comparator);
        return node;
    } else if (comparator(value, node->value) == Greater) {
        node->right = removeValue(node->right, value, comparator);
        return node;
    }
    return NULL;
}

/**
 * Insert the given value while still satsifying the BST criteria.
 * 
 * @param node the BST to insert into.
 * @param value the value to insert.
 * @return the new root of the given BST.
 */
Node *insertABR(Node *node, WeatherRow value, Comparator comparator) {
    if (node == NULL) return createNode(value);
    else {
        if (comparator(value, node->value) == Less) node->left = insertABR(node->left, value, comparator);
        if (comparator(value, node->value) == Greater) node->right = insertABR(node->right, value, comparator);
        return node;
    }
}

/**
 * Check if the given tree is a BST.
 * 
 * @param node the BST to check.
 * @return true if the given tree satsifies the BST criteria.
 */
bool isABR(Node *node, Comparator comparator) {
    if (node == NULL) return true;
    else {
        bool lessLeft = node->left == NULL || comparator(node->left->value, node->value) == Less;
        bool greaterRight = node->right == NULL || comparator(node->right->value, node->value) == Greater;
        return lessLeft && greaterRight && isABR(node->left, comparator) && isABR(node->right, comparator);
    }
}