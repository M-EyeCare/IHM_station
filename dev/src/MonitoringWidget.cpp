#include "MonitoringWidget.h"

MonitoringWidget::MonitoringWidget(QWidget *parent) : QWidget(parent)
{
    
    tempChart = new QChart();
    bpmChart = new QChart();
    breathChart = new QChart();
    sweatingChart = new QChart();

    tempSeries = new QLineSeries();
    bpmSeries = new QLineSeries();
    breathSeries = new QLineSeries();
    sweatingSeries = new QLineSeries();

    tempChart->addSeries(tempSeries);
    tempChart->legend()->hide();
    tempChart->createDefaultAxes();
    tempChart->setTitle("Temperature");

    bpmChart->addSeries(bpmSeries);
    bpmChart->legend()->hide();
    bpmChart->createDefaultAxes();
    bpmChart->setTitle("Heartbeat");

    breathChart->addSeries(breathSeries);
    breathChart->legend()->hide();
    breathChart->createDefaultAxes();
    breathChart->setTitle("Breathing");

    sweatingChart->addSeries(sweatingSeries);
    sweatingChart->legend()->hide();
    sweatingChart->createDefaultAxes();
    sweatingChart->setTitle("Sweating");

    tempChartView = new QChartView(this->tempChart);
    tempChartView->setRenderHint(QPainter::Antialiasing);

    bpmChartView = new QChartView(this->bpmChart);
    bpmChartView->setRenderHint(QPainter::Antialiasing);

    breathChartView = new QChartView(this->breathChart);
    breathChartView->setRenderHint(QPainter::Antialiasing);

    sweatingChartView = new QChartView(this->sweatingChart);
    sweatingChartView->setRenderHint(QPainter::Antialiasing);

    gridLayout = new QGridLayout(this);
    gridLayout->addWidget(this->tempChartView, 0, 0);
    gridLayout->addWidget(this->bpmChartView, 0, 1);
    gridLayout->addWidget(this->breathChartView, 1, 0);
    gridLayout->addWidget(this->sweatingChartView, 1, 1);

    bpmMem = new QSharedMemory();
    bpmMem->setKey("BPM");
    bpmMem->create(32);
    bpmMem->attach();
    
    tempMem = new QSharedMemory();
    tempMem->setKey("TEMP");
    tempMem->create(32);
    tempMem->attach();

    breathMem = new QSharedMemory();
    breathMem->setKey("BREATH");
    breathMem->create(32);
    breathMem->attach();

    sweatingMem = new QSharedMemory();
    sweatingMem->setKey("SWEATING");
    sweatingMem->create(32);
    sweatingMem->attach();

    updateTimer=new QTimer(this);
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(update_bpm_chart()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(update_temp_chart()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(update_breath_chart()));
    connect(updateTimer,SIGNAL(timeout()),this,SLOT(update_sweating_chart()));
    updateTimer->start(TIMER_UPDATE_TIME);

    time=0;
}

void MonitoringWidget::update_bpm_chart()
{
    qDebug()<<"update BPM chart";

    int* data;
    this->bpmMem->lock();
    data = (int*)(this->bpmMem->data());
    this->bpmMem->unlock();
    this->bpmSeries->append(time,*data);
    time+=TIMER_UPDATE_TIME;

    bpmChart->removeSeries(bpmSeries);
    if (bpmSeries->count() > 100)
    {
        bpmSeries->remove(0);
    }
    bpmChart->addSeries(bpmSeries);
    bpmChart->createDefaultAxes();
    bpmChart->axes().begin();
}

void MonitoringWidget::update_temp_chart()
{
    qDebug()<<"update TEMPERATURE chart";

    int* data;
    this->tempMem->lock();
    data = (int*)(this->tempMem->data());
    this->tempMem->unlock();
    this->tempSeries->append(time,*data);

    tempChart->removeSeries(tempSeries);
    if (tempSeries->count() > 100)
    {
        tempSeries->remove(0);
    }
    tempChart->addSeries(tempSeries);
    tempChart->createDefaultAxes();
}

void MonitoringWidget::update_breath_chart()
{
    qDebug()<<"update BREATHING chart";

    int* data;
    this->breathMem->lock();
    data = (int*)(this->breathMem->data());
    this->breathMem->unlock();
    this->breathSeries->append(time,*data);

    breathChart->removeSeries(breathSeries);
    if (breathSeries->count() > 100)
    {
        breathSeries->remove(0);
    }
    breathChart->addSeries(breathSeries);
    breathChart->createDefaultAxes();
}

void MonitoringWidget::update_sweating_chart()
{
    qDebug()<<"update SWEATING chart";

    int* data;
    this->sweatingMem->lock();
    data = (int*)(this->sweatingMem->data());
    this->sweatingMem->unlock();
    this->sweatingSeries->append(time,*data);

    sweatingChart ->removeSeries(sweatingSeries);
    if (sweatingSeries->count() > 100)
    {
        sweatingSeries->remove(0);
    }
    sweatingChart ->addSeries(sweatingSeries);
    sweatingChart ->createDefaultAxes();
}
