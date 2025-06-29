#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H
#include <qpropertyanimation.h>
#include <QPushButton>
#include <QDialog>
#include <QGridLayout>
#include <QTableWidget>
#include <QMessageBox>
#include <QLabel>
#include <QThread>
#include <QMutex>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QTimer>
class MyPushButton : public QPushButton
{
public:
    explicit MyPushButton(QWidget *parent = nullptr):QPushButton(parent){};
    //正常显示和按下显示的图片路径
    MyPushButton(QString normalImg, QString pressImg = "");
    //弹跳特效
    void zoom1();
    void zoom2();

private:
    QString normalImgPath;
    QString pressImgPath;
};

class MyDialog : public QDialog {//提示框的dialog
    Q_OBJECT
public:
    MyDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("提示");
        resize(300, 100);

        QVBoxLayout *layout = new QVBoxLayout(this);
        label = new QLabel("操作进行中...", this);
        layout->addWidget(label);

        QPushButton *closeButton = new QPushButton("关闭", this);
        layout->addWidget(closeButton);

        connect(closeButton, &QPushButton::clicked, this, &MyDialog::close);
    }

    void updateLabelText(int amount) {
        if(amount != 0)
            label->setText(QString("当前地图共有" + QString::number(amount) + "个解\n关闭该窗口后再次点击，可以根据目前放置的切片给出提示"));
        else
            label->setText(QString("您的地图无解"));
    }

private:
    QLabel *label;
};


class errorProtectQuestionDialog : public QDialog
{
    Q_OBJECT
public:
    errorProtectQuestionDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        //分配内存
        this->setFixedSize(500,300);
        QLabel *message = new QLabel("这都能把你宿舍号和手机号忘了？给你些选择",this);
        QPushButton *watchVideoBtn = new QPushButton("看一个133大片，直接允许修改密码",this);
        QPushButton *retryBtn = new QPushButton("重试",this);
        QPushButton *challengeBtn = new QPushButton("测测你的知识水平",this);
        QGridLayout *mainLayout = new QGridLayout(this);

        mainLayout->addWidget(message,0,0,1,2);
        mainLayout->addWidget(watchVideoBtn,2,0,1,2);
        mainLayout->addWidget(retryBtn,3,0,1,2);
        mainLayout->addWidget(challengeBtn,4,0,1,2);

        this->setLayout(mainLayout);
        connect(retryBtn,&QPushButton::clicked,[=](){

            emit showFindPassWordWidget();
            this->close();
        });
    }
signals:
    void showFindPassWordWidget();
};



class inputDialog : public QDialog
{
    Q_OBJECT
public:
    void input();
    int* getDataFromTable();

public slots:
    bool checkData();
private:
    QTableWidget *inputTable;
};


class selectModeDialog : public QDialog
{
    Q_OBJECT

signals:
    void customMapButtonClicked();
    void othersMapButtonClicked();
public:
    selectModeDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        mapSelection();
    }
    void mapSelection()
    {
        this->setFixedSize(300,200);
        // 创建按钮
        MyPushButton *customMapButton = new MyPushButton(this);
        customMapButton->setText("自定义地图");
        customMapButton->setFixedHeight(100);
        MyPushButton *othersMapButton = new MyPushButton(this);
        othersMapButton->setText("加载其他玩家的地图");
        othersMapButton->setFixedHeight(100);
        // 添加按钮点击信号与槽
        connect(customMapButton, &QPushButton::clicked, this, &selectModeDialog::customMapButtonClicked);
        connect(othersMapButton, &QPushButton::clicked, this, &selectModeDialog::othersMapButtonClicked);

        // 创建布局
        QHBoxLayout *layout = new QHBoxLayout(this);
        layout->addWidget(customMapButton);
        layout->addWidget(othersMapButton);

        // 设置对话框属性
        setWindowTitle("地图选择");
        setLayout(layout);
        setModal(true); // 使对话框为模态，用户必须响应后才能继续
    }

};
#endif // MYCONTROLLER_H
