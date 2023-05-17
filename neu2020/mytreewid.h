#ifndef MYTREEWID_H
#define MYTREEWID_H
#include <QTreeWidget>
#include<QGraphicsView>
class MytreeWid :public QTreeWidget
{
    Q_OBJECT




public:
    MytreeWid(QWidget *parent = 0);
    ~MytreeWid();
    void updateParentItem(QTreeWidgetItem* item);
public slots:
    void treeItemChanged(QTreeWidgetItem* item, int column);
};
#endif // MYTREEWID_H
