#include "SensorWidget.h"

SensorWidget::SensorWidget(QString memKey, float *valueStorage, QString noticeImagePath, QString notice , QString capteur, QString unit, QWidget *parent) : QWidget(parent)
{
    sensorMem = new QSharedMemory();
    sensorMem->setKey(memKey);
    // sensorMem->create(4);
    sensorMem->attach();

    this->memKey = memKey.toStdString();
    this->unit = unit.toStdString();

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

    //nextButton = new QPushButton("Suivant >", this);

    layout = new QGridLayout(this);
    layout->addWidget(capteurLabel, 0, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(noticeLabel, 2, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(noticeImageLabel, 1, 0,1,2,Qt::AlignCenter);
    layout->addWidget(acquireButton, 3, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(sensorValueLabel, 3, 1, 1, 1, Qt::AlignLeft);
    layout->addWidget(prevButton, 4, 0, 1, 1, Qt::AlignLeft);
    //layout->addWidget(nextButton, 4, 1, 1, 1, Qt::AlignRight);

    acquireTimer = new QTimer(this);

    connect(acquireTimer, SIGNAL(timeout()), this, SLOT(acquire()));
    connect(acquireButton, SIGNAL(clicked()), this, SLOT(startAcquire()));
    //connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
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

        // Affecter la valeur de data à acquisitionData
        acquisitionData = *data;

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
    nextButton = new QPushButton("Suivant >", this);
    layout->addWidget(nextButton, 4, 1, 1, 1, Qt::AlignRight);
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));

    qDebug()<<"attempt to acquire sensor data";
    if (sensorMem->lock())
    {
        *valueStorage = (float )*(int*)(this->sensorMem->data());
        *valueStorage/=10.0;
        qDebug() << "VALUE: " << *valueStorage;
        std::string valueStr=std::to_string(*valueStorage);
        sensorValueLabel->setText(QString::fromStdString(std::string("Valeur capteur: ") + valueStr.substr(0, valueStr.find(".")+3)+ std::string(" ") + unit));
        sensorMem->unlock();
        acquireTimer->stop();

        // Utiliser la valeur de acquisitionData pour récup la demande capteur
        if (acquisitionData == 1){
            // pulsation cardiaque
            qDebug()<<"analyse pulsation cardiaque";
        }
        else if (acquisitionData == 2){
            // temperature
            qDebug()<<"analyse temperature";
        }
        else if (acquisitionData == 3){
            // sudation
            qDebug()<<"analyse sudation";
        }
        else if (acquisitionData == 4){
            // pression
            qDebug()<<"analyse pression";
        }
        
        qDebug()<<"before reset 0";
        if(activationMem->lock())
        {
            int* destination = (int*)activationMem->data();
            int* data=(int*)malloc(sizeof(int));
            *data=0;
            memcpy(destination,data,activationMem->size());
            qDebug()<<"after reset 0";
            activationMem->unlock();
        }
        emit(acquireSig());
    }
}


