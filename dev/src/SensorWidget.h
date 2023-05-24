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
    float *valueStorage;
    QPushButton *confirmButton;
    QPushButton *acquireButton;
    QLabel * sensorValueLabel;
    QGridLayout * layout;
    QTimer * acquireTimer;

public:
    SensorWidget(QString memKey, float *valueStorage, QString noticeImagePath, QWidget *parent = nullptr);

public slots:
    void acquire();
    void confirm();
    void startTimer();

signals:
    void confirmed();
    void acquired();

};

#endif // __SENSORWIDGET_H__