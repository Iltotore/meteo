#include <stdbool.h>
#include <stdio.h>
#include "doublelinkedlist.h"
#include "model.h"
#include "util.h"

/**
 * Implementation for `forEach`
 */
void forEachCell(Cell *cell, Callback callback, bool reversed) {
    if(cell != NULL) {
        callback(cell->value);
        if(reversed) forEachCell(cell->parent, callback, reversed);
        else forEachCell(cell->tail, callback, reversed);
    }
}

/**
 * Execute the given callback for each element.
 *
 * @param list the list to iterate.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEach(DoubleLinkedList *list, Callback callback, bool reversed) {
    if(reversed) forEachCell(list->last, callback, reversed);
    else forEachCell(list->head, callback, reversed);
}

/**
 * Implementation for `printList`.
 */
void printCell(Cell *cell) {
    if(cell != NULL) {
        printf("%d ", cell->value.id);
        printCell(cell->tail);
    }
}

/**
 * Print the given list.
 *
 * @param list the list to print.
 */
void printList(DoubleLinkedList *list) {
    printCell(list->head);
    printf("\n");
}


/**
 * Create an empty list.
 *
 * @return an empty list with no tail.
 */
DoubleLinkedList *emptyList() {
    DoubleLinkedList *list = safeMalloc(sizeof(list));
    list->head = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}

/**
 * Create a new cell.
 *
 * @param row the value of the new cell.
 * @return a newly created cell containing `row`.
 */
Cell *createCell(WeatherRow row) {
    Cell *cell = safeMalloc(sizeof(Cell));
    cell->value = row;
    cell->tail = NULL;
    cell->parent = NULL;
    return cell;
}

/**
 * Prepend a value to the given list.
 *
 * @param list the list to prepend to.
 * @param a the value to prepend.
 * @return this list for chaining.
 */
DoubleLinkedList *prepend(DoubleLinkedList *list, WeatherRow a) {
    Cell *cell = createCell(a);
    if(list->head == NULL) {
        list->last = cell;
    } else {
        cell->tail = list->head;
        list->head->parent = cell;
    }
    list->head = cell;
    list->length += 1;
    return list;
}

/**
 * Append a value to the given list.
 *
 * @param list the list to append to.
 * @param a the value to append.
 * @return this list for chaining.
 */
DoubleLinkedList *append(DoubleLinkedList *list, WeatherRow a) {
    Cell *cell = createCell(a);
    if(list->last == NULL) {
        list->head = cell;
    } else {
        cell->parent = list->last;
        list->last->tail = cell;
    }
    list->last = cell;
    list->length += 1;
    return list;
}

/**
 * Implementation for `insertOrd`.
 *
 * @param last the pointer to the `last` field of the modified DoubleLinkedList.
 * @return the new head of the modified list.
 */
Cell *insertOrdCell(Cell *cell, WeatherRow a, Comparator comparator, Cell **last) {
    if(cell == NULL) {
        Cell *newCell = createCell(a);
        *last = newCell;
        return newCell;
    } else {
        Comparison comp = comparator(cell->value, a);
        if(comp == Greater || comp == Equal) {
            Cell *newCell = createCell(a);
            newCell->tail = cell;
            cell->parent = newCell;
            return newCell;
        } else {
            cell->tail = insertOrdCell(cell->tail, a, comparator, last);
            cell->tail->parent = cell;
            return cell;
        }
    }
}

/**
 * Insert a value into the given list, maintaining the (ascending) order.
 *
 * @param list the list to insert into.
 * @param a the value to insert.
 * @return this list for chaining.
 */
DoubleLinkedList *insertOrd(DoubleLinkedList *list, WeatherRow a, Comparator comparator) {
    if(list->head == NULL) {
        list->head = createCell(a);
        list->last = list->head;
    } else {
        list->head = insertOrdCell(list->head, a, comparator, &(list->last));
    }
    list->length += 1;
    return list;
}