#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TURE 1
#define FALSE 0

typedef struct Information{
    char id[10];
    char date[20];
}Information;

typedef struct Borrower{
    struct Borrower* next;
    Information news;
}Borrower;

typedef struct Book{
    int bno;//书号
    char bname[20];//书名
    char writer[20];//作者
    int remain;//现存量
    int totalremain;//总库存量
    Borrower bor;//借阅者
}Book;

typedef struct BiTNode{
    Book data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

void menu(){
    printf("----------------------------------------------\n");
    printf("-----------------图书管理系统-----------------\n");
    printf("-----1.采编入库----------------2.清除库存-----\n");
    printf("-----3.借阅图书----------------4.归还图书-----\n");
    printf("-----5.查看图书----------------6.查看借阅信息-\n");
    printf("-------------------0.退出---------------------\n");
    printf("----------------------------------------------\n");
}

int SearchBST(BiTree T,int key,BiTree f,BiTree* p){
    if(!T){
        *p=f;
        return FALSE;
    }
    else if(key == T->data.bno){
        *p=T;
        return TURE;
    }//查找成功
    else if(key < T->data.bno) return SearchBST(T->lchild,key,T,p);
    else return SearchBST(T->rchild,key,T,p);
}//SearchBST
int InsertBST(BiTree* T,int e){
    BiTree p=NULL;
    BiTree s;
    int num=0;
    if(!SearchBST(*T,e,NULL,&p)){
        s=(BiTree)malloc(sizeof(BiTNode));
        s->data.bno = e;
        s->data.bor.next = NULL;
        scanf("%s%s",s->data.bname,s->data.writer);
        scanf("%d",&s->data.remain);
        s->data.totalremain = s->data.remain;//新书入库，购买数目即为现存量和总库存量
        s->rchild=s->lchild=NULL;
        if(!p) *T=s;
        else if(e<p->data.bno)
            p->lchild=s;
        else p->rchild=s;
        return TURE;
    }
    else {
        scanf("%*s%*s",p->data.bname,p->data.writer);
        scanf("%d",&num);
        p->data.totalremain += num;
        p->data.remain += num;
        return FALSE;
    }
}

void PreOrder(BiTree T){
    //先序遍历，递归写法
    if(T){
        printf("%d",T->data.bno);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T){
    //中序遍历
    if(T){
        InOrder(T->lchild);
        printf("%3d   %-10s %-10s %6d    %6d\n",T->data.bno,T->data.bname,
               T->data.writer,T->data.remain,T->data.totalremain);
        InOrder(T->rchild);
    }
}

int Delete(BiTree* p){
    BiTree q,s;
    if(!(*p)->rchild){
        q=(*p);
        *p=(*p)->lchild;
        free(q);
    }
    else if(!(*p)->lchild){
        q=(*p);
        *p=(*p)->rchild;
        free(q);
    }
    else{
        q=(*p);
        s=(*p)->lchild;
        while(s->rchild){
            q=s;
            s=s->rchild;
        }
        (*p)->data.bno=s->data.bno;
        if(q!=(*p)) q->rchild = s->lchild;
        else q->lchild=s->lchild;
        free(s);
    }
    return TURE;
}

int DeleteBST(BiTree* T,int key){
    if(!T) return FALSE;
    else{
        if(key == (*T)->data.bno) return Delete(T);
        else if(key<(*T)->data.bno) return DeleteBST(&((*T)->lchild),key);
        else return DeleteBST(&((*T)->rchild),key);
    }
}

int Borrow(BiTree* T,int e){
    BiTree p=NULL;
    BiTree s;
    Borrower* temp=NULL;
    temp=(Borrower*)malloc(sizeof(Borrower));
    if(!SearchBST(*T,e,NULL,&p)) return FALSE;//没有这本书
    else if(p->data.remain == 0) return FALSE;//这本书没库存了
    else{
        printf("请输入借阅者信息(图书证号，归还日期(格式:xx/xx/xx)):>\n");
        fflush(stdin);
        scanf("%s%s",temp->news.id,temp->news.date);
        temp->next = p->data.bor.next;
        p->data.bor.next = temp;
        p->data.remain--;
        return TURE;
    }
}

int Back(BiTree* T,int e){
    Borrower *n1=NULL,*n2=NULL;//n2在n1的前一个结点
    BiTree p;
    char id[10],date[20];
    if(!SearchBST(*T,e,NULL,&p)) return FALSE;//没有这本书
    printf("请输入借阅信息(图书证号，归还日期(格式:xx/xx/xx)):>\n");
    fflush(stdin);
    scanf("%s%s",id,date);
    n1 = p->data.bor.next;
    while(n1 && !(!strcmp(id,n1->news.id) && !strcmp(date,n1->news.date))){
        n2 = n1;
        n1 = n1->next;
    }
    if(!n1) return FALSE;//没找到这条边
    if(!n2) p->data.bor.next = n1->next;
    else n2->next = n1->next;
    free(n1);
    p->data.remain++;
    return TURE;
}

int ShowBor(BiTree* T,int e){
    Borrower *n=NULL;
    BiTree p;
    SearchBST(*T,e,NULL,&p);
    n = p->data.bor.next;
    if(!n) return FALSE;
    printf("图书证号      归还期限\n");
    while(n){
        printf("%-10s    %-20s\n",n->news.id,n->news.date);
        n = n->next;
    }
    return TURE;
}