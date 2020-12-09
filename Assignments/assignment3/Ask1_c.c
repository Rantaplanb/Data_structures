/*   HY240b - Askisi 1 - Erwtima C */
  
#include <stdio.h>
#include <stdlib.h>

//Εστω οτι καθε κομβος του δεντρου ειναι της μορφης:
struct node
{
	int data;
	struct node* leftChild;
	struct node* rightChild;
};

int preOrderTraversal(struct node* treeRoot)
{
	Stack s = makeEmptyStack();
	
	if(treeRoot == NULL)
		return 0;
	
	for(push(&s, treeRoot); !isEmptyStack(&s); pop(&s)){
		struct node* current = top(&s);
		//Apply a function to the current node
		//EG: printf("%d\n", current->data);
		if(current->rightChild != NULL)
			push(&s, current->rightChild);
		if(current->leftChild != NULL)
			push(&s, current->left);
	}
	
	return 1;
}