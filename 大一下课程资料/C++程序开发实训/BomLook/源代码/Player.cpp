#include "Player.h"

//构造函数初始化
Player::Player():
    m_id(-1),m_pwd("123456"),m_userName("tourist"),m_levelNeedUpdate(0)
{
    m_time=new long long[13];
    m_steps=new int [13];
    m_backSteps=new int [13];
    m_hasPlayed=new bool [13];
    for(int i=0;i<=12;i++)
    {
        m_time[i]=INT_MAX;
        m_steps[i]=INT_MAX;
        m_backSteps[i]=INT_MAX;
        m_hasPlayed[i]=false;
    }
}

Player::~Player()
{
    if(m_time!=nullptr)
    {
        delete []m_time;
        m_time=nullptr;
    }
    if(m_steps!=nullptr)
    {
        delete []m_steps;
        m_steps=nullptr;
    }
    if(m_backSteps!=nullptr)
    {
        delete []m_backSteps;
        m_backSteps=nullptr;
    }
    if(m_hasPlayed)
    {
        delete []m_hasPlayed;
        m_hasPlayed=nullptr;
    }
}

//设置用户名
void Player::setUserName(const QString UserName)
{
    m_userName=UserName;
}

//设置用户密码
void Player::setPwd(const QString Pwd)
{
    m_pwd=Pwd;
}

//设置某个关卡对应的时间
void Player::setTime(const long long Time,const int level)
{
    m_time[level]=Time;
}

//设置某个关卡对应的操作步数
void Player::setSteps(const int steps,const int level)
{
    m_steps[level]=steps;
}

//设置某个关卡对应的回退步数
void Player::setBackSteps(const int burnSteps,const int level)
{
    m_backSteps[level]=burnSteps;
}

//设置用户的ID
void Player::setID(const int ID)
{
    m_id=ID;
}

//获取用户的名字
QString Player::getUserName()const
{
    return m_userName;
}

//获取用户的密码
QString Player::getPwd()const
{
    return m_pwd;
}

//获取某个关卡的操作步数
int Player::getSteps(const int level)const
{
    return m_steps[level];
}

//获取某个关卡的回退步数
int Player::getBackSteps(const int level)const
{
    return m_backSteps[level];
}

//获取某个关卡花费的时间
long long Player::getTime(const int level)const
{
    return m_time[level];
}

//获取用户的ID
int Player::getID()const
{
    return m_id;
}

//获取总ID
int Player::getTotID()const
{
    return totID;
}

//更新总ID
void Player::totIDadd()
{
    totID++;
}

//设置当前需要更新的关卡
void Player::setLevelneedUpdate(const int level)
{
    m_levelNeedUpdate=level;
}

//获取当前需要更新的关卡
int Player::getLevelNeedUpdate()const
{
    return m_levelNeedUpdate;
}

//设置某个关卡的游玩状态：已经游玩或者没有游玩
void Player::setHasPlayed(const bool hasPlayed,const int level)
{
    m_hasPlayed[level]=hasPlayed;
}

//获取某个关卡的游玩状态：已经游玩或者没有游玩
bool Player::getHasPlayed(const int level)const
{
    return m_hasPlayed[level];
}

//退出账号时重新初始化数据
void Player::original()
{
    m_id=-1;
    m_pwd="123456";
    m_userName="tourist";
    m_levelNeedUpdate=0;
    for(int i=0;i<=12;i++)
    {
        m_time[i]=INT_MAX;
        m_steps[i]=INT_MAX;
        m_backSteps[i]=INT_MAX;
        m_hasPlayed[i]=false;
    }
}

//重载<<运算符，使得能够输出Player类数据
QDataStream& operator<<(QDataStream &out,const Player &player)
{
    out<<player.m_id<<player.m_userName<<player.m_pwd;
    for(int i=1;i<=12;i++)
    {
        out<<player.m_hasPlayed[i]<<player.m_time[i]<<player.m_steps[i]<<player.m_backSteps[i];
    }
    return out;
}

//重载>>运算符，使得能够输入Player类数据
QDataStream& operator>>(QDataStream &in,Player &account)
{
    in>>account.m_id>>account.m_userName>>account.m_pwd;
    for(int i=1;i<=12;i++)
    {
        in>>account.m_hasPlayed[i]>>account.m_time[i]>>account.m_steps[i]>>account.m_backSteps[i];
    }
    return in;
}

int Player::totID=0;
