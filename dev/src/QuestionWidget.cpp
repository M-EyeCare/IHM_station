#include "QuestionWidget.h"

QuestionWidget::QuestionWidget(char* question, char* key, std::map<char* , bool> *responseMap, QWidget *parent) : QWidget(parent)
{

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

    nextButton = new QPushButton("Suivant >", this);

    layout = new QGridLayout(this);
    layout->addWidget(questionLabel, 0, 0, 0, 2, Qt::AlignCenter);
    layout->addWidget(yesButton, 1, 0, 1, 1, Qt::AlignRight);
    layout->addWidget(noButton, 1, 1, 1, 1, Qt::AlignLeft);
    layout->addWidget(prevButton, 2, 0, 1, 1, Qt::AlignLeft);
    layout->addWidget(nextButton, 2, 1, 1, 1, Qt::AlignRight);
    
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
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
    responseMap->insert(std::make_pair(key, true));
    emit(nextSig());
}

void QuestionWidget::respondFalse()
{
    responseMap->insert(std::make_pair(key, false));
    emit(nextSig());
}


