#include "locationwidget.h"
#include "latlong.h"
#include <QHBoxLayout>

LocationWidget::LocationWidget(QWidget *parent) :
    QWidget(parent)
{
    x = 0;
    y = 0;
    offsetX = 0;
    offsetY = 0;

    QHBoxLayout * layout = new QHBoxLayout();
    XYWidget = new coordinateWidget();
    geoWidget = new LatLonWidget();
    layout->addWidget(XYWidget);
    layout->addWidget(geoWidget);
    this->setLayout(layout);
    QObject::connect(XYWidget, SIGNAL(coordinateChanged(int, int)), this, SLOT(ChangeCoordinate(int,int)));
    QObject::connect(geoWidget, SIGNAL(latLonChanged(double, double)), this, SLOT(ChangeLatLong(double,double)));
}

void LocationWidget::ChangeLatLong(double lat,double lon)
{
    int i,j;
    LatLong::Getlinepixel(lat, lon, &i, &j);
    y = i - 1 - offsetY;
    x = j - 1 - offsetX;
    XYWidget->setXY(x , y );
    geoWidget->setLatLon(lat, lon);
    emit coordinateChanged(x, y);
}

void LocationWidget::ChangeCoordinate(int X, int Y)
{
    displayCoordinate(X,Y);
    emit coordinateChanged(x, y);
}

void LocationWidget::displayCoordinate(int X, int Y)
{
    x = X;
    y = Y;
    double lat;
    double lon;
    LatLong::Getlatlon(&lat, &lon, y + 1 + offsetY, x + 1 + offsetX);
    XYWidget->setXY(X,Y);
    geoWidget->setLatLon(lat, lon);
}

void LocationWidget::setOffsetX(int ox)
{
    offsetX = ox;
}

void LocationWidget::setOffsetY(int oy)
{
    offsetY = oy;
}
