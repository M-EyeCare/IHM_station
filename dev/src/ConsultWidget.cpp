#include "ConsultWidget.h"

ConsultWidget::ConsultWidget(QWidget * parent) : QStackedWidget(parent)
{

    responseMap = new std::map<std::string,bool>();


    SensorWidget * bpmWidget= new SensorWidget("BPM", &bpm, "../img/bpmNotice.png",this);

    this->addWidget(bpmWidget);
    connect(bpmWidget, SIGNAL(confirmed()), this, SLOT(nextWidget()));

}

void ConsultWidget::nextWidget()
{
    this->setCurrentIndex(stackedWidget->currentIndex()+1);
}

void ConsultWidget::previousWidget()
{
    this->setCurrentIndex(stackedWidget->currentIndex()-1);
}


