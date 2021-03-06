#ifndef LABALDECOUPE_H
#define LABALDECOUPE_H

#include <QLabel>
#include <QMouseEvent>
#include <QPainter>

class LabelDecoupe : public QLabel
{
    Q_OBJECT
public:
    explicit LabelDecoupe(QWidget *parent = 0);
    void drawVLine(QPainter *qp, int x);
    void drawHLine(QPainter *qp , int y);
    void setPixmap(QPixmap * qp);
    void setPointX1(int n);
    void setPointY1(int n);
    void setPointX2(int n);
    void setPointY2(int n);
    void setFirstClick(bool b);
    void setSecondClick(bool b);

private:
    int point1_x;
    int point1_y;
    int point2_x;
    int point2_y;
    bool firstClick;
    bool secondClick;

    QPixmap * pixmap;

protected:
    void resizeEvent(QResizeEvent *);
    void mouseReleaseEvent(QMouseEvent *ev);
    void paintEvent(QPaintEvent *ev);

    
signals:
    void click1(int x, int y);
    void click2(int x, int y);
    void cleared();

public slots:
    
};

#endif // LABALDECOUPE_H
