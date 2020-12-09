/* HY240b - Ask 1 - Erwtima b */
#include <stdio.h>
#include <stdlib.h>

//Εστω οτι καθε κομβος του δεντρου Τ ειναι της μορφης:
struct node
{
    char key;
    struct node* leftChild;
    struct node* rightSibling;
};

/*
  Καθως αναζητω τον keyNode στο δεντρο Τ, αυξανω την τιμη
  της μεταβλητης vathos μονο οταν διασχιζω leftChild pointer,
  καθως τοτε μονο μεταβαινω στο επομενο επιπεδο βαθους του
  διατεταγμενου δεντρου Δ (του οποιου το βαθος κομβου αναζητω).
*/  
int getNodeDepth(struct node *root, struct node* keyNode, int vathos) 
{ 
    int epomenoVathos;
    if (root == NULL) 
        return 0; 
    if (root->key == keyNode->key)
        return vathos; 
	//Recurse on subtrees until keyNode is found and base cases are hit.
    epomenoVathos = getDepth(root->leftChild, keyNode, vathos + 1); 
    if (epomenoVathos != 0) 
        return epomenoVathos; 
    epomenoVathos = getDepth(root->rightSibling, keyNode, vathos); 
    return epomenoVathos; 
}


//Driver program
int main()
{
    struct node n1, n2, n3, n4, n5, n6;
    n1.key = 'a';
    n2.key = 'b';
    n3.key = 'c';
    n4.key = 'd';
    n5.key = 'e';
    n6.key = 'g';
    n1.rightSibling = NULL;
    n1.leftChild = &n2;
    n2.rightSibling = &n3;
    n2.leftChild = &n5;
    n5.rightSibling = NULL;
    n5.leftChild = NULL;
    n3.rightSibling = &n4;
    n3.leftChild = NULL;
    n4.rightSibling = NULL;
    n4.leftChild = &n6;
    n6.leftChild = NULL;
    n6.rightSibling = NULL;
	
    int nodeDepth = getDepth(&n1, &n6, 0);
    printf("%d", h);
}