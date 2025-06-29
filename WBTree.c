#include <stdio.h>
#include <stdlib.h>
#include "WBTree.h"


void WBcreate(WBTree* tree) {
    tree->root = NULL;
}

WBNode* WBcreateNode(int id) {
    WBNode* node = (WBNode*)malloc(sizeof(WBNode));
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->id = id;
    node->weight = 1;
    return node;
}


// Rebalancing functions
int WBcompare(int id1, int id2) {
    if (id1 > id2) return 1;
    if (id1 < id2) return -1;
    if (id1 == id2) return 0;
}

void WBupdateWeight(WBNode* node) {

    int weight = 1;

    if (node != NULL) {
        if (node->left != NULL) {
            weight += node->left->weight;
        }
        if (node->right != NULL) {
            weight += node->right->weight;
        }
        node->weight = weight;
    }
}

WBNode* WBleftRotate(WBNode* N1) {
    WBNode* N2 = N1->right;
    WBNode* N3 = N2->left;

    N2->parent = N1->parent;
    N2->left = N1;
    N1->parent = N2;
    N1->right = N3;

    if (N3) {
        N3->parent = N1;
    }
    WBupdateWeight(N1);
    WBupdateWeight(N2);
    return N2;
}

WBNode* WBrightRotate(WBNode* N1) {
    WBNode* N2 = N1->left;
    WBNode* N3 = N2->right;

    N2->parent = N1->parent;
    N2->right = N1;
    N1->parent = N2;
    N1->left = N3;

    if (N3) {
        N3->parent = N1;
    }
    WBupdateWeight(N1);
    WBupdateWeight(N2);
    return N2;
}

void WBrebalance(WBTree* tree, WBNode* N) {
    while (N) {
        WBNode* N0 = N;
        WBNode* N1 = N;

        WBNode* left = N1->left;
        WBNode* right = N1->right;

        int leftWeight = 0;
        int rightWeight = 0;

        if (left != NULL) {
            leftWeight = left->weight;
        }

        if (right != NULL) {
            rightWeight = right->weight;
        }

        // If tree skewed to the left
        if (rightWeight * 5 + 2 < leftWeight * 2) {
            int a = 0;
            if (left->left != NULL) {
                a = left->left->weight;
            }

            if (a * 5 < leftWeight * 2) {
                N1->left = WBleftRotate(left); // Small rotate
            }
            N1 = WBrightRotate(N1); // Big rotate

        // If tree skewed to the right
        }else if (leftWeight * 5 + 2 < rightWeight * 2) {

            int a = 0;
            if (right->right != NULL) {
                a = right->right->weight;
            }

            int b = 0;
            if (right->left != NULL) {
                b = right->left->weight;
            }

            if (a * 5 < b * 2) {
                N1->right = WBrightRotate(right); // Small rotate
            }
            N1 = WBleftRotate(N1); // Big rotate

        // No need for rebalance
        }else {
            N1->weight = leftWeight + rightWeight + 1;
            break;
        }


        // Updating root if necessary
        N = N1->parent;
        if (!N) {
            tree->root = N1;
        }
        else if (N->left == N0) {
            N->left = N1;
        }
        else {
            N->right = N1;
        }
    }
}


// Interactions with tree
WBNode* WBsearch(WBTree* tree, int id) {
    if (tree == NULL || tree->root == NULL) {
        return NULL;
    }

    WBNode* N = tree->root;

    while (N) {
        int c = WBcompare(N->id, id); // Comparing root with id

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

void WBinsert(WBTree* tree, int id) {
    WBNode* N1 = NULL;
    WBNode* N2 = tree->root;
    int c = 0;

    // Finding place for insert
    while (N2) {
        c = WBcompare(N2->id, id);

        // If value is duplicate just skipping
        if (c == 0) {
            return;
        }

        // Reminding parent
        N1 = N2;

        if (c < 0) {
            N2 = N2->right;
        }else {
            N2 = N2->left;
        }
    }

    // Creating new Node
    WBNode* N3 = WBcreateNode(id);
    N3->parent = N1;

    // Inserting to tree
    if (N1 == NULL) {
        tree->root = N3; // If tree was empty
    } else {
        if (c <= 0) {
            N1->right = N3;
        }else {
            N1->left = N3;
        }

        //Updating all weights
        WBNode* N4 = N1;
        while (N4) {
            WBupdateWeight(N4);
            N4 = N4->parent;
        }

        WBrebalance(tree, N1); // Rebalancing tree
    }
}

void WBdelete(WBTree* tree, int id) {
    WBNode* node = WBsearch(tree, id);

    if (node == NULL || tree == NULL) {
        return; // Node is empty
    }

    WBNode* NP = node->parent;
    WBNode* NL = node->left;
    WBNode* NR = node->right;
    WBNode* N1 = NULL; // New node
    WBNode* N0 = NULL; // Node for rebalancing

    // Case 1: Node doesn't have right child
    if (NR == NULL) {
        N1 = NL; // Replacing with left child
        N0 = NP;

    // Case 2: Node has right child that has left child
    }else if (NR->left != NULL) {
        N1 = NR;

        // Finding most left child in right subtree
        while (N1->left != NULL) {
            N0 = N1;
            N1 = N1->left;
        }

        // If N1 has a child
        WBNode* a = N1->right;
        if (N0 != NULL) {
            N0->left = a;
            if (a != NULL) {
                a->parent = N0;
            }
        }

    // Case3: Node has right child, but doesn't have left child
    }else {
        N0 = NR;
        N1 = NR; // Replacing with right child
    }

    // Replacing deleted node with new
    if (NP == NULL) {
        tree->root = N1; // If node was a root

    } else if (NP->left == node) {
        NP->left = N1; // If deleted node was left child

    } else {
        NP->right = N1; // If deleted node was right child
    }

    // Updating childs and parent
    if (N1 != NULL) {
        N1->parent = NP; // New Parent

        if (NL != NULL && NL != N1) { // If left child exists
            N1->left = NL;
            NL->parent = N1;
        }

        if (NR != NULL && N1 != NR) { // If right child exists
            N1->right = NR;
            NR->parent = N1;
        }
    }

    // Updating all weights
    WBNode* N2 = N0;
    while (N2!=NULL) {
        WBupdateWeight(N2);
        N2 = N2->parent;
    }
    WBrebalance(tree, N0);
    free(node);
}

void WBprint(WBTree* tree, int maxid) {
    printf("WBTree:\n");
    for (int i = 1; i <= maxid; i++) {
        WBNode* node = WBsearch(tree, i);
        if (node) {
            printf("%d, ", node->id);
        }
    }
}