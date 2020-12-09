/*
    HY240 - 2� ����� - ������ 1
    ��������� ������ - 4457
*/

//����� �������.
void sortNumsUsingStacks(void)
{
    int n;
    Stack inputStack = MakeEmptyStack();
    Stack sortedStack = MakeEmptyStack();

    //�������� �������� ��� ���������� ��� inputStack
    while(scanf("%d", &n) != EOF)
        Push(inputStack, n);

    /* ��� � inputStack ���� ��������, ������ �� ����� �������� ��� ���� tmp.
    ������, ��� � sortedStack ���� �������� ��� �� ����� �������� ���
    ����� ���������� ��� ��� tmp, �� ���� pop ��� �� push-��� ���� inputStack.
    �����, push-��� �� tmp ���� sortedStack. ����, � sortedStack ���������
    ������������, �� ��� ���������� ������ �� ��������� ���� ������! */
    while(!IsEmptyStack(inputStack))
    {
        int tmp = Pop(inputStack);
        while(!IsEmptyStack(sortedStack) && Top(sortedStack)>tmp)
            Push(inputStack, Pop(sortedStack));
        Push(sortedStack, tmp);
    }

    //������ ���� �������� ��� ������������� ������� (�������� �����)
    while(!IsEmptyStack(sortedStack))
        printf("%d", Pop(sortedStack));
}

//������� �������.
void evaluatePrefix(void)
{
    char ch, digit1, digit2;
    Stack storeExp = MakeEmptyStack();
    Stack eval = MakeEmptyStack();
    
	//��������� ��� ��� ������� ���� ������ storeExp
    while((ch = getchar()) != '\n')
        Push(storeExp, ch);
        
	/*������������� 1-1 �� �������� ��� storeExp, ���� �����
	�� push��� ���� ������ eval. ���� ���� ��� �������� operator,
	���� ��� �������� ����� �� �� 2 top digits ��� eval ���
	��������� �� ���������� ���� eval. ���� ��� �������� �
	storeExp, � �������� ��� ������������ ����������� 
	�������� �� ���� ����������� ��� �� ���������� �� ���������
	���� ����� ��� eval ��� �����������! */
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