
#include "SensorWidget.h"

SensorWidget::SensorWidget(QString memKey, int *valueStorage, QString noticeImagePath, QString notice ,QWidget *parent) : QWidget(parent)
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
    layout->addWidget(noticeLabel, 0, 0);
    layout->addWidget(noticeImageLabel, 0, 1);
    layout->addWidget(acquireButton, 1, 0,Qt::AlignRight);
    layout->addWidget(sensorValueLabel, 1, 1);
    layout->addWidget(prevButton,2,0,Qt::AlignLeft);
    layout->addWidget(nextButton, 2, 1,Qt::AlignRight);

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
    qDebug() << "before destination";

   
    if (activationMem->lock())
    {
        int* destination = (int*)activationMem->data();
        qDebug() << "after destination";

        qDebug() << "before if ";

        if(sensorMem->key()==QString("BPM"))
        {
            qDebug() << "in if";

            *data=1;
            qDebug() << "in if after data";

        }
        else{
            *data=0;
        }
        qDebug() << "before memcpy";

        memcpy(destination,data,activationMem->size());
        qDebug() << "after memcpy";
        
        activationMem->unlock();
        acquireTimer->start(100);
        sensorValueLabel->setText(QString::fromStdString(std::string("Acquisition en cours ...")));
    }else
    {
        sensorValueLabel->setText(QString::fromStdString(std::string("[ERROR: Can't lock activationMem]")));
    }

}

void SensorWidget::acquire()
{
    if (sensorMem->lock())
    {
        valueStorage = (int *)(this->sensorMem->data());
        qDebug() << "VALUE: " << *valueStorage;
        sensorValueLabel->setText(QString::fromStdString(std::string("Valeur capteur: ") + std::to_string(*valueStorage)));
        sensorMem->unlock();
        acquireTimer->stop();
        emit(acquireSig());
    }
}

