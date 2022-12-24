#include <stdbool.h>
#include <stdio.h>
#include "doublelinkedlist.h"
#include "model.h"
#include "util.h"

/**
 * Create a new cell.
 *
 * @param row the value of the new cell.
 * @return a newly created cell containing `row`.
 */
Cell *createCell(WeatherRow row) {
    Cell *cell = safeMalloc(sizeof(Cell));
    cell->value = row;
    cell->occurrences = 1;
    cell->tail = NULL;
    cell->parent = NULL;
    return cell;
}

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

Cell *mapCountCell(Cell *cell, Mapper mapper) {
    if(cell == NULL) return NULL;
    else {
        cell->value = mapper(cell->occurrences, cell->value);
        cell->tail = mapCountCell(cell->tail, mapper);
        return cell;
    }
}

/**
 * Map values with their count.
 *
 * @param list the list to map.
 * @param mapper the function to apply.
 * @return this list for chaining.
 */
DoubleLinkedList *mapCount(DoubleLinkedList *list, Mapper mapper) {
    mapCountCell(list->head, mapper);
    return list;
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
Cell *insertOrdCell(Cell *cell, WeatherRow a, Comparator comparator, Reducer reducer, Cell **last) {
    if(cell == NULL) {
        Cell *newCell = createCell(a);
        *last = newCell;
        return newCell;
    } else {
        Comparison comp = comparator(cell->value, a);
        if(comp == Greater) {
            Cell *newCell = createCell(a);
            newCell->tail = cell;
            cell->parent = newCell;
            return newCell;
        } else if(comp == Equal) {
            cell->value = reducer(cell->value, a);
            cell->occurrences += 1;
            return cell;
        } else {
            cell->tail = insertOrdCell(cell->tail, a, comparator, reducer, last);
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
 * @param comparator the ordering used to sort values.
 * @param reducer the reduction policy applied to duplicates (when the comparator returns Equal).
 * @return this list for chaining.
 */
DoubleLinkedList *insertOrd(DoubleLinkedList *list, WeatherRow a, Comparator comparator, Reducer reducer) {
    if(list->head == NULL) {
        list->head = createCell(a);
        list->last = list->head;
    } else {
        list->head = insertOrdCell(list->head, a, comparator, reducer, &(list->last));
    }
    list->length += 1;
    return list;
}