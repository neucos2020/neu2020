#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qDebug>
#include<qcheckbox.h>
#include<iostream>
#include<string>
using namespace std;
MainWindow::MainWindow(QWidget *parent) ://主窗口的构造函数
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//动作：建立Mainwindow.ui的界面
   //************连接信息与槽***************
    connect(ui->upPushButton, SIGNAL(clicked()), this, SLOT(upBtnClicked()));//上一页的触发函数
    connect(ui->downPushButton, SIGNAL(clicked()), this, SLOT(downBtnClicked()));//下一页的触发函数
    connect(ui->btn_head, SIGNAL(clicked()), this, SLOT(change_to_head()));//跳到首页的触发函数
    connect(ui->btn_tail, SIGNAL(clicked()), this, SLOT(change_to_tail()));//跳到尾页的触发函数
    connect(ui->Page_info, SIGNAL(editingFinished()), this, SLOT(change_to_page()));//跳到任意页的触发函数
    connect(ui->cbox_Sort, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_method_selected()));//排序方法选择框触发函数
    connect(ui->cbox_Sort_info, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_info_selected()));//排序指标选择框触发函数
    connect(ui->cbox_Find, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_method()));//查找方法选择框触发函数
    connect(ui->cbox_Find_txt, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_info()));//查找指标选择框触发函数
    connect(ui->Txt_find, SIGNAL(editingFinished()), this, SLOT(Find_txt()));//查找字段文本框触发函数
    connect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem()));//表格双击触发函数:记录所点击的行与列
    connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));//表格信息被修改时的触发函数：这里的修改不一定改变其内容，指的是从点进去的状态中出来
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(delete_info_confirm(int)));//点击表头的触发函数
    //************连接信息与槽***************
    //所有选择框(Combobox)初始化
    ui->cbox_Sort->setSizeAdjustPolicy(QComboBox::AdjustToContents);//根据页面的大小自适应调整选择框尺寸
//***********************************************
    ui->cbox_Sort->addItem(QString("-请选择-"));
    ui->cbox_Sort->addItem(QString("选择排序"));
    ui->cbox_Sort->addItem(QString("基数排序"));
    ui->cbox_Sort->addItem(QString("堆排序"));
    ui->cbox_Sort->addItem(QString("快速排序"));
    ui->cbox_Sort->addItem(QString("插入排序"));
    //***********************************************
    ui->cbox_Sort_info->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->cbox_Sort_info->addItem(QString("-请选择-"));
    ui->cbox_Sort_info->addItem(QString("LinkId"));
    ui->cbox_Sort_info->addItem(QString("flag"));
    ui->cbox_Sort_info->addItem(QString("branch"));
    ui->cbox_Sort_info->addItem(QString("disclass"));
    //***********************************************
    ui->cbox_Find->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->cbox_Find->addItem(QString("-请选择-"));
    ui->cbox_Find->addItem(QString("-顺序查找-"));
    ui->cbox_Find->addItem(QString("-折半查找-"));
    ui->cbox_Find->addItem(QString("-分块查找-"));
    //***********************************************
    ui->cbox_Find_txt->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->cbox_Find_txt->addItem(QString("-请选择-"));
    ui->cbox_Find_txt->addItem(QString("LinkId"));
    ui->cbox_Find_txt->addItem(QString("flag"));
    ui->cbox_Find_txt->addItem(QString("branch"));
    ui->cbox_Find_txt->addItem(QString("disclass"));
    ui->cbox_Find_txt->addItem(QString("roadname"));
    //所有选择框(Combobox)初始化
    //部分成员变量初始化:
    m_pageCount =100;        //此处规定每页有100页
focusedrow=focusedcol=-1;//初始化
chosen=new bool[ls.length];
for(int i=0;i<ls.length;i++){
    chosen[i]=false;
}
 //部分成员变量初始化
 setListWidget(1);//显示初始的表格
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setListWidget(const int &currentPage)//制作表格的函数:传入参数是当前是第几页
{
    if(currentPage <= 0){//如果出现异常，比如当前页面是0

        qDebug() << "Error: The currentPage can't be 0";
        return;
    }
    int startNum = m_pageCount * (currentPage - 1);//开始的序号是前面所有的页数+1;即为分页数*单页信息数+1;

    ui->tableWidget->clear();//表格清空
//生成不包括删除栏的5列
    ui->tableWidget->setColumnCount(5);//设置列数
    //设置列宽
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2,  200);
    ui->tableWidget->setColumnWidth(3, 200);
    ui->tableWidget->setColumnWidth(4, 200);
    //设置列宽
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);
   // check=new QCheckBox*[m_pageCount];//复选框集合
   // for(int i=0;i<m_pageCount;i++){//开辟内存空间
   // check[i]=new QCheckBox();
  //  }
    //设置表头
    QStringList headText;
    headText << "LinkId" << "Flag" << "branch" << "disclass" << "roadname";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    //设置表头
    //表格诸参数设置
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setRowCount(m_pageCount);//表格行数设置
    //表格诸参数设置
    for (int i = startNum; i <std::min(m_pageCount+startNum,ls.length); i++) {//std::min(m_pageCount+startNum是在最后一页时出现不满m_pageCount行时的处理办法;
        ui->tableWidget->setRowHeight(i, 24);//设置行高
        //表格元素设置
        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(ls.base[i]->LinkId));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString::number(ls.base[i]->flag));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(ls.base[i]->brunch));
        QTableWidgetItem *itemContent = new QTableWidgetItem(QString::number(ls.base[i]->disclass));
        QTableWidgetItem *itemTime = new QTableWidgetItem(QString (QString::fromLocal8Bit(ls.base[i]->roadname)));//这里是为了解决中文乱码

//check[i-startNum]->setChecked(Qt::Checked);
        ui->tableWidget->setItem(i-startNum, 0, itemDeviceID);  ui->tableWidget->item(i-startNum, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 1, itemDeviceName);ui->tableWidget->item(i-startNum, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 2, itemDeviceAddr);ui->tableWidget->item(i-startNum, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 3, itemContent);ui->tableWidget->item(i-startNum, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 4, itemTime);ui->tableWidget->item(i-startNum, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //表格元素设置
        ui->tableWidget->item(i-startNum,0)->setFlags(Qt::ItemIsEnabled);//设置第一列不可修改
    }

    //分页*****************************************
    m_currentPageNum = currentPage;//修改当前页
    m_countPageNum = ls.length / m_pageCount + 1;//修改页总数：在ls.length变化的时候会变
    ui->currentPageLabel->setText(QString::number(m_currentPageNum));//改变label ui中内容
    ui->countPageLabel->setText(QString::number(m_countPageNum));//改变label ui中内容
     //分页*****************************************

}

void MainWindow::upBtnClicked()//向上一页触发函数
{if(ui->tableWidget->columnCount()==6)//如过当前的删除栏开着的话要统计并修改选中对象chosen[]
    {for(int i=0;i<m_pageCount;i++){
    if(check[i]->isChecked()){//选中
        chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
    }
    else{//未选中
         chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
    }
        }}//如过当前的删除栏开着的话要统计并修改选中对象chosen[]
   setListWidget(m_currentPageNum - 1);//设置表格
}

void MainWindow::downBtnClicked()//向下一页触发函数
{
    if(m_currentPageNum >= m_countPageNum)//如果超出了总页数不可翻页
        return;
    if(ui->tableWidget->columnCount()==6)//同上
        {for(int i=0;i<m_pageCount;i++){
        if(check[i]->isChecked()){
            chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
        }
        else{
             chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
        }
            }}
    setListWidget(m_currentPageNum + 1);//设置表格
}
void MainWindow::Sort_method_selected()
{}
void MainWindow::Sort_info_selected()
{}
void MainWindow::Find_method()
{}
void MainWindow::Find_info()
{}
void MainWindow::Find_txt()
{
string s=ui->Txt_find->text().toStdString();//这里展示的是文本框内容，QString 也能通过QDebug()<<输出，这里转成std::string输出
cout<<s<<endl;
}
void MainWindow::change_del_col()//打开或关闭删除栏：这个函数相当复杂，或许有较简单的写法
{
    if(ui->tableWidget->columnCount()==5){//******************************展示删除栏
                int nowrows=ui->tableWidget->rowCount();//获取当前行数
                int startNum = nowrows * (m_currentPageNum - 1);//获取该页面开始位置的元素下标
                int width=ui->tableWidget->width();//获得表格宽度
                ui->tableWidget->clear();//表格清空
                ui->tableWidget->setColumnCount(6);//设置列数:6
                //设置各列的宽度:求和不是width:事实上最后一列是总和减去前边的
                ui->tableWidget->setColumnWidth(0, width/10);
                ui->tableWidget->setColumnWidth(1, width/6);
                ui->tableWidget->setColumnWidth(2, width/6);
                ui->tableWidget->setColumnWidth(3,  width/6);
                ui->tableWidget->setColumnWidth(4, width/6);
                //设置各列的宽度
                ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);
                //复选框启动
                check=new QCheckBox*[m_pageCount];//复选框集合
                for(int i=0;i<m_pageCount;i++){
                check[i]=new QCheckBox();
                }
                //复选框启动
                //设置表头
                QStringList headText;
                headText <<QString::fromLocal8Bit("删除")<< "LinkId" << "Flag" << "branch" << "disclass" << "roadname";
                ui->tableWidget->setHorizontalHeaderLabels(headText);
                          //设置表头
                //表格诸参数控制
                  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
                ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
                ui->tableWidget->setAlternatingRowColors(true);
                ui->tableWidget->verticalHeader()->setVisible(false);
                ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
                //表格诸参数控制
                ui->tableWidget->setRowCount(nowrows);//设置列数
                for (int i = startNum; i <std::min(nowrows+startNum,ls.length); i++)
                {
                    ui->tableWidget->setRowHeight(i, 24);//设置行数
                    //表格元素设置
                    QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(ls.base[i]->LinkId));
                    QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString::number(ls.base[i]->flag));
                    QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(ls.base[i]->brunch));
                    QTableWidgetItem *itemContent = new QTableWidgetItem(QString::number(ls.base[i]->disclass));
                    QTableWidgetItem *itemTime = new QTableWidgetItem(QString (QString::fromLocal8Bit(ls.base[i]->roadname)));
                    QWidget *widget = new QWidget(ui->tableWidget);//这个widget放进tablewidgetitem
                     if(chosen[i])//改变复选框状态：已经选过的就标选过
                         check[i-startNum]->setCheckState(Qt::Checked);
                     else
                         check[i-startNum]->setCheckState(Qt::Unchecked);
                     //改变复选框状态：已经选过的就标选过
                        QHBoxLayout *hLayout = new QHBoxLayout();//设置水平布局
                        hLayout->addWidget(check[i-startNum]);//复选框放入widget
                        hLayout->setMargin(0);                              // 必须添加, 否则CheckBox不能正常显示
                        hLayout->setAlignment(check[i-startNum], Qt::AlignCenter);   // 居中显示复选框
                        widget->setLayout(hLayout);
                        ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i-startNum , 0), widget);//widget放进tablewidget
                        //插入元素并居中
                    ui->tableWidget->setItem(i-startNum, 1, itemDeviceID);  ui->tableWidget->item(i-startNum, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 2, itemDeviceName);ui->tableWidget->item(i-startNum, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 3, itemDeviceAddr);ui->tableWidget->item(i-startNum, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 4, itemContent);ui->tableWidget->item(i-startNum, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 5, itemTime);ui->tableWidget->item(i-startNum, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                        //插入元素并居中
                        //删除栏打开时别的都设为不可选中
                    ui->tableWidget->item(i-startNum,1)->setFlags(Qt::ItemIsEnabled);
                    ui->tableWidget->item(i-startNum,2)->setFlags(Qt::ItemIsEnabled);
                    ui->tableWidget->item(i-startNum,3)->setFlags(Qt::ItemIsEnabled);
                    ui->tableWidget->item(i-startNum,4)->setFlags(Qt::ItemIsEnabled);
                    ui->tableWidget->item(i-startNum,5)->setFlags(Qt::ItemIsEnabled);
                        //删除栏打开时别的都设为不可选中
          //表格元素设置
                }
    }
    else{//收删除栏
        //*******************************该部分先计算chosen[]
        for(int i=0;i<m_pageCount;i++){
            if(check[i]->isChecked()){
                chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
            }
            else{
                 chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
            }
            }
        //*******************************该部分先计算chosen[]
        //下面的部分和setListWidget相同：
        int nowrows=ui->tableWidget->rowCount();
        int startNum = nowrows * (m_currentPageNum - 1);

     ui->tableWidget->clear();//表格清空
//表格尺寸设置
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setColumnWidth(0, 200);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2,  200);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);
//表格尺寸设置
        //表头设置
        QStringList headText;
        headText << "LinkId" << "Flag" << "branch" << "disclass" << "roadname";
        ui->tableWidget->setHorizontalHeaderLabels(headText);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setAlternatingRowColors(true);
        ui->tableWidget->verticalHeader()->setVisible(false);
        ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
         //表头设置
        ui->tableWidget->setRowCount(nowrows);//设置行数

        for (int i = startNum; i <std::min(nowrows+startNum,ls.length); i++)
        {
            ui->tableWidget->setRowHeight(i, 24);

            QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(ls.base[i]->LinkId));
            QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString::number(ls.base[i]->flag));
            QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(ls.base[i]->brunch));
            QTableWidgetItem *itemContent = new QTableWidgetItem(QString::number(ls.base[i]->disclass));
            QTableWidgetItem *itemTime = new QTableWidgetItem(QString (QString::fromLocal8Bit(ls.base[i]->roadname)));

            ui->tableWidget->setItem(i-startNum, 0, itemDeviceID);  ui->tableWidget->item(i-startNum, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i-startNum, 1, itemDeviceName);ui->tableWidget->item(i-startNum, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i-startNum, 2, itemDeviceAddr);ui->tableWidget->item(i-startNum, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i-startNum, 3, itemContent);ui->tableWidget->item(i-startNum, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->setItem(i-startNum, 4, itemTime);ui->tableWidget->item(i-startNum, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tableWidget->item(i-startNum,0)->setFlags(Qt::ItemIsEnabled);
        }
    }
}
void MainWindow::getItem()//辅助inputregex()并展示/收起删除列
{

    if(!ui->tableWidget->selectedItems().isEmpty()){//双击以后触发的该函数，判断是不是没有选中：如果选中的话，就进行信息修改
        connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));//打开inputregex()槽函数的信息接收功能
   focusedrow=ui->tableWidget->selectedItems()[0]->row();
    focusedcol=ui->tableWidget->selectedItems()[0]->column();
}
    else{change_del_col();//如果没有选中就弹出删除栏
        ui->tableWidget->disconnect(SIGNAL(currentCellChanged(int,int,int,int)));//把currentCellChanged(int,int,int,int)发射的信息阻滞住

    }
}
void MainWindow::inputregex(){//判断修改内容:
    if(focusedrow!=-1){ui->tableWidget->disconnect(SIGNAL(currentCellChanged(int,int,int,int)));
cout<<focusedrow<<" "<<focusedcol<<endl;
//***********************

//***********************
}
}
void MainWindow::delete_info_confirm(int col){//删除确信函数
    if(ui->tableWidget->columnCount()==6&&col==0){
        QStringList headText;
        if(ui->tableWidget->horizontalHeaderItem(0)->text().toStdString()=="sure?"){//确信删除
cout<<"already cleared"<<endl;
        }
        headText <<"sure?"<<"LinkId" << "Flag" << "branch" << "disclass" << "roadname";
        ui->tableWidget->setHorizontalHeaderLabels(headText);
    }
}
void MainWindow::change_to_head(){//跳到首页函数
    if(ui->tableWidget->columnCount()==6)//凡是翻页的函数都要重新统计删除栏的选择与否
        {for(int i=0;i<m_pageCount;i++){
        if(check[i]->isChecked()){
            chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
        }
        else{
             chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
        }
            }}
    setListWidget(1);
}
void MainWindow::change_to_tail(){//跳到尾页函数
    if(ui->tableWidget->columnCount()==6)//凡是翻页的函数都要重新统计删除栏的选择与否
        {for(int i=0;i<m_pageCount;i++){
        if(check[i]->isChecked()){
            chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
        }
        else{
             chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
        }
            }}
    setListWidget(m_countPageNum);
}
void MainWindow::change_to_page(){//跳到任意页的函数
    QRegExp rx("^[0-9]*[1-9][0-9]*$");//正则表达式判断是不是正整数
     if(rx.indexIn(ui->Page_info->text())==-1){//不是正整数
         ui->Page_info->setText(QString("illegal input"));
     }
     else if(ui->Page_info->text().toInt()> m_countPageNum){//超出页数范围
         ui->Page_info->setText(QString("page overflow"));
     }
     else{
         if(ui->tableWidget->columnCount()==6)//凡是翻页的函数都要重新统计删除栏的选择与否
             {for(int i=0;i<m_pageCount;i++){
             if(check[i]->isChecked()){
                 chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
             }
             else{
                  chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
             }
                 }}
         setListWidget(ui->Page_info->text().toInt());//调转
     }
}
