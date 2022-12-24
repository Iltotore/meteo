#include <stdbool.h>
#include "model.h"

#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

/**
 * A double linked node.
 * 
 * @param value the value of this cell.
 * @param occurrences the number of times this cell occurred (before reduction).
 * @param tail the next cell. Might be NULL.
 * @param parent the precedent cell. Might be NULL.
 */
typedef struct _Cell {
    WeatherRow value;
    int occurrences;
    struct _Cell *tail;
    struct _Cell *parent;
} Cell;

/**
 * A double linked list implementation, caching the length.
 *
 * @param head the first cell of this list.
 * @param last the last cell of this list.
 * @param length the length of this list, directly stored in the structure to prevent unnecessary recalculations.
 * @note `head` equals `last` if the list is empty or have only one element.
 * @see Cell.
 */
typedef struct {
    Cell *head;
    Cell *last;
    int length;
} DoubleLinkedList;

/**
 * Execute the given callback for each element.
 *
 * @param list the list to iterate.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEach(DoubleLinkedList *list, Callback callback, bool reversed);

/**
 * Map values with their count.
 *
 * @param list the list to map.
 * @param mapper the function to apply.
 * @return this list for chaining.
 */
DoubleLinkedList *mapCount(DoubleLinkedList *list, Mapper mapper);

/**
 * Print the given list.
 * 
 * @param list the list to print.
 */
void printList(DoubleLinkedList *list);


/**
 * Create an empty list.
 *
 * @return an empty list with no tail.
 */
DoubleLinkedList *emptyList();

/**
 * Prepend a value to the given list.
 *
 * @param list the list to prepend to.
 * @param a the value to prepend.
 * @return this list for chaining.
 */
DoubleLinkedList *prepend(DoubleLinkedList *list, WeatherRow a);

/**
 * Append a value to the given list.
 * 
 * @param list the list to append to.
 * @param a the value to append.
 * @return this list for chaining.
 */
DoubleLinkedList *append(DoubleLinkedList *list, WeatherRow a);

/**
 * Insert a value into the given list, maintaining the (ascending) order.
 * 
 * @param list the list to insert into.
 * @param a the value to insert.
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 * @return this list for chaining.
 */
DoubleLinkedList *insertOrd(DoubleLinkedList *list, WeatherRow a, Comparator comparator, Reducer reducer);

#endif