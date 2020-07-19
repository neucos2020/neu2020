#ifndef LMS_H
#define LMS_H
class lms
{private:
    typedef struct {
        /*int LinkId;
        int flag;
        int brunch;
        int disclass;*/
        int*data;//依次填入LinkId,flag,brunch,disclass
        char* roadname;
        bool selected;//判断是否被选中：单独搞一个数组很麻烦

    }LandMark,*LM;
public:

    lms();
    ~lms();
    void print();
    void heapInsert(LM*r,int length,int info);//建大根堆
    void heapify(LM*r,int index,int size,int info);//堆调整:info是第几个判据
    void heapSort(LM*r,int length,int info);//堆排序:info是第几个判据
    void shellsort(LM*r,int length,int info);//希尔排序:info是第几个判据
    int Partition(LM*r,int start,int end,int info);//快速排序分隔
    void bubbleSort(LM* r,int length,int info);//冒泡排序
    void selectionSort(LM* r,int length,int info);//选择排序
    void QuickSort(LM*r,int start,int end,int info);//快速排序:info是第几个判据:注意调用时QuickSort(LM,0,lms.length-1,info);
    int length;
    int origin_length;//存放base的内存长度;
    LM* base;
};

#endif // LMS_H
