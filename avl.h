#include <stdbool.h>
#include "model.h"

#ifndef avl_h
#define avl_h

/**
 * A node of a balanced BST tree, more efficient than the naive implementation.
 * 
 * @param value the inner value of this node.
 * @param left the left child if exists or NULL.
 * @param right the right child if exists or NULL.
 * @param balance the balance factor of this node. Must be between -1 and 1 after balance.
 */
typedef struct _AVL {
    WeatherRow value;
    int occurrences;
    struct _AVL *left;
    struct _AVL *right;
    int balance;
} AVL;

/**
 * Create a new AVL node.
 * 
 * @param value the value of the new node.
 * @return a pointer to the newly created node which contains the given value.
 */
AVL *createAVL(WeatherRow value);

/**
 * Executes the given callback to each node using infix path.
 * @param avl the tree to visit.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEachInfixAVL(AVL *avl, Callback callback, bool reversed);

/**
 * Map values with their count.
 *
 * @param avl the avl to map.
 * @param mapper the function to apply.
 * @return this tre for chaining.
 */
AVL *mapCountInfixAVL(AVL *avl, Mapper mapper);

/**
 * Print the given AVL using infix path.
 * 
 * @param avl the tree to visit.
 */
void printAVLInfix(AVL *avl);

/**
 * Get the height of the AVL.
 * 
 * @param avl the tree to get the height from.
 */
int heightAVL(AVL *avl);

/**
 * Balance the given AVL.
 * 
 * @param avl the tree to balance.
 * @return the new root of the given AVL in which all nodes have a balance factor between -1 and 1.
 */
AVL *balanceAVL(AVL *avl);

/**
 * Insert the passed value into the given AVL.
 * 
 * @param avl the tree to insert into.
 * @param value the value to insert.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 * @return the new root of the given AVL containing the passed value, balanced.
 * @see balanceAVL
 */
AVL *insertAVL(AVL *avl, WeatherRow value, Comparator comparator, Reducer reducer);

/**
 * Rotates from right to left (counter-clockwise) the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateLeft(AVL *avl);

/**
 * Rotates from left to right (clockwise) the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateRight(AVL *avl);

/**
 * Rotates from left to right then from right to left the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateDoubleLeft(AVL *avl);

/**
 * Rotates from right to left then from left to right the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateDoubleRight(AVL *avl);

#endif