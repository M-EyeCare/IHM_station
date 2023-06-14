#include "WelcomeWidget.h"

WelcomeWidget::WelcomeWidget(QString logoPath, QString welcome, QString intro, QString name, QWidget *parent) : QWidget(parent)
{
    /*sensorMem = new QSharedMemory();
    sensorMem->setKey(memKey);
    sensorMem->attach();

    this->memKey = memKey.toStdString();

    activationMem = new QSharedMemory();
    activationMem->setKey("ACT");

    activationMem->attach();*/

    // Mémoire pour la récupération de l'identifiant de la mémoire partagée
    cardMem = new QSharedMemory(this);
    cardMem->setKey("CARD");
    cardMem->attach();

    activationMem = new QSharedMemory(this);
    activationMem->setKey("ACT");
    activationMem->attach();

    // Bienvenue dans la station de diagnostic M'Eye Consult ! 
    welcomeLabel = new QLabel(this);
    QString welcomeText = "<html><body><p style='font-size:18pt;font-weight:bold;'>" + welcome + "</p></body></html>";
    welcomeLabel->setText(welcomeText);
    welcomeLabel->setProperty("class", "welcomeLabel");

    //Logo
    QPixmap notImg(logoPath);
    QLabel * logoLabel= new QLabel();
    logoLabel->setPixmap(notImg.scaled(500,500,Qt::KeepAspectRatio));
    logoLabel->setAlignment(Qt::AlignCenter);

    // Avant de démarrer le diagnostic, veuillez insérer votre carte vitale dans le lecteur puis, appuyez sur "Commencer"
    introLabel = new QLabel(this);
    QString introText = "<html><body><p style='font-size:18pt;font-weight:bold;'>" + intro + "</p></body></html>";
    introLabel->setText(introText);
    introLabel->setProperty("class", "introLabel");

    startButton = new QPushButton(" J'ai inséré ma carte vitale ", this);
    startButton->setProperty("class","startButton");

    layout = new QGridLayout(this);
    layout->addWidget(welcomeLabel, 0, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(logoLabel, 1, 0,1,2,Qt::AlignCenter);
    layout->addWidget(introLabel, 2, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(startButton, 3, 0, 1, 2, Qt::AlignCenter);

    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
}

void WelcomeWidget::start()
{

    int* data=(int*)malloc(sizeof(int));
    if (activationMem->lock()){
        int* destination = (int*)activationMem->data();
        *data=6;
        memcpy(destination,data,activationMem->size());
        activationMem->unlock();
    }

    sleep(1);

    char* valueCard=(char*)malloc(sizeof(char));
    qDebug()<<"attempt to acquire card identifier";
    bool run=true;

    while(run){
        if (cardMem->lock())
        {
            valueCard = (char*)(this->cardMem->data());
            std::string valueStr=std::string(valueCard);
            qDebug() << "NAME CARD : " << valueCard;
            welcomeLabel->setText(QString::fromStdString(std::string("<html><body><p style='font-size:18pt;font-weight:bold;'> Bienvenue ") + valueStr + std::string(" ! </p></body></html>")));
            cardMem->unlock();

            introLabel->setText("<html><body><p style='font-size:18pt;font-weight:bold;'> Maintenant, veuillez appuyer sur le bouton \"Commencer\" </p></body></html>");
            startButton->setText("Commencer");
            connect(startButton, SIGNAL(clicked()), this, SLOT(start2()));
            run=false;
        }
        sleep(0.2);
    }
}

void WelcomeWidget::start2()
{
    emit(nextSig());
}




/*
int* valueCard=(int*)malloc(sizeof(int));
    qDebug()<<"attempt to acquire card identifier";
    bool run=true;

    while(run){
        if (cardMem->lock())
        {
            *valueCard = *(int*)(this->cardMem->data());

            // Exécution d'une requête SQL
            sql::Statement *stmt;
            sql::ResultSet *res;

            stmt = con->createStatement();
            // Construction de la requête SQL
            std::string query = "SELECT name FROM PATIENTS WHERE id=" + std::to_string(valueCard);
            // Exécution de la requête SQL
            res = stmt->executeQuery(query);

            qDebug() << "NAME CARD : " << res;

            
            //std::string valueStr=std::to_string(valueCard);
            //welcomeLabel->setText(QString::fromStdString(std::string("Bienvenue au patient n° ") + valueStr));
            cardMem->unlock();

            introLabel->setText("Maintenant, veuillez appuyer sur le bouton \"Commencer\"");
            startButton->setText("Commencer");
            connect(startButton, SIGNAL(clicked()), this, SLOT(start2()));
            run=false;
        }
        sleep(1);
    
*/