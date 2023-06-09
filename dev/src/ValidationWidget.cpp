#include "ValidationWidget.h"

ValidationWidget::ValidationWidget(std::map<char *, bool> *responseMap, QWidget *parent): QWidget(parent)
{
    this->responseMap=responseMap;

    topLabel = new QLabel();
    bottomLabel=new QLabel();

}

void ValidationWidget::confirm()
{
    
}

void ValidationWidget::confirmed()
{
    
}

void ValidationWidget::previousSig()
{
    
}

