#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qDebug>
#include<qcheckbox.h>
#include<iostream>
#include<string>
#include<string.h>
#include<QMessageBox>
#include<QTextCodec>
#include<QDialog>
using namespace std;
MainWindow::MainWindow(QWidget *parent) ://主窗口的构造函数
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);//动作：建立Mainwindow.ui的界面
   //************连接信息与槽***************
    //*******************************连接槽函数：算法分析
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)),this, SLOT(slotOpen(QTreeWidgetItem*,int)));
    //*******************************连接槽函数：算法分析
    connect(ui->upPushButton, SIGNAL(clicked()), this, SLOT(upBtnClicked()));//上一页的触发函数
    connect(ui->downPushButton, SIGNAL(clicked()), this, SLOT(downBtnClicked()));//下一页的触发函数
    connect(ui->btn_head, SIGNAL(clicked()), this, SLOT(change_to_head()));//跳到首页的触发函数
    connect(ui->btn_tail, SIGNAL(clicked()), this, SLOT(change_to_tail()));//跳到尾页的触发函数
    connect(ui->Page_info,SIGNAL(returnPressed()), this, SLOT(change_to_page()));//跳到任意页的触发函数
    connect(ui->cbox_Sort, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_method_selected()));//排序方法选择框触发函数
    connect(ui->cbox_Sort_info, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_info_selected()));//排序指标选择框触发函数
    connect(ui->cbox_Find, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_method()));//查找方法选择框触发函数
    connect(ui->cbox_Find_txt, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_info()));//查找指标选择框触发函数
    connect(ui->Txt_find, SIGNAL(returnPressed()), this, SLOT(Find_txt()));//查找字段文本框触发函数
    connect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem()));//表格双击触发函数:记录所点击的行与列
    connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));//表格信息被修改时的触发函数：这里的修改不一定改变其内容，指的是从点进去的状态中出来
    connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(delete_info_confirm(int)));//点击表头的触发函数
    connect(ui->action,&QAction::triggered, this,MainWindow::refresh_data);//菜单栏文件：重新导入数据
    connect(ui->action_O,&QAction::triggered,this,MainWindow::delete_selected);//菜单栏文件：删除已经选择的条目
      connect(ui->action_X,&QAction::triggered,this,MainWindow::addtabitems);//菜单栏文件：增添条目
       connect(ui->action_S,&QAction::triggered,this,MainWindow::outputdata);//菜单栏文件：导出数据
        connect(ui->action_C,&QAction::triggered,this,MainWindow::deleteandfree);//菜单栏文件：导出数据

    //************连接信息与槽***************
    //所有选择框(Combobox)初始化
    ui->cbox_Sort->setSizeAdjustPolicy(QComboBox::AdjustToContents);//根据页面的大小自适应调整选择框尺寸
//***********************************************
    ui->cbox_Sort->addItem(QString("-请选择-"));
    ui->cbox_Sort->addItem(QString("选择排序"));
    ui->cbox_Sort->addItem(QString("冒泡排序"));
    ui->cbox_Sort->addItem(QString("堆排序"));
    ui->cbox_Sort->addItem(QString("快速排序"));
    ui->cbox_Sort->addItem(QString("希尔排序"));
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
    ui->cbox_Find->addItem(QString("-二分查找-"));
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
    ls.origin_length=ls.length;//这个变量用于对所有的数据进行排序或查找的时候重置ls.length
focusedrow=focusedcol=-1;//初始化
 //部分成员变量初始化
 setListWidget(1);//显示初始的表格
ui->textEdit->setFocusPolicy(Qt::NoFocus);
ui->textEdit->setStyleSheet("background-color:rgb(83,168,255);padding:0px;border:0px");
ui->treeWidget->setStyleSheet("background-color:rgb(83,168,255);");
ui->textEdit->setHtml("<html><body><h1 align='center'>算法综述</h1><h2>&nbsp;&nbsp;该部分介绍了5种排序算法的时空复杂度和3种查找算法的查找成功或失败的ASL"
                      "</h2></body></html>");
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
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setStyleSheet("selection-background-color:gold;");
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
{check_close_delcol();//如过当前的删除栏开着的话要统计并修改选中对象chosen[]
   setListWidget(m_currentPageNum - 1);//设置表格
}

void MainWindow::downBtnClicked()//向下一页触发函数
{
    if(m_currentPageNum >= m_countPageNum)//如果超出了总页数不可翻页
        return;
check_close_delcol();
    setListWidget(m_currentPageNum + 1);//设置表格
}
void MainWindow::Sort_method_selected()//这和下面的函数是一样的效果
{
    int i;
        int p=ui->cbox_Sort->currentIndex();
        int q=ui->cbox_Sort_info->currentIndex();
        if(p>0&&q>0){ qDebug()<<p<<q;
            //*******************************************
check_close_delcol();
            //*******************************************
          ls.heapSort(ls.base,ls.length,-5);//选人
           for(i=0;i<ls.length;i++){
               if(!ls.base[i]->selected){break;}
           }
           if(i!=0){
               ls.length=i;
           }

           switch(p){
           case 1:cout<<"初级排序可能比较慢"<<endl;ls.selectionSort(ls.base,ls.length,q);break;
           case 2:cout<<"初级排序可能比较慢"<<endl;ls.bubbleSort(ls.base,ls.length,q);break;
           case 3:ls.heapSort(ls.base,ls.length,q);break;
           case 4:ls.QuickSort(ls.base,0,ls.length-1,q);break;
           case 5:ls.shellsort(ls.base,ls.length,q);break;
           }
         setListWidget(1);
        }
}
void MainWindow::Sort_info_selected()
{
    Sort_method_selected();
}
void MainWindow::Find_method()
{
int i;
      int p=ui->cbox_Find->currentIndex();
      int q=ui->cbox_Find_txt->currentIndex();
      if(!ui->Txt_find->text().isEmpty()){
      QByteArray cpath = ui->Txt_find->text().toLocal8Bit();
      if(p>0&&q>0){
             switch(p)
             {
             case 1:
                 cout<<"yep"<<endl;
                 ls.Search(ls.base,ls.length,q,cpath.toStdString());break;

             case 2:
                 cout<<"yehhhhh"<<endl;
                 ls.Bsearch(ls.base,0,ls.length,q,cpath.toStdString());
                 break;
             case 3:ls.blocksearch(ls.base,ls.length,q,cpath.toStdString());
                 //ui->cbox_Find->removeItem(3);
                 break;

             }
             ls.heapSort(ls.base,ls.length,-5);
             for(i=0;i<ls.length;i++){
                 if(!ls.base[i]->selected){
                     break;
                 }
             }
             ls.length=i;
             }
           setListWidget(1);
      }
}
void MainWindow::Find_info()
{
    Find_method();
}
void MainWindow::Find_txt()
{
    Find_method();
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
                headText <<"全选"<< "LinkId" << "Flag" << "branch" << "disclass" << "roadname";
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
                     if(ls.base[i]->selected)//改变复选框状态：已经选过的就标选过
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
        for(int i=0;i<min(m_pageCount,ls.length-(m_currentPageNum-1)*m_pageCount);i++)
        {
            if(check[i]->isChecked()){
              //  chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
                   ls.base[i+(m_currentPageNum-1)*m_pageCount]->selected=true;
            }
            else{
                // chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
                    ls.base[i+(m_currentPageNum-1)*m_pageCount]->selected=false;
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
//***********************
QRegExp rx("^[0-9]*[1-9][0-9]*$");//正则表达式判断是不是正整数
if(rx.indexIn(ui->tableWidget->item(focusedrow,focusedcol)->text())==-1&&focusedcol<4){//不是正整数
    ui->Page_info->setText(QString("illegal input"));
}
else{//修改lms.ls
   if(focusedcol<4){
       //ls.base[focusedrow+(m_currentPageNum-1)*m_pageCount]
       switch(focusedcol){
       case 1:ls.base[focusedrow+(m_currentPageNum-1)*m_pageCount]->flag=ui->tableWidget->item(focusedrow,focusedcol)->text().toInt();break;
        case 2:ls.base[focusedrow+(m_currentPageNum-1)*m_pageCount]->brunch=ui->tableWidget->item(focusedrow,focusedcol)->text().toInt();break;
       case 3:ls.base[focusedrow+(m_currentPageNum-1)*m_pageCount]->disclass=ui->tableWidget->item(focusedrow,focusedcol)->text().toInt();break;
       }
   }
   else{QByteArray cpath = ui->tableWidget->item(focusedrow,focusedcol)->text().toLocal8Bit();char *p = cpath.data();//解决QString转char*中文乱码
        strcpy(ls.base[focusedrow+(m_currentPageNum-1)*m_pageCount]->roadname,p);
   }
}
//***********************
}
}
void MainWindow::delete_info_confirm(int col){//删除全选函数
  int i;
    if(ui->tableWidget->columnCount()==6&&col==0){
        for(i=0;i<m_pageCount;i++){
            if(!check[i]->isChecked()){
                break;
            }
        }
        if(i!=m_pageCount){
            for(i=0;i<m_pageCount;i++){
                check[i]->setChecked(true);
            }
        }
        else{
            for(i=0;i<m_pageCount;i++){
                check[i]->setChecked(false);
            }
        }
    }
    else if(ui->tableWidget->columnCount()==5){
        lms::LM temp;
        for(i=0;i<ls.length/2;i++){
            temp=ls.base[i];
            ls.base[i]=ls.base[ls.length-1-i];
            ls.base[ls.length-1-i]=temp;
        }
       setListWidget(1);
    }
}
void MainWindow::refresh_data(){
    qDebug()<<ls.length<<ls.origin_length;
    for(int i=0;i<ls.length;i++)
        ls.base[i]->selected=false;
    ls.length=ls.origin_length;
    setListWidget(1);
    QMessageBox::information(this, tr("状态"), tr("数据已成功还原"));
}
void MainWindow::change_to_head(){//跳到首页函数
check_close_delcol();
    setListWidget(1);
}
void MainWindow::delete_selected(){
    int i;
    //*******************************该部分先计算chosen[]
check_close_delcol();
    //*******************************该部分先计算chosen[]
    QMessageBox:: StandardButton result= QMessageBox::question(NULL, "状态", "确认删除已选择的项目?",QMessageBox::Yes|QMessageBox::No);
   if(result==QMessageBox::Yes){
ls.heapSort(ls.base,ls.length,5);//把选中的元素放到最后
for(i=0;i<ls.length;i++){
if(ls.base[i]->selected){
    break;
}
}
if(i==ls.length){
    QMessageBox::warning(NULL, "状态", "请选择删除的元素!");
}
else{
    ls.length=i;
setListWidget(1);
 QMessageBox::information(NULL, "状态", "删除成功!");
}
   }
   else{
       cout<<"no"<<endl;
   }
}
void MainWindow::change_to_tail(){//跳到尾页函数
check_close_delcol();
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
check_close_delcol();
         setListWidget(ui->Page_info->text().toInt());//调转
     }
}
void MainWindow::check_close_delcol(){
    //*******************************该部分先计算chosen[]
    if(ui->tableWidget->columnCount()==6){
    for(int i=0;i<min(m_pageCount,ls.length-(m_currentPageNum-1)*m_pageCount);i++)
    {
        if(check[i]->isChecked()){
          //  chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
               ls.base[i+(m_currentPageNum-1)*m_pageCount]->selected=true;
        }
        else{
            // chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
                ls.base[i+(m_currentPageNum-1)*m_pageCount]->selected=false;
        }
        }
    }
    //*******************************该部分先计算chosen[]
}
void MainWindow::save_insert(){
    int i=0;int rows=ui->tableWidget->rowCount();

    while(i<rows-1){
        for(int j=0;j<4;j++){
        if(ui->tableWidget->item(i,j)->background()==QColor("red")||ui->tableWidget->item(i,j)->text()==QString("")){
          QMessageBox::critical(NULL, "错误", QString("标红位置数据错误"),
                                QMessageBox::Yes);
          return;
        }
        }
        i++;
    }
    QMessageBox:: StandardButton result= QMessageBox::question(NULL, "状态", "确认添加这些信息吗?",QMessageBox::Yes|QMessageBox::No);
   if(result==QMessageBox::Yes){
    for(int j=0;j<rows-1;j++){//******************************************************修改lms.ls
        QByteArray cpath = ui->tableWidget->item(j,4)->text().toLocal8Bit();char *p = cpath.data();//解决QString转char*中文乱码
      insert_item(ui->tableWidget->item(j,0)->text().toInt(),ui->tableWidget->item(j,1)->text().toInt(),
                  ui->tableWidget->item(j,2)->text().toInt(),ui->tableWidget->item(j,3)->text().toInt(),
                  p);
    }//*******************************************************修改lms.ls
    disconnect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(addrows(int,int,int,int)));//取消增行器
      disconnect(ui->action_C_2,&QAction::triggered,this,MainWindow::save_insert);//菜单栏文件：确认添加:关闭其效果
      connect(ui->upPushButton, SIGNAL(clicked()), this, SLOT(upBtnClicked()));//上一页的触发函数
      connect(ui->downPushButton, SIGNAL(clicked()), this, SLOT(downBtnClicked()));//下一页的触发函数
     connect(ui->btn_head, SIGNAL(clicked()), this, SLOT(change_to_head()));//跳到首页的触发函数
     connect(ui->btn_tail, SIGNAL(clicked()), this, SLOT(change_to_tail()));//跳到尾页的触发函数
      connect(ui->Page_info,SIGNAL(returnPressed()), this, SLOT(change_to_page()));//跳到任意页的触发函数
    connect(ui->cbox_Sort, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_method_selected()));//排序方法选择框触发函数
      connect(ui->cbox_Sort_info, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_info_selected()));//排序指标选择框触发函数
     connect(ui->cbox_Find, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_method()));//查找方法选择框触发函数
     connect(ui->cbox_Find_txt, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_info()));//查找指标选择框触发函数
      connect(ui->Txt_find, SIGNAL(returnPressed()), this, SLOT(Find_txt()));//查找字段文本框触发函数
     connect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem()));//表格双击触发函数:记录所点击的行与列
      connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));//表格信息被修改时的触发函数：这里的修改不一定改变其内容，指的是从点进去的状态中出来
      connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(delete_info_confirm(int)));//点击表头的触发函数
     //disconnect(ui->action,&QAction::triggered, this,MainWindow::refresh_data);//菜单栏文件：重新导入数据
      connect(ui->action_O,&QAction::triggered,this,MainWindow::delete_selected);//菜单栏文件：删除已经选择的条目
        connect(ui->action_X,&QAction::triggered,this,MainWindow::addtabitems);//菜单栏文件：增添条目
         connect(ui->action_S,&QAction::triggered,this,MainWindow::outputdata);//菜单栏文件：导出数据
          connect(ui->action_C,&QAction::triggered,this,MainWindow::deleteandfree);//菜单栏文件：导出数据
          connect(ui->action,&QAction::triggered, this,MainWindow::refresh_data);//菜单栏文件：重新导入数据
setListWidget(1);
   }
else{
        QMessageBox:: StandardButton re= QMessageBox::question(NULL, "状态", "那选择重置表格吗?",QMessageBox::Yes|QMessageBox::No);
        if(re==QMessageBox::Yes){//重置添加表格
            disconnect(ui->action_C_2,&QAction::triggered,this,MainWindow::save_insert);//菜单栏文件：确认添加:防止重复调用
addtabitems();
        }
   }
}
void MainWindow::addrows(int x1,int x2,int x3,int x4){//x1,x2是当前focus,x3,x4是之前focus
  QRegExp rx("^[1-9]\d*|0$");//正则表达式判断是不是非负整数
  qDebug()<<x1<<x2<<x3<<x4;
if(x3>=0&&x4>=0){
    QTableWidgetItem*item=ui->tableWidget->item(x3,x4);
    switch(x4){
    case 0:
        if(rx.indexIn(item->text())==-1||item->text().toInt()<0){//匹配不是非负整数
           item->setBackgroundColor(QColor("red"));
        }
        else {
            int msg=item->text().toInt();
            int i;
            int row=ui->tableWidget->rowCount();
            for(i=0;i<row;i++){
                if(i!=x3){
                 if(ui->tableWidget->item(i,0)->text().toInt()==msg){
                     break;
                 }
                }
            }
            if(i!=row){
                 item->setBackgroundColor(QColor("red"));
            }
            else{
                for(i=0;i<ls.length;i++){
                    if(msg==ls.base[i]->LinkId){
                        break;
                    }
                }
                if(i==ls.length){
                     item->setBackgroundColor(QColor("white"));
                }
                else{
                      item->setBackgroundColor(QColor("red"));
                }
            }
        }
        break;//主码列，需要判断唯一性
    case 1:
    case 2:
    case 3:
        if(rx.indexIn(item->text())==-1||item->text().toInt()<0){//匹配不是正整数
              item->setBackgroundColor(QColor("red"));
        }
        else{
              item->setBackgroundColor(QColor("white"));
        }
        break;
    case 4:qDebug()<<"成功输入一组路名";break;//非数字列，可空
    }
    if(ui->tableWidget->item(x3,0)->background()==QColor("red")||ui->tableWidget->item(x3,1)->background()==QColor("red")
            ||ui->tableWidget->item(x3,2)->background()==QColor("red")||ui->tableWidget->item(x3,3)->background()==QColor("red")){
        qDebug()<<"存在错误改行";
    }
    else if((x3==ui->tableWidget->rowCount()-1)&&
            ui->tableWidget->item(x3,0)->text()!=QString("")
            && ui->tableWidget->item(x3,1)->text()!=QString("")
            && ui->tableWidget->item(x3,2)->text()!=QString("")
            && ui->tableWidget->item(x3,3)->text()!=QString("")){//扩行
        ui->tableWidget->insertRow(x3+1);
        QTableWidgetItem *ans1 = new QTableWidgetItem(QString(""));
        QTableWidgetItem *ans2 = new QTableWidgetItem(QString(""));
        QTableWidgetItem *ans3 = new QTableWidgetItem(QString(""));
        QTableWidgetItem *ans4 = new QTableWidgetItem(QString(""));
        QTableWidgetItem *ans5 = new QTableWidgetItem(QString(""));
          ui->tableWidget->setItem(x3+1, 0, ans1);ui->tableWidget->setItem(x3+1, 1, ans2);ui->tableWidget->setItem(x3+1,2, ans3);
          ui->tableWidget->setItem(x3+1, 3, ans4);ui->tableWidget->setItem(x3+1,4, ans5);
    }
}
}
void MainWindow::addtabitems(){
    /*

    */
        //切断所有信号槽
    disconnect(ui->upPushButton, SIGNAL(clicked()), this, SLOT(upBtnClicked()));//上一页的触发函数
    disconnect(ui->downPushButton, SIGNAL(clicked()), this, SLOT(downBtnClicked()));//下一页的触发函数
    disconnect(ui->btn_head, SIGNAL(clicked()), this, SLOT(change_to_head()));//跳到首页的触发函数
    disconnect(ui->btn_tail, SIGNAL(clicked()), this, SLOT(change_to_tail()));//跳到尾页的触发函数
    disconnect(ui->Page_info,SIGNAL(returnPressed()), this, SLOT(change_to_page()));//跳到任意页的触发函数
    disconnect(ui->cbox_Sort, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_method_selected()));//排序方法选择框触发函数
    disconnect(ui->cbox_Sort_info, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_info_selected()));//排序指标选择框触发函数
    disconnect(ui->cbox_Find, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_method()));//查找方法选择框触发函数
    disconnect(ui->cbox_Find_txt, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_info()));//查找指标选择框触发函数
    disconnect(ui->Txt_find, SIGNAL(returnPressed()), this, SLOT(Find_txt()));//查找字段文本框触发函数
    disconnect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem()));//表格双击触发函数:记录所点击的行与列
    disconnect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));//表格信息被修改时的触发函数：这里的修改不一定改变其内容，指的是从点进去的状态中出来
    disconnect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(delete_info_confirm(int)));//点击表头的触发函数
   //disconnect(ui->action,&QAction::triggered, this,MainWindow::refresh_data);//菜单栏文件：重新导入数据
    disconnect(ui->action_O,&QAction::triggered,this,MainWindow::delete_selected);//菜单栏文件：删除已经选择的条目
      disconnect(ui->action_X,&QAction::triggered,this,MainWindow::addtabitems);//菜单栏文件：增添条目
       disconnect(ui->action_S,&QAction::triggered,this,MainWindow::outputdata);//菜单栏文件：导出数据
        disconnect(ui->action_C,&QAction::triggered,this,MainWindow::deleteandfree);//菜单栏文件：导出数据
        disconnect(ui->action,&QAction::triggered, this,MainWindow::refresh_data);//菜单栏文件：重新导入数据
                   //切断所有信号槽
                 ui->Txt_find->setText(QString("添加状态!"));
                 ui->tableWidget->clear();
                 ui->tableWidget->setColumnCount(5);//设置列数
                 //设置列宽
                 ui->tableWidget->setColumnWidth(0, 200);
                 ui->tableWidget->setColumnWidth(1, 200);
                 ui->tableWidget->setColumnWidth(2,  200);
                 ui->tableWidget->setColumnWidth(3, 200);
                 ui->tableWidget->setColumnWidth(4, 200);
                 //设置列宽
                 ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);
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
                 ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色
                 ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
                 ui->tableWidget->setRowCount(1);//表格先置一行，写完一行以后再出现一行
                 QTableWidgetItem *ans1 = new QTableWidgetItem(QString(""));
                 QTableWidgetItem *ans2 = new QTableWidgetItem(QString(""));
                 QTableWidgetItem *ans3 = new QTableWidgetItem(QString(""));
                 QTableWidgetItem *ans4 = new QTableWidgetItem(QString(""));
                 QTableWidgetItem *ans5 = new QTableWidgetItem(QString(""));
                   ui->tableWidget->setItem(0, 0, ans1);ui->tableWidget->setItem(0, 1, ans2);ui->tableWidget->setItem(0,2, ans3);
                   ui->tableWidget->setItem(0, 3, ans4);ui->tableWidget->setItem(0,4, ans5);
                 //表格诸参数设置
                 connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(addrows(int,int,int,int)));//增行器
                    connect(ui->action_C_2,&QAction::triggered,this,MainWindow::save_insert);//菜单栏文件：确认添加

}
void MainWindow::insert_item(int id,int flag,int br,int dis,char road[]){

    if(ls.length==ls.origin_length){
        ls.base=(lms::LM*)realloc(ls.base,(ls.length+1)*sizeof(lms::LM));
        ls.base[ls.length]=(lms::LM)malloc(sizeof(lms::LandMark));
        ls.base[ls.length]->LinkId=id;
        ls.base[ls.length]->flag=flag;
        ls.base[ls.length]->brunch=br;
        ls.base[ls.length]->disclass=dis;
        ls.base[ls.length]->selected=false;
        ls.base[ls.length]->roadname=(char*)malloc(sizeof(char)*30);
        strcpy(ls.base[ls.length]->roadname,road);
        ls.origin_length++;ls.length++;
    }
    else{
        ls.base[ls.length]->LinkId=id;
        ls.base[ls.length]->flag=flag;
        ls.base[ls.length]->brunch=br;
        ls.base[ls.length]->disclass=dis;
        ls.base[ls.length]->selected=false;
        memset(ls.base[ls.length]->roadname,'\0',sizeof(ls.base[ls.length]->roadname));
        strcpy(ls.base[ls.length++]->roadname,road);
    }
}
void MainWindow::slotOpen(QTreeWidgetItem* p,int q){
   QString* sort=new QString("<html><body>"
                            "<h2 align='center'>排序的基本概念</h2><h3>1. 内排序：<br/>&nbsp;&nbsp;在排序的整个过程中，待排序的所有记录全部被放置在内存中"
                            "<br/>2. 外排序：<br/>&nbsp;&nbsp;由于待排序的记录个数太多，不能同时放置在内存，而需要将一部分记录放置在内存，<br/>"
                            "另一部分记录放置在外存上，<br/>"
                            "整个排序过程需要在内外存之间多次交换数据才能得到排序的结果。</h3></body></html>");
//ui->textEdit->setHtml(*sort);
QString *find=new QString("<html><body>"
                          "<h2 align='center'>查找的基本概念</h2><h3>查找 ：<br/>&nbsp;&nbsp;在具有相同类型的记录构成的集合中找出满足给定条件的记录。<br/>查找的结果 ："
                          "<br/>&nbsp;&nbsp;若在查找集合中找到了与给定值相匹配的记录，则称查找成功；否则，称查找失败。</h3></body></html>");
QString* select=new QString("<html><body>"
                         "<h2 align='center'>选择排序</h2><h3>&nbsp;&nbsp;选择排序（Selection sort）是一种简单直观的排序算法。它的工作原理是："
                            "第一次从待排序的数据元素中选出最小（或最大）的一个元素，存放在序列的起始位置，然后再从剩余的未排序元素中寻找到最小（大）元素，"
                            "然后放到已排序的序列的末尾。以此类推，直到全部待排序的数据元素的个数为零。选择排序是不稳定的排序方法。"
                         "整个排序过程需要在内外存之间多次交换数据才能得到排序的结果。</h3></body></html>");
QString*bubble=new QString("<html><body>"
                          "<h2 align='center'>冒泡排序</h2><h3>&nbsp;&nbsp;冒泡排序（Bubble Sort），是一种计算机科学领域的较简单的排序算法，"
                          "它重复地走访过要排序的元素列，依次比较两个相邻的元素，如果顺序（如从大到小、首字母从Z到A）错误就把他们交换过来。走访元素的工作是重复地进行直到没有相邻元素需要交换，也就是说该元素列已经排序完成。"
                          "这个算法的名字由来是因为越小的元素会经由交换慢慢“浮”到数列的顶端（升序或降序排列），就如同碳酸饮料中二氧化碳的气泡最终会上浮到顶端一样，故名“冒泡排序”。</h3></body></html>");
QString*quick=new QString("<html><body>"
                          "<h2 align='center'>快速排序</h2><h3>&nbsp;&nbsp;快速排序（Quicksort）是对冒泡排序的一种改进。"
                          "快速排序由C. A. R. Hoare在1960年提出。它的基本思想是：通过一趟排序将要排序的数据分割成独立的两部分，"
                          "其中一部分的所有数据都比另外一部分的所有数据都要小，然后再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列</h3></body></html>");
QString*heap=new QString("<html><body>"
                                         "<h2 align='center'>堆排序</h2><h3>&nbsp;&nbsp;堆排序（英语：Heapsort）是指利用堆这种数据结构所设计的一种排序算法。"
                          "堆是一个近似完全二叉树的结构，并同时满足堆积的性质：即子结点的键值或索引总是小于（或者大于）它的父节点。</h3></body></html>");
QString*shell=new QString("<html><body>"
                          "<h2 align='center'>希尔排序</h2><h3>&nbsp;&nbsp;希尔排序(Shell's Sort)是插入排序的一种又称“缩小增量排序”（Diminishing Increment Sort），"
                          "是直接插入排序算法的一种更高效的改进版本。希尔排序是非稳定排序算法。该方法因D.L.Shell于1959年提出而得名。"
                          "希尔排序是把记录按下标的一定增量分组，对每组使用直接插入排序算法排序；随着增量逐渐减少，每组包含的关键词越来越多，当增量减至1时，整个文件恰被分成一组，算法便终止。</h3></body></html>");
QString*search=new QString("<html><body>"
                           "<h2 align='center'>顺序查找</h2><h3>&nbsp;&nbsp;顺序查找是按照序列原有顺序对数组进行遍历比较查询的基本查找算法。</h3></body></html>");
QString*Bsearch=new QString("<html><body>"
                            "<h2 align='center'>折半查找</h2><h3>&nbsp;&nbsp;二分查找也称折半查找（Binary Search），它是一种效率较高的查找方法"
                            "。但是，折半查找要求线性表必须采用顺序存储结构，而且表中元素按关键字有序排列。</h3></body></html>");
QString*block=new QString("<html><body>"
                                        "<h2 align='center'>分块查找</h2><h3>&nbsp;&nbsp;分块查找是折半查找和顺序查找的一种改进方法，"
                          "分块查找由于只要求索引表是有序的，对块内节点没有排序要求，因此特别适合于节点动态变化的情况。</h3></body></html>");
ui->textEdit->setHtml(*quick);
if(p->text(0)==QString("查找")){
    // setGraphScene("./debug/images/heapsort.png");
    ui->textEdit->setHtml(*find);
}
else if(p->text(0)==QString("排序")){
     setGraphScene("./debug/images/sorttimeroom.png");
    ui->textEdit->setHtml(*sort);
}
else if(p->text(0)==QString("选择排序")){
   setGraphScene("./debug/images/selectsort.png");
     ui->textEdit->setHtml(*select);
}
else if(p->text(0)==QString("冒泡排序")){
    setGraphScene("./debug/images/bubblesort.png");
     ui->textEdit->setHtml(*bubble);
}
else if(p->text(0)==QString("快速排序")){
    setGraphScene("./debug/images/quicksort.png");
     ui->textEdit->setHtml(*quick);
}
else if(p->text(0)==QString("堆排序")){
     setGraphScene("./debug/images/heapsort.png");
     ui->textEdit->setHtml(*heap);
}
else if(p->text(0)==QString("希尔排序")){
     setGraphScene("./debug/images/shellsort.png");
     ui->textEdit->setHtml(*shell);
}
else if(p->text(0)==QString("顺序查找")){
      setGraphScene("./debug/images/search.png");
     ui->textEdit->setHtml(*search);
}
else if(p->text(0)==QString("二分查找")){
 setGraphScene("./debug/images/binary.png");
     ui->textEdit->setHtml(*Bsearch);
}
else if(p->text(0)==QString("分块查找")){
     setGraphScene("./debug/images/blocksearch.png");
     ui->textEdit->setHtml(*block);
}
}
void MainWindow::setGraphScene(char path[]){
     QGraphicsScene* originalScene =new QGraphicsScene(this);
     ui->graphicsView_2->setScene(originalScene);
     QPixmap* pix=new QPixmap(path);
     originalScene->addPixmap(*pix);
}
void MainWindow::outputdata(){
    ls.imwrite(ls,"./debug/file.dat");//输出到源文件
    QMessageBox::information(this, tr("状态"), tr("数据已成功导出"));  
}
void MainWindow::deleteandfree(){
    QMessageBox:: StandardButton result= QMessageBox::question(NULL, "状态", "确认删除彻底删除吗?",QMessageBox::Yes|QMessageBox::No);
   if(result==QMessageBox::Yes){
ls.heapSort(ls.base,ls.origin_length,5);
ls.base=(lms::LM*)realloc(ls.base,(ls.length)*sizeof(lms::LM));
ls.origin_length=ls.length;
QMessageBox::information(this, tr("状态"), tr("数据已成功删除"));
setListWidget(1);
}
}
