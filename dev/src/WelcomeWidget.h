#ifndef __WELCOMEWIDGET_H__
#define __WELCOMEWIDGET_H__

#include <QtCore>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <iostream>
#include <QGridLayout>
#include <QTimer>
#include <time.h>
#include <unistd.h>


class WelcomeWidget : public QWidget
{
    Q_OBJECT

protected:
    // QSharedMemory *sensorMem;
    // QSharedMemory *activationMem;
    
    QImage *logo;

    //int *valueCard;

    QPushButton *startButton;

    QSharedMemory *cardMem;
    QSharedMemory *activationMem;
    
    QLabel *welcomeLabel;
    QLabel *introLabel;
    QLabel *nameLabel;

    QGridLayout *layout;

    //std::string memKey;

public:
    WelcomeWidget(QString logoPath, QString welcome, QString intro, QString name, QWidget *parent = nullptr);

public slots:
    void start();
    void start2();

signals:
    void nextSig();
};

#endif // __WELCOMEWIDGET_H__