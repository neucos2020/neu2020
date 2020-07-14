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
    int length;
    LM* base;
};

#endif // LMS_H
