#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define null NULL
#define memory (lptr)(malloc(sizeof(struct linkednode)))
#define submemory (subptr)(malloc(sizeof(struct subnode)))
#define smemory (sptr)(malloc(sizeof(struct stacknode)))
#define imemory (iptr)(malloc(sizeof(struct intstack)))

typedef struct linkednode* lptr;
typedef struct subnode* subptr;
typedef struct stacknode* sptr;
typedef struct intstack* iptr;

struct linkednode //the list which contain the list that has the string..
{
    lptr next;
    subptr subnext;
};
struct subnode //the string node..
{
    char eq[1000];
};

struct stacknode //stack for all things except the calculation..
{
    char data;
    sptr next;
};


struct intstack //the calculation stack...
{
    double data;
    iptr next;
};


lptr createbig(lptr);
void rev(char[]);
iptr result(lptr);
int op(char);

int main()
{

    lptr equations=createbig(equations);
    lptr valid;//here the valid equation stored
    lptr invalid;//here the invalid equation stored
    lptr pre;//prefixes

    int len;


    int choice=-1;

    iptr res;//the results of prefixes stores here...
    while(choice != 7)
    {
        printf("Choose what...\n1-Read from file   2-Check the validity   3-infix to prefix   4-Evaluate the prefix   5-Print invalid   6-print to output file   7-exit.\n");
        scanf("%d",&choice);
        char name;
        switch(choice)
        {

        case 1://i put here all the function to be able to use them without call one by one function....
            //to read the equations from file and store them in list of lists
            printf("Enter the name of the file you want to read: ");
            char nn[100];
            scanf("%s",nn);//the name of the file that the user want to read...
            printf("Reading...\n");
            equations->next=null;
            readfile(equations,nn);
            printf("Reading done...\n");
            printall(equations);
            valid=createbig(valid);
            invalid=createbig(invalid);
            fillvalid(equations,valid,invalid);
            sipnum(valid);
            sipnum(invalid);
            pre=createbig(pre);
            intopre(pre,valid);
            res=result(pre);

            printf("\n\n");
            break;

        case 2://checking the validity
            len=size(equations);
            lptr t=equations->next;
            for(int i=0; i<len; i++)
            {
                printf("Equation No. %d --> ",i+1);
                isvalid(t->subnext->eq);
                printf("\n");


                t=t->next;
            }
            printf("\n\n");
            break;

        case 3://prefix....
            printall(pre);

            printf("\n\n");
            break;
        case 4://res of prefix

            printres(res);
            printf("\n\n");
            break;
        case 5://print invalid....
            printf("\n\n");
            printall(invalid);
            printf("\n\n");
            break;
        case 6://print into the file...
            printfile(valid,invalid,res,pre);

            printf("\n\n");
            break;
        case 7:
            printf("good bye....\n");
            break;
        default:
            printf("no no you must choose from above choices...");
            break;
        }
    }
    return 0;
}

lptr createbig(lptr list) //create a node to lptr..
{
    list=memory;
    list->next=null;
    list->subnext=null;
    return list;
}

void insertneweq(lptr list) //insert new node to the end of lptr list...
{
    lptr t=list;
    while(t->next!=null)t=t->next;

    lptr temp=createbig(temp);
    t->next=temp;
}

void readfile(lptr list,char name[]) //reading from file...
{
    FILE* in;
    in=fopen(name,"r");
    char eq[1000];
    while(fgets(eq,1000,in)!=null)
    {//reading loop

        subptr temp=submemory;
        insertneweq(list);
        strcpy(temp->eq,eq);


        lptr t=list;
        while(t->next!=null)t=t->next;
        t->subnext=temp;
    }

    fclose(in);
}

int isnum(char a) //isnum??
{
    return (a>=48&&a<=57);
}
int isoperand(char a) //isoperation??
{
    return (a=='+'||a=='-'||a=='*'||a=='/'||a=='^');
}
int isbrackets(char a) //isbrackets??
{
    return (a=='('||a==')'||a=='['||a==']');
}
void isvalid(char name[]) //this function is to determined if the equation is valid or not...
{
    int check=0;
    int lng=strlen(name)-1;//because the string have  \n as a last char
    int count=0,numberofbra1=0,numberofbra2=0,numberofbra3=0,numberofbra4=0;
    char error;
    if(name[0]=='*'||name[0]=='/'||name[0]=='^')
    {
        printf("invalid, because (%c) in the first of equation",name[0]);
        return;
    }
    if(isoperand(name[strlen(name)-2]))
    {
        printf("invalid, because (%c) in the end of equation",name[strlen(name)-2]);
        return;
    }
    for(int i=0; i<lng; i++)
    {//to access the whole string
        if(isnum(name[i])||isoperand(name[i])||isbrackets(name[i]))
        {
            count++;
            if(name[i]=='(')numberofbra1++;
            if(name[i]==')')numberofbra2++;
            if(name[i]=='[')numberofbra3++;
            if(name[i]==']')numberofbra4++;
        }
        else
        {
            error=name[i];
            break;
        }
    }

    if(count==lng) //just numbers and .....
    {
        //to catch the brackets invalidness
        if((numberofbra1+numberofbra2+numberofbra3+numberofbra4)%2 !=0)
        {
            check++;
            //printf("%d   %d  %d  %d ------\n",numberofbra1,numberofbra2,numberofbra3,numberofbra4);//printf("%c",name[strlen(name)-1]);
            if(numberofbra1>numberofbra2)printf("invalid, ( not closed");
            if(numberofbra1<numberofbra2)printf("invalid, ) not opened");
            if(numberofbra3>numberofbra4)printf("invalid, [ not closed");
            if(numberofbra3<numberofbra4)printf("invalid, ] not opened");
        }
        else //if number of brackets are even....
        {
            sptr stack=smemory;
            stack->next=null;
            for(int i=0; i<lng; i++)
            {//to access the whole string
                if(name[i]=='('||name[i]=='[')
                {
                    push(stack,name[i]);
                }
                else if(name[i]==')'||name[i]==']')
                {
                    if(name[i]==')'&&stack->next->data=='(')
                    {
                        pop(stack);
                    }
                    else if(name[i]==']'&&stack->next->data=='[')
                    {
                        pop(stack);
                    }
                    else
                    {
                        check++;
                        printf("invalid, because there are a mistake in the brackets...");
                        break;
                    }
                }
            }

        }

        for(int i=0; i<lng; i++)
        {//to access the whole string
            if(name[i]=='('||name[i]=='[')
            {
                if(i!=0)
                {
                    if(isnum(name[i-1]))
                    {
                        check++;
                        printf("invalid, because there are no operand here -- %c%c --",name[i-1],name[i]);
                        break;
                    }
                }
            }
            if(name[i]==')'||name[i]==']')
            {
                if(i!=lng-1)
                {
                    if(isnum(name[i+1]))
                    {
                        check++;
                        printf("invalid, because there are no operand here -- %c%c --",name[i],name[i+1]);
                        break;
                    }
                }
            }
        }
        for(int i=0; i<lng; i++)
        {//to access the whole string
            if(i+1!=lng)
            {
                if(op(name[i])&&op(name[i+1]))
                {
                    check++;
                    printf("invalid, because %c%c are next to each other",name[i],name[i+1]);
                }
                else if(isoperand(name[i])&&op(name[i+1]))
                {
                    check++;
                    printf("invalid, because %c%c are next to each other",name[i],name[i+1]);
                }

            }
        }

    }
    else  //invalid...c
    {
        check++;
        printf("invalid, because (%c) is not neither a number nor operand nor brackets...\n",error);
    }

    if(check==0)
    {
        printf("valid");
    }
}

int op(char a) //is * / ^
{
    return (a=='*'||a=='/'||a=='^');

}

void fillvalid(lptr list,lptr valid,lptr invalid) //the same as isvalid function but without prints and fill valid or invalid lists..
{

    lptr t = list;
    while(t->next!=null)
    {//to access the whole list so i can access the whole strings
        t=t->next;
        int check=0;
        int not=0;
        int lng=strlen(t->subnext->eq)-1;
        char name[1000];
        strcpy(name,t->subnext->eq);
        int count=0,numberofbra1=0,numberofbra2=0,numberofbra3=0,numberofbra4=0;
        char error='-';
        if(isoperand(name[0]))
        {
            check++;
        }
        else if(isoperand(name[strlen(name)-2]))
        {
            check++;
        }
        else
        {
            for(int i=0; i<lng; i++)
            {//to access the whole string
                if(isnum(name[i])||isoperand(name[i])||isbrackets(name[i]))
                {
                    count++;
                    if(name[i]=='(')numberofbra1++;
                    if(name[i]==')')numberofbra2++;
                    if(name[i]=='[')numberofbra3++;
                    if(name[i]==']')numberofbra4++;
                }
                else
                {
                    error=name[i];
                    break;
                }
            }
        }

        if(count==lng) //just numbers and .....
        {
            //to catch the brackets invalidness
            if((numberofbra1+numberofbra2+numberofbra3+numberofbra4)%2 !=0)
            {
                check++;

            }
            else   //if number of brackets are even....
            {
                sptr stack=smemory;
                stack->next=null;
                for(int i=0; i<lng; i++)
                {//to access the whole string..
                    if(name[i]=='('||name[i]=='[')
                    {
                        push(stack,name[i]);
                    }
                    else if(name[i]==')'||name[i]==']')
                    {
                        if(name[i]==')'&&stack->next->data=='(')
                        {
                            pop(stack);
                        }
                        else if(name[i]==']'&&stack->next->data=='[')
                        {
                            pop(stack);
                        }
                        else
                        {
                            check++;
                            break;
                        }
                    }
                }
            }

            for(int i=0; i<lng; i++) //to check if there are a number before or after brackets... then invalid..
            {
                if(name[i]=='('||name[i]=='[')
                {
                    if(i!=0)
                    {
                        if(isnum(name[i-1]))
                        {
                            check++;
                            break;
                        }
                    }
                }
                if(name[i]==')'||name[i]==']')
                {
                    if(i!=lng-1)
                    {
                        if(isnum(name[i+1]))
                        {
                            check++;
                            break;
                        }
                    }
                }
            }

            for(int i=0; i<lng; i++) // to check if ++ or */ or /* or -* or *- ......
            {
                if(i+1!=lng)
                {
                    if(op(name[i])&&op(name[i+1]))
                    {
                        check++;
                        not++;
                    }
                    else if(isoperand(name[i])&&op(name[i+1]))
                    {
                        check++;
                        not++;
                    }
                    else if(isoperand(name[i])&&isoperand(name[i+1]))
                    {
                        check++;
                        not++;
                    }
                }

            }
        }
        else if(error!='-') //invalid...c
        {
            check++;

        }
        if(check==0&&not==0) //valid so insert it in valid...
        {
            insertneweq(valid);
            subptr temp=submemory;
            lptr tt=valid;
            while(tt->next!=null)tt=tt->next;
            char eqq[1000];
            strcpy(eqq,t->subnext->eq);
            strcpy(temp->eq,eqq);
            tt->subnext=temp;
            tt->next=null;

        }
        else if(check!=0&&not==0) //invalid so insert it in invalid..
        {

            insertneweq(invalid);
            subptr temp=submemory;
            lptr tt=invalid;
            while(tt->next!=null)tt=tt->next;
            char eqq[1000];
            strcpy(eqq,t->subnext->eq);
            strcpy(temp->eq,eqq);
            tt->subnext=temp;
            tt->next=null;

        }
    }

}


void push(sptr stack,char data) //push stack..
{
    sptr temp=smemory;
    temp->data=data;
    temp->next=stack->next;
    stack->next=temp;
}
void pop(sptr stack) //pop stack..
{
    if(stack->next==null)return;
    sptr temp=stack->next;
    stack->next=stack->next->next;
    temp->next=null;
    free(temp);
}

void intopre(lptr pre,lptr list) //this transfer form infix to prefix
{

    lptr t=list;
    lptr tt=pre;

    while(t->next!=null)
    {//to access the whole list so i can access the whole strings
        t=t->next;
        insertneweq(pre);
        tt=tt->next;
//now i need to transfer the infix in list to prefix and put it in pre...
        char name[1000];

        strcpy(name,t->subnext->eq);//now name contain the equation..

        rev(name);
        name[strlen(name)+1]='\0';
        name[strlen(name)]=' ';//because sipnum function supposes that the final char is \n so i have to put any char so the last char can exceded...
        lptr tosup=createbig(tosup);
        insertneweq(tosup);
        subptr supto=submemory;
        tosup->next->subnext=supto;
        strcpy(supto->eq,name);
        sipnum(tosup);//to add spaces between numbers...
        strcpy(name,supto->eq);

        itop(name);

        subptr temp=submemory;
        tt->subnext=temp;

        strcpy(tt->subnext->eq,name);
    }

}

void itop(char name[]) //continue of infix to prefix function....
{

    sptr stack=smemory;
    stack->next=null;
    int len=strlen(name);
    char res[1000]="";
    int j=0;



    for(int i=0; i<len; i++)
    {

        if(isnum(name[i]))
        {
            while(name[i]!=' ')
            {
                i++;
            }
            int last=i;
            i--;
            while(isnum(name[i]))
            {
                res[j]=name[i];
                j++;
                if(i-1<0)
                {
                    i--;
                    break;
                }
                i--;
            }

            i=last-1;
        }
        else if(isoperand(name[i])) //+-*/
        {
            if(stack->next==null)
            {
                push(stack,name[i]);
            }
            else
            {
                char prev=stack->next->data;//printf("(%c)",prev);
                //the prority casessss
                if((name[i]=='+'||name[i]=='-')&&(prev=='+'||prev=='-'))
                {
                    /*res[j]=stack->next->data;j++;pop(stack);push(stack,name[i]);*/push(stack,name[i]);
                }
                else if((name[i]=='*'||name[i]=='/')&&(prev=='*'||prev=='/'))
                {
                    res[j]=stack->next->data;
                    j++;
                    pop(stack);
                    push(stack,name[i]);
                }
                else if(name[i]=='^'&&prev=='^')
                {
                    push(stack,name[i]);
                }
                else if((name[i]=='^')&&(prev=='*'||prev=='/'||prev=='+'||prev=='-'))
                {
                    push(stack,name[i]);
                }
                else if((name[i]=='*'||name[i]=='/'||name[i]=='+'||name[i]=='-')&&(prev=='^'))
                {
                    res[j]=stack->next->data;
                    j++;
                    pop(stack);
                    push(stack,name[i]);
                }
                else if((name[i]=='*'||name[i]=='/')&&(prev=='+'||prev=='-'))
                {
                    push(stack,name[i]);
                }
                else if((name[i]=='+'||name[i]=='-')&&(prev=='*'||prev=='/'))
                {
                    res[j]=stack->next->data;
                    j++;
                    pop(stack);
                    push(stack,name[i]);
                }
                else
                {
                    push(stack,name[i]);
                }

            }
        }
        else if(name[i]==')'||name[i]==']')
        {
            char prev=stack->next->data;
            if(name[i]==')')
            {
                while(prev != '(')
                {
                    res[j]=stack->next->data;
                    j++;
                    pop(stack);
                    prev=stack->next->data;
                }
                pop(stack);//to pop (
            }
            else if(name[i]==']')
            {
                prev=stack->next->data;
                while(prev !='[')
                {
                    res[j]=stack->next->data;
                    j++;
                    pop(stack);
                    prev=stack->next->data;
                }
                pop(stack);//to pop [
            }


        }


        else if(name[i]=='('||name[i]=='[')push(stack,name[i]);
        else if(name[i]==' ')
        {
            res[j]=name[i];
            j++;
        }
    }
    while(stack->next!=null)
    {
        res[j]=stack->next->data;
        j++;
        pop(stack);
    }
//now in res, we have the postfix of the equation, now we need to make it prefix by rev it...

    revin(res);//to rev it with spaces..
    strcpy(name,res);
}

void rev(char name[]) //rev
{

    int len=strlen(name);//len-1 to access the last char

    char temp[1000]="";
    int j=0;
    for(int i=len-1; i>=0; i--)
    {//to access the whole string
        if(name[i]=='(')name[i]=')';
        else if(name[i]==')')name[i]='(';
        else if(name[i]=='[')name[i]=']';
        else if(name[i]==']')name[i]='[';
        if(name[i]==' ')
        {
            i--;
            while(isnum(name[i]))
            {
                if(i-1<0)
                {
                    i--;
                    break;
                }
                i--;

            }
            i++;
            int lastindex=i;
            while(isnum(name[i]))
            {
                temp[j]=name[i];
                j++;
                i++;
            }
            i=lastindex;
        }
        else
        {
            temp[j]=name[i];
            j++;
        }

    }
    temp[len]='\0';//to make it the end of this string, if i don't type it, the string will be more than the original size...
    //or i can entialize it as temp[1000]="";...all trueeeeee
    strcpy(name,temp);

}
void revin(char name[]) //revering with space and all things
{
    int len=strlen(name);//len-1 to access the last char

    char temp[1000]="";
    int j=0;
    for(int i=len-1; i>=0; i--)
    {//to access the whole string

        temp[j]=name[i];
        j++;

    }
    strcpy(name,temp);
}

void printall(lptr list) //to print lptr lists.
{
    lptr t=list;
    while(t->next!=null)
    {//to access the whole list so i can access the whole strings
        t=t->next;
        printf("%s",t->subnext->eq);
        printf("\n");
    }


}
int size(lptr list) //size of list.
{

    lptr t=list;
    int sum=0;
    while(t->next!=null)
    {//to access the whole list
        t=t->next;
        sum++;
    }

    return sum;
}

void sipnum(lptr valid) //to add spaces at the end of each number to handle with it in calculation
{

    lptr t=valid;
    while(t->next!=null)
    {//to access the whole list so i can access the whole strings
        t=t->next;
        char name[1000]="";
        strcpy(name,t->subnext->eq);
//name has the equation to add { } between numbers....
        int len=strlen(name);
//len-2 is the last ele..
        char res[1000]="";
        int j=0;
        for(int i=0; i<len-1; i++)
        {
            if(isnum(name[i])&&i!=len-2)
            {
                while(isnum(name[i]))
                {
                    res[j]=name[i];
                    j++;
                    if(i+1==len-1)
                    {
                        i++;
                        break;
                    }
                    i++;//2365888*65899-(44-66)+444, here im at * index..
                }       //2365888}*65899}-(44}-66})+444}
                res[j]=' ';
                j++;

            }

            if(isnum(name[i])&&i==len-2) //5+6
            {
                res[j]=name[i];
                j++;
                res[j]=' ';
                j++;
            }//5}
            if(isoperand(name[i]))
            {
                res[j]=name[i];
                j++;
            }
            else if(isbrackets(name[i]))
            {
                res[j]=name[i];
                j++;
            }

        }

        strcpy(t->subnext->eq,res);
    }

}

void pushint(iptr stack,double data) //push to calculation stack..
{
    iptr temp=imemory;
    temp->data=data;
    temp->next=stack->next;
    stack->next=temp;
}

void popint(iptr stack) //pop calc stack..
{
    if(stack->next==null)return;
    iptr temp=stack->next;
    stack->next=stack->next->next;
    temp->next=null;
    free(temp);
}

iptr result(lptr pre) //the calculation of prefix...
{

    iptr res=imemory;
    res->next=null;

    lptr t=pre;

    iptr stack=imemory;
    stack->next=null;

    iptr tt=res;
    while(t->next!=null)
    {//to access the whole list so i can access the whole strings
        t=t->next;
        char name[1000]="";
        strcpy(name,t->subnext->eq);//now, name contain the equation to calculate the prefix....
        int len=strlen(name);
//len-1 is the last digit....
        for(int i=len-1; i>=0; i--)
        {//to access the whole string

            if(isnum(name[i]))
            {
                int number=0;
                int factor=1;
                while(isnum(name[i]))
                {// to get to the end of this number.
                    number=number+((name[i]-'0') * factor);

                    factor*=10;
                    i--;
                }
                pushint(stack,number);
            }
            else if(isoperand(name[i]))
            {
                double num1=stack->next->data;//top..
                popint(stack);
                double num2=stack->next->data;
                popint(stack);
                double firstres;
                char operation=name[i];
                switch(operation)
                {
                case '+':
                    firstres=num1+num2;
                    pushint(stack,firstres);
                    break;
                case '-':
                    firstres=num1-num2;
                    pushint(stack,firstres);
                    break;
                case '*':
                    firstres=num1*num2;
                    pushint(stack,firstres);
                    break;
                case '/':
                    firstres=(double)num1/num2;
                    pushint(stack,firstres);
                    break;
                case '^':
                    firstres=pow(num1,num2);
                    pushint(stack,firstres);
                    break;
                }

            }

        }

        iptr temp=imemory;
        temp->next=null;

        tt->next=temp;
        tt=tt->next;

        double finalres=stack->next->data;
        popint(stack);
        temp->data=finalres;

    }

    return res;
}

void printres(iptr list)
{
    iptr t=list;
    while(t->next!=null)
    {
        t=t->next;
        printf("%f",t->data);
        printf("\n");
    }

}

void printfile(lptr valid,lptr invalid,iptr res,lptr pre)
{
    FILE* out=fopen("output.txt","w");
    fprintf(out,"Valid equations    ......................\n");
    printallfile(valid,out);
    fprintf(out,"prefix of the equations    ......................\n");
    printallfile(pre,out);
    fprintf(out,"the results    ......................\n");
    printresfile(res,out);
    fprintf(out,"\n........................................\n");
    fprintf(out,"\n\ninValid equations  ......................\n");
    printallfile(invalid,out);
    fprintf(out,"\n........................................\n");
    fclose(out);
    printf("done");
}
void printallfile(lptr list,FILE* out)
{
    lptr t=list;
    while(t->next!=null)
    {
        t=t->next;
        fprintf(out,"%s",t->subnext->eq);
        fprintf(out,"\n");
    }

}
void printresfile(iptr list,FILE* out)
{
    iptr t=list;
    while(t->next!=null)
    {
        t=t->next;
        fprintf(out,"%f",t->data);
        fprintf(out,"\n");
    }


}

