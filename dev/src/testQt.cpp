#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include <iostream>
#include <QHBoxLayout>
#include <QChart>
#include <MonitoringWidget.h>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QWidget consult;

    MonitoringWidget monitoring;

    QWidget main;

    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->addTab(&monitoring, "Monitoring");
    tabWidget->addTab(&consult, "Consultation");

    QHBoxLayout *mainLayout = new QHBoxLayout(&main);
    mainLayout->addWidget(tabWidget);

    tabWidget->setWindowTitle("TabWidget");
    QPushButton buttonYes("Oui", &consult);
    QPushButton buttonNo ("Non",&consult);

    main.setAutoFillBackground(true);

    main.setPalette(QPalette(QColor(qRgb(20, 20, 30))));
    main.setWindowTitle("Main");
    QRect screenGeometry = main.geometry();
    tabWidget->setAutoFillBackground(true);
    int height1 = screenGeometry.height();
    int width1 = screenGeometry.width();
    std::cout << "height:" << height1 << "width:" << width1 << std::endl;

    main.showFullScreen();
    
    return app.exec();
}
