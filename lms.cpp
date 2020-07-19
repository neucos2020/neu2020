#include "lms.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctime>
#define MCGETCHAR(data)(*((char*)(data)))
#define MCGETSHORT(data)((unsigned short)((((unsigned short)(*((char*)(data))))<<8)|(((unsigned short)(*((char*)(data)+1)))&0x00ff)))
#define MCGETLONG(data)((((unsigned long)MCGETSHORT((data)))<<16)|(((unsigned long)MCGETSHORT((char*)(data)+2))&0x0000ffff))
#define MCGET3BN(data)((((unsigned long)MCGETCHAR((data)))<<16)|(((unsigned long)MCGETSHORT((char*)(data+1))&0x0000ffff))
#define Length 60000
#define Addition 1000
lms::lms()
{
    int m;
    int i=0;//循环量
    char aclinkId[4];
    char acroadnamesize[2];
    char acNodeInfo[4];
    unsigned short ustotalsize;
    unsigned long ullinkId;
    unsigned short usroadnamesize;
    char actotalsize[2];
this->base=(LM*)malloc(sizeof(LM)*Length);
    this->length=Length;
    FILE*pfp=fopen("G://Pr\\GTBL.dat","rb");
    if(pfp==NULL)
    {
    printf("can not open the GTBL.DAT file or there is no the file!\n");system("pause");
    return ;
    }
   // printf("\n\n\t\t\t\t导入成功\n");

    while(fread(actotalsize,sizeof(actotalsize),1,pfp)==1)
    {
        if(i==this->length){
        this->base=(LM*)realloc(this->base,(this->length+Addition)*sizeof(LM));
        if(! this->base){printf("fail to share memory->1\n");exit(1);}
            this->length+=Addition;
        }
    fread(aclinkId,sizeof(aclinkId),1,pfp);
    fread(acroadnamesize,sizeof(acroadnamesize),1,pfp);
    fread(acNodeInfo,sizeof(acNodeInfo),1,pfp);
    ustotalsize=MCGETSHORT(actotalsize);
    ullinkId=MCGETLONG(aclinkId);
    usroadnamesize=MCGETSHORT(acroadnamesize);
    m=(int)acNodeInfo[3]&255;
    char roadname[30];
    fread(roadname,sizeof(char),ustotalsize-12,pfp);
   this->base[i]=(LM)malloc(sizeof(LandMark));
    this->base[i]->data=(int*)malloc(sizeof(int)*4);
   if(! this->base[i]){printf("fail to share memory->2\n");exit(2);}
    this->base[i]->data[0]=ullinkId;
    this->base[i]->data[1]=(m&128)/128;
    this->base[i]->data[2]=(m&112)/16;
    this->base[i]->data[3]=m&15;
   this->base[i]->selected=false;//默认没有选中
    this->base[i]->roadname=(char*)malloc(30*sizeof(char));
    if(! this->base[i]->roadname){printf("fail to share memory->3\n");exit(3);}
   strcpy( this->base[i]->roadname,roadname+4);
   i++;
    }
    this->length=i;
    for(int j=this->length-1;j>=i;j--){
          free(this->base[j]->roadname);
          free(this->base[j]->data);
        free(this->base[j]);
    }
    fclose(pfp);
        printf("load OK\n");
}
void lms::print(){
    for(int i=0;i<this->length;i++){
        printf("LinkId:%d flag:%d brunch:%d disclass:%d roadname:%s\n",this->base[i]->data[0],this->base[i]->data[1], this->base[i]->data[2],this->base[i]->data[3],this->base[i]->roadname);
    }
}
lms::~lms(){
    for(int j=0;j<this->length;j++){
        free(this->base[0]->roadname);
        free(this->base[0]);
    }
    free (this->base);
}
void lms::heapInsert(LM *r, int length, int info){
    for (int i = 0; i <length; i++) {
             //当前插入的索引
             int currentIndex = i;
             LM temp;
             //父结点索引
             int fatherIndex = (currentIndex - 1) / 2;
             //如果当前插入的值大于其父结点的值,则交换值，并且将索引指向父结点
             //然后继续和上面的父结点值比较，直到不大于父结点，则退出循环
             while (r[currentIndex]->data[info-1]>r[fatherIndex]->data[info-1]) {
                 //交换当前结点与父结点的值
                 temp=r[currentIndex];r[currentIndex]=r[fatherIndex];r[fatherIndex]=temp;
                 //将当前索引指向父索引
                 currentIndex = fatherIndex;
                 //重新计算当前索引的父索引
                 fatherIndex = (currentIndex - 1) / 2;
             }
         }
}
void lms::heapify(LM *r, int index, int size, int info){
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    LM temp;
    while (left < size) {
        int largestIndex;
        //判断孩子中较大的值的索引（要确保右孩子在size范围之内）
        if (r[right]->data[info-1]>r[left]->data[info-1] && right < size) {
            largestIndex = right;
        } else {
            largestIndex = left;
        }
        //比较父结点的值与孩子中较大的值，并确定最大值的索引
        if (r[index]->data[info-1]>r[largestIndex]->data[info-1]) {
            largestIndex = index;
        }
        //如果父结点索引是最大值的索引，那已经是大根堆了，则退出循环
        if (index == largestIndex) {
            break;
        }
        //父结点不是最大值，与孩子中较大的值交换
       temp=r[index];r[index]=r[largestIndex];r[largestIndex]=temp;
        //将索引指向孩子中较大的值的索引
        index = largestIndex;
        //重新计算交换之后的孩子的索引
        left = 2 * index + 1;
        right = 2 * index + 2;
    }
}
void lms::heapSort(LM *r, int length, int info){
    //构造大根堆
    clock_t start, stop;
        start=clock();
    LM temp;
          heapInsert(r,length,info);
          int size = length;
          while (size > 1) {
              //固定最大值
             temp=r[0];r[0]=r[size-1];r[size-1]=temp;
              size--;
              //构造大根堆
              heapify(r,0,size,info);

          }
          stop=clock();
          double duration=(double)(stop-start)/CLK_TCK;
          printf("time cost of sorting\n:%.1fms\n",1000*duration);
}
void lms::shellsort(LM *r, int length, int info)
{clock_t start, stop;
    start=clock();
    int j=length/2;
    int i,h;
    LM temp;
    for(;j>0;j=j/2){
        for(i=j;i<length;i++){
            temp=r[i];
            for(h=i-j;h>0&&r[h]->data[info-1]<r[h]->data[info-1];h=h-j){
                r[h+j]=r[h];
            }
            r[h+j]=temp;
        }
    }
    stop=clock();
    double duration=(double)(stop-start)/CLK_TCK;
    printf("time cost of sorting\n:%.1fms\n",1000*duration);
}
int lms::Partition(LM *r, int start, int end, int info){
    int i,j;
    i=start;j=end;
    LM temp;
    while(i<j){
        while(i<j&&r[j]->data[info-1]>=r[i]->data[info-1]){
            j--;
        }
        if(i<j){
            temp=r[i];r[i]=r[j];r[j]=temp;i++;
        }
        while(i<j&&r[j]->data[info-1]>=r[i]->data[info-1])i++;
        if(i<j){
            temp=r[i];r[i]=r[j];r[j]=temp;j--;
        }
}
    return i;
}
void lms::QuickSort(LM *r, int start, int end, int info){
    int flag;
   if(start<end){
       flag=Partition(r,start,end,info);
       QuickSort(r,start,flag-1,info);
        QuickSort( r,flag+1,end,info);
   }
}
void  lms:: bubbleSort(LM* r,int length,int info) {
    clock_t start, stop;
    start=clock();
    LM rtemp;
    int i,j;
    for(i = 0; i < length - 1; i++) {
        for(j = 0; j < length - 1 - i; j++) {
            if(r[j+1]->data[info-1]<r[j]->data[info-1]) {        // 相邻元素两两对比
                rtemp = r[j+1];        // 元素交换
                r[j+1] = r[j];
                r[j] = rtemp;
            }
        }
    }
    stop=clock();
    double duration=(double)(stop-start)/CLK_TCK;
    printf("time cost of sorting\n:%.1fms\n",1000*duration);
}
void  lms:: selectionSort(LM* r,int length,int info) {
    clock_t start, stop;
    start=clock();
    int i,j,minIndex;
    LM temp;
    for(i = 0; i < length - 1; i++) {
        minIndex = i;
        for(j = i + 1; j < length; j++) {
            if(r[j]->data[info-1]<r[minIndex]->data[info-1]) {     // 寻找最小的数
                minIndex = j;                 // 将最小数的索引保存
            }
        }
        temp = r[i];
        r[i] = r[minIndex];
        r[minIndex] = temp;
    }
    stop=clock();
    double duration=(double)(stop-start)/CLK_TCK;
    printf("time cost of sorting\n:%.1fms\n",1000*duration);
}

