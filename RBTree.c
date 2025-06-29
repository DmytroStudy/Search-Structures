#include <stdio.h>
#include <stdlib.h>
#include "RBTree.h"


void RBcreate(RBTree* tree) {
    tree->root = NULL;
}

RBNode* RBcreateNode(int id) {
    RBNode* node = (RBNode*)malloc(sizeof(RBNode));
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->id = id;
    node->color = 'R';
    return node;
}


// Rebalancing functions
int RBcompare(int id1, int id2) {
    if (id1 > id2) return 1;
    if (id1 < id2) return -1;
    if (id1 == id2) return 0;
}

void RBleftRotate(RBTree* tree, RBNode* N1) {
    RBNode* N2 = N1->right;
    N1->right = N2->left;
    if ( N2->left != NULL) {
        N2->left->parent = N1;
    }

    N2->parent = N1->parent;

    // If N1 was root
    if (N1->parent == NULL){
        tree->root = N2;

    // If N1 was left child
    }else if (N1->parent->left == N1) {
        N1->parent->left = N2;

    // If N1 was right child
    }else {
        N1->parent->right = N2;
    }

    N2->left = N1;
    N1->parent = N2;
}

void RBrightRotate(RBTree* tree, RBNode* N1) {
        RBNode* N2 = N1->left;
        N1->left = N2->right;
        if (N2->right != NULL) {
            N2->right->parent = N1;
        }

        N2->parent = N1->parent;

        // If N1 was root
        if (N1->parent == NULL) {
            tree->root = N2;

        // If N1 was right child
        } else if (N1 == N1->parent->right) {
            N1->parent->right = N2;

        // If N1 was left child
        } else {
            N1->parent->left = N2;
        }

        N2->right = N1;
        N1->parent = N2;
}

void RBshifting(RBTree* tree, RBNode* N1, RBNode* N2) {
    // Changing parents parameters
    if (N1->parent == NULL) {
        tree->root = N2;
    }else if (N1->parent->left == N1) {
        N1->parent->left = N2;
    }else {
        N1->parent->right = N2;
    }

    if (N2!=NULL) {
        N2->parent = N1->parent;
    }
}

RBNode* RBminimum(RBNode* N) {
    if(N == NULL) {
        return N;
    }

    while (N->left != NULL) {
        N = N->left;
    }
    return N;
}


// Interactions with tree
RBNode* RBsearch(RBTree* tree, int id) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    RBNode* N = tree->root;

    while (N) {
        int c = RBcompare(N->id, id); // Comparing our root with id

        if (c < 0) {
            N = N->right;
        } else if (c > 0) {
            N = N->left;
        } else if (c == 0) {
            return N; // Node is found
        }

    }
    return NULL; // Node isn't found
}

void RBinsert(RBTree* tree, int id) {
    RBNode* N = RBcreateNode(id);
    RBNode* N1 = NULL;
    RBNode* N2 = tree->root;

    // Finding place for new Node
    while (N2 != NULL) {
        N1 = N2;
        if (id < N2->id) {
            N2 = N2->left;
        }else {
            N2 = N2->right;
        }
    }
    N->parent = N1;

    // Inserting node
    if (N1 == NULL) {
        tree->root = N; // If tree has no root
    } else if (id < N1->id) {
        N1->left = N; // If N<N1
    } else {
        N1->right = N; // If N>N1
    }


    // Fixing :
    RBNode* NU = NULL; // Uncle
    while (N != tree->root && N->parent->color == 'R') {
        RBNode* NG = N->parent->parent; // Grandparent

        // Finding Uncle
        if (N->parent == NG->left) {
            NU = NG->right;
        } else {
            NU = NG->left;
        }

        //Case 1: node is root
        if (N->parent == NULL) {
            break;

        //Case 2: node has Black parent
        }else if (N->parent->color == 'B') {
            break;

        //Case 3: node has Red parent and Red sibling
        }else if (NU != NULL && N->parent->color == 'R' && NU->color == 'R') {
            N->parent->color = 'B';
            NU->color = 'B';
            NG->color = 'R';
            N = NG; // Move up to grandparent
            continue;

        //Case 4: node is right child and parent is left child, or contrariwise
        }else if ((N == N->parent->right && N->parent == NG->left) || (N == N->parent->left && N->parent == NG->right)) {

            // First rotate
            if (N == N->parent->right) {
                RBleftRotate(tree, N->parent);
                N = N->left;
            } else {
                RBrightRotate(tree, N->parent);
                N = N->right;
            }

            // Updating pointers
            NG = N->parent->parent;
            N->parent->color = 'B';
            NG->color = 'R';

            // Second rotate
            if (N == N->parent->left) {
                RBrightRotate(tree, NG);
            } else {
                RBleftRotate(tree, NG);
            }
            break;

        //Case 5: node and parent are lefts or rights
        }else if ((N == N->parent->left && N->parent == NG->left) || (N == N->parent->right && N->parent == NG->right)) {

            N->parent->color = 'B';
            NG->color = 'R';

            if (N == N->parent->left) {
                RBrightRotate(tree, NG);
            } else {
                RBleftRotate(tree, NG);
            }
            break;
        }

    }
    tree->root->color = 'B';
}

void RBdelete(RBTree* tree, int id){
    RBNode* N = RBsearch(tree, id);
    if (N == NULL) {
        return;
    }

    RBNode* N1 = N;
    char C1 = N->color;
    RBNode* N2 = NULL; // For fixing

    //Case1: node doesnt have left child
    if (N->left == NULL) {
        N2 = N->right;
        RBshifting(tree, N, N2);

    //Case2: node doesnt have right child
    }else if (N->right == NULL) {
        N2 = N->left;
        RBshifting(tree, N, N2);

    //Case3: node has 2 children
    }else {
        N1 = RBminimum(N->right);
        C1 = N1->color;
        RBNode* temp = NULL;

        if (N1->parent != N) {
            temp = N1->right;
            RBshifting(tree, N1, N1->right);
            N1->right = N->right;
            if (N->right != NULL) {
                N1->right->parent = N1;
            }
        }else {
            temp = N1->right;
        }
        RBshifting(tree, N, N1);
        N1->left = N->left;
        if (N1->left != NULL) {
            N1->left->parent = N1;
        }
        N1->color = N->color;

        N2 = temp;
    }

    // Fixing:
    if (C1 == 'B') {
        while (N2 != NULL && N2 != tree->root && N2->color == 'B') {

            // If N2 is left child
            if (N2->parent->left == N2) {

                while (N2 != tree->root && N2->color == 'B') {

                    RBNode* NS = N2->parent->right; // node sibling

                    if (NS == NULL) {
                        N2 = N2->parent;
                        break;
                    }

                    // Case1: sibling is Red
                    if (NS->color == 'R') {
                        NS->color = 'B';
                        N2->parent->color = 'R';
                        RBleftRotate(tree, N2->parent);
                        NS = N2->parent->right;

                    //Case2: sibling is black with black children
                    }else if ((NS->left == NULL || NS->left->color == 'B') && (NS->right == NULL || NS->right->color == 'B')) {
                        NS->color = 'R';
                        N2 = N2->parent;

                    //Case3: sibling is black with red left child
                    }else {
                        if (NS->left != NULL && NS->left->color == 'R') {
                            if (NS->left != NULL) {
                                NS->left->color = 'B';
                            }
                            NS->color = 'R';
                            RBrightRotate(tree, NS);
                            NS = N2->parent->right;
                        }

                        //Case4: sibling is black with red right child
                        NS->color = N2->parent->color;
                        N2->parent->color = 'B';

                        if (NS->right != NULL) {
                            NS->right->color = 'B';
                        }

                        RBleftRotate(tree, N2->parent);
                        N2 = tree->root;
                    }
                }

            // If N2 is right child
            }else if (N2->parent->right == N2) {

                while (N2 != NULL && N2 != tree->root && N2->color == 'B'){

                    RBNode* NS = N2->parent->left;

                    if (NS == NULL) {
                        N2 = N2->parent;
                        break;
                    }

                    // Case1: sibling is Red
                    if (NS->color == 'R') {
                        NS->color = 'B';
                        N2->parent->color = 'R';
                        RBrightRotate(tree, N2->parent);
                        NS = N2->parent->left;

                    // Case2: sibling is Black with Black cildren
                    } else if ((NS->right == NULL || NS->right->color == 'B') && (NS->left == NULL || NS->left->color == 'B')) {
                        NS->color = 'R';
                        N2 = N2->parent;

                    //Case3: sibling is black with red right child
                    } else {
                        if (NS->right != NULL && NS->right->color == 'R') {
                            if (NS->right != NULL) {
                                NS->right->color = 'B';
                            }
                            NS->color = 'R';
                            RBleftRotate(tree, NS);
                            NS = N2->parent->left;
                        }

                        //Case4: sibling is black with red left child
                        NS->color = N2->parent->color;
                        N2->parent->color = 'B';

                        if (NS->left != NULL) {
                            NS->left->color = 'B';
                        }

                        RBrightRotate(tree, N2->parent);
                        N2 = tree->root;
                    }
                }
            }
        }

    }
    if (N2 != NULL) {
        N2->color = 'B';
    }

    free(N);
}
