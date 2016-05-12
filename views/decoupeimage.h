#ifndef DECOUPEIMAGE_H
#define DECOUPEIMAGE_H
#include "labeldecoupe.h"
#include "locationwidget.h"

#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

class DecoupeImage : public QWidget
{
    Q_OBJECT
public:
    explicit DecoupeImage(QWidget *parent = 0);
    void afficher();
    void setPixmap(QPixmap * qpixmap);

private:
    QPixmap * pixmap;

    LocationWidget * locationwidget1;
    LocationWidget * locationwidget2;
    LabelDecoupe * labelDecoupe;
    QPushButton * bouttonDecouper;
    QLabel * labelPoint1;
    QLabel * labelPoint2;

    int point1_x;
    int point1_y;
    int point2_x;
    int point2_y;


signals:
    void decouper(int x1, int y1, int x2, int y2);
public slots:
    void decoup();
    void setPoint1(int x, int y);
    void setPoint2(int x, int y);
    void clear();

    void changeCoordinate1(int x, int y);
    void changeCoordinate2(int x, int y);
    
};

#endif // DECOUPEIMAGE_H
