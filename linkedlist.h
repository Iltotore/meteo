#include <stdbool.h>
#ifndef linkedlist
#define linkedlist

//TODO re-do LinkedList implementation

/**
 * A LinkedList implementation that supports emptyness and pointer stability.
 * 
 * @param head the value (head) of this cell.
 * @param tail the next value (tail) of this cell.
 * @param empty whether this cell is empty.
 */
typedef struct CellR {
  int head;
  struct CellR* tail;
  int empty;
} Cell;

typedef Cell* LinkedList;

/**
 * Get the length of the given list.
 * 
 * @param plist the list to measure.
 * @return the length of the given list.
 */
int length(LinkedList plist);

/**
 * Get the last element of the given list.
 * 
 * @param plist the list to get from.
 * @return the last element of the given list.
 */
int last(LinkedList plist);

/**
 * Print the given list.
 * 
 * @param cell the list to print.
 */
void printCell(LinkedList cell);

/**
 * Set the value of the head of the given list and update its state.
 * 
 * @param plist the list to modify.
 * @param a the value to set.
 * @return this list for chaining or a newly created one if plist is NULL.
 */
LinkedList setHead(LinkedList plist, int a);

/**
 * Create an empty list.
 * 
 * @return an empty cell with no tail.
 */
LinkedList emptyCell();

/**
 * Create a new LinkedList with a head.
 * 
 * @param a the head value.
 * @return a cell containing a with no tail.
 */
LinkedList createCell(int a);

/**
 * Prepend a value to the given list.
 * 
 * @param plist the list to prepend to.
 * @param a the value to prepend.
 * @return the new root of the given list.
 */
LinkedList prepend(LinkedList plist, int a);

/**
 * Append a value to the given list.
 * 
 * @param plist the list to append to.
 * @param a the value to append.
 * @return the new root of the given list.
 */
LinkedList append(LinkedList plist, int a);

/**
 * Insert a value into the given list, maintaining the (ascending) order.
 * 
 * @param plist the list to insert into.
 * @param a the value to insert.
 * @return the new root of the given list.
 */
LinkedList insertOrd(LinkedList plist, int a);

/**
 * Remove the first occurrence of the given value in the given list.
 * 
 * @param plist the list to pop.
 * @param a the target value.
 * @return the new root of the given list.
*/
LinkedList removeFirst(LinkedList plist, int a);

/**
 * Remove all occurrences of the given value in the given list.
 * 
 * @param plist the list to pop.
 * @param a the target value.
 * @return the new root of the given list.
*/
LinkedList removeAll(LinkedList plist, int a);

/**
 * Reverse the given list.
 * 
 * @param plist the list to reverse.
 * @return a pointer to the last cell of this list.
*/
LinkedList reverse(LinkedList plist);

#endif