#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>

#include <QGridLayout>
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>
#include <QCheckBox>
#include <QRadioButton>
#include <QFile>
#include <QDataStream>

#include "player.h"
class accountWidget : public QWidget {
    Q_OBJECT
public:
    accountWidget(QWidget *parent = nullptr);
    void onLoginButtonClicked();
    void setOnLoginPlayer(Player &player){onLoginPlayer = &player;}
    GameRecord matchRecord(const QString filename, int index);

public slots:
    //注册账号窗口
    void registerBtnClicked();
    //游客模式游玩
    void onGuestModeContinueClicked();
    void onGuestModeConfirmed();

signals:
    void returnToMainPage();
    void StartPlayWithAccount();
    void StartPlay();//以游客模式开始
private:
    Player *onLoginPlayer;

    QLabel *passWord;
    QLabel *account;
    QPushButton *registerButton;
    QPushButton *loginButton;
    QPushButton *NoAccountBtn;
    QPushButton *returnButton;
    QGridLayout *mainLayout;
    QLineEdit *passwordInput;
    QLineEdit *accountInput;
    QLabel *ImageLabel;
    QPushButton *findPasswordBtn;
    QCheckBox *showPasswordCheckBox;

};
class FindPasswordWidget : public QWidget
{
    Q_OBJECT

public:
    FindPasswordWidget(QWidget *parent = nullptr);
    void readAndStorePositions(qint64 &accountPos, qint64 &passwordPos);
    void modifyPassword(const QString &newPassword);

public slots:
    void continueBtnClicked();//点击继续后执行逻辑
    void toProtectQuesetion();
    void verifyQuestion(QString protectQuestionInput);


private:
    qint64 accountStartPos;
    qint64 passwordEndPos;
    QString orginalPassword;

    qint64 passwordStartPos;

    bool hasAccount = 0;

    Player findpasswordPlayer;

    //第一个页面，账号
    QLabel *account;
    QLineEdit *AccountInput;
    QPushButton *continueBtn;
    //第二个页面，密保问题
    QPushButton *verifyQuestionBtn;
    QLineEdit *protectQuestionInput;
    QLabel *protectQuestion;
    QGridLayout *mainLayout;
    //第三个页面，显示密码，是否修改
    QPushButton *revisePasswordBtn;
    QLabel *showPasswordBtn;
    QPushButton *returnLoginWidget;
    //第四个页面，错误，其他选项
    QLabel *message;
    QPushButton *watchVideoBtn;
    QPushButton *retryBtn;
    QPushButton *registerBtn;

};

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    RegisterWidget(QWidget *parent = nullptr);
    bool registerAccountLogic(QString, QString);
    void writeToFile();
public slots:
    void registerAccount();


private:
    Player registerplayer;

    //第一层页面，注册账号密码
    QLabel *welcome;
    QLabel *poem;
    QLabel *poem2;

    QLabel *introduction2;
    QLabel *account;
    QLabel *password;
    QLabel *confirmPassword;
    QLineEdit *AccountInput;
    QLineEdit *PasswordInput;
    QLineEdit *confirmPasswordInput;
    QCheckBox *showpasswordCheckBox;
    QCheckBox *showConfirmPassWordCheckBox;
    QPushButton *registerBtn;

    //第二层页面，设置密保问题
    QLineEdit *dormitoryInput;
    QLineEdit *phoneNumberInput;
    QPushButton *setProtectQuestionBtn;
    QPushButton *skipBtn;

    QGridLayout *mainLayout;

};

#endif // ACCOUNTWIDGET_H
