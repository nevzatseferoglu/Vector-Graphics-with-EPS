#include <stdio.h>
#include <stdlib.h>
#include "headers/bst.h"

pTree newNode(pTree right , pTree left , double num )
{
	pTree newNode = NULL;
	newNode = (pTree)malloc( sizeof(Tree) * 1 );
	
	newNode -> right = right;
	newNode -> left = left;
	newNode -> num = num;
}

void insert( pTree* root , double num )
{
	if( *root == NULL )
	{
		*root = newNode( NULL , NULL , num );	
	}
	else
	{
		if( num > ( (*root) -> num ) )
		{
			insert( &( (*root) -> right ) , num );
		}
		else
		{
			insert( &( (*root) -> left ) , num );
		}
	}
}

void inorder(pTree root) {
    if (root == NULL) {
        return;
    }
    else {
        inorder(root -> left);
        printf("%1lf\n", root -> num);
        inorder(root -> right);
    }
}

unsigned int findDepth(pTree root) {

    int left, right;

    if (root == NULL) {
        return 0;
    }

    left = 1 + findDepth(root->left);
    right = 1 + findDepth(root->right);

    if(left > right) {
        return left;
    }

    return right;
}

void tearUp(pTree root) {

    if ( root == NULL )
        return;

    tearUp(root -> left);
    tearUp(root -> right);

    free(root);

}

/*
int main(void) {

    pTree root = NULL;
    insert(&root, 5);

    tearUp(root);
    return 0;
}
*/
