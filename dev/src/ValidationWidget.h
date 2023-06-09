#ifndef __VALIDATIONWIDGET_H__
#define __VALIDATIONWIDGET_H__

#include <QtCore>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <iostream>
#include <QGridLayout>

class ValidationWidget : public QWidget
{
    Q_OBJECT

protected:
    QPushButton *prevButton;
    QPushButton *confirmButton;
    QLabel *topLabel;
    QLabel *midLabel;
    QLabel *bottomLabel;
    QGridLayout *layout;
    QSharedMemory * questMem;
    std::map<char*, bool> *responseMap;

public:
    ValidationWidget(std::map<char *, bool> *responseMap, QWidget *parent = nullptr);

public slots:
    void confirm();

signals:
    void confirmSig();
    void previousSig();

};
#endif // __VALIDATIONWIDGET_H__