#ifndef WADIALOG_H
#define WADIALOG_H

#include <QDialog>

class WADialog : public QDialog
{
    Q_OBJECT
public:
    WADialog(QWidget *parent);
    ~WADialog();
public slots:
    void back();
    void GoOn();
signals:
    void backToMain();
};

#endif // WADIALOG_H
