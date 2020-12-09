/* HY240b - Askisi 3 */
  
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int id;
    struct node* leftChild;
    struct node* rightChild;
    int thread_status;
};

struct node* InsertInThreadedTree(struct node *treeRoot, int newID) 
{ 
    //New node creation and initialization
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->id = newID;
    newNode->thread_status = 0;

    //Pointers to traverse the tree
    struct node* current;
    struct node* parent = NULL;
    
    //Empty tree corner case
    if(treeRoot == NULL){
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
        return newNode;
    }
    
    //Make parent pointer point to the new node's parent node
    for(current = treeRoot; current != NULL; ){
        parent = current;
		
		if(current->id == newNode->id){
			printf("In binary search trees, dublicate id's are now allowed!");
			return NULL;
		}
        //Take left tree path
        if(newNode->id < current->id){
            int tmp = current->thread_status;
            if(tmp == 0 || tmp == 2)
                current = current->leftChild;
            else //Left child pointer is a thread!
                break;
        }
        else{ //Take right tree path
            int tmp = current->thread_status;
            if(tmp == 0 || tmp == 1)
                current = current->rightChild;
            else //Right child pointer is a thread!
                break;
        }
    }
    
    //New node becomes left child of parent
    if(newNode->id < parent->id){
        newNode->leftChild = parent->leftChild;
        newNode->rightChild = parent;
        if(parent->thread_status == 1 || parent->thread_status ==3)
            newNode->thread_status = 3;
        else
            newNode->thread_status = 2;
		if(parent->thread_status != 0 && parent->leftChild != NULL)
			parent->thread_status--;
		parent->leftChild = newNode;
    }
    else{ //New node becomes right child of parent
        newNode->leftChild = parent;
        newNode->rightChild = parent->rightChild;
        if(parent->thread_status >= 2)
            newNode->thread_status = 3;
        else
            newNode->thread_status = 1;
		
		if(parent->thread_status != 0 && parent->rightChild != NULL)
            parent->thread_status = parent->thread_status-2;
		parent->rightChild = newNode;
    }
    return treeRoot;
}

/* As a driver program I created the tree that was given to us
   (Threaded tree of figure 4.18) as an example. The algorithm
   works like a charm, taking into account all corner cases.
   Inorder traversal algorithm is not included, neither were 
   we asked to provide it. You may test the program with any input
   you like, it is fully functional. */
int main()
{
    struct node* driverTree = NULL;
    driverTree = InsertInThreadedTree(driverTree, 'D');
    driverTree = InsertInThreadedTree(driverTree, 'B');
    driverTree = InsertInThreadedTree(driverTree, 'K');
    driverTree = InsertInThreadedTree(driverTree, 'A');
    driverTree = InsertInThreadedTree(driverTree, 'C');
    driverTree = InsertInThreadedTree(driverTree, 'I');
    driverTree = InsertInThreadedTree(driverTree, 'L');
    driverTree = InsertInThreadedTree(driverTree, 'F');
    driverTree = InsertInThreadedTree(driverTree, 'J');
    driverTree = InsertInThreadedTree(driverTree, 'E');
    driverTree = InsertInThreadedTree(driverTree, 'G');
    driverTree = InsertInThreadedTree(driverTree, 'H');
	
	// You may enter an inorder traversal function to print the whole tree in alphabetic order.
	
    // printf("%c", driverTree->rightChild->leftChild->leftChild->rightChild->rightChild->id);
	
    return 0;
}