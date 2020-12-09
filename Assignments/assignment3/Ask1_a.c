/*   HY240b - Askisi 1 - Erwtima A */
  
#include <stdio.h>
#include <stdlib.h>

//You may change the rank of the tree, preset to 3.
#define RANK 3

struct node
{
    int data;
    struct node* pArray[RANK]; //array of pointers to children, depends on tree rank!
};

struct node* createTree(int rank, int height)
{
    int i;
	if(rank < 0 || height < 0)
		return NULL;
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
	
	/* The span of the tree depends on its rank.
	I used a for loop to access all child pointers.*/
    if(height == 0){ //Base case
        for(i = 0; i < rank; i++){
            newNode->pArray[i] = NULL;
            //newNode->data = dataOfYourChoice;
            return newNode;
        }
    }
    else{
        for(i = 0; i < rank; i++){
            //newNode->data = dataOfYourChoice;
            newNode->pArray[i] = createTree(rank, height - 1);
        }
    }
    return newNode;
}

// Example driver program
int main()
{
    struct node* root = createTree(3, 3);
    //print NodeOfYourChoice
}