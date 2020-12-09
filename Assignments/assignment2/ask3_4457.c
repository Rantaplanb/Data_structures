/*
    HY240 - 2η Σειρα - Ασκηση 3
    Μερτζάνης Λουκάς - 4457
*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

//Πρωτο ερωτημα
int Equal(struct node* L1, struct node* L2)
{
    for(; L1!=NULL && L2!=NULL; L1=L1->next, L2=L2->next)
    {
        //Προσπερασε τα στοιχεια που υπαρχουν πολλαπλες φορες.
        while(L1->next != NULL && L1->data == L1->next->data)
            L1 = L1->next;
        while(L2->next != NULL && L2->data == L2->next->data)
            L2 = L2->next;

        if(L1->data != L2->data)
            return 0;
    }

    if(L1==NULL && L2!=NULL)
        return 0;
    else if(L1!=NULL && L2==NULL)
        return 0;
    else if(L1==NULL && L1 == NULL)
        return 1;
}
/*
    O αλγοριθμος εχει πραγματι πολυπλοκοτητα O(n1+n2) οπως
    ζητειται, αφου στην χειροτερη περιπτωση, δηλαδη οταν
    τα συνολα των στοιχειων των 2 λιστων ειναι ισα, τοτε
    θα χρειαστει να διασχισουμε ολους τους κομβους της
    πρωτης λιστας (n1 προσπελασεις κομβων) και ολους τους
    κομβους της δευτερης λιστας (n2 προσπελασεις κομβων).
    Συνολικα πραγματοποιουνται n1+n2 προσπελασεις -> O(n1+n2).
    Σε οποιαδηποτε αλλη περιπτωση (δηλαδη οταν τα συνολα των
    των στοιχειων των 2 λιστων δεν ειναι ισα), θα χρειαστει
    να κανουμε απο 2 εως n1+n2 προσπελασεις κομβων -> O(n1+n2).
*/



//Δευτερο ερωτημα
int Equal(struct node* L1, struct node* L2)
{
    int flag = 0;
    struct node* tmp1 = L1;

    if(L1==NULL&&L2==NULL)
        return 1;

    for(; tmp1!=NULL; tmp1 = tmp1->next)
    {
        struct node* tmp2 = L2;
        for(; tmp2!=NULL; tmp2=tmp2->next)
        {
            if(tmp1->data == tmp2->data)
                flag = 1;
        }
        if(flag == 0)
            return 0;
        flag = 0;
    }

    tmp1 = L2;
    for(; tmp1!=NULL; tmp1 = tmp1->next)
    {
        struct node* tmp2 = L1;
        for(; tmp2!=NULL; tmp2=tmp2->next)
        {
            if(tmp1->data == tmp2->data)
                flag = 1;
        }
        if(flag == 0)
            return 0;
        flag = 0;
    }
    return 1;
}

/*
	Αν n1, n2 το πληθος των στοιχειων των συνολων των 2 λιστων, 
	τοτε μελετωντας την χειροτερη περιπτωση, 
	δηλαδη την περιπτωση κατα την οποια εχουμε
	ισοτητα των συνολων των στοιχειων των 2 λιστων,
	προκυπτει μεγιστος αριθμος προσπελασεων κομβων λιστων ισος με:
	n1*n2 + n2*n1 = n1*n2 + n1*n2 = 2*n1*n2 => O(n1*n2) => O(n^2) με n = max(n1,n2)
	Οπου: n1*n2 η πολυπλοκοτητα του 1ου ζευγους απο for loops
	και n2*n1 η πολυπλοκοτητα του 2ου ζευγους απο for loops.
*/
	
	
	
	
	
	
	
	
	
	
	