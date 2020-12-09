/* HY240b - Ask 3 */
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* leftChild;
    struct node* rightChild;
};
struct DS 
{
    struct node* root;
    int nn;
};

enum path{leftPath, rightPath}; //left=0, right=1;

//eisagwgi se plires diadiko dentro
int Insert(struct DS* H, int K)
{
    //New node creation and initialization
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = K;
    newNode->leftChild = NULL; //newNode will be a leaf
    newNode->rightChild = NULL;
	
    if(H->root == NULL){ //empty tree corner case
        H->root = newNode;
        return 1;
    }
	
    Stack s;
    H->nn++;
    int parentNum =  h->nn / 2;
	
    //Culculte path to newNode's parent and save it in the stack.
    while(parentNum <= 1){
        if((parentNum % 2) != 0)
            push(s, rightPath);
        else
            push(s, leftPath);
        parentNum = parentNum / 2;
    }
	
    struct node* tmp = H->root;
    while(!isEmptyStack(s)){
        if(pop(s))
            tmp = tmp->rightChild;
        else
            tmp = tmp->leftChild;
    }
    //now tmp points to the parent of the newNode.
	if(tmp->leftChild == NULL)
		tmp->leftChild = newNode;
	else
		tmp->rightChild = newNode;
	
	return 1;
}

/*
  Χρησιμοποιησα την τιμη του μετρητη για να υπολογισω
  την διαδρομη προς τον γονικο κομβο του νεου κομβου
  και την αποθηκευσα σε μια στοιβα. Επειτα ο αλγοριθμος
  πραγματοποιει h-1 διασχισεις ακολουθωντας την διαδρομη
  και τελος εισαγει τον νεο κομβο στην καταλληλη θεση.
  Τηρειται η ζητουμενη πολυπλοκοτητα O(h)!
*/

