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
    lms();
    ~lms();
    void print();
    void sift(LM*r,int length,int info);//堆调整:info是第几个判据
    void heapsort(LM*r,int length,int info);//堆排序:info是第几个判据
    int length;
    LM* base;
    int cmp(LM p,LM q,int info);//按照LinkId比较
};

#endif // LMS_H
