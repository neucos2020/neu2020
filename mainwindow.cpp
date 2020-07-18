#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qDebug>
#include<qcheckbox.h>
#include<iostream>
#include<string>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   m_pageCount =100;        //如果每页100条
    //默认第一页
    connect(ui->upPushButton, SIGNAL(clicked()), this, SLOT(upBtnClicked()));
    connect(ui->downPushButton, SIGNAL(clicked()), this, SLOT(downBtnClicked()));
    ui->cbox_Sort->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    ui->cbox_Sort->addItem(QString("-请选择-"));
ui->cbox_Sort->addItem(QString("选择排序"));
ui->cbox_Sort->addItem(QString("基数排序"));
ui->cbox_Sort->addItem(QString("堆排序"));
ui->cbox_Sort->addItem(QString("快速排序"));
ui->cbox_Sort->addItem(QString("插入排序"));
 connect(ui->cbox_Sort, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_method_selected()));
 ui->cbox_Sort_info->setSizeAdjustPolicy(QComboBox::AdjustToContents);
 ui->cbox_Sort_info->addItem(QString("-请选择-"));
ui->cbox_Sort_info->addItem(QString("LinkId"));
ui->cbox_Sort_info->addItem(QString("flag"));
ui->cbox_Sort_info->addItem(QString("branch"));
ui->cbox_Sort_info->addItem(QString("disclass"));
connect(ui->cbox_Sort_info, SIGNAL(currentIndexChanged(int)), this, SLOT(Sort_info_selected()));
ui->cbox_Find->setSizeAdjustPolicy(QComboBox::AdjustToContents);
ui->cbox_Find->addItem(QString("-请选择-"));
ui->cbox_Find->addItem(QString("-顺序查找-"));
ui->cbox_Find->addItem(QString("-折半查找-"));
ui->cbox_Find->addItem(QString("-分块查找-"));
connect(ui->cbox_Find, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_method()));
ui->cbox_Find_txt->setSizeAdjustPolicy(QComboBox::AdjustToContents);
ui->cbox_Find_txt->addItem(QString("-请选择-"));
ui->cbox_Find_txt->addItem(QString("LinkId"));
ui->cbox_Find_txt->addItem(QString("flag"));
ui->cbox_Find_txt->addItem(QString("branch"));
ui->cbox_Find_txt->addItem(QString("disclass"));
ui->cbox_Find_txt->addItem(QString("roadname"));
connect(ui->cbox_Find_txt, SIGNAL(currentIndexChanged(int)), this, SLOT(Find_info()));
connect(ui->Txt_find, SIGNAL(editingFinished()), this, SLOT(Find_txt()));
connect(ui->tableWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(getItem()));
connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));
connect(ui->tableWidget->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(delete_info_confirm(int)));
focusedrow=focusedcol=-1;//初始化
chosen=new bool[ls.length];
for(int i=0;i<ls.length;i++){
    chosen[i]=false;
}
 setListWidget(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setListWidget(const int &currentPage)
{
    if(currentPage <= 0){

        qDebug() << "Error: The currentPage can't be 0";
        return;
    }
    int startNum = m_pageCount * (currentPage - 1);

 ui->tableWidget->clear();

   /* for(int i = 0; i < m_pageCount; i++){
        if(startNum + i >= m_vec.size())
            break;
        ui->tabWidget->addItem(m_vec[startNum + i]);
    }
    m_currentPageNum = currentPage;
    m_countPageNum = m_vec.size() / m_pageCount + 1;
    ui->currentPageLabel->setText(QString::number(m_currentPageNum));
    ui->countPageLabel->setText(QString::number(m_countPageNum));*/
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, 200);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2,  200);
    ui->tableWidget->setColumnWidth(3, 200);
    ui->tableWidget->setColumnWidth(4, 200);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);
    check=new QCheckBox*[m_pageCount];//复选框集合
    for(int i=0;i<m_pageCount;i++){
    check[i]=new QCheckBox();
    }
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
    //设置行高
    ui->tableWidget->setRowCount(m_pageCount);

    for (int i = startNum; i <std::min(m_pageCount+startNum,ls.length); i++) {
        ui->tableWidget->setRowHeight(i, 24);

        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(ls.base[i]->LinkId));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString::number(ls.base[i]->flag));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(ls.base[i]->brunch));
        QTableWidgetItem *itemContent = new QTableWidgetItem(QString::number(ls.base[i]->disclass));
        QTableWidgetItem *itemTime = new QTableWidgetItem(QString (QString::fromLocal8Bit(ls.base[i]->roadname)));
check[i-startNum]->setChecked(Qt::Checked);
        ui->tableWidget->setItem(i-startNum, 0, itemDeviceID);  ui->tableWidget->item(i-startNum, 0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 1, itemDeviceName);ui->tableWidget->item(i-startNum, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 2, itemDeviceAddr);ui->tableWidget->item(i-startNum, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 3, itemContent);ui->tableWidget->item(i-startNum, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        ui->tableWidget->setItem(i-startNum, 4, itemTime);ui->tableWidget->item(i-startNum, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
ui->tableWidget->item(i-startNum,0)->setFlags(Qt::ItemIsEnabled);
    }

    //分页*****************************************
    m_currentPageNum = currentPage;
    m_countPageNum = ls.length / m_pageCount + 1;
    ui->currentPageLabel->setText(QString::number(m_currentPageNum));
    ui->countPageLabel->setText(QString::number(m_countPageNum));
     //分页*****************************************

}

void MainWindow::upBtnClicked()
{if(ui->tableWidget->columnCount()==6)
    {for(int i=0;i<m_pageCount;i++){
    if(check[i]->isChecked()){
        chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
    }
    else{
         chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
    }
        }}
   setListWidget(m_currentPageNum - 1);
}

void MainWindow::downBtnClicked()
{
    if(m_currentPageNum >= m_countPageNum)
        return;
    if(ui->tableWidget->columnCount()==6)
        {for(int i=0;i<m_pageCount;i++){
        if(check[i]->isChecked()){
            chosen[i+(m_currentPageNum-1)*m_pageCount]=true;
        }
        else{
             chosen[i+(m_currentPageNum-1)*m_pageCount]=false;
        }
            }}
    setListWidget(m_currentPageNum + 1);
}
void MainWindow::Sort_method_selected()
{
    //printf("%d\n",ui->cbox_Sort->currentIndex());
}
void MainWindow::Sort_info_selected()
{
    //printf("%d\n",ui->cbox_Sort_info->currentIndex());
}
void MainWindow::Find_method()
{

         //    printf("%d\n",ui->cbox_Find->currentIndex());
}
void MainWindow::Find_info()
{
       // printf("%d\n",ui->cbox_Find_txt->currentIndex());
}
void MainWindow::Find_txt()
{

string s=ui->Txt_find->text().toStdString();
cout<<s<<endl;
}
void MainWindow::change_del_col()
{
    if(ui->tableWidget->columnCount()==5){//展示删除栏
                int nowrows=ui->tableWidget->rowCount();
                int startNum = nowrows * (m_currentPageNum - 1);
int width=ui->tableWidget->width();
             ui->tableWidget->clear();
                ui->tableWidget->setColumnCount(6);
                ui->tableWidget->setColumnWidth(0, width/10);
                ui->tableWidget->setColumnWidth(1, width/6);
                ui->tableWidget->setColumnWidth(2, width/6);
                ui->tableWidget->setColumnWidth(3,  width/6);
                ui->tableWidget->setColumnWidth(4, width/6);
                ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

                QStringList headText;
                headText <<QString::fromLocal8Bit("delete")<< "LinkId" << "Flag" << "branch" << "disclass" << "roadname";
                ui->tableWidget->setHorizontalHeaderLabels(headText);
             //   ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
                  ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
                //ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
                ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
                ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
                ui->tableWidget->setAlternatingRowColors(true);
                ui->tableWidget->verticalHeader()->setVisible(false);
                ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

                //设置行高
                ui->tableWidget->setRowCount(nowrows);
                for (int i = startNum; i <std::min(nowrows+startNum,ls.length); i++)
                {
                    ui->tableWidget->setRowHeight(i, 24);
                    QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(ls.base[i]->LinkId));
                    QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString::number(ls.base[i]->flag));
                    QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(ls.base[i]->brunch));
                    QTableWidgetItem *itemContent = new QTableWidgetItem(QString::number(ls.base[i]->disclass));
                    QTableWidgetItem *itemTime = new QTableWidgetItem(QString (QString::fromLocal8Bit(ls.base[i]->roadname)));
                // QLabel *l1 = new QLabel();
                // l1->setPixmap(QPixmap("C://Users\\SUE\\Documents\\neu2020\\green_panel.jpg"));
                    QWidget *widget = new QWidget(ui->tableWidget);
                  //  printf("%d\n",i);
                     if(chosen[i])
                         check[i-startNum]->setCheckState(Qt::Checked);
                     else
                         check[i-startNum]->setCheckState(Qt::Unchecked);
                        QHBoxLayout *hLayout = new QHBoxLayout();
                        hLayout->addWidget(check[i-startNum]);
                        hLayout->setMargin(0);                              // 必须添加, 否则CheckBox不能正常显示
                        hLayout->setAlignment(check[i-startNum], Qt::AlignCenter);   // 居中显示复选框
                        widget->setLayout(hLayout);
                        ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(i-startNum , 0), widget);
                // l1->setAlignment(Qt::AlignHCenter);  ui->tableWidget->setCellWidget(i-startNum,0,l1);
                    ui->tableWidget->setItem(i-startNum, 1, itemDeviceID);  ui->tableWidget->item(i-startNum, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 2, itemDeviceName);ui->tableWidget->item(i-startNum, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 3, itemDeviceAddr);ui->tableWidget->item(i-startNum, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 4, itemContent);ui->tableWidget->item(i-startNum, 4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                    ui->tableWidget->setItem(i-startNum, 5, itemTime);ui->tableWidget->item(i-startNum, 5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            ui->tableWidget->item(i-startNum,1)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget->item(i-startNum,2)->setFlags(Qt::ItemIsEnabled);\
            ui->tableWidget->item(i-startNum,3)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget->item(i-startNum,4)->setFlags(Qt::ItemIsEnabled);
            ui->tableWidget->item(i-startNum,5)->setFlags(Qt::ItemIsEnabled);
          //  ui->tableWidget->item(i-startNum,0)->setFlags(Qt::ItemIsUserCheckable);
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
        int nowrows=ui->tableWidget->rowCount();
        int startNum = nowrows * (m_currentPageNum - 1);

     ui->tableWidget->clear();

       /* for(int i = 0; i < m_pageCount; i++){
            if(startNum + i >= m_vec.size())
                break;
            ui->tabWidget->addItem(m_vec[startNum + i]);
        }
        m_currentPageNum = currentPage;
        m_countPageNum = m_vec.size() / m_pageCount + 1;
        ui->currentPageLabel->setText(QString::number(m_currentPageNum));
        ui->countPageLabel->setText(QString::number(m_countPageNum));*/
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setColumnWidth(0, 200);
        ui->tableWidget->setColumnWidth(1, 200);
        ui->tableWidget->setColumnWidth(2,  200);
        ui->tableWidget->setColumnWidth(3, 200);
        ui->tableWidget->setColumnWidth(4, 200);
        ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

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

        //设置行高
        ui->tableWidget->setRowCount(nowrows);

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

    if(!ui->tableWidget->selectedItems().isEmpty()){connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));
   focusedrow=ui->tableWidget->selectedItems()[0]->row();
    focusedcol=ui->tableWidget->selectedItems()[0]->column();
}
    else{change_del_col();
        ui->tableWidget->disconnect(SIGNAL(currentCellChanged(int,int,int,int)));

    }
}
void MainWindow::inputregex(){//判断修改内容
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


