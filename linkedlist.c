#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "linkedlist.h"
#include "util.h"

void printCell(LinkedList cell) {
    if (cell->empty) printf("END\n");
    else {
        printf("%d", cell->head);
        printf("->");
        printCell(cell->tail);
    }
}

int last(LinkedList plist) {
    if (plist->empty) error("Calling last item of empty list");
    if (plist->tail->empty) return plist->head;
    else return last(plist->tail);
}

LinkedList setHead(LinkedList plist, int a) {
    plist->head = a;
    if (plist->empty) {
        plist->tail = emptyCell();
        plist->empty = false;
    }
    return plist;
}

LinkedList emptyCell() {
    LinkedList plist = safeMalloc(sizeof(Cell));
    plist->tail = NULL;
    plist->empty = true;
    return plist;
}

LinkedList createCell(int a) {
    return setHead(emptyCell(), a);
}

LinkedList prepend(LinkedList plist, int a) {
    int oldHead = plist->head;
    plist->head = a;

    LinkedList newTail = createCell(oldHead);
    newTail->tail = plist->tail;
    plist->tail = newTail;

    return plist;
}

LinkedList append(LinkedList plist, int a) {
    if (plist->empty) return setHead(plist, a);
    else {
        append(plist->tail, a);
        return plist; //Keep original head
    }
}

LinkedList insertOrd(LinkedList plist, int a) {
    if (plist->head > a) return prepend(plist, a);
    if (plist->empty) return setHead(plist, a);
    else {
        insertOrd(plist->tail, a);
        return plist;
    }
}

LinkedList shift(LinkedList plist) {
    if (plist->empty) return plist;
    LinkedList oldTail = plist->tail;
    plist->head = oldTail->head;
    plist->tail = oldTail->tail;
    plist->empty = oldTail->empty;
    if (oldTail->empty) safeFree(oldTail);
    return plist;
}

LinkedList shiftValues(LinkedList plist, int placeholder) {
    if (plist->empty) return plist;

    plist->head = plist->tail->empty ? placeholder : plist->tail->head;

    shiftValues(plist->tail, placeholder);

    return plist;
}

LinkedList removeFirst(LinkedList plist, int a) {
    if (plist->empty) return plist;
    else if (plist->head == a) return shift(plist);
    else {
        removeFirst(plist->tail, a);
        return plist;
    }
}

LinkedList removeAll(LinkedList plist, int a) {
    if (plist->empty) return plist;
    else {
        if (plist->head == a) {
            shift(plist);
            removeAll(plist, a);
        } else removeAll(plist->tail, a);

        return plist;
    }
}

int length(LinkedList plist) {
    if (plist->empty) return 0;
    else return 1 + length(plist->tail);
}

LinkedList getCell(LinkedList plist, int index) {
    if (plist->empty) {
        printf("Index out of bound\n");
        exit(1);
    } else if (index == 0) return plist;
    else return getCell(plist->tail, index - 1);
}

LinkedList reverse(LinkedList plist) {
    if (plist->empty) return plist;
    else {
        int left = 0;
        int right = length(plist) - 1;
        while (left < right) {

            LinkedList leftCell = getCell(plist, left);
            LinkedList rightCell = getCell(plist, right);

            int leftHead = leftCell->head;

            leftCell->head = rightCell->head;
            rightCell->head = leftHead;

            left++;
            right--;
        }
        return plist;
    }
}