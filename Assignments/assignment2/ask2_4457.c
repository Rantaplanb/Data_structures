/*
    HY240 - 2η Σειρα - Ασκηση 2
    Μερτζάνης Λουκάς - 4457
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

/* Θα χρησιμοποιησω μια απλα συνδεδεμενη κυκλικη λιστα.
 Καθε κομβος της λιστας θεωρειται τυπου struct node. */
struct node
{
    char* banditName;
    struct node* next;
};

/* Η συναρτηση προσομειωνει το παιχνιδι της εκφωνησης.
Δεχεται ως ορισματα εναν pointer στον κομβο του
αρχηγου-ληστη(head) και το πληθος των ληστων. */
void banditGame(struct node* head, int n)
{
    int i,j, select;
	if(n <= 1 || head == NULL) 
		exit(1);
    /* Το loop εκτελειται n-1 φορες, για καθε εκτελεση του
    εξαιρειται ακομη ενας ληστης απο το παιχνιδι και ο
    κομβος του διαγραφεται */
    for(i = n; i > 1; i--)
    {
        struct node* ptr = head;

        /* Η μεταβλητη select παιρνει σε καθε γυρο του παιχνιδιου
        τυχαια τιμη απο 1 εως το εκαστοτε πληθος των ληστων.*/
        select = rand()%i +1;

        /* Αυτο το loop κανει τον ptr να δειξει στον κομβο που
        προηγειται αυτου που θελουμε να διαγραψουμε. */
        for(j=2; j<select; j++)
        {
            ptr = ptr->next;
        }

        printf("%s is out of the game!\n",(ptr->next)->banditName); //print bandit name
        struct node* tmp = ptr->next; //tmp points to the node that must be deleted.

        //Delete the selected bandit
        ptr->next = (ptr->next)->next;
        head = ptr->next; //Αρχη της νεας αριθμησης ο επομενος ληστης αυτου που φευγει
        free(tmp->banditName);
        free(tmp->next);
        free(tmp);
    }
    printf("\nThe bandit who escapes is %s!\n", head->banditName);
}

/*Driver program with a 5-node circular linked list*/
main()
{
    struct node n1, n2, n3, n4, n5;
    struct node* hd = &n1;
    srand(time(0));
    //Initialize nodes
    n1.banditName = (char*)malloc(10*sizeof(char));
    n1.banditName = "Loukas";
    n2.banditName = (char*)malloc(10*sizeof(char));
    n2.banditName = "Sarantis";
    n3.banditName = (char*)malloc(10*sizeof(char));
    n3.banditName = "Kwstas";
    n4.banditName = (char*)malloc(10*sizeof(char));
    n4.banditName = "Eugenia";
    n5.banditName = (char*)malloc(10*sizeof(char));
    n5.banditName = "Maria";
    n1.next = &n2;
    n2.next = &n3;
    n3.next = &n4;
    n4.next = &n5;
    n5.next = &n1;

    banditGame(hd, 5);
}
