#ifndef __QUESTIONWIDGET_H__
#define __QUESTIONWIDGET_H__

#include <QtCore>
#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <iostream>
#include <QGridLayout>

class QuestionWidget : public QWidget
{
    Q_OBJECT

protected:
    QPushButton *prevButton;
    QPushButton *nextButton;
    QPushButton *yesButton;
    QPushButton *noButton;
    QLabel *questionLabel;
    QLabel *consigneLabel;
    QGridLayout *layout;
    char* key;
    std::map<char*, bool> *responseMap;

public:
    QuestionWidget(char* question, char* consigne, char* key, std::map<char *, bool> *responseMap, QWidget *parent = nullptr);

public slots:
    void next();
    void previous();
    void respondTrue();
    void respondFalse();

signals:
    void nextSig();
    void previousSig();

};

#endif // __QUESTIONWIDGET_H__