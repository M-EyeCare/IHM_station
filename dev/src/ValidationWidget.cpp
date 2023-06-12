#include "ValidationWidget.h"

ValidationWidget::ValidationWidget(QWidget *parent) : QWidget(parent)
{
    this->responseMap = responseMap;

    topLabel = new QLabel();
    topLabel->setText("Merci d'avoir choisi M'EyeConsult !");

    midLabel = new QLabel();
    midLabel->setText("Votre diagnostic est terminé. Veuillez appuyer sur \"Valider\" pour terminer la consultation.");

    bottomLabel = new QLabel();
    bottomLabel->setText("Un médecin va prendre en charge votre consultation.\nRetrouvez vos résultats sur meyeconsult.alwaysdata.net");

    prevButton = new QPushButton("< Retour",this);
    confirmButton = new QPushButton("Valider",this);

    layout=new QGridLayout(this);
    layout->addWidget(topLabel,0,0,Qt::AlignCenter);
    layout->addWidget(midLabel,1,0,Qt::AlignCenter);
    layout->addWidget(confirmButton,2,0,Qt::AlignCenter);
    layout->addWidget(bottomLabel,3,0,Qt::AlignCenter);
    layout->addWidget(prevButton,4,0,Qt::AlignLeft);

    connect(confirmButton, SIGNAL(clicked()), this, SLOT(confirm()));
    connect(prevButton, SIGNAL(clicked()), this, SLOT(previous()));

}

void ValidationWidget::confirm()
{
    qDebug()<<"confirm";
    emit(confirmSig());
}

void ValidationWidget::previous()
{
    emit(previousSig());
}