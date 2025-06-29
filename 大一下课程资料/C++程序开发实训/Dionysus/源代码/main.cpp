#include "mainscene.h"
#include <QApplication>
#include "player.h"
#include "config.h"
#include <QFile>
#include "map.h"
int main(int argc, char *argv[])
{

    QFile file(ACCOUNTLISTROAD);
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
    {
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_5); // 使用你的Qt版本

        // 从文件中读取Player对象
        while(!in.atEnd()){
            Player player;
            in >> player;
            qDebug() << player.getIndex() << player.getAccount() << player.getPassword()
                     << player.getStartPos() << player.getDormitoryNumber()
                     << player.getPhoneNumber();
        }

        file.close();
    }
    else qDebug() << "无法打开文件：" << file.errorString();

    //测试游戏记录读写
    // QFile filea(PRACTICE_RECORD_PATH);
    // filea.open(QIODevice::ReadOnly);
    // QDataStream in(&filea);
    // GameRecord record;
    // while(!filea.atEnd()){
    //     in >> record;
    //     qDebug() << record.getAverageTime() << record.getSuccessTimes();
    // }
    // filea.close();

    //写入地图
    // QFile filea(COMPETITION_MAP_ROAD);
    // filea.open(QIODevice::WriteOnly|QIODevice::Append);
    // int array[36] = {1,3,3,1,1,0, 1,4,3,1,1,0,
    //                  1,2,2,1,1,0, 1,2,2,1,1,0,
    //                  1,1,1,1,1,1, 1,1,1,0,1,1};//从左到右，从上到下，先做练习模式试试看
    // if(filea.isOpen())
    // {
    //     QDataStream out(&filea);
    //     out.setVersion(QDataStream::Qt_6_5);
    //     for (int i = 0; i < 36; ++i) {
    //         out << array[i];
    //     }
    //     filea.close();
    // }

    //测试地图的加载
    Map map;
    map.loadSliceRandomly();

    //测试地图是否有解：
    map.convertMapToElement(practiceMode);
    if(map.canBeSolved()){
        qDebug() << "success!!";
    }
    else qDebug() << "failed555";
    // map.testFile();
    //filea.close();

    //测试随机生成地图

    // //测试随机数
    // std::array<std::array<double,4>,4> arr;
    // for (auto& innerArr : arr) {
    //     std::fill_n(innerArr.begin(), innerArr.size(), 0);
    // }//初始化为0

    // for(int i = 0; i < 1000000; i++){
    //     int random_X = QRandomGenerator::global()->bounded(0, 4);
    //     int random_Y = QRandomGenerator::global()->bounded(0, 4);
    //     arr[random_X][random_Y] ++;
    // }
    // for(int i = 0; i < 4; i++){
    //     for(int j = 0; j < 4; j++){
    //         float possibility = arr[i][j] / 1000000 *100 ;
    //         qDebug() << possibility << "%";
    //     }
    // }
    QApplication a(argc, argv);
    // sele m;
    // m.input();
    // m.show();
    MainScene w;
    w.show();
    return a.exec();
}
