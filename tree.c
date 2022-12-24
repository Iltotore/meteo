#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "model.h"
#include "util.h"

/**
 * Create a new node containing the given value.
 * 
 * @param value the value of the new node.
 * @return a pointer to the newly created node.
 */
Tree *createNode(WeatherRow value) {
    Tree *node = safeMalloc(sizeof(Tree));
    node->value = value;
    node->occurrences = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/**
 * Executes the given callback to each tree using infix path.
 * @param tree the tree to visit.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEachInfix(Tree *tree, Callback callback, bool reversed) {
    if(tree != NULL) {
        forEachInfix(reversed ? tree->right : tree->left, callback, reversed);
        callback(tree->value);
        forEachInfix(reversed ? tree->left : tree->right, callback, reversed);
    }
}

/**
 * Map values with their count.
 *
 * @param tree the tree to map.
 * @param mapper the function to apply.
 * @return this tree for chaining.
 */
Tree *mapCountInfix(Tree *tree, Mapper mapper) {
    if(tree == NULL) return NULL;
    else {
        tree->left = mapCountInfix(tree->left, mapper);
        tree->value = mapper(tree->occurrences, tree->value);
        tree->right = mapCountInfix(tree->right, mapper);
        return tree;
    }
}

void printPrefixRec(Tree *tree) {
    if(tree != NULL) {
        printf("%d ", tree->value.id);
        printPrefixRec(tree->left);
        printPrefixRec(tree->right);
    }
}

/**
 * Print the given tree using prefix path.
 * 
 * @param tree the tree to visit.
 */
void printPrefix(Tree *tree) {
    printPrefixRec(tree);
    printf("\n");
}

void printPostfixRec(Tree *tree) {
    if(tree != NULL) {
        printPostfixRec(tree->left);
        printPostfixRec(tree->right);
        printf("%d ", tree->value.id);
    }
}

/**
 * Print the given tree using postfix path.
 * 
 * @param tree the tree to visit.
 */
void printPostfix(Tree *tree) {
    printPostfixRec(tree);
    printf("\n");
}

void printInfixRec(Tree *tree) {
    if(tree != NULL) {
        printInfixRec(tree->left);
        printf("%d ", tree->value.id);
        printInfixRec(tree->right);
    }
}

/**
 * Print the given tree using infix path.
 * 
 * @param tree the tree to visit.
 */
void printInfix(Tree *tree) {
    printInfixRec(tree);
    printf("\n");
}

/**
 * Check if the given tree is empty.
 * 
 * @param tree the tree to test.
 * @return true if the tree is NULL, false otherwise.
*/
bool isEmpty(Tree *tree) {
    return tree == NULL;
}

/**
 * Check if the given tree is a leaf.
 * 
 * @param tree the tree to test.
 * @return true if the tree have neither right or left child.
 * @see hasLeft, hasRight
 */
bool isLeaf(Tree *tree) {
    return tree != NULL && tree->left == NULL && tree->right == NULL;
}

/**
 * Check if the given tree has a left child.
 * 
 * @param tree the tree to test.
 * @return true if tree->left is NULL.
 */
bool hasLeft(Tree *tree) {
    return tree->left != NULL;
}

/**
 * Check if the given tree has a right child.
 * 
 * @param tree the tree to test.
 * @return true if tree->right is NULL.
 */
bool hasRight(Tree *tree) {
    return tree->right != NULL;
}

/**
 * Set the left child of the given tree.
 * 
 * @param tree the tree to modify.
 * @param value the value of the left child.
 * @note exits if the tree already has a left child.
 * @see addRight, removeLeft
 */
void addLeft(Tree *tree, WeatherRow value) {
    if(tree->left != NULL) error("This tree already has a left child!");
    tree->left = createNode(value);
}

/**
 * Set the right child of the given tree.
 * 
 * @param tree the tree to modify.
 * @param value the value of the right child.
 * @note exits if the tree already has a right child.
 * @see addLeft, removeRight
 */
void addRight(Tree *tree, WeatherRow value) {
    if(tree->right != NULL) error("This tree already has a right child!");
    tree->right = createNode(value);
}

/**
 * Set the root value of the given tree.
 * 
 * @param tree the tree to change its value.
 * @param value the root value.
 * @return this tree, mutated, or a newly created one if tree was NULL.
 */
Tree *setRoot(Tree *tree, WeatherRow value) {
    if(tree == NULL) return createNode(value);
    else {
        tree->value = value;
        return tree;
    }
}

void freeNode(Tree *node) {
    if(node == NULL) return;
    freeNode(node->left);
    freeNode(node->right);
    safeFree(node);
}

/**
 * Remove the left child of this tree.
 * 
 * @param tree the parent of the child to remove.
 * @see removeRight, addLeft
 */
void removeLeft(Tree *tree) {
    freeNode(tree->left);
    tree->left = NULL;
}

/**
 * Remove the right child of this tree.
 * 
 * @param tree the parent of the child to remove.
 * @see removeLeft, addRight
 */
void removeRight(Tree *tree) {
    freeNode(tree->right);
    tree->right = NULL;
}

/**
 * Count the leaves of the given tree.
 * 
 * @param tree the tree to visit.
 * @return the leaf count of the given tree.
 * @see isLeaf
 */
int leafCount(Tree *tree) {
    if(tree == NULL) return 0;
    if(tree->left == NULL && tree->right == NULL) return 1;
    return leafCount(tree->left) + leafCount(tree->right);
}

/**
 * Get the height of the tree.
 * 
 * @param tree the tree to get the height from.
 */
int height(Tree *tree) {
    if(tree == NULL) return 0;
    else {
        int leftHeight = height(tree->left);
        int rightHeight = height(tree->right);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }
}

/**
 * Check if the given BST contains the given value.
 * 
 * @param tree the BST to search in.
 * @param value the value to search.
 * @return true if the tree contains value.
 */
bool containsBST(Tree *tree, WeatherRow value, Comparator comparator) {
    if(tree == NULL) return false;
    else {
        if(comparator(value, tree->value) == Less) return containsBST(tree->left, value, comparator);
        else if(comparator(value, tree->value) == Greater) return containsBST(tree->right, value, comparator);
        else return true;
    }
}

Tree *popMax(Tree *node, WeatherRow *max) {
    if(node == NULL) return NULL;
    else {
        *max = node->value;
        popMax(node->right, max);
        return node;
    }
}

/**
 * Remove the given value from the given BST.
 * 
 * @param tree the BST to remove from.
 * @param value the value to remove.
 * @return the new root of the given BST.
 */
Tree *removeValue(Tree *tree, WeatherRow value, Comparator comparator) {
    if(tree == NULL) return NULL;
    else if(comparator(value, tree->value) == Equal) {
        if(tree->left == NULL) return tree->right;
        else {
            WeatherRow max;
            Tree *left = popMax(tree->left, &max);
            left->right = tree->right;
            return left;
        }
    } else if(comparator(value, tree->value) == Less) {
        tree->left = removeValue(tree->left, value, comparator);
        return tree;
    } else if(comparator(value, tree->value) == Greater) {
        tree->right = removeValue(tree->right, value, comparator);
        return tree;
    }
    return NULL;
}

/**
 * Insert the given value while still satsifying the BST criteria.
 * 
 * @param tree the BST to insert into.
 * @param value the value to insert.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 * @return the new root of the given BST.
 */
Tree *insertBST(Tree *tree, WeatherRow value, Comparator comparator, Reducer reducer) {
    if(tree == NULL) return createNode(value);
    else {
        if(comparator(value, tree->value) == Less) tree->left = insertBST(tree->left, value, comparator, reducer);
        else if(comparator(value, tree->value) == Greater) tree->right = insertBST(tree->right, value, comparator, reducer);
        else {
            tree->value = reducer(tree->value, value);
            tree->occurrences += 1;
        }
        return tree;
    }
}

/**
 * Check if the given tree is a BST.
 * 
 * @param tree the BST to check.
 * @return true if the given tree satsifies the BST criteria.
 */
bool isBST(Tree *tree, Comparator comparator) {
    if(tree == NULL) return true;
    else {
        bool lessLeft = tree->left == NULL || comparator(tree->left->value, tree->value) == Less;
        bool greaterRight = tree->right == NULL || comparator(tree->right->value, tree->value) == Greater;
        return lessLeft && greaterRight && isBST(tree->left, comparator) && isBST(tree->right, comparator);
    }
}