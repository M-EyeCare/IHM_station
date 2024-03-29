#include "ConsultWidget.h"

ConsultWidget::ConsultWidget(QWidget *parent) : QStackedWidget(parent)
{

    responseMap = new std::map<char*, bool>();

    questionMem = new QSharedMemory(this);
    questionMem->setKey("QUEST");
    questionMem->attach();

    validationMem = new QSharedMemory(this);
    validationMem->setKey("VAL");
    validationMem->attach();

    activationMem = new QSharedMemory(this);
    activationMem->setKey("ACT");
    activationMem->attach();

    WelcomeWidget *welcomeWidget = new WelcomeWidget("../img/logo.png", "Bienvenue dans la station de diagnostic M'Eye Consult ! ", "Avant de démarrer le diagnostic, veuillez insérer votre carte vitale dans le lecteur puis, appuyez sur le bouton", "Julia", this);

    SensorWidget *bpmWidget = new SensorWidget("BPM", &bpm, "../img/bpmNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", "CAPTEUR CARDIAQUE", "BPM", this);
    SensorWidget *sweatingWidget = new SensorWidget("SWEATING", &sweatingRate, "../img/sweatingNotice.png", "Glissez l'index et le majeur dans les petits rouleaux qui contiennent les capteurs !","CAPTEUR DE SUDATION", "", this);
    SensorWidget *breathWidget = new SensorWidget("BREATH", &bcpm, "../img/breathNotice.png", "Approchez votre bouche de l'embout et respirez normalement dans le petit tube !","CAPTEUR DE PRESSION", "CPM", this);
    SensorWidget *tempWidget = new SensorWidget("TEMP", &temperature, "../img/tempNotice.png", "Positionnez le capteur dans le creux de votre coude et venez toucher votre épaule avec mon main !", "CAPTEUR DE TEMPERATURE","°C",this);
    
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
    
    validationWidget = new ValidationWidget("../img/logo.png", this);
    
    this->addWidget(welcomeWidget);
    
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

    this->addWidget(validationWidget);

    connect(welcomeWidget,SIGNAL(nextSig()), this, SLOT(nextWidget()));

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

    connect(validationWidget, SIGNAL(confirmSig()), this, SLOT(reset()));
    connect(validationWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));
}

void ConsultWidget::debug()
{
    //qDebug()<< responseMap->count("yolo");
}

void ConsultWidget::nextWidget()
{
    this->setCurrentIndex(this->currentIndex() + 1);
}

void ConsultWidget::previousWidget()
{
    this->setCurrentIndex(this->currentIndex() - 1);
}

void ConsultWidget::reset()
{
    qDebug() << "Reset";
    bool run = true;

    while (run)
    {
        if (questionMem->lock())
        {
                
            // send responses
            char buff[100] = "";
            int i=0;
            for (std::map<char *, bool>::iterator it = responseMap->begin(); it != responseMap->end(); ++it)
            {
                i++;
                qDebug()<< i;

                char *response=(char*)malloc(2);
                if (it->second)
                {
                    response="1";
                }
                else
                {
                    response="0";
                }
                strcat(buff, response);
                strcat(buff, ";");
                qDebug() << response;
                qDebug() << buff;
            }
            qDebug() << buff;

            char *destination = (char *)questionMem->data();

            std::memcpy(destination, buff, questionMem->size());

            questionMem->unlock();

            // Utilisation de la mémoire partagée ACT
            if (activationMem->lock())
            {
                int* data=(int*)malloc(sizeof(int));
                int* destination = (int*)activationMem->data();
                qDebug() << "envoi de la commande 5";
                *data=5;
                std::cout << *data << std::endl;
                memcpy(destination,data,activationMem->size());
                activationMem->unlock();
            }

            
            /*
            if (validationMem->lock())
            {
                int* data=(int*)malloc(sizeof(int));
                int* destination = (int*)validationMem->data();
                qDebug() << "envoi de la commande 5";
                *data=5;
                std::cout << *data << std::endl;
                memcpy(destination,data,validationMem->size());
                validationMem->unlock();
            }

            sleep(0.5);

            if(validationMem->lock())
            {
                int* data=(int*)malloc(sizeof(int));
                int* destination = (int*)validationMem->data();
                qDebug() << "remise à 0 de la commande 5";
                *data=0;
                memcpy(destination,data,validationMem->size());
                qDebug()<<"after reset 0";
                validationMem->unlock();
            }
            */

            sleep(5);

            // RESET
            responseMap = new std::map<char *, bool>();


            for(int i = this->count(); i>0; i--){
                QWidget* widget = this->widget(i);
                this->removeWidget(widget);
                widget->deleteLater();
            }
            
            welcomeWidget = new WelcomeWidget("../img/logo.png", "Bienvenue dans la station de diagnostic M'Eye Consult ! ", "Avant de démarrer le diagnostic, veuillez insérer votre carte vitale dans le lecteur puis, appuyez sur \"Commencer\"", "Julia", this);

            bpmWidget = new SensorWidget("BPM", &bpm, "../img/bpmNotice.png", "Glissez votre doigt à l'intérieur du petit rouleau dans lequel se trouve le capteur !", "CAPTEUR CARDIAQUE", "BPM", this);
            sweatingWidget = new SensorWidget("SWEATING", &sweatingRate, "../img/sweatingNotice.png", "Glissez l'index et le majeur dans les petits rouleaux qui contiennent les capteurs !","CAPTEUR DE SUDATION", "", this);
            breathWidget = new SensorWidget("BREATH", &bcpm, "../img/breathNotice.png", "Approchez votre bouche de l'embout et respirez normalement dans le petit tube !","CAPTEUR DE PRESSION", "CPM", this);
            tempWidget = new SensorWidget("TEMP", &temperature, "../img/tempNotice.png", "Positionnez le capteur dans le creux de votre coude et venez toucher votre épaule avec mon main !", "CAPTEUR DE TEMPERATURE","°C",this);

            headacheWidget = new QuestionWidget("Ressentez vous des douleurs au crâne ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "headache", responseMap, this);
            stomacacheWigget = new QuestionWidget("Ressentez vous des douleurs au ventre ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "stomacache", responseMap, this);
            backacheWidget = new QuestionWidget("Ressentez vous des douleurs au dos ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "backache", responseMap, this);
            throatacheWidget = new QuestionWidget("Ressentez vous des douleurs à la gorge ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "throatache", responseMap, this);
            breathingacheWidget = new QuestionWidget("Avez-vous une respiration douloureuse ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "breathingache", responseMap, this);
            otheracheWidget = new QuestionWidget("Avez-vous des douleurs autres que celles énoncées précédemment ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "otherache", responseMap, this);
            nauseasWidget = new QuestionWidget("Avez-vous des nausées ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "nauseas", responseMap, this);
            tiredWidget = new QuestionWidget("Ressentez-vous une fatigue ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "tired", responseMap, this);
            sleepingWidget = new QuestionWidget("Avez-vous des troubles du sommeil ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "sleeping", responseMap, this);
            treatmentWidget = new QuestionWidget("Suivez-vous actuellement un traitement ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "treatment", responseMap, this);
            rashesWidget = new QuestionWidget("Avez-vous des éruptions cutanées ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "rashes", responseMap, this);
            smokingWidget = new QuestionWidget("Êtes-vous fumeur ?", "VEUILLEZ REPONDRE AUX QUESTION CI-DESSOUS", "smoking", responseMap, this);

            validationWidget = new ValidationWidget("../img/logo.png", this);
            
            this->insertWidget(0,welcomeWidget);
            this->setCurrentIndex(0);

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
            this->addWidget(validationWidget);

            connect(welcomeWidget, SIGNAL(nextSig()), this, SLOT(nextWidget()));

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

            connect(validationWidget, SIGNAL(confirmSig()), this, SLOT(reset()));
            connect(validationWidget, SIGNAL(previousSig()), this, SLOT(previousWidget()));

            qDebug() << "reset";
            run=false;
        }
        sleep(0.2);
    }
}