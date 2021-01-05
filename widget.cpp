#include "widget.h"
#include "ui_widget.h"

#define HEIGHT 800
#define WIDTH 800

#define MID  400
#define MIDX 400
#define MIDY 400

#define D2R(x) (float)((x)*M_PI/180.0f)

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    oldpos.setX(MID+70);
    oldpos.setY(MID+170);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::draw(QPainter *p, float d1, float d2)
{
    O.setX(MID);
    O.setY(MID);
    t1.setX(MIDX+l1*qCos(d1));
    t1.setY(MID+l1*qSin(d1));
    p->drawLine(O,t1);
    t2.setX((t1.x()+l2*qCos(d1+d2)));
    t2.setY((t1.y()+l2*qSin(d1+d2)));
    p->drawLine(t1,t2);
    p->drawEllipse(t2.x()-10,t2.y()-10,20,20);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
      {
        moveFlag = true;
        oldpos = event->pos();
      }
    QWidget::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && moveFlag)
      {
        newpos = event->pos();
        dpos = newpos - oldpos;
        oldpos = newpos;
      }
    QWidget::mouseMoveEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if ((event->buttons() == Qt::LeftButton) && moveFlag)
      {
        moveFlag = false;
      }
    QWidget::mouseReleaseEvent(event);
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter clear(this);
    clear.translate(WIDTH-1,HEIGHT-1);
    clear.setBrush(QBrush(QColor(255,255,255)));
    clear.drawRect(0,0,WIDTH,HEIGHT);

    QPainter p_base(this);
    p_base.setBrush(QBrush(QColor(0,0,0)));
    p_base.drawLine(0,MID,WIDTH,MID);//x
    p_base.drawLine(MID,0,MID,HEIGHT);//y

    QPainter p_max(this);
    p_max.drawEllipse(MID-(l1+l2),MID-(l1+l2),(l1+l2)*2,(l1+l2)*2);

    QPainter p_l(this);
    p_l.setBrush(QBrush(QColor(Qt::red)));
    draw(&p_l,IK1(oldpos),IK2(oldpos));

    update();
}

float Widget::IK1(QPointF p)
{
    auto x = p.x()-MID;
    auto y = p.y()-MID;
    float tan21 = qAtan2(y,x);
    float cos = (x*x+y*y-l1*l1-l2*l2)/(2*l1*l2);
    float sin = sqrt(1-cos*cos);
    float tan22 = qAtan2(l2*sin,l1+l2*cos);
    return tan21-tan22;
}

float Widget::IK2(QPointF p)
{
    auto x = p.x()-MID;
    auto y = p.y()-MID;
    float cos = (x*x+y*y-l1*l1-l2*l2)/(2*l1*l2);
    float sin = sqrt(1-cos*cos);
    float tan2 = qAtan2(sin,cos);
//    qDebug()<<"x : "<<x<<" y : "<<y<<" sin : "<<sin<<" cos : "<<cos<<" tan : "<<tan2;
    return tan2;
}

