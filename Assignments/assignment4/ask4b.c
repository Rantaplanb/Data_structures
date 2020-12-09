/* Ο αλγοριθμους μου σιγουρα δεν ειναι ο πιο αποδοτικος,
   ωστοσο ειναι απλος και κατανοητος. Πραγματοποιωντας
   μια διασχιση του δεντρου βρισκω το μεγιστο βαθος φυλλου
   σε πολυπλοκοτητα της ταξης Ο(n). Πραγματοποιωντας ακομα 
   μια διασχιση βρισκω το ελαχιστο βαθος φυλλου, επισης σε 
   πολυπλοκοτητα O(n). Τελος, αφαιρω το ελαχιστο απο το μεγιστο
   βαθος για να παρω την μεγιστη διαφορα βαθους μεταξυ φυλλων
   στο AVL δεντρο. Συνολικη πολυπλοκοτητα O(2*n) -> O(n).
   Εκανα διαφορες προσπαθειες για αυτη την ασκηση αλλα
   κατεληξα στο συμπερασμα οτι δεν ειναι εφικτο να βρεθει το
   ζητουμενο σε πολυπλοκοτητα μικροτερης ταξης απο O(n),
   συνεπως παρουσιαζω την αρχικη, οχι τοσο κομψη
   αλλα λειτουργικη απαντηση. */
   
#include <stdio.h>
#include <stdlib.h>

int min(struct node *root)
{
	//base case
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;

    if (root->left == 0) //νο left subtree, recurse right
    return min(root->right) + 1;

    if (root->right == 0) //no right subtree, recurse left
    return min(root->left) + 1;

	int base1 = min(root->left);
	int base2 = min(root->right);
	if(base1 <= base2) return (base1+1);
	else return (base2+1);
}

int max(struct node* root)
{
   if (root==NULL) return 0; //base case
   else{
       int lDepth = max(node->left); //vathos aristerou upodentrou
       int rDepth = max(node->right); //vathos deksiou upodentrou

       if (lDepth > rDepth) return (lDepth+1);
       else return (rDepth+1);
   }
}

int maxDepthDifference(struct node* rootAVL)
{
	return (max(rootAVL) - min(rootAVL));
}

