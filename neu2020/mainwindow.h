#define MAINWINDOW_H
#include <QMainWindow>
#include<lms.h>
#include<string>
#include<mytreewid.h>
#include<QTableWidget>
#include<QCheckBox>
using namespace std;
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
   // friend class MytreeWid;
    ~MainWindow();

protected:
    void setListWidget(const int &currentPage);//制作表格函数
void setGraphScene(char path[]);//设置图片：算法分析
protected slots://槽函数
void save_insert();//保存插入
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
void refresh_data();//还原数据表格
void delete_selected();//删除选中的元组
void addtabitems();//更新表格，构造新元素
void addrows(int,int,int,int);//构造新元素时增行
void outputdata();//导出数据
void deleteandfree();//确认删除
void slotOpen(QTreeWidgetItem*,int);//点击QtreeWidgetitem事件
private:
 Ui::MainWindow *ui;//页面指针
    int m_pageCount;//每页的页数
QCheckBox**check;//复选框对象指针
    int m_currentPageNum;   //当前页数
    int m_countPageNum;        //总页数
    int focusedrow;//指示修改的行数
    int focusedcol;//指示修改的页数
    lms ls;//数据操作的核心对象
    void insert_item(int id,int flag,int br,int dis,char road[]);//插入新条目到对象中
    void check_close_delcol();//检查并关闭删除栏
};

