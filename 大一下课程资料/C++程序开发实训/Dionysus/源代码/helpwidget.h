#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollArea>
#include <QSpacerItem>
#include <QLabel>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPlainTextEdit>
#include <QCheckBox>
#include <QFrame>
class helpWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *returnButton;
    QGridLayout *mainLayout;


public:
    explicit helpWidget(QWidget *parent = nullptr);
    void hideBtn();
    void showBtn();
signals:
    void returnToMainPage();
};

#endif // HELPWIDGET_H
