#include "decoupeimage.h"

DecoupeImage::DecoupeImage(QWidget *parent) :
    QWidget(parent)
{
    point1_x = 0;
    point1_y = 0;
    point2_x = 0;
    point2_y = 0;

    this->setAttribute(Qt::WA_DeleteOnClose);

    QHBoxLayout * Hlayout = new QHBoxLayout();
    QVBoxLayout * Vlayout = new QVBoxLayout();

    labelDecoupe = new LabelDecoupe();
    locationwidget1 = new LocationWidget();
    locationwidget2 = new LocationWidget();
    bouttonDecouper = new QPushButton("d�couper");
    labelPoint1 = new QLabel("Point 1");
    labelPoint2 = new QLabel("Point 2");

    Vlayout->addWidget(labelPoint1);
    Vlayout->addWidget(locationwidget1);
    Vlayout->addWidget(labelPoint2);
    Vlayout->addWidget(locationwidget2);
    Vlayout->addWidget(bouttonDecouper);

    Hlayout->addWidget(labelDecoupe);
    Hlayout->addLayout(Vlayout);

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setLayout(Hlayout);

    QObject::connect(labelDecoupe, SIGNAL(click1(int,int)), this, SLOT(setPoint1(int,int)));
    QObject::connect(labelDecoupe, SIGNAL(click2(int,int)), this, SLOT(setPoint2(int,int)));
    QObject::connect(labelDecoupe, SIGNAL(cleared()), this, SLOT(clear()));
    QObject::connect(bouttonDecouper, SIGNAL(clicked()), this, SLOT(decoup()));

    QObject::connect(locationwidget1, SIGNAL(coordinateChanged(int,int)), this, SLOT(changeCoordinate1(int,int)));
    QObject::connect(locationwidget2, SIGNAL(coordinateChanged(int,int)), this, SLOT(changeCoordinate2(int,int)));

}

void DecoupeImage::afficher()
{
    this->showMaximized();
}

void DecoupeImage::setPixmap(QPixmap * qpixmap)
{
    pixmap = qpixmap;
    labelDecoupe->setPixmap(pixmap);
}

void DecoupeImage::setPoint1(int x, int y)
{
    point1_x = x;
    point1_y = y;

    locationwidget1->displayCoordinate(x, y);
}

void DecoupeImage::setPoint2(int x, int y)
{
    point2_x = x;
    point2_y = y;

    locationwidget2->displayCoordinate(x, y);
}

void DecoupeImage::clear()
{
    point1_x = 0;
    point1_y = 0;
    point2_x = 0;
    point2_y = 0;

    locationwidget1->displayCoordinate(1, 1);
    locationwidget1->displayCoordinate(1, 1);
}

void DecoupeImage::decoup()
{
    emit decouper(point1_x, point1_y, point2_x, point2_y);
    this->close();
}

void DecoupeImage::changeCoordinate1(int x, int y)
{
    int y1 =(int) ((double)(y * labelDecoupe->geometry().height()) /(double) pixmap->height() + 1);
    int x1 =(int) ((double)(x * labelDecoupe->geometry().width()) / (double)pixmap->width() )+ 1;

    labelDecoupe->setPointX1(x1);
    labelDecoupe->setPointY1(y1);
    labelDecoupe->update();
}

void DecoupeImage::changeCoordinate2(int x, int y)
{
    int y1 =(int) ((double)(y * labelDecoupe->geometry().height()) /(double) pixmap->height() ) + 1;
    int x1 =(int) ((double)(x * labelDecoupe->geometry().width()) / (double)pixmap->width() ) + 1;

    labelDecoupe->setPointX2(x1);
    labelDecoupe->setPointY2(y1);
    labelDecoupe->update();
}
