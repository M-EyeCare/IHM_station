#include "ConsultWidget.h"

ConsultWidget::ConsultWidget(QWidget *parent) : QStackedWidget(parent)
{

    responseMap = new std::map<char*, bool>();

    SensorWidget *bpmWidget = new SensorWidget("BPM", &bpm, "../img/bpmNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", "CAPTEUR CARDIAQUE", this);
    SensorWidget *sweatingWidget = new SensorWidget("SWEATING", &sweatingRate, "../img/sweatingNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !","CAPTEUR DE SUDATION", this);
    SensorWidget *breathWidget = new SensorWidget("BREATH", &bcpm, "../img/breathNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !","CAPTEUR DE PRESSION", this);
    SensorWidget *tempWidget = new SensorWidget("TEMP", &temperature, "../img/tempNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", "CAPTEUR DE TEMPERATURE",this);
    
    QuestionWidget *headacheWidget= new QuestionWidget("Ressentez vous des douleurs au crâne ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","headache", responseMap,this);
    QuestionWidget *stomacacheWigget= new QuestionWidget("Ressentez vous des douleurs au ventre ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","stomacache", responseMap,this);
    QuestionWidget *backacheWidget= new QuestionWidget("Ressentez vous des douleurs au dos ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","backache", responseMap,this);
    QuestionWidget *throatacheWidget= new QuestionWidget("Ressentez vous des douleurs à la gorge ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","throatache", responseMap,this);
    QuestionWidget *breathingacheWidget= new QuestionWidget("Avez-vous une respiration douloureuse ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","breathingache", responseMap,this);
    QuestionWidget *otheracheWidget= new QuestionWidget("Avez-vous des douleurs autres que celles énoncées précédemment ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","otherache", responseMap,this);
    QuestionWidget *nauseasWidget= new QuestionWidget("Avez-vous des nausées ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","nauseas", responseMap,this);
    QuestionWidget *tiredWidget= new QuestionWidget("Ressentez-vous une fatigue ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","tired", responseMap,this);
    QuestionWidget *sleepingWidget= new QuestionWidget("Avez-vous des troubles du sommeil ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","sleeping", responseMap,this);
    QuestionWidget *treatmentWidget= new QuestionWidget("Suivez-vous actuellement un traitement ?","VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "treatment", responseMap,this);
    QuestionWidget *rashesWidget= new QuestionWidget("Avez-vous des éruptions cutanées ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","rashes", responseMap,this);
    QuestionWidget *smokingWidget= new QuestionWidget("Êtes-vous fumeur ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS","smoking", responseMap,this);
    
    this->addWidget(bpmWidget);
    this->addWidget(sweatingWidget);
    this->addWidget(breathWidget);
    this->addWidget(tempWidget);

    this->addWidget(headacheWidget);
    this->addWidget(stomacacheWigget);
    this->addWidget(backacheWidget);
    this->addWidget(throatacheWidget);
    this->addWidget(breathingacheWidget);
    this->addWidget(otheracheWidget);
    this->addWidget(nauseasWidget);
    this->addWidget(tiredWidget);
    this->addWidget(sleepingWidget);
    this->addWidget(treatmentWidget);
    this->addWidget(rashesWidget);
    this->addWidget(smokingWidget);

    connect(bpmWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(bpmWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
    connect(sweatingWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(sweatingWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
    connect(breathWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(breathWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
    connect(tempWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(tempWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
    
    connect(headacheWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(headacheWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(stomacacheWigget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(stomacacheWigget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(backacheWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(backacheWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(throatacheWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(throatacheWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(breathingacheWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(breathingacheWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(otheracheWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(otheracheWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(nauseasWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(nauseasWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(tiredWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(tiredWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(sleepingWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(sleepingWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(treatmentWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(treatmentWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(rashesWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(rashesWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

    connect(smokingWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));
    connect(smokingWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
}

void ConsultWidget::debug()
{
    qDebug()<< responseMap->count("yolo");
}

void ConsultWidget::nextWidget()
{
    this->setCurrentIndex(this->currentIndex() + 1);
}

void ConsultWidget::previousWidget()
{
    this->setCurrentIndex(this->currentIndex() - 1);
}
