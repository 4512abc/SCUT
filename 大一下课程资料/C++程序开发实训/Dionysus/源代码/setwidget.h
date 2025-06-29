#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>

#include <QPushButton>
class setWidget : public QWidget
{
    Q_OBJECT
public:
    explicit setWidget(QWidget *parent = nullptr);
signals:
    void returnToMainPage();
};
#endif // SETWIDGET_H
