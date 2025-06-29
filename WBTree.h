#ifndef WBTREE_H
#define WBTREE_H

//Structure for Node of Tree
typedef struct WBNode {
    struct WBNode* parent;
    struct WBNode* left;
    struct WBNode* right;
    int id;
    int weight;
} WBNode;

//Structure for the whole Tree
typedef struct WBTree {
    WBNode* root;
} WBTree;


void WBcreate(WBTree* tree);

WBNode* WBcreateNode(int key);

int WBcompare(int key1, int key2);

void WBupdateWeight(WBNode* node);

WBNode* WBleftRotate(WBNode* N1);

WBNode* WBrightRotate(WBNode* N1);

void WBrebalance(WBTree* tree, WBNode* N);

WBNode* WBsearch(WBTree* tree, int key);

void WBinsert(WBTree* tree, int key);

void WBdelete(WBTree* tree, int key);

void WBprint(WBTree* tree, int maxKey);

#endif