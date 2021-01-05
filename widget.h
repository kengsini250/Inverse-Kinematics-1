#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPointF>
#include <QPainter>
#include <QPaintEvent>

#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void draw(QPainter* p, float d1, float d2);
protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *);
private:
    Ui::Widget *ui;
    bool moveFlag = false;
    QPointF oldpos,newpos,dpos
            ,O,t1,t2;

    float IK1(QPointF p);
    float IK2(QPointF p);

    float l1=100,l2=100;
    QPointF l1P,l2P;
};
#endif // WIDGET_H
