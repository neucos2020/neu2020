#include "lms.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
    printf("\n\n\t\t\t\t导入成功\n");

    while(fread(actotalsize,sizeof(actotalsize),1,pfp)==1)
    {
        if(i==this->length){
        this->base=(LM*)realloc(this->base,(this->length+Addition)*sizeof(LM));
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
   printf("LinkID=");
    printf("%ld\t",ullinkId);
  printf("flag=");
  printf("%d\t",(m&128)/128);
  printf("brunch=");
  printf("%d\t",(m&112)/16);
  printf("dispclass=");
   printf("%d\t",m&15);
  printf("Roadname=");
 printf("%d\t",strlen(roadname+4));
  printf("#");
   printf("\n");
   printf("%d %d\n",i,this->length);
   this->base[i]=(LM)malloc(sizeof(LandMark));
    this->base[i]->brunch=(m&112)/16;
    this->base[i]->disclass=m&15;
    this->base[i]->flag=(m&128)/128;
    this->base[i]->LinkId=ullinkId;
    this->base[i]->roadname=(char*)malloc((strlen(roadname+4))*sizeof(char));
   strcpy( this->base[i]->roadname,roadname+4);
   i++;
    }
    for(int j=i;j<this->length;j++){//清理多余的空间
        free(this->base[j]->roadname);
        free(this->base[j]);
    }
    this->length=i;
    fclose(pfp);
}
void lms::print(){
    for(int i=0;i<this->length;i++){
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
