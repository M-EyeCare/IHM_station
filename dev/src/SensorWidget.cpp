
#include "SensorWidget.h"

SensorWidget::SensorWidget(QString memKey, float *valueStorage, QString noticeImagePath, QWidget *parent) : QWidget(parent)
{
    sensorMem = new QSharedMemory();
    sensorMem->setKey(memKey);
    sensorMem->attach();

    noticeImage = new QImage(noticeImagePath);

    sensorValueLabel = new QLabel(this);

    this->valueStorage = valueStorage;

    acquireButton = new QPushButton("Commencer l'acquisition", this);
    confirmButton = new QPushButton("Confirmer", this);

    layout = new QGridLayout(this);

    layout->addWidget(sensorValueLabel, 1, 1);
    layout->addWidget(acquireButton, 2, 0);
    layout->addWidget(confirmButton, 2, 2);

    acquireTimer = new QTimer(this);

    connect(acquireTimer, SIGNAL(timeout()), this, SLOT(acquire()));
    connect(acquireButton, SIGNAL(clicked()), this, SLOT(startTimer()));
    // connect(this, SIGNAL(acquired()), acquireTimer, SLOT(stop()));
    // connect(this, SIGNAL(acquired()), sensorValueLabel, SLOT(setText(QString(*valueStorage))));
    connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
}

void SensorWidget::confirm()
{
    emit(confirmed());
}

void SensorWidget::startTimer()
{
    acquireTimer->start(100);
}

void SensorWidget::acquire()
{
    if (sensorMem->lock())
    {
        valueStorage = (float *)(this->sensorMem->data());
        qDebug()<<"VALUE: "<<*valueStorage ;
        sensorValueLabel->setText(QString::number(*valueStorage));
        acquireTimer->stop();
        sensorMem->unlock();
        emit(acquired());
    } 
}
