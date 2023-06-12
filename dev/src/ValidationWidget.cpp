#include "ValidationWidget.h"

ValidationWidget::ValidationWidget(QString logoPath, QWidget *parent) : QWidget(parent)
{
    this->responseMap = responseMap;

    topLabel = new QLabel();
    QFont boldFont;
    boldFont.setBold(true);
    topLabel->setFont(boldFont);
    topLabel->setText("Merci d'avoir choisi M'EyeConsult !");

    midLabel = new QLabel();
    midLabel->setText("Votre diagnostic est terminé. Veuillez appuyer sur \"Valider\" pour terminer la consultation.");

    bottomLabel = new QLabel();
    bottomLabel->setText("Un médecin va prendre en charge votre consultation.");

    siteLabel = new QLabel();
    QFont boldItalicFont;
    boldItalicFont.setBold(true);
    boldItalicFont.setItalic(true);
    siteLabel->setFont(boldItalicFont);

    //QPalette palette;
    //palette.setColor(QPalette::Text, QColor("#ADD8E6")); // Couleur bleu clair
    //siteLabel->setPalette(palette);

    QString siteText = "Retrouvez vos résultats sur ";
    siteText += "<span style=\"color:#0f84b8\"><i>meyeconsult.alwaysdata.net</i></span>";
    siteLabel->setText(siteText);
    siteLabel->setOpenExternalLinks(true);
    siteLabel->setTextFormat(Qt::RichText);

    //Logo
    QPixmap notImg(logoPath);
    QLabel * logoLabel= new QLabel();
    logoLabel->setPixmap(notImg.scaled(500,500,Qt::KeepAspectRatio));
    logoLabel->setAlignment(Qt::AlignCenter);

    prevButton = new QPushButton("< Retour",this);
    confirmButton = new QPushButton("Valider",this);

    layout=new QGridLayout(this);
    layout->addWidget(topLabel,0,0,Qt::AlignCenter);
    layout->addWidget(logoLabel, 1, 0,Qt::AlignCenter);
    layout->addWidget(midLabel,2,0,Qt::AlignCenter);
    layout->addWidget(confirmButton,3,0,Qt::AlignCenter);
    layout->addWidget(bottomLabel,4,0,Qt::AlignCenter);
    layout->addWidget(siteLabel,5,0,Qt::AlignCenter);
    layout->addWidget(prevButton,6,0,Qt::AlignLeft);

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