#include "mytreewid.h"
#include<mainwindow.h>
#include "ui_mainwindow.h"
#include<QDebug>
MytreeWid::MytreeWid(QWidget *parent):QTreeWidget(parent){
    QHeaderView *head=this->header();
    head->setVisible(false);
       head->setSectionResizeMode(QHeaderView::ResizeToContents);
    //******************************MytreeWid初始化部分
    QTreeWidgetItem *group1 = new QTreeWidgetItem(this);
    group1->setText(0, "排序");
    group1->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    QTreeWidgetItem *subItem11 = new QTreeWidgetItem(group1);
    subItem11->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    subItem11->setText(0, "快速排序");

    QTreeWidgetItem *subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
    subItem12->setText(0, "选择排序");

    QTreeWidgetItem *subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags( Qt::ItemIsEnabled |Qt::ItemIsUserCheckable);
    subItem13->setText(0, "冒泡排序");


    QTreeWidgetItem *subItem14 = new QTreeWidgetItem(group1);
    subItem14->setFlags( Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
    subItem14->setText(0, "堆排序");


    QTreeWidgetItem *subItem15 = new QTreeWidgetItem(group1);
    subItem15->setFlags(Qt::ItemIsEnabled|Qt::ItemIsUserCheckable);
    subItem15->setText(0, "希尔排序");
    //第二个分组
    QTreeWidgetItem *group2 = new QTreeWidgetItem(this);
    group2->setText(0, "查找");
    group2->setFlags( Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    QTreeWidgetItem *subItem21 = new QTreeWidgetItem(group2);
    subItem21->setFlags( Qt::ItemIsEnabled |Qt::ItemIsUserCheckable);
    subItem21->setText(0, "顺序查找");

    QTreeWidgetItem *subItem22 = new QTreeWidgetItem(group2);
    subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
    subItem22->setText(0, "二分查找");

    QTreeWidgetItem *subItem23 = new QTreeWidgetItem(group2);
    subItem23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled );
    subItem23->setText(0, "分块查找");
    //******************************MytreeWid初始化部分

}
MytreeWid::~MytreeWid(){

}
void MytreeWid::treeItemChanged(QTreeWidgetItem* item, int column)
{
    QString itemText = item->text(0);
    //选中时
    if (Qt::Checked == item->checkState(0))
    {
           //QTreeWidgetItem* parent = item->parent();
           int count = item->childCount();
           if (count > 0)
           {
                for (int i = 0; i < count; i++)
                {
                      //子节点也选中
                      item->child(i)->setCheckState(0, Qt::Checked);
                }
           }
           else
           {
                //是子节点
                updateParentItem(item);
           }
    }
    else if (Qt::Unchecked == item->checkState(0))
    {
           int count = item->childCount();
           if (count > 0)
           {
                for (int i = 0; i < count; i++)
                {
                 item->child(i)->setCheckState(0, Qt::Unchecked);
                }
           }
           else
           {
                updateParentItem(item);
           }
    }
}

void MytreeWid::updateParentItem(QTreeWidgetItem* item)
{
    QTreeWidgetItem *parent = item->parent();
    if (parent == NULL)
    {
         return;
    }

    //选中的子节点个数
    int selectedCount = 0;
    int childCount = parent->childCount();
    for (int i = 0; i < childCount; i++)
    {
         QTreeWidgetItem *childItem = parent->child(i);
         if (childItem->checkState(0) == Qt::Checked)
         {
                selectedCount++;
         }
    }
    if (selectedCount <= 0)
    {
         //选中状态
         parent->setCheckState(0, Qt::Unchecked);
    }
    else if (selectedCount > 0 && selectedCount < childCount)
    {
         //部分选中状态
         parent->setCheckState(0, Qt::PartiallyChecked);
    }
    else if (selectedCount == childCount)
    {
         //未选中状态
         parent->setCheckState(0, Qt::Checked);
    }
}
