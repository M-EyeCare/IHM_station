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

class SensorWidget : public QWidget
{
    Q_OBJECT

protected:
    QSharedMemory *sensorMem;
    QSharedMemory *activationMem;
    QImage *noticeImage;
    float *valueStorage;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *acquireButton;
    QLabel *sensorValueLabel;
    QGridLayout *layout;
    QTimer *acquireTimer;
    QLabel *noticeLabel;
    QLabel *capteurLabel;
    std::string memKey;

public:
    SensorWidget(QString memKey, float *valueStorage, QString noticeImagePath, QString notice, QString capteur, QString unit, QWidget *parent = nullptr);

public slots:
    void acquire();
    void next();
    void previous();
    void startAcquire();

signals:
    void nextSig();
    void previousSig();
    void acquireSig();
};

#endif // __SENSORWIDGET_H__