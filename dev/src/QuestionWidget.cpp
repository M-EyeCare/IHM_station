#include "QuestionWidget.h"

QuestionWidget::QuestionWidget(char* question, char* consigne, char* key, std::map<char* , bool> *responseMap, QWidget *parent) : QWidget(parent)
{

    consigneLabel = new QLabel(this);
    QString consigneText = "<html><body><p style='font-size:18pt;font-weight:bold;'>" + QString(consigne) + "</p></body></html>";
    consigneLabel->setText(consigneText);
    consigneLabel->setProperty("class", "consigneLabel");
    
    questionLabel = new QLabel(this);
    questionLabel->setText(QString(question));
    questionLabel->setProperty("class", "questionLabel");

    this->key=key;
    this->responseMap=responseMap;
    
    yesButton = new QPushButton("Oui", this);
    yesButton->setProperty("class", "yesButton");

    noButton = new QPushButton("Non", this);
    noButton->setProperty("class", "noButton");

    prevButton = new QPushButton("< Retour", this);

    //nextButton = new QPushButton("Suivant >", this);

    layout = new QGridLayout(this);
    layout->addWidget(consigneLabel, 0, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(questionLabel, 1, 0, 1, 2, Qt::AlignCenter);
    layout->addWidget(yesButton, 2, 0, 1, 1, Qt::AlignCenter | Qt::AlignRight);
    layout->addWidget(noButton, 2, 1, 1, 1, Qt::AlignCenter | Qt::AlignLeft);
    layout->addWidget(prevButton, 3, 0, 1, 1, Qt::AlignLeft);
    
    //connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(prevButton, SIGNAL(clicked()), this, SLOT(previous())); 
    connect(yesButton, SIGNAL(clicked()), this, SLOT(respondTrue()));
    connect(noButton, SIGNAL(clicked()), this, SLOT(respondFalse()));


}

void QuestionWidget::next()
{
    emit(nextSig());
}

void QuestionWidget::previous()
{
    emit(previousSig());
}

void QuestionWidget::respondTrue()
{
    nextButton = new QPushButton("Suivant >", this);
    layout->addWidget(nextButton, 3, 1, 1, 1, Qt::AlignRight);
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));

    responseMap->insert(std::make_pair(key, true));
    emit(nextSig());
}

void QuestionWidget::respondFalse()
{
    nextButton = new QPushButton("Suivant >", this);
    layout->addWidget(nextButton, 3, 1, 1, 1, Qt::AlignRight);
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));

    responseMap->insert(std::make_pair(key, false));
    emit(nextSig());
}


