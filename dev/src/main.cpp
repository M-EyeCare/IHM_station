#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QLabel>
#include <iostream>
#include <QHBoxLayout>
#include <QChart>
#include "MonitoringWidget.h"
#include "ConsultWidget.h"
#include <QFile>

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QDir::setCurrent(qApp->applicationDirPath());
    QFile styleFile("../style/style.qss");
    styleFile.open(QFile::ReadOnly);

    // Apply the loaded stylesheet
    QString style(styleFile.readAll());

    ConsultWidget consult;

    MonitoringWidget monitoring;

    QWidget main;

    QTabWidget *tabWidget = new QTabWidget();
    tabWidget->addTab(&consult, "Consultation");
    tabWidget->addTab(&monitoring, "Monitoring");

    QHBoxLayout *mainLayout = new QHBoxLayout(&main);
    mainLayout->addWidget(tabWidget);

    tabWidget->setWindowTitle("TabWidget");

    main.setAutoFillBackground(true);
    app.setStyleSheet(style);

    main.setWindowTitle("Main");
    QRect screenGeometry = main.geometry();
    tabWidget->setAutoFillBackground(true);

    main.showFullScreen();

    return app.exec();
}
