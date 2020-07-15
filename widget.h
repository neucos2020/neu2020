#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
#include <QObject>
#include <QMutex>

class QPushButton;
class QLineEdit;
class QProgressBar;
class QSlider;
class QRadioButton;
class QCheckBox;
class QScrollBar;
class QComboBox;
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void setListWidget(const int &currentPage);

protected slots:
    void upBtnClicked();
    void downBtnClicked();

private:
    Ui::Widget *ui;
    int m_pageCount;

    int m_currentPageNum;   //当前页数
    int m_countPageNum;        //总页数
};

#endif // WIDGET_H
