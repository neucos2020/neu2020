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
    void setListWidget(const int &currentPage);

protected slots:
    void upBtnClicked();
    void downBtnClicked();
void Sort_method_selected();
void Sort_info_selected();
void Find_method();
void Find_info();
void Find_txt();
void getItem();
void inputregex();
void change_del_col();//展示/关闭删除栏
void delete_info_confirm(int);//点击header事件
private:
    Ui::MainWindow *ui;
    int m_pageCount;
QCheckBox**check;
    int m_currentPageNum;   //当前页数
    int m_countPageNum;        //总页数
    int focusedrow;
    int focusedcol;
    bool* chosen;//显示某元素是否已经被选中：准备删除
    lms ls;
};

#endif // MAINWINDOW_H



