#include "airlines.h"

struct planeData{
    int pid;                                   
    int dest;                           
    int depart_time;                     
};

struct node{
    int path; //1 = leftPath, 2 = middledlePath, 3 = rightPath
    struct node* next;
};

int initialize() {
    int i;
    /*Header node of sorted, doubly linked, airline list.*/
    airlines = (_airline*)malloc(sizeof(_airline));
    airlines->aid = 9999;
    airlines->next = airlines;
    airlines->prev = airlines;
    airlines->pR = NULL;
    /*Set destTable pointers to null*/
    for(i=0; i<10; i++)
        DESTINATIONS[i] = NULL;
    /*initialize priority queue*/
    PQ = (_priority_queue*)malloc(sizeof(_priority_queue));
    PQ->num_elements = -1; //may be changed
    PQ->Q = NULL;
    /*initialize fifo queue*/
    FQ = (_fifo_queue*)malloc(sizeof(_fifo_queue));
    return 1;
}

void inorderTraversal(_airplane *root)
{
    if (root != NULL){
        inorderTraversal(root->lc);
        printf("%d, ", root->pid);
        inorderTraversal(root->rc);
    }
}

int print_airlines() {
    _airline* tmp = airlines->next;
    while(tmp->aid != 9999){
        printf("Airline%d = ", tmp->aid);
        inorderTraversal(tmp->pR);
        printf("\n");
        tmp = tmp->next;
    }
	printf("DONE\n");
    return 1;
}

void printAirlineList()
{
    _airline* tmp = airlines->next;
    printf("Airlines = ");
    while(tmp->aid != 9999){
        printf("%d, ", tmp->aid);
        tmp = tmp->next;
    }
    printf("\n");
}

/*Returns leftmost node of a threaded tree*/
_flight* leftMost(_flight* root)
{
    if (root == NULL)
       return NULL;
    while( (root->lc != NULL)&& !(root->thread_status%2) ) //oso aristera den einai null, oute thread
        root = root->lc;
    return root;
}

/*Inorder traversal of a threaded tree(using threads)*/
void inorderThreaded(_flight *root)
{
    _flight* tmp = leftMost(root);
    while (tmp != NULL)
    {
        printf("%d:%d, ", tmp->pid, tmp->depart_time);
        //if tmp has a right thread, use it to find the inorder successor
        if (tmp->thread_status >=2)
            tmp = tmp->rc;
        else // Else go to the leftmost child in right subtree (inorder successor)
            tmp = leftMost(tmp->rc);
    }
}

int print_destinations() {
    int i;
    for(i=0; i<10; i++){
        printf("Destination%d = ", i+1);
        inorderThreaded(DESTINATIONS[i]);
        printf("\n");
    }
    printf("DONE\n");
    return 1;
}

int register_airline(int aid) {
    /*Allocate memory for new airline node and initialize*/
    _airline* newAirline = (_airline*)malloc(sizeof(_airline));
    if(newAirline == NULL){
        printf("\nMemory allocation failed!");
        return 0;
    }
    newAirline->aid = aid;
    newAirline->pR = NULL;
    /*Insert node in sorted doubly linked list*/
    if(airlines == airlines->next){ /*empty list case*/
        airlines->next = newAirline;
        airlines->prev = newAirline;
        newAirline->next = airlines;
        newAirline->prev = airlines;
    }
    else{ /*common insertion case*/
        _airline* tmp = airlines;
        while(tmp->next->aid < newAirline->aid)
            tmp = tmp->next;
        tmp->next->prev = newAirline;
        newAirline->next = tmp->next;
        newAirline->prev = tmp;
        tmp->next = newAirline;
    }
    printAirlineList();
    printf("DONE\n");
    return 1;
}

/*Search the airline list and return airline with aid = aidValue*/
_airline* searchAirline(int aidValue)
{
    int flag = 0;
    if(airlines == airlines->next){
        printf("Airline list is empty!");
        return NULL;
    }
    _airline* tmp = airlines->next;
    while(1){
        if(tmp->aid == aidValue)
            return tmp;
        if(tmp->aid == 9999){
            flag++;
        }
        if(flag == 1) //airline does not exist!
            return NULL;
        tmp = tmp->next;
    }
}

/*Airplane insertion in the plane BST*/
_airplane* insertPlane(_airplane* airplane, _airplane* root)
{
    if (root == NULL) return airplane;

    if (airplane->pid < root->pid){
        root->lc  = insertPlane(airplane, root->lc);
    }
    else if (airplane->pid > root->pid) {
        root->rc = insertPlane(airplane, root->rc);
    }
    return root;
}

/*Flight insertion in the threaded BST*/
_flight* InsertInThreadedTree(_flight* treeRoot, _flight* newNode)
{
    _flight* current;
    _flight* parent = NULL;
    if(treeRoot == NULL){ //Empty tree case
        newNode->lc = NULL;
        newNode->rc = NULL;
        return newNode;
    }
    //Traverse/search the tree to make parent point to the new node's parent node
    for(current = treeRoot; current != NULL; ){
        parent = current;
        //Take left tree path
        if(newNode->depart_time < current->depart_time){
            int tmp = current->thread_status;
            if(tmp == 0 || tmp == 2) //if no left thread
                current = current->lc;
            else //Left child pointer is a thread so we reached a leaf
                break;
        }
        else{ //Take right tree path
            int tmp = current->thread_status;
            if(tmp == 0 || tmp == 1) //if no right thread
                current = current->rc;
            else //Right child pointer is a thread so we reached a leaf
                break;
        }
    } 
    //New node becomes left child of parent
    if(newNode->depart_time < parent->depart_time){
        newNode->lc = parent->lc;
        newNode->rc = parent;
        //if parent had a left thread, newNode will have both threads
        if(parent->thread_status == 1 || parent->thread_status ==3) 
            newNode->thread_status = 3;
        else //only right thread
            newNode->thread_status = 2;
		if(parent->thread_status != 0 && parent->lc != NULL) //parent's Lthread becomes a child
			parent->thread_status--;
		parent->lc = newNode;
    }
    else{ //New node becomes right child of parent
        newNode->lc = parent;
        newNode->rc = parent->rc;
        //if parent had a right thread, newNode will have both threads
        if(parent->thread_status >= 2)
            newNode->thread_status = 3;
        else //only left thread
            newNode->thread_status = 1;
		if(parent->thread_status != 0 && parent->rc != NULL) //parent's Rthread becomes a child
            parent->thread_status = parent->thread_status-2;
		parent->rc = newNode;
    }
    return treeRoot;
}


int insert_airplane(int pid, int aid, int dest, int depart_time)
{
    /*Allocate memory for new airplane node and initialize*/
    _airplane* newAirplane = (_airplane*)malloc(sizeof(_airplane));
    if(newAirplane == NULL){
        printf("\nMemory allocation failed!");
        return 0;
    }
    newAirplane->pid = pid;
    newAirplane->dest = dest;
    newAirplane->depart_time = depart_time;
    newAirplane->lc = NULL;
    newAirplane->rc = NULL;
    //Insert new plane node in BST
    _airline* currAirline = searchAirline(aid);
    if(currAirline->pR == NULL) //empty BST
        currAirline->pR = insertPlane(newAirplane, currAirline->pR);
    else
        insertPlane(newAirplane, currAirline->pR);

    /*Allocate memory for new flight node and initialize*/
    _flight* newFlight = (_flight*)malloc(sizeof(_flight));
    if(newFlight == NULL){
        printf("\nMemory allocation failed!");
        return 0;
    }
    newFlight->pid = pid;
    newFlight->depart_time = depart_time;
    newFlight->thread_status = 0;
    //Insert new flight node in threaded BST
    DESTINATIONS[dest] = InsertInThreadedTree(DESTINATIONS[dest], newFlight);
    printf("Airline%d = ", aid);
    inorderTraversal(currAirline->pR);
    printf("\n");
    printf("Destination%d = ", dest+1);
    inorderThreaded(DESTINATIONS[dest]);
    printf("\nDONE\n");
    return 1;
}

_airplane* smallestPlane(_airplane* root)
{
    _airplane* tmp = root;
    while (tmp && tmp->lc != NULL)
        tmp = tmp->lc;
    return tmp;
}

/* Searches and deletes the plane node with pid from the plane BST*/
_airplane* deletePlane(_airplane* root, int pid)
{
    if (root == NULL) return root; //empty tree corner case

    /*Search node in BST to be deleted*/
    if (pid < root->pid) //recurse left
        root->lc = deletePlane(root->lc, pid);
    else if (pid > root->pid) //recurse right
        root->rc = deletePlane(root->rc, pid);
    else //found
    {
        //Subcases
        if (root->lc == NULL) //only right child or none
        {
            _airplane* temp = root->rc; //replace deleted node with rc
            free(root);
            return temp;
        }
        else if (root->rc == NULL) //only left child
        {
            _airplane *temp = root->lc; //replace deleted node with lc
            free(root);
            return temp;
        }
        //Two children: replace with inorder successor node (smallest of right subtree)
        _airplane* temp = smallestPlane(root->rc);
        //Copy successor's content to the node that must be deleted
        root->pid = temp->pid;
        //Delete successor
        root->rc = deletePlane(root->rc, temp->pid);
    }
    return root;
}

int cancel_flight(int aid, int pid, int dest) {
    _airline* airline = searchAirline(aid);
    //code to delete plane's flight!
    //reconstructThreaded
    //DESTINATIONS[dest] = reconstructThreaded(DESTINATIONS[dest], pid);
    airline->pR = deletePlane(airline->pR, pid);
    printf("Airline%d = ", aid);
    inorderTraversal(airline->pR);
    printf("\n");
    printf("Destination%d = ", dest+1);
    inorderThreaded(DESTINATIONS[dest]);
    printf("\nDONE\n");
    return 1;
}

/*Traverse plane BST in post order, for every plane delete the 
corresponding flight and then delete the plane itself */
void deletePostOrderBSTandThreaded(_airplane* root)
{
    if (root == NULL) return;
    deletePostOrderBSTandThreaded(root->lc);
    deletePostOrderBSTandThreaded(root->rc);
    //add code to delete flight nodes here
    free(root);
}

//Not ready yet
int delete_airline(int aid) {
    _airline* tmp = searchAirline(aid);
    _airplane* planeRoot = tmp->pR;
    deletePostOrderBSTandThreaded(planeRoot); //delete planes and flights
    tmp->prev->next = tmp->next; //delete airline
    tmp->next->prev = tmp->prev;
    free(tmp);
    printf("Airlines\n");
    print_airlines();
    printf("Destinations\n");
    print_destinations();
    return 1;
}

/*Saves all planes' data of a plane BST in a sorted array*/
void inorderSaver( _airplane* root, struct planeData arr[], int* i)
{
    if (root == NULL) //base case
        return;
    inorderSaver(root->lc, arr, i); //recurse left
    //save current node
    arr[*i].depart_time = root->depart_time;
    arr[*i].dest = root->dest;
    arr[*i].pid = root->pid;
    (*i)++;  // increase array index
    inorderSaver(root->rc, arr, i); //recurse right
}

/*Combines two sorted arrays containing plane data into a bigger one (still sorted) */
struct planeData* merge(struct planeData arr1[], struct planeData arr2[], int n1, int n2)
{
    struct planeData* result = (struct planeData*) malloc((n1+n2)*sizeof(struct planeData));
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2)  { //Traverse arrays
        //Sorting based on pid
        if (arr1[i].pid < arr2[j].pid){ //copy arr1 element
            result[k].depart_time = arr1[i].depart_time;
            result[k].pid = arr1[i].pid;
            result[k].dest = arr1[i].dest;
            i++;
        }
        else{ //copy arr2 element
            result[k].depart_time = arr2[j].depart_time;
            result[k].pid = arr2[j].pid;
            result[k].dest = arr2[j].dest;
            j++;
        }
        k++;
    }
    while (i < n1) { //Copy elements left in arr1(if any)
        result[k].depart_time = arr1[i].depart_time;
        result[k].pid = arr1[i].pid;
        result[k].dest = arr1[i].dest;
        i++; k++;
    }
    while (j < n2){ //Copy elements left in arr2(if any)
        result[k].depart_time = arr2[j].depart_time;
        result[k].pid = arr2[j].pid;
        result[k].dest = arr2[j].dest;
        j++; k++;
    }
    return result;
}

/*Create an airplane node from a planeData element to reconstruct the tree*/
_airplane* convert2PlaneNode(struct planeData element)
{
    _airplane* new = (_airplane*) malloc(sizeof(_airplane));
    new->depart_time = element.depart_time;
    new->dest = element.dest;
    new->pid = element.pid;
    new->lc = NULL;
    new->rc = NULL;
    return new;
}

/*Recursively constructs a plane BST from a sorted array containing planes' data*/
_airplane* sortedArrayToBST(struct planeData arr[], int start, int finish)
{
    if (start > finish) //Base case
      return NULL;
    //Middle arr element becomes root: helps keep tree balanced
    int middle = (start + finish)/2;
    _airplane* root = convert2PlaneNode(arr[middle]);
    //Construct left subtree using 1st half of the array
    root->lc =  sortedArrayToBST(arr, start, middle-1);
    //Construct right subtree using 2nd half of the array
    root->rc = sortedArrayToBST(arr, middle+1, finish);
    return root;
}

/*Count nodes contained in a BST*/
int countNodes(_airplane* root)
{
  if (root==NULL) return 0;
  else
      return(countNodes(root->lc) + 1 + countNodes(root->rc));
}

/*Free all plane nodes contained in BST*/
void BSTdeletePostOrder(_airplane* root)
{
    if (root == NULL) return;
    BSTdeletePostOrder(root->lc);
    BSTdeletePostOrder(root->rc);
    free(root);
}

/*Combines two BST's by storing their data in a sorted array, deleting both 
trees completely and reconstructing a new tree from the sorted array */
_airplane* combineBinarySearchTrees(_airplane* root1, _airplane* root2)
{
    //count nodes of each tree O(n1+n2)
    int n1 = countNodes(root1);
    int n2 = countNodes(root2);
    if(n2 == 0) //seller has no planes corner case
        return root1;

    //allocate 2 arrays to store the data of each tree's planes
    struct planeData* treeArray1 = (struct planeData*) malloc(n1*sizeof(struct planeData));
    struct planeData* treeArray2 = (struct planeData*) malloc(n2*sizeof(struct planeData));

    //Save planes' data in arrays and delete trees
    int index = 0;
    inorderSaver(root1, treeArray1, &index); //O(n1)
    BSTdeletePostOrder(root1); //O(n1)
    index = 0;
    inorderSaver(root2, treeArray2, &index); //O(n2)
    BSTdeletePostOrder(root2); //O(n2)

    //Merge the two sorted arrays O(n1+n2)
    struct planeData* finalTreeArr = merge(treeArray1, treeArray2, n1, n2);

    //Construct new BST from merged array and return its root O(n1+n2)
    return sortedArrayToBST(finalTreeArr, 0, n1+n2-1);
}

/* Time complexity of O(5*(n1+n2)) -> O(n1+n2) */
int acquisition_airline(int aid1, int aid2) {
    _airline* seller = searchAirline(aid1); //to be deleted
    _airline* buyer = searchAirline(aid2);
    buyer->pR = combineBinarySearchTrees(buyer->pR, seller->pR);
    seller->prev->next = seller->next;
    seller->next->prev = seller->prev;
    free(seller);
    print_airlines();
    return 1;
}

/*Returns the number of plane nodes that DON'T fly to dest*/
int countNotSoldNodes(_airplane* root, int dest)
{
    if (root==NULL)
        return 0;
    else if(dest == root->dest) //This node will be deleted from the tree
        return(countNotSoldNodes(root->lc, dest) + countNotSoldNodes(root->rc, dest));
    else
        return(countNotSoldNodes(root->lc, dest) + 1 + countNotSoldNodes(root->rc, dest));
}

/*Stores planes' data that are NOT going to be sold in an array (sorted)*/
void inorderSaverNotDest( _airplane* root, struct planeData arr[], int* i, int dest)
{
    if (root == NULL) //base case
        return;
    inorderSaverNotDest(root->lc, arr, i, dest); //Recurse left
    if(dest != root->dest){ //Save plane's data if it is NOT gonna be sold
        arr[*i].depart_time = root->depart_time;
        arr[*i].dest = root->dest;
        arr[*i].pid = root->pid;
        (*i)++;  // increase index for next entry
    }
    inorderSaverNotDest(root->rc, arr, i, dest); //Recurse right
}

/*Traverses seller's plane tree in postorder, if a plane travels to dest,
it is inserted in buyer's plane BST, otherwise it gets deleted*/
void insertOrDestroy(_airplane* seller, _airplane* buyer, int dest)
{
    if(seller == NULL) //Base case
        return;
    insertOrDestroy(seller->lc, buyer, dest);
    insertOrDestroy(seller->rc, buyer, dest);
    if(seller->dest == dest){
        seller->rc = NULL;
        seller->lc = NULL;
        insertPlane(seller, buyer);
    }
    else
        free(seller);
    return;
}

/*Final complexity of O(h*m) */
int subsidiary_airline(int aid1, int aid2, int dest) {
    _airline* seller = searchAirline(aid1);
    _airline* buyer = searchAirline(aid2);
    int notSoldNodesNum = countNotSoldNodes(seller->pR, dest); //O(m)
    struct planeData* sellerTreeArr = (struct planeData*) malloc(notSoldNodesNum*sizeof(struct planeData));
    int index = 0;
    inorderSaverNotDest(seller->pR, sellerTreeArr, &index, dest); //O(m)
    insertOrDestroy(seller->pR, buyer->pR, dest); //O(h*m)
    seller->pR = sortedArrayToBST(sellerTreeArr, 0, notSoldNodesNum-1); // O(m)
    print_airlines();
    return 1;
}

int find_flight(int dest, int ts) {
    _flight* tmp = leftMost(DESTINATIONS[dest]);
    printf("Available flights = ");
    while(tmp != NULL){
        if(tmp->depart_time > ts)
            printf("%d:%d, ", tmp->pid, tmp->depart_time);
        if(tmp->thread_status >= 2)
            tmp = tmp->rc;
        else 
            tmp = leftMost(tmp->rc);
    }
    printf("\nDestination%d = ", dest+1);
    inorderThreaded(DESTINATIONS[dest]);
    printf("\nDONE\n");
    return 1;
}

/*I have changed the fifo queue to contain an array of pointers (**Q), 
intead of an array of structs because of space efficiency */
int print_clients() {
    FQ->Q = (_client**)malloc((PQ->num_elements+1)*sizeof(_client*)); 
    FQ->front = 0;
    FQ->length = 0;
    int i;
    //initialize queue pointers to NULL
    for(i=0; i<PQ->num_elements+1; i++){
        FQ->Q[i] = NULL;
    }
    _client* curr = PQ->Q;
    printf("Priority Queue = ");
    while(curr){
        printf("%d:%d, ", curr->cid, curr->miles); //Visit current
        if(curr->lc){ //Enqueue its left child
            FQ->Q[FQ->length] = curr->lc;
            FQ->length++;
        }
        if(curr->mc){ //Enqueue its middle child
            FQ->Q[FQ->length] = curr->mc;
            FQ->length++;
        }
        if(curr->rc){ //Enqueue its right child
            FQ->Q[FQ->length] = curr->rc;
            FQ->length++;
        }
        curr = FQ->Q[FQ->front]; //Continue with the first enqueued element (FIFO)
        FQ->front++;
    }
	printf("\nDONE\n");
    return 1;
}
/* Complexity of O(h) where h is the height of the priority queue triad tree*/
int new_client(int cid) {
	PQ->num_elements++;
    //new node creation and initialization
    _client* newClient = (_client*)malloc(sizeof(_client));
    newClient->cid = cid;
    newClient->miles = 0;
    newClient->lc = newClient->mc = newClient->rc = newClient->p = NULL;

    //empty tree case
    if(PQ->Q == NULL){
        PQ->Q = newClient;
		print_clients();
		printf("\nDONE\n");
        return 1;
    }
    int parentNum = (PQ->num_elements - 1)/3;
    struct node* pathHead = NULL;

    //calculate path (bottom->root) and store it in a linked list-> Ο(h)
    while(parentNum > 0){
        struct node* currentChoice = (struct node*)malloc(sizeof(struct node));
        currentChoice->next = pathHead;
        if((parentNum % 3) == 1) //1?
            currentChoice->path = 1; //leftPath
        else if((parentNum % 3) == 2)
            currentChoice->path = 2; //middledlePath
        else
            currentChoice->path = 3; //rightPath

        pathHead = currentChoice;
        parentNum = (parentNum - 1)/3;
    }
    //Now the linked list contains the path to the parent of the new node(root->bottom)

    struct node* choice = pathHead;
    _client* tmp = PQ->Q;
    //traverse tree according to the precalculated path -> O(h)
    while(choice != NULL){
        if(choice->path == 1)
            tmp = tmp->lc;
        else if(choice->path == 2)
            tmp = tmp->mc;
        else
            tmp = tmp->rc;
        choice = choice->next;
    }
    //now tmp points to the parent of the new node
    if(tmp->lc == NULL){
        tmp->lc = newClient;
    }
    else if(tmp->mc == NULL){
        tmp->mc = newClient;
    }
    else{
        tmp->rc = newClient;
    }
    newClient->p = tmp;
    print_clients();
    return 1;
}


int erase_client() {
    int parentNum = (PQ->num_elements - 1)/3;
    struct node* pathHead = NULL;
    if(PQ->num_elements < 0){
        printf("EMPTY TREE!");
        exit(1);
    }
    //calculate path (bottom->root) and store it in a linked list
    while(parentNum > 0){
        struct node* currentChoice = (struct node*)malloc(sizeof(struct node));
        currentChoice->next = pathHead;
        if((parentNum % 3) == 1) //1?
            currentChoice->path = 1; //leftPath
        else if((parentNum % 3) == 2)
            currentChoice->path = 2; //middledlePath
        else
            currentChoice->path = 3; //rightPath

        pathHead = currentChoice;
        parentNum = (parentNum - 1)/3;
    }
    //Now the linked list contains the path to the parent of the last node
    
    struct node* choice = pathHead;
    _client* tmp = PQ->Q;
    //traverse tree according to the precalculated path -> O(h)
    while(choice != NULL){
        if(choice->path == 1)
            tmp = tmp->lc;
        else if(choice->path == 2)
            tmp = tmp->mc;
        else
            tmp = tmp->rc;
        choice = choice->next;
    }
    //now tmp points to the parent of the last node
    //copy last node to 1st node and delete last
    _client* del;
    if(tmp->rc != NULL){
        PQ->Q->cid = tmp->rc->cid;
        PQ->Q->miles = tmp->rc->miles;
        del = tmp->rc;
        tmp->rc = NULL;
        free(del);
    }
    else if(tmp->mc != NULL){
        PQ->Q->cid = tmp->mc->cid;
        PQ->Q->miles = tmp->mc->miles;
        del = tmp->mc;
        tmp->mc = NULL;
        free(del);
    }
    else{
        PQ->Q->cid = tmp->lc->cid;
        PQ->Q->miles = tmp->lc->miles;
        del = tmp->lc;
        tmp->lc = NULL;
        free(del);
    }
	PQ->num_elements--;

    //now we have to restore the properties of the heap
    tmp = PQ->Q;
    int cidTmp, milesTmp;
    while(1){
        if(tmp->lc == NULL){
            break;
        }
        else if(tmp->mc == NULL){ //only lc
            if(tmp->lc->miles > tmp->miles){
                cidTmp = tmp->cid;
                milesTmp = tmp->miles;
                tmp->cid = tmp->lc->cid;
                tmp->miles = tmp->lc->miles;
                tmp->lc->cid = cidTmp;
                tmp->lc->miles = milesTmp;
                tmp = tmp->lc;
            }
            break;
        }
        else if(tmp->rc == NULL){ //only lc and mc
            if(tmp->lc->miles >= tmp->mc->miles){
                cidTmp = tmp->cid;
                milesTmp = tmp->miles;
                tmp->cid = tmp->lc->cid;
                tmp->miles = tmp->lc->miles;
                tmp->lc->cid = cidTmp;
                tmp->lc->miles = milesTmp;
                tmp = tmp->lc;
            }
            else{
                cidTmp = tmp->cid;
                milesTmp = tmp->miles;
                tmp->cid = tmp->mc->cid;
                tmp->miles = tmp->mc->miles;
                tmp->mc->cid = cidTmp;
                tmp->mc->miles = milesTmp;
                tmp = tmp->mc;
            }
            break;
        }
        else if((tmp->miles < tmp->lc->miles) || (tmp->miles < tmp->mc->miles) || (tmp->miles < tmp->rc->miles)){
            if((tmp->lc->miles >= tmp->mc->miles) && (tmp->lc->miles >= tmp->rc->miles)){
                //If lc has the most miles, swap it with papa!
                cidTmp = tmp->cid;
                milesTmp = tmp->miles;
                tmp->cid = tmp->lc->cid;
                tmp->miles = tmp->lc->miles;
                tmp->lc->cid = cidTmp;
                tmp->lc->miles = milesTmp;
                tmp = tmp->lc;
            }
            else if((tmp->mc->miles >= tmp->lc->miles) && (tmp->mc->miles >= tmp->rc->miles)){
                //If mc has the most miles, swap it with papa!
                cidTmp = tmp->cid;
                milesTmp = tmp->miles;
                tmp->cid = tmp->mc->cid;
                tmp->miles = tmp->mc->miles;
                tmp->mc->cid = cidTmp;
                tmp->mc->miles = milesTmp;
                tmp = tmp->mc;
            }
            else{ //Else rc has the most miles, swap it with papa!
                cidTmp = tmp->cid;
                milesTmp = tmp->miles;
                tmp->cid = tmp->rc->cid;
                tmp->miles = tmp->rc->miles;
                tmp->rc->cid = cidTmp;
                tmp->rc->miles = milesTmp;
                tmp = tmp->rc;
            }
        }
        else break; //There is no child with more miles
    }
    print_clients();
    return 1;
}

/*Returns pointer to the client node with cid == cidTarget*/
_client* searchClient(_client* root, int cidTarget)
{
    _client* tmp;
    if(root == NULL || root->cid == cidTarget) //Base case
        return root;
    tmp = searchClient(root->lc, cidTarget); //rec left
    if(tmp != NULL) return tmp; //found
    tmp = searchClient(root->mc, cidTarget); //rec mid
    if(tmp != NULL) return tmp; //found
    tmp = searchClient(root->rc, cidTarget); //rec right
    if(tmp != NULL) return tmp; //found
    return tmp;
}

int travel_client(int cid, int dest) {
    _client* curr = searchClient(PQ->Q, cid);
    curr->miles = curr->miles + (dest+1)*100;
    int cidTmp, milesTmp;
    while(curr->p != NULL){
        if(curr->miles > curr->p->miles){
            cidTmp = curr->p->cid;
            milesTmp = curr->p->miles;
            curr->p->cid = curr->cid;
            curr->p->miles = curr->miles;
            curr->cid = cidTmp;
            curr->miles = milesTmp;
        }
        curr = curr->p;
    }
    print_clients();
    return 1;
}

int free_all(void) {
    return 1;
}
