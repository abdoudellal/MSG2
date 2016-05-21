#ifndef DBIMAGESVIEW_H
#define DBIMAGESVIEW_H

#include "db.h"

#include <QWidget>
#include <QSqlQueryModel>
#include <QTableView>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

class DbImagesView : public QWidget
{
    Q_OBJECT
public:
    explicit DbImagesView(QWidget *parent = 0);

private:
    QSqlQueryModel * myModel;
    QTableView * myTableView;
    QLabel * labelBoutton;
    QPushButton * bouttonAfficher;
    
signals:
    void imageSelected(QString fichier);
public slots:
    void clicSelection();
};

#endif // DBIMAGESVIEW_H
