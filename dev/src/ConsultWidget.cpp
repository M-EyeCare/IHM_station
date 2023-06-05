#include "ConsultWidget.h"

ConsultWidget::ConsultWidget(QWidget *parent) : QStackedWidget(parent)
{

    responseMap = new std::map<std::string, bool>();

    SensorWidget *bpmWidget = new SensorWidget("BPM", &bpm, "../img/bpmNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", this);
    SensorWidget *sweatingWidget = new SensorWidget("SWEATING", &sweatingRate, "../img/sweatingNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", this);
    SensorWidget *breathWidget = new SensorWidget("BREATH", &bcpm, "../img/breathNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", this);
    SensorWidget *tempWidget = new SensorWidget("TEMP", &temperature, "../img/tempNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", this);

    this->addWidget(bpmWidget);
    this->addWidget(sweatingWidget);
    this->addWidget(breathWidget);
    this->addWidget(tempWidget);

    connect(bpmWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(bpmWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
    connect(sweatingWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(sweatingWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
    connect(breathWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(breathWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
    connect(tempWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(tempWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
}

void ConsultWidget::nextWidget()
{
    this->setCurrentIndex(this->currentIndex() + 1);
}

void ConsultWidget::previousWidget()
{
    this->setCurrentIndex(this->currentIndex() - 1);
}
