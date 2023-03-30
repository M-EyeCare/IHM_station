#ifndef __MONITORINGTHREAD_H__
#define __MONITORINGTHREAD_H__

#include <QtCore>
#include <QDebug>
#include <iostream>
// #include "MonitoringWidget.h"
class MonitoringWidget;

class MonitoringThread: public QThread{
    protected:
        MonitoringWidget* mw;
        QSharedMemory * bpm_mem;
        int time;

    public:
        MonitoringThread(MonitoringWidget* monitoringWidget);
        void run();
};


#endif // __MONITORINGTHREAD_H__