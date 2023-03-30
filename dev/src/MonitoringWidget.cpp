#include "MonitoringWidget.h"

MonitoringWidget::MonitoringWidget(QWidget *parent) : QWidget(parent)
{
    
    tempChart = new QChart();
    bpmChart = new QChart();
    pressureChart = new QChart();
    sweatingChart = new QChart();

    tempSeries = new QLineSeries();
    bpmSeries = new QLineSeries();
    pressureSeries = new QLineSeries();
    sweatingSeries = new QLineSeries();


    // TEST SERIES*
    // bpmSeries->append(0,0);
    // bpmSeries->append(1000,1);

    tempSeries->append(0, 1);
    tempSeries->append(1, 2);
    tempSeries->append(2, 1);

    pressureSeries->append(0, 1);
    pressureSeries->append(2, 3);
    pressureSeries->append(3, 8);

    sweatingSeries->append(0, 1);
    sweatingSeries->append(2, 3);
    sweatingSeries->append(3, 8);

    tempChart->addSeries(tempSeries);
    tempChart->legend()->hide();
    tempChart->createDefaultAxes();
    tempChart->setTitle("Temperature");

    bpmChart->addSeries(bpmSeries);
    bpmChart->legend()->hide();
    bpmChart->createDefaultAxes();
    bpmChart->setTitle("Pulsations cardiaques");

    pressureChart->addSeries(pressureSeries);
    pressureChart->legend()->hide();
    pressureChart->createDefaultAxes();
    pressureChart->setTitle("Respiration");

    sweatingChart->addSeries(sweatingSeries);
    sweatingChart->legend()->hide();
    sweatingChart->createDefaultAxes();
    sweatingChart->setTitle("Transpiration");

    tempChartView = new QChartView(this->tempChart);
    tempChartView->setRenderHint(QPainter::Antialiasing);

    bpmChartView = new QChartView(this->bpmChart);
    bpmChartView->setRenderHint(QPainter::Antialiasing);

    pressureChartView = new QChartView(this->pressureChart);
    pressureChartView->setRenderHint(QPainter::Antialiasing);

    sweatingChartView = new QChartView(this->sweatingChart);
    sweatingChartView->setRenderHint(QPainter::Antialiasing);

    gridLayout = new QGridLayout(this);

    gridLayout->addWidget(this->tempChartView, 0, 0);
    gridLayout->addWidget(this->bpmChartView, 0, 1);
    gridLayout->addWidget(this->pressureChartView, 1, 0);
    gridLayout->addWidget(this->sweatingChartView, 1, 1);

    // monitor_thread=new MonitoringThread(this);
    // monitor_thread->start();
    bpm_mem = new QSharedMemory();
    bpm_mem->setKey("BPM");
    bpm_mem->create(32);
    bpm_mem->attach();

    updateTimer=new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(updaterSlot()));
    updateTimer->start(100);
    time=0;
}


void MonitoringWidget::updaterSlot()
{    
    qDebug()<<"UPDATE";

    int* data;
    qDebug()<<"before lock";
    this->bpm_mem->lock();
    qDebug()<<"before data";
    data = (int*)(this->bpm_mem->data());
    this->bpm_mem->unlock();
    qDebug()<<"Time:"<<time<<"BPM: "<<*data;
    this->bpmSeries->append(time,*data);
    qDebug()<<"data append";
    time++;
    qDebug()<<"time incremented";

    qDebug()<<"sleep";

    bpmChart->removeSeries(bpmSeries);
    if (bpmSeries->count() > 100)
    {
        bpmSeries->remove(0);
    }
    bpmChart->addSeries(bpmSeries);
    bpmChart->createDefaultAxes();
    


}
