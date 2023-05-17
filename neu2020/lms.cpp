#include "lms.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctime>
#include<direct.h>
#define Length 60000
#define Addition 1000
lms::lms()
{
    int m;
    int i=0;//循环量
    unsigned char actotalsize[2];//从二进制文件中读取道路信息的总体数据长度 , actotalsize[2]->两字节.
    unsigned char aclinkId[4];//从二进制文件中读取道路编号 , aclinkId[4]->四字节.
    unsigned char acroadnamesize[2];//从二进制文件中读取道路名称数据长度 , acroadnamesize[2]->两字节.
    unsigned char acNodeInfo[4];//从二进制文件中读取Node的情报 , acNodeInfo[4]->四字节.

    unsigned char a, b, c, d;//unsigned char一个字节
    unsigned short ustotalsize;//两字节 unsigned short
    unsigned long ullinkId;//四字节 unsigned long
    unsigned short usroadnamesize;//两字节 unsigned short

    this->base=(LM*)malloc(sizeof(LM)*Length);//申请空间，用于存储每一条道路，
    this->length=Length;
    FILE*pfp=fopen("./debug/file.dat","rb");//定义文件指针pfp 指向文件GTBL.dat，并以rb(读取二进制文件)的形式打开(fopen函数)
    if(pfp==NULL)//读取文件失败
    {
    printf("can not open the GTBL.DAT file or there is no the file!\n");system("pause");
    return ;
    }

    //读取成功 <-> fread()==1 <-> 一直循环,不断读取数据
    while(fread(actotalsize,sizeof(actotalsize),1,pfp)==1)//利用fread函数读取道路信息的总体数据长度，将数据存进actotalsize[2]
    {
        if(i==this->length){
        this->base=(LM*)realloc(this->base,(this->length+Addition)*sizeof(LM));//数据超过60000条，申请新的空间
        if(! this->base){printf("fail to share memory->1\n");exit(1);}//申请空间失败
            this->length+=Addition;
        }
    fread(aclinkId,sizeof(aclinkId),1,pfp);//利用fread函数读取道路编号，将数据存进aclinkId[4]
    fread(acroadnamesize,sizeof(acroadnamesize),1,pfp);//利用fread函数读取道路名称数据长度，将数据存进acroadnamesize[2]
    fread(acNodeInfo,sizeof(acNodeInfo),1,pfp);//利用fread函数读取Node的情报，将数据存进acNodeInfo[4]

    ustotalsize = (actotalsize[0] << 8) | actotalsize[1];
    a = (aclinkId[0]);
    b = (aclinkId[1]);
    c = (aclinkId[2]);
    d = (aclinkId[3]);
    ullinkId = (unsigned long)(a << 24) | (unsigned long)(b << 16) | (unsigned long)(c << 8) | (unsigned long)(d);
    usroadnamesize = (acroadnamesize[0] << 8) | acroadnamesize[1];

    char roadname[30];//定义roadname[],用于保存道路名称
    fread(roadname,sizeof(char),ustotalsize-12,pfp);//利用fread函数读取道路名称，将数据存进roadname[30]
   this->base[i]=(LM)malloc(sizeof(LandMark));//申请空间，用于存储每条道路的信息
   if(! this->base[i])//申请失败
   {
       printf("fail to share memory->2\n");
       exit(2);
   }
    m=(int)acNodeInfo[3];//acNodeInfo[3](1个字节)包含flag(7)、brunch(6-4)、disclass(3-0)的信息
    this->base[i]->brunch=(m&112)/16;//m&112 <-> xxxx xxxx & 0111 0000 = 0xxx 0000 <-> 要右移四位，所以/16( /(2^4) )
    this->base[i]->disclass=(int)m&15;//m&15 <-> xxxx xxxx & 0000 1111 = 0000 xxxx  清掉m的高4位,而保留低4位(disclass(3-0))
    this->base[i]->flag=(m&128)/128;//m&125 <-> xxxx xxxx & 1000 0000 = x000 0000 <-> 要右移七位，所以/125( /(2^7) )
    this->base[i]->LinkId=ullinkId;
    this->base[i]->selected=false;//默认没有选中
    this->base[i]->roadname=(char*)malloc((30)*sizeof(char));//申请空间，用于存储每条道路的roadname
    if(! this->base[i]->roadname)//申请失败
    {
        printf("fail to share memory->3\n");
        exit(3);
    }
   strcpy( this->base[i]->roadname,roadname);//将上面定义的roadname[30] 字符串复制到 base[i]->roadname
                                               //roadname+4 <-> xxxx xxxx + 0000 0100 <-> 相当于给xxxx xxxx 第三位加上1
                                               //效果就是把roadname中的 “=１＝”去掉:如果是新文件应该直接取
   i++;
    }
    this->length=i;
    for(int j=this->length-1;j>=i;j--){ //释放多余的空间
          free(this->base[j]->roadname);
        free(this->base[j]);
    }
    fclose(pfp);
        printf("load OK\n");
}
void lms::print(){
    for(int i=0;i<4;i++){
        printf("LinkId:%d flag:%d brunch:%d disclass:%d roadname:%s\n",this->base[i]->LinkId,this->base[i]->brunch, this->base[i]->brunch,this->base[i]->disclass,this->base[i]->roadname);
    }
}
lms::~lms(){
    for(int j=0;j<this->length;j++){
        free(this->base[0]->roadname);
        free(this->base[0]);
    }
    free (this->base);
}
int lms:: cmp(LM p,LM q,int info){
    switch(info){
    case 1:if(p->LinkId>q->LinkId)return 1;
    else if(p->LinkId==q->LinkId) return 0;
    else return -1;break;
    case 2:if(p->flag>q->flag)return 1;
        else if(p->flag==q->flag) return 0;
        else return -1;break;
    case 4:if(p->disclass>q->disclass)return 1;
        else if(p->disclass==q->disclass) return 0;
        else return -1;break;
      case 3:if(p->brunch>q->brunch)return 1;
        else if(p->brunch==q->brunch) return 0;
        else return -1;break;
    case 5:if(p->selected==true&&q->selected==false)
            return 1;
            else if(p->selected==false&&q->selected==true)
                return -1;
                        else return 0;
            break;
    default:return cmp(q,p,-info);break;//不常用:用来swapselected();
        }
    }
void lms::heapInsert(LM *r, int length, int info)
{
    for (int i = 0; i <length; i++) {
             //当前插入的索引
             int currentIndex = i;
             LM temp;
             //父结点索引
             int fatherIndex = (currentIndex - 1) / 2;
             //如果当前插入的值大于其父结点的值,则交换值，并且将索引指向父结点
             //然后继续和上面的父结点值比较，直到不大于父结点，则退出循环
             while (cmp(r[currentIndex],r[fatherIndex],info)==1) {
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
        if (cmp(r[right],r[left],info)==1 && right < size) {
            largestIndex = right;
        } else {
            largestIndex = left;
        }
        //比较父结点的值与孩子中较大的值，并确定最大值的索引
        if (cmp(r[index],r[largestIndex],info)==1) {
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
void lms::insertfun(LM *r, int gap, int i,int info){
   LM inserted=r[i];
    int j;
    for(j=i-gap;j>=0&&cmp(r[j],inserted,info)==1;j=j-gap){
        r[j+gap]=r[j];
    }
    r[j+gap]=inserted;
}
void lms::shellsort(LM *r, int length, int info)
{clock_t start, stop;
    start=clock();
    for(int gap=length/2;gap>0;gap=gap/2){
        for(int i=gap;i<length;i++){
            insertfun(r,gap,i,info);
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
        while(i<j&&cmp(r[j],r[i],info)!=-1){
            j--;
        }
        if(i<j){
            temp=r[i];r[i]=r[j];r[j]=temp;i++;
        }
        while(i<j&&cmp(r[j],r[i],info)!=-1)i++;
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
            if(cmp(r[j+1],r[j],info)==-1) {        // 相邻元素两两对比
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
            if(cmp(r[j],r[minIndex],info)==-1) {     // 寻找最小的数
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

void lms::imwrite(lms ls,char path[])//输出该文件到指定路径
{
    int i,k;    unsigned long ullinkid;  unsigned char totalsize;
      unsigned  a, b, c, d; unsigned char rodesize;
      unsigned int bb[2];  unsigned int aa[4];
      FILE* fp;   unsigned int cc[1];

      fp = fopen(path, "wb"); //以“wb”的形式打开指定路径的文件
      if(!fp){ //打开文件失败
      printf("cannot find this file or there is no file!\n");exit(3);
      }

      for(k=0;k<ls.length;k++){
      //totalsize的写入
      totalsize = strlen(ls.base[k]->roadname)+1+12;
      a = (totalsize & 255);//25
      b = (totalsize >> 8) & 255;//0
      bb[0] = b;
      bb[1] = a;
      fwrite(&bb[0], sizeof(char), 1, fp);
      fwrite(&bb[1], sizeof(char), 1, fp);

      //linkid的写入
      ullinkid = ls.base[k]->LinkId;
      a = (ullinkid & 255);
      b = (ullinkid >> 8) & 255;
      c = (ullinkid >> 16) & 255;
      d = (ullinkid >> 24) & 255;
      aa[0] = d;
      aa[1] = c;
      aa[2] = b;
      aa[3] = a;
      fwrite(&aa[0], sizeof(char), 1, fp);
      fwrite(&aa[1], sizeof(char), 1, fp);
      fwrite(&aa[2], sizeof(char), 1, fp);
      fwrite(&aa[3], sizeof(char), 1, fp);

      //rodesize的写入
      rodesize = strlen(ls.base[k]->roadname)+1;
      a = (rodesize & 255);//25
      b = (rodesize >> 8) & 255;//0
      bb[0] = b;
      bb[1] = a;
      fwrite(&bb[0], sizeof(char), 1, fp);
      fwrite(&bb[1], sizeof(char), 1, fp);

      //nodeinfo的写入
      unsigned  w;
      w = (ls.base[k]->flag << 7) | (ls.base[k]->brunch << 4) | ls.base[k]->disclass;
      cc[0] = 0;
      fwrite(cc, sizeof(char), 1, fp);
      fwrite(cc, sizeof(char), 1, fp);
      fwrite(cc, sizeof(char), 1, fp);
      cc[0] = w;
      fwrite(cc, sizeof(char), 1, fp);

      //道路信息的写入
      int ccc;
      ccc = strlen(ls.base[k]->roadname)+1;
      fwrite(ls.base[k]->roadname, sizeof(char), ccc, fp);
     /*if (totalsize - 12 != ccc)
      {
          cc[0] = 0;
          for (i = 0; i < totalsize - ccc - 12; i++)
          {
              fwrite(cc, sizeof(char), 1, fp);
          }
      }*/
      }
      fclose(fp);
}
int lms::matching(lms::LM r, int info, string txt){
    int n=atof(txt.c_str());
printf("%d\n",n);
    string rn;
    switch(info){
    case 1:if(n==r->LinkId)return 0;
        else if(n>r->LinkId)return 1;
        else return -1;break;
    case 2:if(n==r->flag)return 0;
        else if(n>r->flag)return 1;
        else return -1;break;
    case 4:if(n==r->disclass)return 0;
        else if(n>r->disclass)return 1;
        else return -1;break;
    case 3:if(n==r->brunch)return 0;
        else if(n>r->brunch)return 1;
        else return -1;break;
    case 5:rn=r->roadname;
      return strcmp(r->roadname,txt.data());
            break;
    //default:break;
        }
}
void lms::Search(lms::LM *r, int length, int info, string txt){
    int i;
    for(i=1;i<length;++i)
        if(matching(r[i],info,txt)==0)
            r[i]->selected=true;
            //return i;
    //return 0;
}

int lms::Bsearch(LM* r, int low, int high, int info, string txt){//折半查找
    int mid;
    int count=0;
    while(high-low>0)  //当子表长度大于等于1时进行循环
    {
       mid=(low+high)/2;
        if(matching(r[mid],info,txt)==0)
          {  r[mid]->selected=true;
             return mid;
        }
        else if(matching(r[mid],info,txt)==-1)
            high=mid-1;
        else
            low=mid+1;
    }
        //r[mid]->selected=true;
    //return mid;
    //return 0;  //查找失败
}

void lms::blocksearch(LM* r, int length, int info, string txt){//分块查找
    int q1=0;int q2=64540;
    int temp=q2/60;//分块节点
    for(int i=0;i<length;i=i+temp){
        if(i+temp>=length){
            for(int j=i;j<length;j++){
                if(matching(r[j],info,txt)==0){
                    r[j]->selected=true;
                    //break;
                }
            }
        }
        else{
            if(((matching(r[i],info,txt)==0)||(matching(r[i],info,txt)==1))&&
                    ((matching(r[i+temp],info,txt)==0)||(matching(r[i+temp],info,txt)==-1))){
                for(int j=i;j<=i+temp;j++){
                    if(matching(r[j],info,txt)==0){
                        r[j]->selected=true;
                        //break;
                    }
                }
            }
        }
    }
}
