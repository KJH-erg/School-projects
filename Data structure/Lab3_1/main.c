#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node{
    struct tree_node *left_child;
    struct tree_node *right_child;
    int data;
    int level;
} Node;

typedef Node* Tree;


Tree Create(int key)
{
    Tree point;
    point = (Tree)malloc(sizeof(Tree));
    point->data = key;
    point->left_child = NULL;
    point->right_child = NULL;
    return point;
}
Tree searchPoint(Tree root, int key)
{

     if (root==NULL) return NULL;



     if ((key < root->data) && (root->left_child!=NULL)){

            return searchPoint(root->left_child, key);

     }
     if ((key > root->data) && (root->right_child!=NULL)){

            return searchPoint(root->right_child,key);

            }

     return root;

}

Tree insert(Tree root, int key)
{
	Tree ptr;
	Tree point;

	point = searchPoint(root, key);
	ptr =Create(key);


	if(point==NULL)
    {
        ptr->level =1;
        return ptr;
    }
    else if(point->data>key)
    {
        ptr->level = point->level+1;
        point->left_child = ptr;
    }
    else
    {
        ptr->level = point->level+1;
        point->right_child = ptr;
    }


	return root;	// root may be updated


}

void preorder(Tree root)
{
        if(root!=NULL){
        printf("%d %d\n", root->data, root->level);
        preorder(root->left_child);
        preorder(root->right_child);
        }


}

void postorder(Tree root)
{

        if(root!=NULL){
        postorder(root->left_child);
        postorder(root->right_child);
        printf("%d %d\n", root->data, root->level);
        }

}

int main()
{
    int n, key;
    Tree root = NULL;
    // printf("Input the number of integers:\n");
    scanf("%d",&n);
    // printf("Input these integers:\n");
    for(int i=0; i < n; i++)
    {
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("preorder\n");
    preorder(root);


    printf("postorder\n");
    postorder(root);

    return 0;
}
