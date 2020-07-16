#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include<lms.h>
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
private:
    Ui::MainWindow *ui;
    int m_pageCount;

    int m_currentPageNum;   //当前页数
    int m_countPageNum;        //总页数
    int focusedrow;
    int focusedcol;
    lms ls;
};

#endif // MAINWINDOW_H

