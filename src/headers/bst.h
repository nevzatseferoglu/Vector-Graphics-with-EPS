#ifndef _BST_
#define _BST_

typedef struct Tree Tree;
typedef Tree* pTree;

struct Tree {

	struct Tree* right;
	struct Tree* left;
	double num;

};

void inorder(pTree root);
void insert(pTree* root , double num);
void tearUp(pTree root);
unsigned int findDepth(pTree root);

#endif