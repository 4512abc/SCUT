#include "gamerecord.h"

GameRecord::GameRecord() {

}

void GameRecord::updateRecord(int thisTime)
{
    //更新游戏次数
    successTimes ++;
    //更新总时长
    totalTime += thisTime;
    //更新平均用时
    averageTime = totalTime / successTimes;
    //更新最快用时
    if( thisTime < fastestTime ){
        fastestTime = thisTime;
        qDebug() << fastestTime;
    }
}

void GameRecord::writeToFile(const QString filename,int index)
{
    //先判断先前是否存在
    bool recordIndex_isExist = false;
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    GameRecord record;
    while(!file.atEnd()){
        qDebug() << "2222";
        in >> record;
        qDebug() << record.getIndex() << index;
        if(record.getIndex() == index){
            recordIndex_isExist = true;
            qDebug() << "find index";
        }
    }
    file.close();

    //如果存在，那么修改数据
    if(recordIndex_isExist){
        //获取新数据的二进制表示
        QByteArray newdata;
        //创建qdatastream，写入模式，对象为newdata
        QDataStream out(&newdata, QIODevice::WriteOnly);
        out << *this;
        //获取该用户数据在文件中的偏移量，那么指定就只有这些数据了，因为没有记录起始位置，后续要添加只能在其他文件执行
        int dataGroupSize = sizeof(int) * 4 + sizeof(long long);//增加了写入的成员时候这里要注意
        qint64 modifyPos = index * dataGroupSize;
        //打开文件
        QFile filex(filename);
        //判断是否正常打开
        if(!filex.open(QIODevice::ReadOnly)){
            qDebug() << "Failed to open the file for reading.";
            return;
        }
        //开始读取内容
        QByteArray originalData = filex.readAll();

        filex.close();//关闭文件

        //在指定位置修改数据
        QByteArray updatedData;
        updatedData.reserve(originalData.size() + newdata.size());//完成预分配空间
        updatedData.append(originalData.mid(0,modifyPos));//插入前面的数据
        updatedData.append(newdata);//插入修改新数据
        updatedData.append(originalData.mid(modifyPos + dataGroupSize) );

        //重新打开文件写入
        if(filex.open(QIODevice::WriteOnly)){
            filex.write(updatedData);
            filex.close();
        }
        else {
            qDebug() << "打开文件失败";
            return;
        }
    }

    //如果不存在，把信息写到末尾
    else{
        QFile refile(filename);
        if(refile.open(QIODevice::WriteOnly | QIODevice::Append)){
            QDataStream out(&refile);
            out << *this;
            qDebug() << "321321";
            refile.close();
        }
        else qDebug() << "file cannot be opened";
    }
}


int GameRecord::getAverageTime()
{
    return averageTime;
}

int GameRecord::getfastestTime()
{
    return fastestTime;
}

long long GameRecord::getTotalTime()
{
    return totalTime;
}

int GameRecord::getSuccessTimes()
{
    return successTimes;
}

QDataStream &operator<<(QDataStream &out, const GameRecord &record) {
    out << record.Index << record.successTimes << record.totalTime << record.averageTime
        << record.fastestTime;// 将所有成员变量写入流
    return out;
}

QDataStream &operator>>(QDataStream &in, GameRecord &record) {
    in >> record.Index >> record.successTimes >> record.totalTime >> record.averageTime
        >> record.fastestTime ;// 从流中读取成员变量
    return in;
}

QString GameRecord::convertTimeToString(long long targetTime)
{

    int minutes=(targetTime/(100*60))%60;
    int seconds=(targetTime/100)%60;
    int milliseconds=targetTime%100;

    QString timeString=QString("%1:%2:%3").arg(minutes,2,10,QChar('0'))
                             .arg(seconds,2,10,QChar('0'))
                             .arg(milliseconds,2,10,QChar('0'));
    return timeString;
}

long long GameRecord::convertStringToTime(const QString &timeString)
{
    int minutes, seconds, milliseconds;
    bool ok;

    // 创建正则表达式
    QRegularExpression regex(QStringLiteral("^([0-9]{2}):([0-9]{2}):([0-9]{2})$"));

    // 搜索匹配
    QRegularExpressionMatch match = regex.match(timeString);
    if (!match.hasMatch()) {
        // 处理格式错误
        throw std::runtime_error("Invalid time format");
    }

    // 解析时间字符串
    minutes = match.captured(1).toInt(&ok);
    Q_ASSERT(ok);
    seconds = match.captured(2).toInt(&ok);
    Q_ASSERT(ok);
    milliseconds = match.captured(3).toInt(&ok);
    Q_ASSERT(ok);

    // 计算总毫秒数
    long long totalTime = (minutes * 60LL * 1000) + (seconds * 1000) + milliseconds;

    return totalTime;
}

GameRecord GameRecord::matchRecord(const QString filename)
{
    GameRecord record;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
        QDataStream in(&file);
        while (!file.atEnd()){
            in >> record;
            if(record.getIndex() == Index){
                *this = record;//找到了，返回
                qDebug() << "1111";
            }
        }
        //没找到，那其实无所谓，还是空的，已经完成索引号匹配，玩完游戏写到末尾就好
    }
    file.close();
}
