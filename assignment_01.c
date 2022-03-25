# Construct and expression tree from postfix/prefix expression and perform recursive and non-recursive In-order, pre-order and post-order traversals

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node
{
    int val;
    struct node *lchild;
    struct node *rchild;
}NODE;

typedef struct stack
{
    int data;
    struct stack *next;
}STACK;

STACK* push(STACK *top, NODE *data)
{
    STACK *NewNode=(STACK*)malloc(sizeof(STACK));
    NewNode->data=data;
    NewNode->next=NULL;
    if(top==NULL)
    {
        top=NewNode;
    }
    else
    {
        NewNode->next=top;
        top=NewNode;
    }
    return top;
 }
 
STACK* pop(STACK *top)
{
    STACK *temp=top;
    if(top==NULL)
    {
        printf("\nStack is Empty");
    }
    else
    {
        top=top->next;
        free(temp);
    }
    return top;
}

NODE* ReadTop(STACK *top)
{
    return top->data;
}

NODE* postfix_ex(NODE *root)
{
    STACK *top=NULL;
    char str[50];
    int i;
    printf("\nEnter the Postfix Expression: ");
    scanf("%s",str);
    for(i=0;str[i]!='\0';i++)
    {
        NODE *tree_node=(NODE*)malloc(sizeof(NODE));
        tree_node->val=str[i];
        tree_node->rchild=tree_node->lchild=NULL;

        if(isalpha(str[i]))
        {
            top=push(top,tree_node);
        }
        else
        {
            tree_node->rchild=ReadTop(top);
            top=pop(top);
            tree_node->lchild=ReadTop(top);
            top=pop(top);

            top=push(top,tree_node);
        }
    }

    root=ReadTop(top);
    top=pop(top);
    return root;
}

NODE* prefix_ex(NODE *root)
{
    STACK *top=NULL;
    char str[50];
    int i;
    printf("\nEnter the Prefix Expression: ");
    scanf("%s",str);
    int length=strlen(str);
    for(i=length-1;i>=0;i--)
    {
        // printf("In the loop");
        NODE *tree_node=(NODE*)malloc(sizeof(NODE));
        tree_node->val=str[i];
        tree_node->lchild=tree_node->rchild=NULL;

        if(isalpha(str[i]))
        {
            top=push(top,tree_node);
        }
        else
        {
            tree_node->lchild=ReadTop(top);
            top=pop(top);
            tree_node->rchild=ReadTop(top);
            top=pop(top);

            top=push(top,tree_node);
        }
    }

    root=ReadTop(top);
    top=pop(top);
    return root;
}

void preorder_traversal(NODE *root)
{
    if(root!=NULL)
    {
        printf("%c",root->val);
        preorder_traversal(root->lchild);
        preorder_traversal(root->rchild);
    }
}

void postorder_traversal(NODE *root)
{
    if(root!=NULL)
    {
        postorder_traversal(root->lchild);
        preorder_traversal(root->rchild);
        printf("%c",root->val);
    }
}

void inorder_traversal(NODE *root)
{
    if(root!=NULL)
    {
        inorder_traversal(root->lchild);
        printf("%c",root->val);
        inorder_traversal(root->rchild);
    }
}

int main()
{
    NODE *root=NULL;
    int n, c, co;
    printf("1. Expression tree from postfix expression \n2. Expression tree from prefix expression\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1: 
            root=postfix_ex(root);
            printf("1. Pre-order traversal \n2. Post-order traversal \n3. In-order traversal\n");
            scanf("%d",&c);
            switch(c)
            {
                case 1: 
                    printf("\nPre-order traversal: ");
                    preorder_traversal(root);
                break;
                case 2: 
                    printf("\nPost-order traversal: ");
                    postorder_traversal(root);
                break;
                case 3:
                    printf("\nIn-order traversal: ");
                    inorder_traversal(root);
                break;
                default: printf("Invalid input");
            }
        break;
        case 2: 
            root=prefix_ex(root);
            printf("1. Pre-order traversal \n2. Post-order traversal \n3. In-order traversal\n");
            scanf("%d",&c);
            switch(c)
            {
                case 1: 
                    printf("\nPre-order traversal: ");
                    preorder_traversal(root);
                break;
                case 2: 
                    printf("\nPost-order traversal: ");
                    postorder_traversal(root);
                break;
                case 3:
                    printf("\nIn-order traversal: ");
                    inorder_traversal(root);
                break;
                default: printf("Invalid input");
            }
        break;
        default: printf("Invalid input");            
    }
    for(;;)
    printf("Enter 1 to continue\nEnter 0 to exit");
    scanf("%d",&co);
    if(co==1)
        return main;
    else
        return 0;    
}
