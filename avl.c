#include <stdlib.h>
#include "avl.h"
#include "util.h"

/**
 * Create a new AVL node.
 * 
 * @param value the value of the new node.
 * @return a pointer to the newly created node which contains the given value.
 */
AVL *createAVL(WeatherRow value) {
    AVL *avl = safeMalloc(sizeof(AVL));
    avl->value = value;
    avl->left = NULL;
    avl->right = NULL;
    avl->balance = 0;
    return avl;
}

/**
 * Executes the given callback to each node using infix path.
 * @param avl the tree to visit.
 * @param callback the callback to call.
 * @param reversed use descending order if true.
 */
void forEachInfixAVL(AVL *avl, Callback callback, bool reversed) {
    if(avl != NULL) {
        forEachInfixAVL(reversed ? avl->right : avl->left, callback, reversed);
        callback(avl->value);
        forEachInfixAVL(reversed ? avl->left : avl->right, callback, reversed);
    }
}

void printAVLInfixRec(AVL *avl) {
    if (avl != NULL) {
        printAVLInfixRec(avl->left);
        printf("%d(%d) ", avl->value.id, avl->balance);
        printAVLInfixRec(avl->right);
    }
}

/**
 * Print the given AVL using infix path.
 * 
 * @param avl the tree to visit.
 */
void printAVLInfix(AVL *avl) {
    printAVLInfixRec(avl);
    printf("\n");
}

/**
 * Get the height of the AVL.
 * 
 * @param avl the tree tree to get the height from.
 */
int heightAVL(AVL *avl) {
    if (avl == NULL) return 0;
    else {
        int leftHeight = heightAVL(avl->left);
        int rightHeight = heightAVL(avl->right);
        return 1 + leftHeight > rightHeight ? leftHeight : rightHeight;
    }
}

/**
 * Balance the given AVL.
 * 
 * @param avl the tree to balance.
 * @return the new root of the given AVL in which all nodes have a balance factor between -1 and 1.
 */
AVL *balanceAVL(AVL *avl) {
    if (avl->balance >= -1 && avl->balance <= 1) return avl;
    else if (avl->balance == 2) return avl->right->balance == 1 ? rotateLeft(avl) : rotateDoubleLeft(avl);
    else return avl->left->balance == -1 ? rotateRight(avl) : rotateDoubleRight(avl);
}

AVL *insertAVLRec(AVL *avl, WeatherRow value, int *h, Comparator comparator) {
    if (avl == NULL) { //Création d'un AVL -> équilibre +- 1
        *h = 1;
        return createAVL(value);
    } else if (comparator(value, avl->value) == Equal) { //Noeud déjà présent
        *h = 0;
        return avl;
    } else {
        if (comparator(value, avl->value) == Less) { //Ajouter à gauche
            avl->left = insertAVLRec(avl->left, value, h, comparator);
            *h = -*h;
        } else { //Ajouter à droite
            avl->right = insertAVLRec(avl->right, value, h, comparator);
        }

        if (*h != 0) { //Si il y a eu ajout
            avl->balance += *h;
            avl = balanceAVL(avl);
            *h = avl->balance == 0 ? 0 : 1; //Valeur absolue pour éviter la double négation avec l'ajout à gauche
        }
        return avl;
    }
}

/**
 * Insert the passed value into the given AVL.
 * 
 * @param avl the tree to insert into.
 * @param value the value to insert.
 * @return the new root of the given AVL containing the passed value, balanced.
 * @see balanceAVL
 */
AVL *insertAVL(AVL *avl, WeatherRow value, Comparator comparator) {
    int *h = safeMalloc(sizeof(int));
    *h = 0;
    return insertAVLRec(avl, value, h, comparator);
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a <= b ? a : b;
}

/**
 * Rotates from right to left (counter-clockwise) the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateLeft(AVL *avl) { //Rotate the tree to the left
    AVL *root = avl->right;
    avl->right = root->left;
    root->left = avl;
    int eq_a = avl->balance;
    int eq_root = root->balance;
    avl->balance = eq_a - max(eq_root, 0) - 1;
    root->balance = min(eq_a - 2, min(eq_a + eq_root - 2, eq_root - 1));
    return root;
}

/**
 * Rotates from left to right (clockwise) the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateRight(AVL *avl) { //Rotate the tree to the right
    AVL *root = avl->left;
    avl->left = root->right;
    root->right = avl;
    int eq_a = avl->balance;
    int eq_root = root->balance;
    avl->balance = eq_a - min(eq_root, 0) + 1;
    root->balance = max(eq_a + 2, max(eq_a + eq_root + 2, eq_root + 1));
    return root;
}

/**
 * Rotates from left to right then from right to left the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateDoubleLeft(AVL *avl) {
    avl->right = rotateRight(avl->right);
    return rotateLeft(avl);
}

/**
 * Rotates from right to left then from left to right the given AVL.
 * 
 * @param avl the tree to rotate.
 * @return the new root of the given AVL, rotated.
 */
AVL *rotateDoubleRight(AVL *avl) {
    avl->left = rotateLeft(avl->left);
    return rotateRight(avl);
}

