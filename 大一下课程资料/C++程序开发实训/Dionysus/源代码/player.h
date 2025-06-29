#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QDataStream>
#include <QFile>
#include <QVector>
#include "gamerecord.h"
#include "map.h"
class Player
{
public:
    //默认构造
    Player();
    //重载流运算符以及深拷贝
    friend QDataStream &operator<<(QDataStream &out, const Player &player);
    friend QDataStream &operator>>(QDataStream &in, Player &player);
    Player &operator=(const Player &other);
    //设置，修改Player数据
    bool setAccount(QString);
    bool setPassword(QString);
    void setIndex(int a){accountIndex = a;}
    void setStartPos(qint64 posInFile){StartPos = posInFile;}
    void setDormitoryNumber(QString a){dormitoryNumber = a;}
    void setPhoneNumber(QString number){phoneNumber = number;}
    void revisePassword(QString newPassword);
    void reInitialize();
    //数据接口
    QString getAccount(){return account;}
    QString getPassword(){return password;}
    int getIndex(){return accountIndex;}
    Map &getPlayMap(){return playMap;}
    qint64 getStartPos(){return StartPos;}
    QString getDormitoryNumber(){return dormitoryNumber;}
    QString getPhoneNumber(){return phoneNumber;}
    GameRecord  &getPracticeRecord(){return practiceGameRecords;}
    GameRecord &getCompetitionRecord(){return competitionGameRecords;}
    GameRecord &getEndlessCompetitonRecord(){return endless_competitionRecord;}
    GameRecord &getEndlessPracticeRecord(){return endless_practiceRecord;}

private:
    //账号初始化
    QString account;
    QString password;
    int accountIndex;
    qint64 StartPos;
    //密保问题
    QString dormitoryNumber;
    QString phoneNumber;
    //游戏记录
    GameRecord practiceGameRecords;
    GameRecord competitionGameRecords;//完成游戏才添加记录
    GameRecord endless_practiceRecord;
    GameRecord endless_competitionRecord;
    Map playMap;

};

#endif // PLAYER_H
