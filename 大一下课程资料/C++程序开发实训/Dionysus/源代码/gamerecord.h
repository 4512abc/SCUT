#ifndef GAMERECORD_H
#define GAMERECORD_H

#include <QFile>
#include <QDebug>
#include <QRegularExpression>
#include <QByteArray>
#include <QDataStream>
#include <QString>
class GameRecord//每个玩家有一个游戏记录对象，根据序列号匹配
{
public:
    GameRecord();
    friend QDataStream &operator<<(QDataStream &out, const GameRecord &record);
    friend QDataStream &operator>>(QDataStream &in, GameRecord &record);

    void updateRecord(int thisTime);//0为练习模式，1为挑战模式
    void writeToFile(const QString filename, int index);//传入索引号
    GameRecord matchRecord(const QString filename);


    QString convertTimeToString(long long targetTime);
    long long convertStringToTime(const QString &timeString);
    int getAverageTime();
    int getfastestTime();
    long long getTotalTime();
    int getSuccessTimes();

    void setIndex(int a){Index = a;};//玩完游戏都默认存最后，然后索引号和玩家索引号一致，通过这个搜索
    int getIndex(){return Index;}
private:
    int averageTime = 0;
    int fastestTime = INT_MAX;
    long long totalTime = 0;
    int successTimes = 0;
    int Index = INT_MAX - 1;//把索引号也要写入,完成登录之后就在文件中读取
    //如果是尚未游玩，应该是没有办法找到文件中的游戏记录的，没找到就给它添加一条在末尾，完成创建


};

#endif // GAMERECORD_H
