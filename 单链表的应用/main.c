#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TURE 1
#define FALSE 0
#define NUM 20

typedef struct LNode
{
    char data[NUM];
    struct LNode *next;
}LNode,* LinkList;


void selectSort(LinkList *L)//选择排序
{
    char temp[20];
    LinkList p,q,m;
    //保证单链表至少有两个结点
    if(!(*L)->next||!(*L)->next->next)
        return ;
    p=(*L)->next;//p指向首结点
    while(p->next)
    {
        m=p;//m指向当前值最小的结点
        q=p->next;
        while(q)
        {
            if(strcmp(q->data,m->data)<0)
                m=q;
            q=q->next;
        } //while(q)
        strcpy(temp,m->data);
        strcpy(m->data,p->data);
        strcpy(p->data,temp);
        p=p->next;
    }//while(p->next)
}

int Is_repeat(LinkList L,const char* str)//判断输入的字符串是否与链表L中的结点重复，重复返回TURE，否则返回FALSE
{
    if(!L->next) return FALSE;//单链表为空，肯定不重复
    LinkList p=L->next;
    while(p && strcmp(p->data,str)!=0){
        p=p->next;
    }
    if(!p) return FALSE;
    else return TURE;
}//Is_repeat

void CreateList_L(LinkList* L)
{//制作带头结点的单链表,尾插法
    int flag=0;//用来标记文本中是否有重复
    char* end="end";
    char temp[NUM];//临时储存字符串
    LinkList p = NULL,tail;
    *L = (LinkList)malloc(sizeof(LNode));
    //因为申请的不是很大且连续的空间，所以不验证没要下来空间的情况了
    (*L)->next = NULL;
    tail = *L;
    scanf("%s",temp);
    while(strcmp(temp,end)!=0)
    {
        if((Is_repeat(*L,temp))) flag=1;
        else{
            p = (LinkList)malloc(sizeof(LNode));
            p->next = NULL;
            strcpy(p->data,temp);
            tail->next = p;
            tail = p;
        }
        scanf("%s",temp);
    }//尾插法
    if(flag==1) printf("文本中有重复值，已去除重复值。\n");
}//CreateList_L

void ShowList(LinkList L)
{//打印带头单链表
    LinkList p = L->next;
    while(p)
    {
        printf("%s ",p->data);
        p = p->next;
    }
    printf("\n");
}

void MergeList(LinkList La,LinkList Lb)//合并
{
    LinkList pa,pb,pc;
    LinkList p;
    pa=La->next;//pa指向La的首结点
    pb=Lb->next;//pb指向Lb的首结点
    pc=La;//以La进行链的连接操作
    La->next=NULL;
    while(pa&&pb)
    {
        if(strcmp(pa->data,pb->data)<0)//La中的数据小于Lb中的数据
        {
            p=pa->next;
            pc->next=pa;
            pa->next=NULL;
            pc=pa;
            pa=p;
        }
        else if(strcmp(pa->data,pb->data)>0){//pb里数据较小，就连接pb指向的结点，pb指向Lb的后一个
            p=pb->next;
            pc->next=pb;
            pb->next=NULL;
            pc=pb;
            pb=p;
        }
        else{
            p=pa;
            pc->next=pa;
            pc=pa;
            pa=pa->next;
            p->next=pb;
            p=pb;
            pb=pb->next;
            free(p);
        }
    }
    if(pa)//合并剩下的没遍历完的部分
        pc->next=pa;
    else pc->next=pb;
    free(Lb);
}

int main() {
    LinkList La,Lb;
    printf("La(以end结尾):>");
    CreateList_L(&La);
    selectSort(&La);
    printf("Lb(以end结尾):>");
    CreateList_L(&Lb);
    selectSort(&Lb);
    MergeList(La,Lb);
    printf("合并后表中的数据:>");
    ShowList(La);
    return 0;
}
