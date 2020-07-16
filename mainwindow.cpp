#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<qDebug>
#include<iostream>
#include<string>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pageCount =100;        //如果每页52条
 setListWidget(1);
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
focusedrow=focusedcol=-1;//初始化
lms ls;
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
{
   setListWidget(m_currentPageNum - 1);
}

void MainWindow::downBtnClicked()
{
    if(m_currentPageNum >= m_countPageNum)
        return;

    setListWidget(m_currentPageNum + 1);
}
void MainWindow::Sort_method_selected()
{
    //printf("%d\n",ui->cbox_Sort->currentIndex());
}
void MainWindow::Sort_info_selected(){
    //printf("%d\n",ui->cbox_Sort_info->currentIndex());
}
void MainWindow::Find_method(){

         //    printf("%d\n",ui->cbox_Find->currentIndex());
}
void MainWindow::Find_info()
{
       // printf("%d\n",ui->cbox_Find_txt->currentIndex());
}
void MainWindow::Find_txt(){

string s=ui->Txt_find->text().toStdString();
cout<<s<<endl;
}
void MainWindow::getItem(){
    connect(ui->tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(inputregex()));
    if(!ui->tableWidget->selectedItems().isEmpty()){
   focusedrow=ui->tableWidget->selectedItems()[0]->row();
    focusedcol=ui->tableWidget->selectedItems()[0]->column();
}
    else{
        ui->tableWidget->disconnect(SIGNAL(currentCellChanged(int,int,int,int)));
    }
}
void MainWindow::inputregex(){
    if(focusedrow!=-1){
ui->tableWidget->disconnect(SIGNAL(currentCellChanged(int,int,int,int)));
cout<<focusedrow<<" "<<focusedcol<<endl;
//***********************

//***********************
}
}

