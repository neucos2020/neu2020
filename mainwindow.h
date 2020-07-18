#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<lms.h>
#include<QTableWidget>
#include<QCheckBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void setListWidget(const int &currentPage);//制作表格函数

protected slots://槽函数
    void upBtnClicked();//上一页
    void downBtnClicked();//下一页
void Sort_method_selected();//排序方法
void Sort_info_selected();//排序指标
void Find_method();//查找方法
void Find_info();//查找指标
void Find_txt();//查找字段
void getItem();//双击触发函数
void inputregex();//表格修改成功函数
void change_del_col();//展示/关闭删除栏
void delete_info_confirm(int);//点击header事件
void change_to_head();//跳到首页
void change_to_tail();//跳到尾页
void change_to_page();//跳到自定义页
private:
    Ui::MainWindow *ui;//页面指针
    int m_pageCount;//每页的页数
QCheckBox**check;//复选框对象指针
    int m_currentPageNum;   //当前页数
    int m_countPageNum;        //总页数
    int focusedrow;//指示修改的行数
    int focusedcol;//指示修改的页数
    bool* chosen;//显示某元素是否已经被选中：准备删除
    lms ls;//数据操作的核心对象
};

#endif // MAINWINDOW_H
