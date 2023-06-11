#ifndef __CONSULTWIDGET_H__
#define __CONSULTWIDGET_H__

#include <iostream>
#include <QWidget>
#include <QtCharts>
#include <QtCore>
#include <QTimer>
#include <QSharedMemory>
#include "SensorWidget.h"
#include "QuestionWidget.h"
#include "WelcomeWidget.h"
#include "ValidationWidget.h"
#include <time.h>

class ConsultWidget : public QStackedWidget
{
    Q_OBJECT
public:

    std::map<char *, bool> *responseMap;
    QSharedMemory *questionMem;
    int temperature;
    int bpm;
    int bcpm;
    int sweatingRate;
    int id;

    WelcomeWidget *welcomeWidget;

    SensorWidget *bpmWidget;
    SensorWidget *sweatingWidget;
    SensorWidget *breathWidget;
    SensorWidget *tempWidget;

    QuestionWidget *headacheWidget;
    QuestionWidget *stomacacheWigget;
    QuestionWidget *backacheWidget;
    QuestionWidget *throatacheWidget;
    QuestionWidget *breathingacheWidget;
    QuestionWidget *otheracheWidget;
    QuestionWidget *nauseasWidget;
    QuestionWidget *tiredWidget;
    QuestionWidget *sleepingWidget;
    QuestionWidget *treatmentWidget;
    QuestionWidget *rashesWidget;
    QuestionWidget *smokingWidget;

    ValidationWidget *validationWidget;

    ConsultWidget(QWidget * parent=nullptr);

public slots:
    void debug();
    void nextWidget();
    void previousWidget();
    void reset();
};
#endif // __CONSULTWIDGET_H__