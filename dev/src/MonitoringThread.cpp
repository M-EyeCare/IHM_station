#include "MonitoringThread.h"
#include "MonitoringWidget.h"


MonitoringThread::MonitoringThread(MonitoringWidget* monitoringWidget)
{
    qDebug()<<"Monitoring Thread constructor";
    mw=monitoringWidget;

    bpm_mem = new QSharedMemory();
    bpm_mem->setKey("BPM");
    bpm_mem->create(32);
    bpm_mem->attach();

    time=0;
    connect(this,SIGNAL (timeout()),mw,SLOT(update()));

}


void MonitoringThread::run()
{
    qDebug()<<"run start\n";
    int* data;
    while(1){
        qDebug()<<"LOOD STARTED";

        qDebug()<<"before lock";
        this->bpm_mem->lock();
        qDebug()<<"before data";
        data = (int*)(this->bpm_mem->data());
        this->bpm_mem->unlock();
        qDebug()<<"Time:"<<time<<"BPM: "<<*data;
        mw->bpmSeries->append(time,*data);
        qDebug()<<"data append";
        time++;
        qDebug()<<"time incremented";

        msleep(100);
        qDebug()<<"sleep";

        qDebug()<<"LOOD ENDED";

    }
}