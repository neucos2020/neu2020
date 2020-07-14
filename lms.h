#ifndef LMS_H
#define LMS_H
class lms
{private:
    typedef struct {
        int LinkId;
        int flag;
        int brunch;
        int disclass;
        char* roadname;

    }LandMark,*LM;
public:
    typedef  int (*FP)(LM a, LM b);  //定义类型
    lms();
    ~lms();
    void print();
    void sift(LM*r,int length);//堆调整
    void heapsort(LM*r,int length);//堆排序
    int length;
    LM* base;
    int cmp1(LM p,LM q);//按照LinkId比较
     int cmp2(LM p,LM q);//按照disclass比较
     FP fp[2];
};

#endif // LMS_H
