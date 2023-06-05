#ifndef __MONITORINGWIDGET_H__
#define __MONITORINGWIDGET_H__

#include <iostream>
#include <QWidget>
#include <QtCharts>
#include <QtCore>
#include <QTimer>

#define TIMER_UPDATE_TIME 200 

class MonitoringWidget : public QWidget
{
    Q_OBJECT

public:

    QSharedMemory * bpmMem;
    QSharedMemory * breathMem;
    QSharedMemory * tempMem;
    QSharedMemory * sweatingMem;

    int time;
    QChart *tempChart;
    QChart *bpmChart;
    QChart *breathChart;
    QChart *sweatingChart;

    QTimer *updateTimer;
    
    QLineSeries *tempSeries;
    QLineSeries *bpmSeries;
    QLineSeries *breathSeries;
    QLineSeries *sweatingSeries;

    QGridLayout *gridLayout;

    QChartView *tempChartView;
    QChartView *bpmChartView;
    QChartView *breathChartView;
    QChartView *sweatingChartView;

    MonitoringWidget(QWidget * parent=nullptr);

public slots:
    void update_bpm_chart();
    void update_temp_chart();
    void update_breath_chart();
    void update_sweating_chart();


};

#endif // __MONITORINGWIDGET_H__