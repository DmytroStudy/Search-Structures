#ifndef RBTREE_H
#define RBTREE_H


//Structure for Node of Tree
typedef struct RBNode {
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
    int id;
    char color;
} RBNode;

//Structure for the whole Tree
typedef struct {
    RBNode* root;
} RBTree;


void RBcreate(RBTree* tree);

RBNode* RBcreateNode(int id);

int RBcompare(int id1, int id2);

void RBleftRotate(RBTree* tree, RBNode* N1);

void RBrightRotate(RBTree* tree, RBNode* N1);

void RBshifting(RBTree* tree, RBNode* N1, RBNode* N2);

RBNode* RBminimum(RBNode* N);

RBNode* RBsearch(RBTree* tree, int id);

void RBinsert(RBTree* tree, int id);

void RBdelete(RBTree* tree, int id);


#endif //RBTREE_H
