#include "WelcomeWidget.h"

WelcomeWidget::WelcomeWidget(int *valueId, QString logoPath, QString welcome, QString intro, QString name, QWidget *parent) : QWidget(parent)
{
    /*sensorMem = new QSharedMemory();
    sensorMem->setKey(memKey);
    sensorMem->attach();

    this->memKey = memKey.toStdString();

    activationMem = new QSharedMemory();
    activationMem->setKey("ACT");

    activationMem->attach();*/

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

    this->valueId = valueId;

    startButton = new QPushButton("Commencer", this);
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
    emit(nextSig());
}


