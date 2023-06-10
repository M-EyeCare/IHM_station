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

class WelcomeWidget : public QWidget
{
    Q_OBJECT

protected:
    // QSharedMemory *sensorMem;
    // QSharedMemory *activationMem;
    
    QImage *logo;

    int *valueId;

    QPushButton *startButton;
    
    QLabel *welcomeLabel;
    QLabel *introLabel;
    QLabel *nameLabel;

    QGridLayout *layout;

    //std::string memKey;

public:
    WelcomeWidget(int *valueId, QString logoPath, QString welcome, QString intro, QString name, QWidget *parent = nullptr);

public slots:
    void start();

signals:
    void nextSig();
};

#endif // __WELCOMEWIDGET_H__