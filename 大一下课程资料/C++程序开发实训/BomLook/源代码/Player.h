#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QDataStream>
class Player
{
    friend QDataStream& operator<<(QDataStream &out, const Player &account);    //重载<<运算符，使得能够输出Player类数据
    friend QDataStream& operator>>(QDataStream &in, Player &account);           //重载>>运算符，使得能够输入Player类数据
public:
    Player();
    ~Player();
    void setUserName(const QString UserName);                   //设置用户名
    void setPwd(const QString Pwd);                             //设置用户密码
    void setTime(const long long Time,const int level);         //设置某个关卡对应的时间
    void setSteps(const int steps,const int level);             //设置某个关卡对应的操作步数
    void setBackSteps(const int burnSteps,const int level);     //设置某个关卡对应的回退步数
    void setID(const int ID);                   //设置用户的ID
    QString getUserName()const;                 //获取用户的名字
    QString getPwd()const;                      //获取用户的密码
    int getSteps(const int level)const;         //获取某个关卡的操作步数
    int getBackSteps(const int level)const;     //获取某个关卡的回退步数
    long long getTime(const int level)const;    //获取某个关卡花费的时间
    int getID()const;                           //获取用户的ID
    int getTotID()const;                        //获取总ID
    void totIDadd();                            //更新总ID
    void setLevelneedUpdate(const int level);   //设置当前需要更新的关卡
    int getLevelNeedUpdate()const;              //获取当前需要更新的关卡
    void setHasPlayed(const bool hasPlayed,const int level);    //设置某个关卡的游玩状态：已经游玩或者没有游玩
    bool getHasPlayed(const int level)const;                    //获取某个关卡的游玩状态：已经游玩或者没有游玩
    void original();                            //退出账号时重新初始化数据
private:
    QString m_pwd;          //玩家密码
    QString m_userName;     //玩家的用户名
    int m_id;               //玩家的ID
    long long *m_time;      //玩家每个关卡对应的游戏时间
    int *m_steps;           //玩家每个关卡对应的操作步数
    int *m_backSteps;       //玩家每个关卡对应的回退步数
    int m_levelNeedUpdate;      //玩家需要更新游戏记录的关卡
    bool *m_hasPlayed;          //玩家每个关卡是否游玩的记录
    static int totID;           //全部的ID
};

#endif // PLAYER_H
