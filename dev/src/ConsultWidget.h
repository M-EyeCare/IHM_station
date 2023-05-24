#ifndef __CONSULTWIDGET_H__
#define __CONSULTWIDGET_H__

#include <iostream>
#include <QWidget>
#include <QtCharts>
#include <QtCore>
#include <QTimer>
#include "SensorWidget.h"

class ConsultWidget : public QStackedWidget
{
    Q_OBJECT
public:

    QStackedWidget *stackedWidget;
    std::map<std::string, bool> *responseMap;
    float temperature;
    float bpm;
    float bcpm;
    float sweatingRate;


    ConsultWidget(QWidget * parent=nullptr);

public slots:
    void nextWidget();
    void previousWidget();


};
#endif // __CONSULTWIDGET_H__