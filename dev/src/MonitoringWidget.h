#ifndef __MONITORINGWIDGET_H__
#define __MONITORINGWIDGET_H__

#include <iostream>
#include <QWidget>
#include <QtCharts>
#include <QtCore>
#include <QTimer>
#include "MonitoringThread.h"

class MonitoringWidget : public QWidget
{

    Q_OBJECT

public:

    MonitoringThread* monitor_thread;

    QSharedMemory * bpm_mem;

    int time;
    QChart *tempChart;
    QChart *bpmChart;
    QChart *pressureChart;
    QChart *sweatingChart;

    QTimer *updateTimer;
    
    QLineSeries *tempSeries;
    QLineSeries *bpmSeries;
    QLineSeries *pressureSeries;
    QLineSeries *sweatingSeries;

    QAreaSeries *bpmArea;

    QGridLayout *gridLayout;

    QChartView *tempChartView;
    QChartView *bpmChartView;
    QChartView *pressureChartView;
    QChartView *sweatingChartView;

    MonitoringWidget(QWidget * parent=nullptr);
public slots:
    void updaterSlot();


};

#endif // __MONITORINGWIDGET_H__