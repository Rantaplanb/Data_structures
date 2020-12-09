/*
    HY240 - 2η Σειρα - Ασκηση 1
    Μερτζάνης Λουκάς - 4457
*/

//Πρωτο ερωτημα.
void sortNumsUsingStacks(void)
{
    int n;
    Stack inputStack = MakeEmptyStack();
    Stack sortedStack = MakeEmptyStack();

    //Διαβασμα ακεραιων και αποθηκευση στο inputStack
    while(scanf("%d", &n) != EOF)
        Push(inputStack, n);

    /* Οσο η inputStack εχει στοιχεια, κραταω το πρωτο στοιχειο της στην tmp.
    Επειτα, οσο η sortedStack εχει στοιχεια και το πρωτο στοιχειο της
    ειναι μεγαλυτερο απο την tmp, το κανω pop και το push-αρω στην inputStack.
    Τελος, push-αρω το tmp στην sortedStack. Ετσι, η sortedStack καταληγει
    ταξινομημενη, με τον μεγαλυτερο αριθμο να βρισκεται στην κορυφη! */
    while(!IsEmptyStack(inputStack))
    {
        int tmp = Pop(inputStack);
        while(!IsEmptyStack(sortedStack) && Top(sortedStack)>tmp)
            Push(inputStack, Pop(sortedStack));
        Push(sortedStack, tmp);
    }

    //Τυπωνω τους αριθμους της ταξινομημενης στοιβας (φθινουσα σειρα)
    while(!IsEmptyStack(sortedStack))
        printf("%d", Pop(sortedStack));
}

//Δευτερο ερωτημα.
void evaluatePrefix(void)
{
    char ch, digit1, digit2;
    Stack storeExp = MakeEmptyStack();
    Stack eval = MakeEmptyStack();
    
	//Αποθηκευω ολη την εκφραση στην στοιβα storeExp
    while((ch = getchar()) != '\n')
        Push(storeExp, ch);
        
	/*Επεξεργαζομαι 1-1 τα στοιχεια της storeExp, καθε ψηφιο
	το pushαρω στην στοιβα eval. Καθε φορα που συνανταω operator,
	κανω την εκαστοτε πραξη με τα 2 top digits της eval και
	αποθηκευω το αποτελεσμα στην eval. Οταν πια αδειασει η
	storeExp, η εκτιμηση της προθεματικης αριθμητικης 
	εκφρασης θα εχει ολοκληρωθει και το αποτελεσμα θα βρισκεται
	στην κορφη της eval και εκτυπωνεται! */
    while(!IsEmptyStack(storeExp))
    {
        ch = Pop(storeExp);
        if(ch>='0'&&ch<='9') //isDigit(ch)
            Push(eval, ch);
        else if(ch=='+'||ch=='-'||ch=='/'||ch=='*') //isOperator(ch)
        {
            if(IsEmptyStack(eval)){
                printf("Entered expression is invalid!");
                //exit(1);
            }
            digit1 = Pop(eval);
            
            if(IsEmptyStack(eval)){
                printf("Entered expression is invalid!");
                //exit(1);
            }
            digit2 = Pop(eval);
            
            switch(ch)
            {
            case '+':
                Push(eval,(digit1-'0') + (digit2-'0'));
                break;
            case '-':
                Push(eval,(digit1-'0') - (digit2-'0'));
                break;
            case '/':
                Push(eval,(digit1-'0') / (digit2-'0'));
                break;
            case '*':
                Push(eval,(digit1-'0') * (digit2-'0'));
                break;
            }
        }
        else{
            printf("Invalid character input!");
            //exit(1);
        }
    }
    printf("\nThe expression was evaluated to: %d", Top(eval));
}