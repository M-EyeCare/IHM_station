#ifndef __CONSULTWIDGET_H__
#define __CONSULTWIDGET_H__

#include <iostream>
#include <QWidget>
#include <QtCharts>
#include <QtCore>
#include <QTimer>
#include "SensorWidget.h"
#include "QuestionWidget.h"
#include "WelcomeWidget.h"
#include "ValidationWidget.h"

class ConsultWidget : public QStackedWidget
{
    Q_OBJECT
public:

    std::map<char *, bool> *responseMap;
    int temperature;
    int bpm;
    int bcpm;
    int sweatingRate;

    int id;


    ConsultWidget(QWidget * parent=nullptr);

public slots:
    void debug();
    void nextWidget();
    void previousWidget();
};
#endif // __CONSULTWIDGET_H__