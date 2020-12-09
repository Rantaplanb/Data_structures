
/* Λουκας Μερτζανης - 4457 - 4ο Σετ HY240b */

/* Θεωρω οτι τα στοιχεια του πινακα ειναι διαφορετικα μεταξυ τους εφοσον πραγματευομαστε διαταξη.

   Για τον 1ο αλγοριθμο:
   Ως γνωστον, σε O(nlogn) πολυπλοκοτητα μπορω να ταξινομησω τον πινακα σε αυξουσα σειρα.
   Στην συνεχεια θα επιστρεψω τα m πρωτα (μικροτερα) στοιχεια του. Συνολικη πολυπλοκοτητα
   O(nlogn + m) <= O(nlogn + n) δηλαδη O(nlogn) */
   
/* Δινω C κωδικα για τον αλγοριθμο, ο οποιος περιλαμβανει τον γνωστο sorting algorithm
   της merge-sort η οποια εκτελειται σε O(nlogn) οπου n το πληθος των στοιχειων του πινακα. */

void merge(int arr[], int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
    int L[n1], R[n2]; 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
    i = 0; // 1st subarray index 
    j = 0; // 2nd subarray index
    k = l; // Merged index
	//Merge two sub arrays into one sorted array
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]){ 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
  
void mergeSort(int arr[], int left, int right) 
{ 
    if (left < right) 
    { 
        int mid = (left+right)/2; 
        mergeSort(arr, left, mid); //Recurse to sort left subarray
        mergeSort(arr, mid+1, right); //Recurse to sort right subarray
        merge(arr, left, mid, right); 
    } 
} 

void printSmallestElements(int *arr, int size, int m)
{
	int i;
	mergeSort(arr, 0, size-1);
	printf("The %d smallest elements are: ", m);
	for(i = 0; i < m; i++){
		printf("%d ", arr[i]);
	}
}


/* Για τον 2ο αλγοριθμο:
   Θα διασχισω ολοκληρο τον πινακα m φορες. Κατα την 1η διασχιση θα τυπωσω το μικροτερο
   στοιχειο του πινακα. Κατα την 2η διασχιση θα τυπωσω το 2ο μικροτερο (δηλαδη το αμεσως
   μεγαλυτερο)... Κατα την διασχιση υπ'αριθμον m θα τυπωσω το m-οστο μικροτερο στοιχειο. 
   Καθε διασχιση ολοκληρου του πινακα εχει πολυπλοκοτητα O(n). 
   Εκτελω συνολικα m διασχισεις, οποτε προκυπτει συνολικη πολυπλοκοτητα της ταξης O(m*n).*/
   
#define MAX_VALUE 999999999
#define MIN_VALUE -999999999

void printSmallestElements(int* arr, int size, int m)
{
    int i, j, prev = MIN_VALUE, curr;
    printf("The %d smallest elements are: ", m);
    for(i = 0; i < m; i++){
        curr = MAX_VALUE;
        for(j = 0; j < size; j++){
            if((arr[j] < curr) && (arr[j] > prev))
                curr = arr[j];
        }
        printf("%d ", curr);
        prev = curr;
    }
}

/* Συγκρινοντας τις 2 πολυπλοκοτητες: O(m*n) και O(n*logn)
   Ουσιαστικα αρκει να συγκρινω τους ορους m και logn (αφου ο n ορος ειναι κοινος).
   Για μεγαλους πινακες, δηλαδη μεγαλο n, και μικρο m προφανως ειναι προτιμοτερο το O(m*n).
   Για μικρoμεσαιους πινακες, δηλαδη μικρο n, και μεγαλο m προφανως ειναι προτιμοτερο το O(n*logn).
   
   Γενικευοντας-> Αν: m < logn <=> 2^m < n τοτε προτιμαμε O(m*n), ειδαλλως Ο(n*logn).
   
   Πχ1: Εστω οτι εχουμε ενα array με 1.048.576 στοιχεια και θελουμε τα 5 μικροτερα:
		O(m*n) -> 5*1.048.576 στοιχειωδεις εντολες
		Ο(n*logn) -> 20*1.048.576 = 4*(5*1.048.576) στοιχειωδεις εντολες 
		Αναμενομενο αφου m < logn <=> 5 < 20
		
   Πχ2: Εστω οτι εχουμε ενα array με 1024 στοιχεια και θελουμε τα 100 μικροτερα:
		Ο(m*n) -> 100*1024 στοιχειωδεις εντολες 
		Ο(n*logn) -> 10*1024 στοιχειωδεις εντολες (10 φορες λιγοτερες)!!
		Αναμενομενο αφου m > logn <=> 100 > 10 */
