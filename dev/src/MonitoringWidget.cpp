#include <MonitoringWidget.h>
#include <iostream>

MonitoringWidget::MonitoringWidget():MonitoringWidget(nullptr)
{
    
}

MonitoringWidget::MonitoringWidget(QWidget * parent):QWidget(parent)
{
    this->tempChart=new QChart();
    this->bpmChart=new QChart();
    this->pressureChart=new QChart();
    this->sweatingChart=new QChart();

    this->tempSeries= new QLineSeries();
    this->bpmSeries= new QLineSeries();
    this->pressureSeries= new QLineSeries();
    this->sweatingSeries =new QLineSeries();

    this->bpmArea=new QAreaSeries(this->bpmSeries);
    this->bpmArea->setColor(Qt::red);
    this->bpmArea->setBorderColor(Qt::black);

// TEST SERIES
    tempSeries->append(0,1);
    tempSeries->append(1,2);
    tempSeries->append(2,1);

    bpmSeries->append(0,1);
    bpmSeries->append(2,3);
    bpmSeries->append(3,8);  
    
    pressureSeries->append(0,1);
    pressureSeries->append(2,3);
    pressureSeries->append(3,8);

    sweatingSeries->append(0,1);
    sweatingSeries->append(2,3);
    sweatingSeries->append(3,8);


    
    this->tempChart->addSeries(tempSeries);
    this->tempChart->legend()->hide();
    this->tempChart->createDefaultAxes();
    this->tempChart->setTitle("Temperature");

    this->bpmChart->addSeries(bpmArea);
    this->bpmChart->legend()->hide();
    this->bpmChart->createDefaultAxes();
    this->bpmChart->setTitle("Pulsations cardiaques");

    this->pressureChart->addSeries(pressureSeries);
    this->pressureChart->legend()->hide();
    this->pressureChart->createDefaultAxes();
    this->pressureChart->setTitle("Respiration");

    this->sweatingChart->addSeries(sweatingSeries);
    this->sweatingChart->legend()->hide();
    this->sweatingChart->createDefaultAxes();
    this->sweatingChart->setTitle("Transpiration");
    
    std::cout<<"hey"<<std::endl;

    this->tempChartView=new QChartView(this->tempChart);
    this->tempChartView->setRenderHint(QPainter::Antialiasing);


    this->bpmChartView=new QChartView(this->bpmChart);
    this->bpmChartView->setRenderHint(QPainter::Antialiasing);

    this->pressureChartView=new QChartView(this->pressureChart);
    this->pressureChartView->setRenderHint(QPainter::Antialiasing);

    this->sweatingChartView=new QChartView(this->sweatingChart);
    this->sweatingChartView->setRenderHint(QPainter::Antialiasing);

    std::cout<<"hey"<<std::endl;

    this->gridLayout=new QGridLayout(this);
    gridLayout->addWidget(this->tempChartView,0,0);
    gridLayout->addWidget(this->bpmChartView,0,1);
    gridLayout->addWidget(this->pressureChartView,1,0);
    gridLayout->addWidget(this->sweatingChartView,1,1);

}


