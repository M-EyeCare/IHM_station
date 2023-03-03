#include <QWidget>
#include <QtCharts>

class MonitoringWidget : public QWidget
{
protected:
    QChart *tempChart;
    QChart *bpmChart;
    QChart *pressureChart;
    QChart *sweatingChart;
    
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
public:
    MonitoringWidget();
    MonitoringWidget(QWidget * parent);
    void updateChart();


};
