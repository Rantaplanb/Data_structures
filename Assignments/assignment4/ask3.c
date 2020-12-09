/* Αρχικα ταξινομω τον πινακα χρησιμοποιοντας τον merge-sort αλγοριθμο-κωδικα
   που δοθηκε στην ασκηση 1. Η ταξινομηση εχει O(n*logn) πολυπλοκοτητα. Στην συνεχεια,
   κατασκευαζω απο τον ταξινομημενο πινακα ενα δυαδικο δεντρο αναζητησης με αναδρομικο
   αλγοριθμο πολυπλοκοτητας O(n). Για να φροντισουμε ωστε το υψος του δεντρου να ανηκει
   στο O(logn) πρεπει να κατασκευασουμε ισοζυγισμενο δεντρο. Για να το πετυχουμε αυτο,
   σε καθε αναδρομικη κληση ακολουθουμε τα εξης βηματα:
   
   -"Κοβουμε" τον πινακα στην μεση και θεωρουμε ριζα τον κομβο που δημιουργειται απο το
   μεσαιο στοιχειο.
   -Αναδρομικα κατασκευαζουμε το αριστερο υποδεντρο (root->lc) απο το πρωτο μισο του πινακα.
   -Αναδρομικα κατασκευαζουμε το δεξι υποδεντρο (root->rc) απο το δευτερο μισο του πινακα.
   
   Καθ' αυτο τον τροπο, μοιραζουμε καταλληλα τους κομβους στα υποδεντρα ωστε να προκυψει
   ισοζυγισμενο δεντρο δυαδικης αναζητησης. Συνολικη χρονικη πολυπλοκοτητα O(n*logn + n) -> O(nlogn)
*/

struct treeNode {
    int data;                                  
    struct treeNode *lc;                      
    struct treeNode *rc;                     
};

struct treeNode* constructBST(int arr[], int start, int finish)
{
    if (start > finish) return NULL; //Βαση αναδρομης
	
    struct treeNode* root = (struct treeNode*) malloc(sizeof(struct treeNode));
	root->lc = root->rc = NULL;
	
    int middle = (start + finish)/2; //Ετσι, θα προκυψει ισοζυγισμενο δεντρο υψους Ο(logn)
    root = arr[middle];
	
    root->lc =  constructBST(arr, start, middle-1);
    root->rc = constructBST(arr, middle+1, finish);
    return root;
}

struct treeNode* arrayToBST(int T[], int n)
{
	struct treeNode* balancedBST;
	mergeSort(T, 0, n-1); //Υλοποιηση της mergeSort() δινεται στην ασκηση 1
	balancedBST = constructBST(T[], 0, n-1);
	return balancedBST;
}