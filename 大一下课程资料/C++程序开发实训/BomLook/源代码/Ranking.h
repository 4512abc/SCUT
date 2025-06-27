#ifndef RANKING_H
#define RANKING_H

#include <QWidget>
#include <QListView>
#include <QStandardItem>
#include <QSortFilterProxyModel>
#include <QFile>
#include "Player.h"
namespace Ui {
class Ranking;
}

class Ranking : public QWidget
{
    Q_OBJECT

public:
    explicit Ranking(QWidget *parent = nullptr,Player *onlinePlayer=nullptr);
    ~Ranking();
    void loadData(const int level);                     //负责从文件导入原始数据，生成排行榜
    void updateData(const int level);                   //负责对文件数据进行更新，并且导入文件
    void updateRanking(const int levelNeedUpdate);      //负责对排行榜的内容进行实时更新
    void updateTimeModel();                             //对时间排行榜进行更新，并且显示
    void updateScoreModel();                            //对分数排行榜进行更新，并且显示
    struct myData                                       //封装的一个小用户信息类，用于接受游戏记录
    {
        QString m_name;     //用户名
        int time;           //时间
        int score;          //分数
    };
private:
    Ui::Ranking *ui;
    QStandardItemModel *time_model;     //时间model
    QStandardItemModel *score_model;    //分数model
    Player *m_player;                   //用户类指针，用来指向当前游玩的用户
    std::vector<myData> playerData[13];     //vector，用于接收12个文件关卡的游戏数据
};


#endif // RANKING_H
