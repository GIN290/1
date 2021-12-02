#include"library.h"
int main()
{
    int select=0;
    int i,n;
    int e=0;
    BiTree T=NULL;
    menu();
    do{
        printf("请选择要进行的操作:>");
        scanf("%d",&select);
        switch(select){
            case 0:
                printf("退出\n");
                break;
            case 1:
                printf("请选择要入库图书的种类个数:>");
                scanf("%d",&n);
                if(n==0) break;
                printf("请输入图书信息(书号，书名，作者名，购买量):>\n");
                for(i=0;i<n;i++){
                    scanf("%d",&e);
                    InsertBST(&T,e);
                }
                printf("操作完成！\n");
                break;
            case 2:
                printf("请选择要删除的图书种类个数:>");
                scanf("%d",&n);
                printf("请输入要删除书号:>\n");
                for(i=0;i<n;i++){
                    scanf("%d",&e);
                    DeleteBST(&T,e);
                }
                printf("操作完成！\n");
                break;
            case 3:
                printf("请选择要借阅的图书种类个数:>");
                scanf("%d",&n);
                printf("请输入要借阅书号(一次输入一个):>\n");
                for(i=0;i<n;i++){
                    scanf("%d",&e);
                    if(Borrow(&T,e) == TURE){
                        printf("图书%d借阅成功\n",e);
                    }
                    else printf("操作失败，书号%d不存在或者没库存了\n",e);
                }
                break;
            case 4:
                printf("请选择要归还的图书种类个数:>");
                scanf("%d",&n);
                printf("请输入要归还书号(一次输入一个):>\n");
                for(i=0;i<n;i++){
                    scanf("%d",&e);
                    if(Back(&T,e) == TURE){
                        printf("图书%d归还成功\n",e);
                    }
                    else printf("操作失败，书号%d错误或者日期错误\n",e);
                }
                break;
            case 5:
                printf("书号  书名       作者       现存量  总库存量\n");
                InOrder(T);
                break;
            case 6:
                printf("请输入想要查询借阅情况的书号:>");
                scanf("%d",&e);
                if(ShowBor(&T,e)==FALSE) printf("无记录\n");
                break;
            default:printf("选择错误，请重新选择！\n");
                break;
        }
    }while(select);
    return 0;
}