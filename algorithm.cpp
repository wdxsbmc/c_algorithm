#include <iostream>
#include "cstdio"
#include "cstring"

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include <string.h>
//famous elf hash algorithm
unsigned int ELFhash(char *str)  
{  
    unsigned int hash=0;  
    unsigned int x=0;  
    while(*str)  
    {  
        hash=(hash<<4)+*str;  
        if((x=hash & 0xf0000000)!=0)  
        {  
            hash^=(x>>24);   //影响5-8位，杂糅一次   
            hash&=~x;   //清空高四位   
        }  
        str++;  
    }  
    return (hash & 0x7fffffff);   
}  


//sort
/*--------------------冒泡排序---------------------*/
void bubleSort(int data[], int n) {
    int i,j,temp;
    //两个for循环，每次遍历一边前n-2个数，把最大的数放在n-1
    //将最大的元素排到最后。
    for(j=0;j<n-1;j++) {
        //外循环一次，就排好一个数，并放在后面，
        //所以比较前面n-j-1个元素即可
        for(i=0;i<n-j-1;i++) {
            if(data[i]>data[i+1]) {
                temp = data[i];
                data[i] = data[i+1];
                data[i+1] = temp;
            }
        }
    }  
}

//快速排序   
//第一个参数要排的数组，第二个参数第一个数，第三个参数数组成员个数  
void quicksort(int a[],int left,int right) 
{ 
    int i,j,t,temp; 
    if(left>right) 
       return; 
                                
    temp=a[left]; //temp中存的就是基准数 
    i=left; 
    j=right; 
    while(i!=j) 
    { 
                   //顺序很重要，要先从右边开始找 
                   while(a[j]>=temp && i<j) 
                            j--; 
                   //再找右边的 
                   while(a[i]<=temp && i<j) 
                            i++; 
                   //交换两个数在数组中的位置 
                   if(i<j) 
                   { 
                            t=a[i]; 
                            a[i]=a[j]; 
                            a[j]=t; 
                   } 
    } 
    //最终将基准数归位   
    a[left]=a[i]; 
    a[i]=temp; 
                             
    quicksort(a,left,i-1);//继续处理左边的，这里是一个递归的过程 
    quicksort(a,i+1,right);//继续处理右边的 ，这里是一个递归的过程 
} 

void kuaipai(int array[],int low,int hight)  
{  
    int i,j,t,m;  
    if(low<hight)  
    {  
        i=low;  
        j=hight;  
        t=array[low];//第一个数为轴  
        while(i<j)  
        {  
            while(i<j && array[j]>t)//从右边找出小于轴的数  
                j--;  
            if(i<j)//将小于轴的数array[j]放到左边array[i]的位置  
            {  
                m=array[i];  
                array[i]=array[j];  
                array[j]=m;  
                i++;  
            }  
            while(i<j && array[i]<=t)//从左边找出大于轴的数 = array[1]may be changed 
                i++;  
            if(i<j)//将大于轴的数array[i]放在右边array[j]的位置  
            {  
                m=array[j];  
                array[j]=array[i];  
                array[i]=m;  
                j--;  
            }     
        }  
          
        array[i]=t;//轴放在中间,现在就有两个区域了分别是[0 i-1]和[i+1 hight],分别快排  
        kuaipai(array,0,i-1);  
        kuaipai(array,i+1,hight);  
    }  
} 




//节点结构体，每个节点分别保存了一个指向前一个节点的指针和指向后一个节点的指针，以及保存数据的指针
struct _node{
    struct _node *prevNode;
    struct _node *nextNode;
    void *data;
};


//链表结构体，记录了链表的首节点和尾节点指针，以及节点总个数
struct _list{
    struct _node *firstNode;
    struct _node *lastNode;
    int len;
};


// 头部加入节点
void lpush(struct _list *list, void *data)
{
    struct _node *node = (struct _node*)malloc(sizeof(struct _node));
    memset(node,0, sizeof(struct _node));
    node->data = data;

    //1 connect node with first
    node->nextNode = list->firstNode;

    //
    if (list->firstNode != NULL)
    {
        list->firstNode->prevNode = node;
    }

    //2  reset fist node  and last node if null
    list->firstNode = node;
    if (list->len == 0)
    {
        list->lastNode = node;
    }
    list->len++;
}


// 尾部加入节点
void rpush(struct _list *list, void *data)
{
    struct _node *node = (struct _node*)malloc(sizeof(struct _node));
    memset(node,0, sizeof(struct _node));
    node->data = data;

    //1 conect with last
    node->prevNode = list->lastNode;
    if (list->lastNode != NULL)
    {
        list->lastNode->nextNode = node;
    }

    //reset last
    list->lastNode = node;

    if (list->len == 0)
    {
        list->firstNode = node;
    }
    list->len++;
}


// 头部弹出节点
void lpop(struct _list *list)
{
    if (list->firstNode == NULL)
    {
        return;
    }


    if (list->firstNode->nextNode != NULL)
    {
        //move first
        list->firstNode = list->firstNode->nextNode;
        //kill node
        free(list->firstNode->prevNode);
        list->firstNode->prevNode = NULL;
    }
    else
    {
        free(list->firstNode);
        list->firstNode = NULL;
    }


    list->len--;


    if (list->len == 0)
    {
        list->lastNode = NULL;
    }
}




// 尾部弹出节点
void rpop(struct _list *list)
{
    if (list->lastNode == NULL)
    {
        return;
    }


    if (list->lastNode->prevNode != NULL)
    {
        //1 tail move
        list->lastNode = list->lastNode->prevNode;
        //2 kill node
        free(list->lastNode->nextNode);
        list->lastNode->nextNode = NULL;
    }
    else
    {
        free(list->lastNode);
        list->lastNode = NULL;
    }


    list->len--;
    if (list->len == 0)
    {
        list->firstNode = NULL;
    }
}


// 获取指定位置上的节点值
void *getVal(struct _list list, int pos)
{
    if (pos < 0)
    {
        return NULL;
    }


    int i;
    struct _node *curNode = list.firstNode;
    for(i = 0; i < pos; i++)
    {
        if(curNode->nextNode != NULL)
        {
            curNode =  curNode->nextNode;
        }
        else
        {
            curNode = NULL;
            break;
        }
    }


    if (curNode == NULL){
        return NULL;
    }
    return curNode->data;
}






static void print_r(struct _list list)
{
    printf("-----------------------------------------\n");
    printf("list.len = %d\n", list.len);
    int i = 0;
    struct _node *node = list.firstNode;
    while(1)
    {
        if (node == NULL)
        {
            break;
        }


        printf("list[%d]: %s\n", i, node->data);
        node = node->nextNode;
        i++;
    }
}





//chain###########################################################################
//    操作系统 win 8.1
//    编译环境 Visual Stuido 2017
typedef int ElementType;        //    定义数据类型,可根据需要进行其他类型定义
                                //    链表节点的定义
typedef struct ListNode {
    ElementType  Element;        //    数据域，存放数据
    ListNode* Next;        //    指向下一个链表节点
}Node, *PNode;

//    函数声明
PNode CreateList(void);    //    声明创建链表函数
void TraverseList(PNode List);    //    声明遍历链表函数
void InsertList(PNode List, int pos, int val);        //    声明链表插入函数
void DeleteTheList(PNode List);    //    声明删除整个链表函数
void DeleteList(PNode List, int pos);    //    声明删除链表元素函数
PNode FindList(PNode List);    //    声明链表查询函数


//    创建链表函数定义
PNode CreateList(void) {
    int len ;    //    用于定义链表长度
    int val ;    //    用于存放节点数值
    PNode PHead = (PNode)malloc(sizeof(Node));    //    创建分配一个头节点内存空间
    if (PHead == NULL)    //    判断是否分配成功
    {
        printf("malloc fail!\n");
        exit(-1);
    }

    PNode PTail = PHead;    //    链表的末尾节点，初始指向头节点
    PTail->Next = NULL;    //    最后一个节点指针置为空
    printf("Input node num:");
    scanf("%d", &len);        //    输入节点个数
    for (int i = 0; i < len; i++) {

        PNode PNew = (PNode)malloc(sizeof(Node));    //    分配一个新节点
        if (PNew == NULL) {
            printf("malloc node fail\n");
            exit(-1);
        }
        printf("Input node:%d data:", i + 1);
        scanf("%d", &val);    //    输入链表节点的数据

        PNew->Element = val;    //    把数据赋值给节点数据域

        PTail->Next = PNew;    //    末尾节点指针指向下一个新节点
        PNew->Next = NULL;        //    新节点指针指向为空
        
        PTail = PNew;    //    将新节点复制给末尾节点        
    }
    printf("Create chain sucess!\n");
    return PHead;    //    返回头节点
}

//    定义链表遍历函数
void TraverseList(PNode List) {
    PNode P = List->Next;    //    首节点赋值给临时节点P
    printf("traver list:");
    if (P == NULL)
        printf("list empty!");
    while (P != NULL)        //当临时节点P不为尾节点时，输出当前节点值 
    {
        printf("%d ", P->Element);
        P = P->Next;
    }
    printf("\n");
}

//    定义链表查询函数
PNode FindList(PNode List) {
    PNode P = List->Next;    //    定义临时指针P指向首节点的地址
    int num = 0;    //    用于记录链表节点位置
    int val = 0;    //    用于存放要查询的值
    printf("Input  serach data:");
    scanf("%d", &val);    //    输入要查询的数值
    while (P != NULL&&P->Element != val) {
        P = P->Next;
        ++num;
    }
    if (P != NULL)
        printf("Find node:%d", num + 1);
    else
        printf("Find node fail!");
    printf("\n");
    return P;
}
//     定义链表插入函数
//    在链表位置第pos节点前插入包含数据val的节点
void InsertList(PNode List, int pos, int val) {
    int position = 0;
    PNode P = List;    //    定义节点p指向头节点
                    //    寻找pos节点的前驱结点
    while (P != NULL&&position<pos - 1)
    {
        P = P->Next;
        ++position;
    }
    PNode Tmp = (PNode)malloc(sizeof(Node));    //    分配一个临时节点用来存储要插入的数据
    if (Tmp == NULL)
    {
        printf("Insert malloc fail!");
        exit(-1);
    }
    //    插入节点
    Tmp->Element = val;
    Tmp->Next = P->Next;
    P->Next = Tmp;
}

//定义删除整个链表函数
void DeleteTheList(PNode List) {
    PNode P, Tmp;
    P = List->Next;    //定义指针P指向链表要删除的链表List的第一个点节点
    List->Next = NULL;
    while (P != NULL) {
        Tmp = P->Next;        //临时Tmp指向要删除的节点的下个节点
        free(P);    //释放指针P指向的节点
        P = Tmp;    //重新赋值
    }
    printf("Delete list success!\n");
}
//    定义删除链表元素函数
//    删除链表中的第pos节点
void DeleteList(PNode List, int pos) {
    int position = 0;
    PNode P = List;    //    定义一个指针p指向链表头节点
                    //    寻找pos节点位置的前驱节点
    while (P != NULL&&position < pos - 1) {
        P = P->Next;
        ++position;
    }

    //    删除节点
    PNode Tmp = P->Next;    //    定义临时指针Tmp指向要删除的节点
    P->Next = Tmp->Next;    //    使要删除节点的前驱结点指向其后驱节点
    free(Tmp);    //    释放删除节点的内存空间，防止内存泄漏
    Tmp = NULL;    //    使q指向空指针，防止产生野指针
}



int main()
{
    std::cout<<"test algorithm start>>>"<<std::endl;

    //test elf hash

    char data[5] = {'a','b','c','d','e'};  
    printf("1 hash result:%d\n",ELFhash(data));


    //test bouble sort
    int test_bs[5] = {1,2,5,4,3};
    bubleSort(test_bs,sizeof(test_bs)/sizeof(int));
    printf("2 bb sort result:\n");
    for(int i=0; i<sizeof(test_bs)/sizeof(int);i++)
        printf("%d ",test_bs[i]);
    
    //test kuai sort
    
    int test_kp[5] = {1,2,5,4,3};
    kuaipai(test_kp,0,4);
    
    printf("\n3 kuai sort result:\n");
    for(int i=0; i<sizeof(test_kp)/sizeof(int);i++)
        printf("%d ",test_kp[i]);

    printf("\n");
    std::cout<<"test algorithm stop<<<"<<std::endl;

//    TEST CHAIN
    PNode List = CreateList();    //    创建一个指针，使其指向新创建的链表的头指针    
    TraverseList(List);        //    遍历链表
    FindList(List);        //    链表查询    
    InsertList(List, 3, 100);    //    链表插入，在第三个位置插入数值100
    TraverseList(List);
    DeleteList(List, 3);    //    删除链表第三个节点
    TraverseList(List);
    DeleteTheList(List);    //    删除整个链表
    TraverseList(List);



    //test double chain
     struct _list list = {NULL, NULL, 0};


    lpush(&list, (void*)"node 0");
    lpush(&list, (void*)"node 1");
    lpush(&list, (void*)"node 2");
    rpush(&list, (void*)"node 3");
    rpush(&list, (void*)"node 4");
    print_r(list);


    lpop(&list);
    rpop(&list);
    print_r(list);


    lpop(&list);
    lpop(&list);
    lpop(&list);
    rpop(&list);
    rpop(&list);
    print_r(list);


    rpush(&list, (void*)"hello node");
    print_r(list);

   return 1;
}
