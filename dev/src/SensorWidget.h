#ifndef __SENSORWIDGET_H__
#define __SENSORWIDGET_H__

#include <QtCore>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <iostream>
#include <QGridLayout>
#include <QTimer>
#include <unistd.h>
#include <QDebug>

// #include "MonitoringWidget.h"
class SensorWidget;

class SensorWidget : public QWidget
{
    Q_OBJECT

protected:
    QSharedMemory *sensorMem;
    QImage *noticeImage;
    int *valueStorage;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *acquireButton;
    QLabel * sensorValueLabel;
    QGridLayout * layout;
    QTimer * acquireTimer;
    QLabel * noticeLabel;

public:
    SensorWidget(QString memKey, int *valueStorage, QString noticeImagePath,QString notice, QWidget *parent = nullptr);

public slots:
    void acquire();
    void next();
    void previous();
    void startTimer();

signals:
    void nextSig();
    void previousSig();
    void acquireSig();

};


#endif // __SENSORWIDGET_H__