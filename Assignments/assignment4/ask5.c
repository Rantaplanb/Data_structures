#include <stdio.h>

struct node{
    int num;
    struct node* next;
};

/*Returns 1 if linked list contains num, 0 otherwise*/
int listContainsNum(struct node* head, int num)
{
    struct node* curr = head;
    while(curr){
        if(curr->num == num)
            return 1;
        curr = curr->next;
    }
    return 0;
}

struct node* insertNum(struct node* head, int num)
{
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->next = head;
    newNode->num = num;
    return newNode;
}

void reversePrintList(struct node* head)
{
    if(!head)
        return;
    reversePrintList(head->next);
    printf("%d ", head->num);
    return;
}

void printWithoutMultiples(int A[], int n)
{
	int i, j;
	struct node* head = (struct node*)malloc(sizeof(struct node));
	head->num = A[0];
	head->next = NULL;
	for(i=1; i<n; i++){
        if(!listContainsNum(head, A[i])){ //Skip multiple instances of same element
            head = insertNum(head, A[i]); //Insert at the beginning of the list
        }
	}
	printListReversed(head);
}

//driver program
int main()
{
    int arr[15] = {1,1,1,5,8,12,4,4,1,1,9,5,8,5,1};
    printWithoutMultiples(arr, 15);
	return 0;

}