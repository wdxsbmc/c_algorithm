#include <iostream>
#include "cstdio"
#include "cstring"


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
            while(i<j && array[i]<=t)//从左边找出大于轴的数  
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
    


    printf("\n");
    std::cout<<"test algorithm stop<<<"<<std::endl;


    return 1;
}