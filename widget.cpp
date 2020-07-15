#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) ://这个函数用来初始化数据，也就是导入数据
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("爸爸的增删改查系统");
    m_pageCount = 52;        //如果每页52条
 setListWidget(1);
    //默认第一页

    connect(ui->upPushButton, SIGNAL(clicked()), this, SLOT(upBtnClicked()));
    connect(ui->downPushButton, SIGNAL(clicked()), this, SLOT(downBtnClicked()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setListWidget(const int &currentPage)
{
    if(currentPage <= 0){

        qDebug() << "Error: The currentPage can't be 0";
        return;
    }
    int startNum = m_pageCount * (currentPage - 1);

    ui->tabWidget->clear();

   /* for(int i = 0; i < m_pageCount; i++){

        if(startNum + i >= m_vec.size())
            break;

        ui->tabWidget->addItem(m_vec[startNum + i]);
    }

    m_currentPageNum = currentPage;
    m_countPageNum = m_vec.size() / m_pageCount + 1;
    ui->currentPageLabel->setText(QString::number(m_currentPageNum));
    ui->countPageLabel->setText(QString::number(m_countPageNum));*/
    ui->tabWidget->setColumnCount(5);
    ui->tabWidget->setColumnWidth(0, 200);
    ui->tabWidget->setColumnWidth(1, 200);
    ui->tabWidget->setColumnWidth(2,  200);
    ui->tabWidget->setColumnWidth(3, 200);
    ui->tabWidget->setColumnWidth(4, 200);
    ui->tabWidget->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "LinkId" << "Flag" << "branch" << "disclass" << "roadname";
    ui->tabWidget->setHorizontalHeaderLabels(headText);
    ui->tabWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tabWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tabWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tabWidget->setAlternatingRowColors(true);
    ui->tabWidget->verticalHeader()->setVisible(false);
    ui->tabWidget->horizontalHeader()->setStretchLastSection(true);

    //设置行高
    ui->tabWidget->setRowCount(m_pageCount);

    for (int i = startNum; i <std::min(m_pageCount+startNum,300); i++) {
        ui->tabWidget->setRowHeight(i, 24);

        QTableWidgetItem *itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemDeviceName = new QTableWidgetItem(QString("测试设备%1").arg(i + 1));
        QTableWidgetItem *itemDeviceAddr = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *itemContent = new QTableWidgetItem("防区告警");
        QTableWidgetItem *itemTime = new QTableWidgetItem("?");

        ui->tabWidget->setItem(i-startNum, 0, itemDeviceID);
        ui->tabWidget->setItem(i-startNum, 1, itemDeviceName);
        ui->tabWidget->setItem(i-startNum, 2, itemDeviceAddr);
        ui->tabWidget->setItem(i-startNum, 3, itemContent);
        ui->tabWidget->setItem(i-startNum, 4, itemTime);

}
    m_currentPageNum = currentPage;
    m_countPageNum = 300 / m_pageCount + 1;
    ui->currentPageLabel->setText(QString::number(m_currentPageNum));
    ui->countPageLabel->setText(QString::number(m_countPageNum));
}

void Widget::upBtnClicked()
{
    setListWidget(m_currentPageNum - 1);
}

void Widget::downBtnClicked()
{
    if(m_currentPageNum >= m_countPageNum)
        return;

    setListWidget(m_currentPageNum + 1);
}
