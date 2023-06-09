#include "SensorWidget.h"

SensorWidget::SensorWidget(QString memKey, int *valueStorage, QString noticeImagePath, QString notice ,QString capteur ,QWidget *parent) : QWidget(parent)
{
    sensorMem = new QSharedMemory();
    sensorMem->setKey(memKey);
    // sensorMem->create(4);
    sensorMem->attach();

    this->memKey = memKey.toStdString();

    activationMem = new QSharedMemory();
    activationMem->setKey("ACT");
    // activationMem->create(4);

    activationMem->attach();
    // activationMem->lock();

    capteurLabel = new QLabel(this);
    QString capteurText = "<html><body><p style='font-size:18pt;font-weight:bold;'>" + capteur + "</p></body></html>";
    capteurLabel->setText(capteurText);
    capteurLabel->setProperty("class", "capteurLabel");

    QPixmap notImg(noticeImagePath);
    QLabel * noticeImageLabel= new QLabel();
    noticeImageLabel->setPixmap(notImg.scaled(500,500,Qt::KeepAspectRatio));
    noticeImageLabel->setAlignment(Qt::AlignCenter);

    noticeLabel= new QLabel(this);
    noticeLabel->setText(notice);
    noticeLabel->setProperty("class","noticeLabel");

    sensorValueLabel = new QLabel(this);
    sensorValueLabel->setAlignment(Qt::AlignLeft);
    sensorValueLabel->setProperty("class","sensorLabel");

    this->valueStorage = valueStorage;

    acquireButton = new QPushButton("Commencer l'acquisition", this);
    acquireButton->setProperty("class","yesButton");

    prevButton = new QPushButton("< Retour", this);

    nextButton = new QPushButton("Suivant >", this);

    layout = new QGridLayout(this);
    layout->addWidget(capteurLabel, 0, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(noticeLabel, 2, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(noticeImageLabel, 1, 0,1,2,Qt::AlignCenter);
    layout->addWidget(acquireButton, 3, 0, 1, 1, Qt::AlignCenter);
    layout->addWidget(sensorValueLabel, 3, 1, 1, 1, Qt::AlignCenter);
    layout->addWidget(prevButton, 4, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(nextButton, 4, 1, 1, 1, Qt::AlignRight);

    acquireTimer = new QTimer(this);

    connect(acquireTimer, SIGNAL(timeout()), this, SLOT(acquire()));
    connect(acquireButton, SIGNAL(clicked()), this, SLOT(startAcquire()));
    // connect(this, SIGNAL(acquired()), acquireTimer, SLOT(stop()));
    // connect(this, SIGNAL(acquired()), sensorValueLabel, SLOT(repaint()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(prevButton, SIGNAL(clicked()), this, SLOT(previous()));

}

void SensorWidget::next()
{
    emit(nextSig());
}

void SensorWidget::previous()
{
    emit(previousSig());
}

void SensorWidget::startAcquire()
{
    int* data=(int*)malloc(sizeof(int));
    // qDebug() << "before destination";

   
    if (activationMem->lock())
    {
        int* destination = (int*)activationMem->data();

        if(sensorMem->key()==QString("BPM"))
        {
            *data=1;
        }
        else if(sensorMem->key()==QString("TEMP"))
        {
            *data=2;
        }else if(sensorMem->key()==QString("SWEATING"))
        {
            *data=3;
        }else if(sensorMem->key()==QString("BREATH"))
        {
            *data=4;
        }
        else{
            *data=0;
        }
        // qDebug() << "before memcpy";

        memcpy(destination,data,activationMem->size());
        // qDebug() << "after memcpy";
        
        activationMem->unlock();
        acquireTimer->start(1000);
        sensorValueLabel->setText(QString::fromStdString(std::string("Acquisition en cours ...")));
    }else
    {
        sensorValueLabel->setText(QString::fromStdString(std::string("[ERROR: Can't lock activationMem]")));
    }

}

void SensorWidget::acquire()
{
    qDebug()<<"attempt to acquire sensor data";
    if (sensorMem->lock())
    {
        valueStorage = (int *)(this->sensorMem->data());
        qDebug() << "VALUE: " << *valueStorage;
        sensorValueLabel->setText(QString::fromStdString(std::string("Valeur capteur: ") + std::to_string(*valueStorage)));
        sensorMem->unlock();
        acquireTimer->stop();
        
        qDebug()<<"before reset 0";
        if(activationMem->lock())
        {
            int* destination = (int*)activationMem->data();
            int* data=(int*)malloc(sizeof(int));
            *data=0;
            memcpy(destination,data,activationMem->size());
            qDebug()<<"after reset 0";

        }
        emit(acquireSig());
    }
}


