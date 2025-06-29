#include "map.h"
#include <QRandomGenerator>
#include <iostream>



void Map::loadSliceFromFile(int mapMode)
{

    int randomNum = 0;

    if(mapMode == practiceMode){
        QFile file(PRACTICEMAPROAD);
        //目前有12张地图，随机加载
        randomNum = QRandomGenerator::global()->bounded(0, 12);//该随机数范围是左闭右开
                                //但读取的顺序是0-11，对的
        qDebug() << randomNum;

        file.open(QIODevice::ReadOnly);
        if(file.isOpen())
        {
            //定位
            qint64 loadPos = randomNum * 36 * sizeof(int);//随机位置*数组大小*int大小
            file.seek(loadPos);

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_6_5); // 使用你的Qt版本

            // 从文件中读取int型地图信息
            for(int i = 0; i<36 ; i++)
            {
                in >> mapInInt[i];
                targetSlice[i].setSliceKind(mapInInt[i]);//给地图和其slice数组都加载进去文档，必要，因为后续还要修改mapinint读入文件方便一些；
            }

            file.close();
        }
        else qDebug() << "无法打开文件：" << file.errorString();
    }

    if(mapMode == competitionMode){
        randomNum = 0;
        QFile file(COMPETITION_MAP_ROAD);
        file.open(QIODevice::ReadOnly);
        if(file.isOpen())
        {
            //定位
            qint64 loadPos = randomNum * 36 * sizeof(int);//随机位置*数组大小*int大小
            file.seek(loadPos);

            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_6_5); // 使用你的Qt版本

            // 从文件中读取int型地图信息
            for(int i = 0; i<36 ; i++)
            {
                in >> mapInInt[i];
                targetSlice[i].setSliceKind(mapInInt[i]);//给地图和其slice数组都加载进去文档，必要，因为后续还要修改mapinint读入文件方便一些；
            }

            file.close();
        }
        else qDebug() << "无法打开文件：" << file.errorString();
    }

}

void Map::loadSliceFromInput(int *arr)
{
    for(int i = 0; i<36; i++){
        mapInInt[i] = arr[i];
        targetSlice[i].setSliceKind(mapInInt[i]);
    }

}

void Map::loadSliceFromOther(int playMode)
{

    if(playMode == practiceMode){
        QFile file(USERDEFINED_RPRATICEMAP_PATH);
        if(file.open(QIODevice::ReadOnly)){
            QDataStream in(&file);
            in.setVersion(QDataStream::Qt_6_5);

            //先读取有多少张地图
            int mapNumber = 0;
            while(!file.atEnd()){
                for(int i = 0 ; i < 36 && !file.atEnd(); i++){
                    in >> mapInInt[i];
                }
                mapNumber++;
            }

            //随机读取地图
            int randomNum = 0;
            randomNum = QRandomGenerator::global()->bounded(0, mapNumber);//该随机数范围是左闭右开
            qint64 loadPos = randomNum * 36 * sizeof(int);//随机位置*数组大小*int大小
            file.seek(loadPos);

            // 从文件中读取int型地图信息
            for(int i = 0; i<36 ; i++)
            {
                in >> mapInInt[i];
                targetSlice[i].setSliceKind(mapInInt[i]);//给地图和其slice数组都加载进去文档，必要，因为后续还要修改mapinint读入文件方便一些；
            }

            file.close();
        }
    }
}

void Map::loadSliceRandomly()
{
    CustomMatrix generater;
    while(!generater.generateMapRandomly());//再次循环直接生成正确地图

    for(int i = 0; i < 6; i++){
        for(int j = 0; j < 6; j++){
            mapInInt[i + (j * 6)] = generater.data[i][j];
            targetSlice[i + (j * 6)].setSliceKind(mapInInt[i + j * 6]);
            qDebug() << mapInInt[ i + j * 6];
        }
    }
    for(int i = 0; i < 7; i++){
        answer_sliceKind[i] = generater.sliceKind[i];
        answer_pos_X[i] = generater.pos_X[i];
        answer_pos_Y[i] = generater.pos_Y[i];
    }
}

void Map::defaultSliceToPut()
{
    sliceToPut[0].setSliceToPutKind(4);
    sliceToPut[1].setSliceToPutKind(3);
    sliceToPut[2].setSliceToPutKind(3);
    sliceToPut[3].setSliceToPutKind(2);
    sliceToPut[4].setSliceToPutKind(2);
    sliceToPut[5].setSliceToPutKind(1);
    sliceToPut[6].setSliceToPutKind(1);
}


void Map::setTargetSlicePixmap(int mapMode)
{
    if(mapMode == practiceMode)
    {
        for(int i = 0; i < 36 ; i++)
        {
            targetSlice[i].setPixmapRoadInPractice();
        }
    }
    if(mapMode == competitionMode)
    {
        for(int i = 0; i < 36 ; i++)
        {
            targetSlice[i].setPixmapRoadInCompetition();
        }
    }
}

void Map::setSliceToPutPixmap()
{
    for(int i = 0; i<7; i++)
    {
        sliceToPut[i].setPixmapRoad();
    }
}
//根据已走过的步数判断，智能一些
QString Map::getTips(QVector<int> sliceKind, QVector<int> numberInArray,
                     QVector<int> dropPos_x, QVector<int> dropPos_y)
{
    //搜索已经放置正确的切片，记录下来正确放置的切片，然后提示没有正确放置的切片

    qDebug() << "当前已经放置了 :" << sliceKind.size() << "张切片";
    int correct[7] = {0,0,0,0,0,0,0};
    for(int i = 0; i < sliceKind.size(); i++){
        for(int j = 0; j < 7; j++){//遍历，玩家放置的顺序不一定与生成顺序一致
            bool hasFindThis = false;
            if(sliceKind[i] == answer_sliceKind[j]){
                qDebug() << "在if判断中，已经加入的步骤" << sliceKind[i] << "*" << sliceKind[i] <<"的位置是放置正确的";
                //注意一下这里行号是Y坐标，列号是X坐标,前面弄反了，怪不得生成的地图对称转换过
                //先找到放置的切片，但是左上角定位在哪里比较麻烦，和updateTargetSlice的方法类似吧，还是必须要switch一下切片类型
                //加一个hasFindThis参数，每个只能找一遍，否则每个切片只有一个答案

                switch (sliceKind[i]) {
                case 1:
                    if(numberInArray[i] / 6 == answer_pos_Y[j] && numberInArray[i] % 6 == answer_pos_X[j]){
                        correct[i] = sliceKind[i];
                        hasFindThis = true;
                    }
                    break;
                case 2:
                    //该图片矩形左上角
                    if(dropPos_x[i] < SLICECHECKCENTER && dropPos_y[i] < SLICECHECKCENTER){
                        //横纵坐标判断
                        if( numberInArray[i] / 6 - 1 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 - 1 == answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];//加入到正确的步骤中
                            hasFindThis = true;
                        }
                    }
                    //该图片矩形框右上角
                    if(dropPos_x[i] > SLICECHECKCENTER && dropPos_y[i] <SLICECHECKCENTER){
                        if( numberInArray[i] / 6 - 1 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 == answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];
                            hasFindThis = true;
                        }
                    }
                    //该图片矩形左下角
                    if(dropPos_x[i] < SLICECHECKCENTER && dropPos_y[i] > SLICECHECKCENTER){
                        if( numberInArray[i] / 6 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 - 1== answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];
                            hasFindThis = true;
                        }
                    }
                    if(dropPos_x[i] > SLICECHECKCENTER && dropPos_y[i] > SLICECHECKCENTER){
                        if( numberInArray[i] / 6 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 == answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];
                            hasFindThis = true;
                        }
                    }
                    break;
                case 3://不需要判断放置位置
                    if(numberInArray[i] / 6 - 1 == answer_pos_Y[j] &&
                        numberInArray[i] % 6 - 1 == answer_pos_X[j])
                    {
                        correct[i] = sliceKind[i];
                        hasFindThis = true;
                    }
                    break;
                case 4:
                    //该图片矩形左上角
                    if(dropPos_x[i] < SLICECHECKCENTER && dropPos_y[i] < SLICECHECKCENTER){
                        //横纵坐标判断
                        if( numberInArray[i] / 6 - 2 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 - 2 == answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];//加入到正确的步骤中
                            hasFindThis = true;
                        }
                    }
                    //该图片矩形框右上角
                    if(dropPos_x[i] > SLICECHECKCENTER && dropPos_y[i] <SLICECHECKCENTER){
                        if( numberInArray[i] / 6 - 2 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 - 1 == answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];
                            hasFindThis = true;
                        }
                    }
                    //该图片矩形左下角
                    if(dropPos_x[i] < SLICECHECKCENTER && dropPos_y[i] > SLICECHECKCENTER){
                        if( numberInArray[i] / 6 - 1 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 - 2 == answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];
                            hasFindThis = true;
                        }
                    }
                    //该图片矩形右下角
                    if(dropPos_x[i] > SLICECHECKCENTER && dropPos_y[i] > SLICECHECKCENTER){
                        if( numberInArray[i] / 6 - 1 == answer_pos_Y[j] &&
                            numberInArray[i] % 6 - 1 == answer_pos_X[j])
                        {
                            correct[i] = sliceKind[i];
                            hasFindThis = true;
                        }
                    }
                    break;
                }
            }
            if(hasFindThis){
                break;
            }
        }
    }

    //现在找到了所有正确放置过的切片，下面遍历正确答案的列表，通过删除找到剩余没有放置正确的切片
    QList<int> notFindKind = {0,0,0,0,0,0,0};
    QList<int> notFindPos_x ={0,0,0,0,0,0,0};
    QList<int> notFindPos_y = {0,0,0,0,0,0,0};
    for(int i = 0; i<7; i++){
        notFindKind[i] = answer_sliceKind[i];
        notFindPos_x[i] = answer_pos_X[i];
        notFindPos_y[i] = answer_pos_Y[i];
    }

    for(int i = 0; i < 7; i++){
        //看一下在correct中能不能找到正确答案
        bool hasFind = false;
        for(int j = 0; j < notFindKind.size(); j++){
            if(correct[i] == notFindKind[j]){
                notFindKind.removeAt(j);
                notFindPos_x.removeAt(j);
                notFindPos_y.removeAt(j);
                break;
            }
        }
    }

    int correctAmount = 0;
    for(int i = 0; i < 7;i++)
    {
        if(correct[i] != 0){
            correctAmount++;
        }
    }
    int correctCopy[7];
    for(int i = 0; i < 7; i++){
        correctCopy[i] = correct[i];
    }
    if(correctAmount < sliceKind.size()){//如果放置的步数比正确的步数多，那么有错的，把它找出来，看哪一块在正确的步骤中找不到
        for(int i =0; i < sliceKind.size(); i++){
            bool hasFound = false;
            for(int j = 0; j< 7;j++){
                if(sliceKind[i] == correct[j]){
                    hasFound = true;
                    correct[j] = 0;
                }
            }
            if(!hasFound){
                QString tip;
                tip = "您当前所放置的" + QString::number(sliceKind[i]) + "*" +QString::number(sliceKind[i]) +"切片位置错误";
                return tip;
            }
        }
    }

    //如果某块切片放置位置不正确，那么返回该切片的信息;
    if(notFindKind.size() != 0){
        QString tip = "对于当前您尚未放置的切片而言\n\t" +
                      QString::number(notFindKind[0]) +
                      "*" + QString::number(notFindKind[0])
                      + "切片的左上角\n\t 应该放置在\n\t  第" +
                      QString::number(notFindPos_x[0] + 1)
                      + "行\n\t  第" + QString::number(notFindPos_y[0] + 1)
                      + "列\n";
        return tip;
    }
    //假如找遍了都是对的，那返回已经完成的信息
    if(notFindKind.size() == 0) return QString("您已经完成该关卡");

    return QString("系统似乎出了些小故障，找不到提示");
}

void Map::printElementMap()
{
    {
        for (int i = 0; i < 36; i++) {
            qDebug() << getElementArray(i).getAmount() << " ";
            if (i % 6 == 5) qDebug() << "\n";
        }
    }
}

// void Map::testFile()//仅用于测试阶段看看能不能从文件中读出
// {
//     for (int i = 0; i<36; i++)
//     {
//         //qDebug() << mapInInt[i];
//         qDebug() << targetSlice[i].getSliceKind();
//         // qDebug() <<
//     }
// }

CustomMatrix::CustomMatrix()
{
    for (int i = 0; i < 6; ++i) {
        QVector<int> row(6, 0);
        data.append(row);
    }
}

void CustomMatrix::cast(int size, int x, int y)
{
    sliceKind.push_back(size);
    pos_X.push_back(x);
    pos_Y.push_back(y);
    for (int i = x; i < x + size; ++i) {
        for (int j = y; j < y + size; ++j) {
            data[i][j]++;
        }
    }
}

bool CustomMatrix::isCastable(int size, int x, int y)
{
    if (x >= 0 && x + size <= 6 && y >= 0 && y + size <= 6 ) {
        for (int i = x; i < x + size; ++i) {
            for (int j = y; j < y + size; ++j) {
                if(data[i][j] >= 3){//如果在该区域内已经有大等于3的了，不能放，因为4在第一次中已经放出来了，遍历检测
                    return false;
                }
            }
        }
        return true;
    }
    else return false;
}

bool CustomMatrix::generateMapRandomly()//最后放3*3和4*4容易崩溃掉，调一下顺序，第一次处理必须先放一块4*4，第二次处理必须先放3*3
{
    //重置一下数据成员
    sliceToPut = QList<int>{4,3,3,2,2,1,1};
    for(int i =0; i < sliceToPut.size(); i++){
        qDebug() << sliceToPut[i];
    }
    data.clear();
    for (int i = 0; i < 6; ++i) {
        QVector<int> row(6, 0);
        data.append(row);
    }
    sliceKind.clear();
    pos_X.clear();
    pos_Y.clear();

    //先随机生成4元素的位置，在至少内部第二层吧，第二层现在目测太简单了，大切片放置可能性好小，那么由此可以设计难度
    int random_X = QRandomGenerator::global()->bounded(1, 5);
    int random_Y = QRandomGenerator::global()->bounded(1, 5);

    qDebug() << "random x :" << random_X + 1 << "random y" << random_Y + 1;
    int remainedSlice = 7;
    for(int i = 0; i < 4; i++){
        //在所有的切片中随机选4张放在4号位的周围，由于是从左上角开始加，不需要考虑右移，看看超了边界没有就好
        int random_Slice = QRandomGenerator::global()->bounded(0,remainedSlice);
        //找到4*4切片把它放了先
        for(int j = 0; j < remainedSlice; j++){
            if(sliceToPut[j] == 4){
                random_Slice = j;
            }
        }
        //其他切片可以放置的位置，默认是从左上角开始
        int up, down, left, right;//该切片可以放的边界位置
        if(random_X - sliceToPut[random_Slice] + 1 < 0) left = 0;
        else left = random_X - sliceToPut[random_Slice] + 1;

        if(random_X + sliceToPut[random_Slice] >= 6) right = 6 - sliceToPut[random_Slice];
        else right = random_X;

        if(random_Y - sliceToPut[random_Slice] + 1 < 0) up = 0;
        else up = random_Y - sliceToPut[random_Slice] + 1;

        if(random_Y + sliceToPut[random_Slice] >= 6) down = 6 - sliceToPut[random_Slice];//random_Y -(random_Y + sliceToPut[random_Slice] - 6);
        else down = random_Y ;

        //在可以放置的位置中随机选择
        int random_OtherPos_X = QRandomGenerator::global()->bounded((left + 1), (right + 2));//由于参数要大于0，所以后续加减调整一下
        int random_OtherPos_Y = QRandomGenerator::global()->bounded((up + 1), (down + 2));
        qDebug() << "sliceKind:" << sliceToPut[random_Slice];
        qDebug() << random_OtherPos_X << random_OtherPos_Y ;
        //放置并记录
        this->cast(sliceToPut[random_Slice], random_OtherPos_X - 1, random_OtherPos_Y - 1);
        //删除元素
        sliceToPut.removeAt(random_Slice);
        remainedSlice --;
    }
    //剩下可以放置的切片，检测一下，可以放就直接放上去，为了增加难度，要考虑一下优先级，重叠得比较多的会难一些
    QElapsedTimer timer;
    timer.start();//可能出现死循环，采用定时器

    while(sliceToPut.size() != 0){//随机生成容易死循环，不如由内而外考虑，这样也增加了重叠度
        int random_Slice = QRandomGenerator::global()->bounded(0,remainedSlice);

        for(int j = 0; j < remainedSlice; j++){//如果有，先把3*3踢出
            if(sliceToPut[j] == 3){
                random_Slice = j;
            }
        }

        //从内层开始，遍历格子是否可以放置
        bool find = false;
        int startRow = 2, startCol = 2, endRow = 3, endCol = 3;
        while (startRow >= 0  && startCol >= 0) {//假如找完了都没找到可以放的地方，find就还是false，函数直接返回false，否则当所有切片都找完后返回true
            // 右上角到右下角
            for (int i = startRow; i <= endRow; ++i) {
                if(isCastable(sliceToPut[random_Slice], i, endCol)){//如果找到了就立马加上，跳出循环
                    cast(sliceToPut[random_Slice], i, endCol);
                    find = true;
                    qDebug() << "slicekind: "<< sliceToPut[random_Slice];
                    qDebug() << i + 1 << endCol + 1;
                    break;
                }
            }
            if(find) {//找到之后打破当前切片的循环，找下一块
                remainedSlice --;
                sliceToPut.removeAt(random_Slice);
                break;
            }

            // 右下角向左一位到左下角
            if (startCol < endCol) {//还有
                for (int i = endCol - 1; i >= startCol; --i) {
                    if(isCastable(sliceToPut[random_Slice], endRow, i)){
                        cast(sliceToPut[random_Slice], endRow, i);
                        find = true;
                        qDebug() << "slicekind: "<< sliceToPut[random_Slice];
                        qDebug() << endRow + 1<< i + 1;
                        break;
                    }
                }
                if(find){
                    remainedSlice --;
                    sliceToPut.removeAt(random_Slice);
                    break;
                }
            }

            // 左下角向上一位到左上角
            if (endRow > startRow){
                for (int i = endRow - 1; i >= startRow; --i) {
                    if(isCastable(sliceToPut[random_Slice], i, startCol)){
                        cast(sliceToPut[random_Slice], i, startCol);
                        find = true;
                        qDebug() << "slicekind: "<< sliceToPut[random_Slice];
                        qDebug() << i + 1 << startCol + 1;
                        break;
                    }
                }
                if(find) {
                    remainedSlice --;
                    sliceToPut.removeAt(random_Slice);
                    break;
                }
            }

            // 左上角向右一位到右上角向左一位（如果还有行可遍历）
            if (startRow + 1 < endRow) {
                for (int i = startCol + 1; i < endCol; ++i) {
                    if(isCastable(sliceToPut[random_Slice], startRow, i)){
                        cast(sliceToPut[random_Slice], startRow, i);
                        find = true;
                        qDebug() << "slicekind: "<< sliceToPut[random_Slice];
                        qDebug() << startRow + 1 << i + 1;
                        break;
                    }
                }
                if(find){
                    remainedSlice --;
                    sliceToPut.removeAt(random_Slice);
                    break;
                }
            }

            //遍历完该层还是没找到，开始找下一层
            startRow --;
            startCol --;
            endRow ++;
            endCol ++;
        }

        if(!find) return false;
    }
    for(int i = 0; i< 7; i++){
        qDebug() << "在随机生成的地图中" << sliceKind[i] << "*" << sliceKind[i] << "的位置是";
        qDebug()<< "( " << pos_X[i] << "," << pos_Y[i] << " )";
    }
    return true;
}

void CustomMatrix::updateSliceToPutList()
{
    sliceToPut = QList<int>({4,3,3,2,2,1,1});
}

void Element::addCastedAmount()
{
    castAmount++;
}

void Element::decCastedAmount()
{
    castAmount--;
}

int Element::getAmount()
{
    return castAmount;
}


float Square::convertAmountToHungry()
{
    if (getAmount() == 4) {
        return 3;//4*4的饥饿感强烈一些
    }
    if (getAmount() == 1) {
        return 1;
    }
    if (getAmount() == 2 || getAmount() == 3) {
        return 3;
    }
    return 0;
}

bool Square::isFull()
{
    if (getAmount() == 4)
        return true;
    else return false;
}

bool Square::isAnswer()
{
    if (getAmount() == 4)
        return true;
    return false;
}

int Square::getElementKind()
{
    return SQUARE;
}

float CircleInPractice::convertAmountToHungry()
{
    if (getAmount() == 0) {
        return 1.1;//常规状态下饥饿感
    }
    else if (getAmount() == 1) {
        return 1.5;//饥饿感变强
    }
    return 0;
}

bool CircleInPractice::isFull()
{
    if (getAmount() == 2)
        return true;
    else return false;
}

bool CircleInPractice::isAnswer()
{
    if (getAmount() == 2)
        return true;
    return false;
}

int CircleInPractice::getElementKind()
{
    return CIRCLEINPRACTICE;
}

float CircleInCompetition::convertAmountToHungry()
{
    if (getAmount() == 0) {
        return 0.2;//饥饿感比较弱，但是有一定优先级，不过四块加起来没有两块0时的三角形强，要削弱一下饥饿感，毕竟存在0的情况
    }
    else if (getAmount() == 1) {
        return 1.5;//饥饿感上升,弱于1还没有的
    }
    return 0;
}
bool CircleInCompetition::isFull()
{
    if (getAmount() == 2)
        return true;
    else return false;
}
bool CircleInCompetition::isAnswer()
{
    if (getAmount() == 0 || getAmount() == 2)
        return true;
    return false;
}
int CircleInCompetition::getElementKind()
{
    return CIRCLEINCOMPETITION;
}
float Cross::convertAmountToHungry()
{
    return -100;//显然不可能放置，不计算，或者最低优先级，设为-10好了
}

bool Cross::isFull()
{
    if (getAmount() == 0) {
        return true;
    }
    else return false;
}

bool Cross::isAnswer()
{
    if (getAmount() == 0)
        return true;
    else return false;
}

int Cross::getElementKind()
{
    return CROSS;
}

float Triangle::convertAmountToHungry()
{
    if (getAmount() == 0)
        return 1.4;
    else if (getAmount() == 1)//在这种状态下饥饿感最小，最次的来考虑
        return 0.7;//强于0的圈圈
    else if (getAmount() == 2)
        return 1.6;//饥饿感增强，但弱于还没有的
    return 0;
}

bool Triangle::isFull()
{
    if (getAmount() == 3) {
        return true;
    }
    else return false;
}

bool Triangle::isAnswer()
{
    if (getAmount() == 1 || getAmount() == 3)
        return true;
    return false;
}

int Triangle::getElementKind()
{
    return TRIANGLE;
}

Map::Map()
{
    for (int i = 0; i < 3; ++i) {
        potential0.push_back(QVector<bool>{true, true, true});
    }
    for (int i = 0; i < 4; i++) {
        potential1.push_back(QVector<bool>{true, true, true, true});
        potential2.push_back(QVector<bool>{true, true, true, true});
    }
    for (int i = 0; i < 4; i++) {
        potential3.push_back(QVector<bool>{true, true, true, true, true});
        potential4.push_back(QVector<bool>{true, true, true, true, true});
    }
}

Map::~Map()
{
}

bool Map::canBeSolved()
{
    //原先打算先找出可以放置的位置，再次优化一下，但是为了让该函数两种状态下都适用，就不找可以放的位置了，然后循环次数少一些，做初步判断即可
    //第一层4*4，可能的有九个，然后每次优先处理“最饥饿”的一块，如果该块放不了，那么设为0，然后寻找次级“饥饿”
    //遍历计算
    for (int i0 = 0; i0 < 9; i0++) //4*4
    {
        int bestPosInArray0 = mostHungryArea(4, potential0);//4*4找最佳位置
        qDebug() << "4*4: (" << bestPosInArray0 / 6 + 1<< "," << bestPosInArray0 % 6 + 1<< ")\n";
        if (canBeCasted(4, bestPosInArray0 % 6, bestPosInArray0 / 6)) //是否可以放置
        {
            //回溯后要给可能位置置位为true一下
            cast(4, bestPosInArray0 % 6, bestPosInArray0 / 6);//可以就放，开始处理下一块
            resetPotential(potential1);//下一块置为全部位置可能，再次计算
            for (int i1 = 0; i1 < 15; i1++) //3*3
            {
                int bestPosInArray1 = mostHungryArea(3, potential1);//第一块3*3找最佳位置
                qDebug() << "第一块3*3: (" << bestPosInArray1 / 6 + 1 << "," << bestPosInArray1 % 6 + 1<< ")\n";
                if (canBeCasted(3, bestPosInArray1 % 6, bestPosInArray1 / 6)) //是否可以放置
                {
                    cast(3, bestPosInArray1 % 6, bestPosInArray1 / 6);//可以就放，开始处理下一块
                    resetPotential(potential2);//下一块全部位置置true

                    for (int i2 = 0; i2 < 15; i2++)
                    {
                        int bestPosInArray2 = mostHungryArea(3, potential2);//第二块3*3找最佳位置
                        qDebug() << "第二块3*3: (" << bestPosInArray2 / 6 + 1<< "," << bestPosInArray2 % 6 + 1<< ")\n";
                        if (canBeCasted(3, bestPosInArray2 % 6, bestPosInArray2 / 6))
                        {
                            cast(3, bestPosInArray2 % 6, bestPosInArray2 / 6);//可以就放，开始处理下一块
                            resetPotential(potential3);//设置一块2*2的回溯
                            for (int i3 = 0; i3 < 20; i3++)
                            {
                                int bestPosInArray3 = mostHungryArea(2, potential3);//第一块2*2找最佳位置，设置一次回溯
                                qDebug() << "第一块2*2: (" << bestPosInArray3 / 6 + 1<< "," << bestPosInArray3 % 6 + 1<< ")\n";
                                //下一块不回溯，无reset
                                if (canBeCasted(2, bestPosInArray3 % 6, bestPosInArray3 / 6))
                                {
                                    cast(2, bestPosInArray3 % 6, bestPosInArray3 / 6);//可以就放，开始处理下一块
                                    resetPotential(potential4);
                                    int bestPosInArray4 = mostHungryArea(2, potential4);//第二块2*2找最佳位置
                                    qDebug() << "第二块2*2: (" << bestPosInArray4 / 6 + 1<< "," << bestPosInArray4 % 6 + 1<< ")\n";
                                    if (canBeCasted(2, bestPosInArray4 % 6, bestPosInArray4 / 6))
                                    {
                                        cast(2, bestPosInArray4 % 6, bestPosInArray4 / 6);//可以就放，后面两块1*1不再做以上相同处理，直接检测当前是不是剩大于两个饿着的就行
                                        //由于有些情况，就算剩两个1也可以完成游戏，即是存在多种解法，最后两个1放在三角形位置就好，这里先检查一遍
                                        // if (isAnswer()) {
                                        //     return true;//不过为了方便赋给答案，就不检验了
                                        // }
                                        //然后检查是不是剩俩
                                        int remained = 0;
                                        for (int final = 0; final < 36; final++)
                                        {
                                            if (!(*elementArray[final]).isAnswer() ) {
                                                remained++;
                                            }
                                        }
                                        if (remained <= 2) {//如果剩的小于俩，那么显然只需要放那两块就好，此时顺便完成答案的输入。
                                            for (int i = 0; i < 36; i++) {
                                                if(!(*elementArray[i]).isAnswer())
                                                    qDebug() << "1*1: (" << i / 6 + 1 << "," << i % 6 + 1 << ")\n";
                                            }
                                            hasAnswer = true;
                                            answer_sliceKind[0] = 4;
                                            answer_pos_X[0] = bestPosInArray0 % 6;
                                            answer_pos_Y[0] = bestPosInArray0 / 6;

                                            answer_sliceKind[1] = 3;
                                            answer_pos_X[1] = bestPosInArray1 % 6;
                                            answer_pos_Y[1] = bestPosInArray1 / 6;

                                            answer_sliceKind[2] = 3;
                                            answer_pos_X[2] = bestPosInArray2 % 6;
                                            answer_pos_Y[2] = bestPosInArray2 / 6;

                                            answer_sliceKind[3] = 2;
                                            answer_pos_X[3] = bestPosInArray3 % 6;
                                            answer_pos_Y[3] = bestPosInArray3 / 6;

                                            answer_sliceKind[4] = 2;
                                            answer_pos_X[4] = bestPosInArray4 % 6;
                                            answer_pos_Y[4] = bestPosInArray4 / 6;

                                            answer_sliceKind[5] = 1;
                                            for(int i = 0; i < 36; i++){
                                                if( !(*elementArray[i]).isAnswer() )
                                                {
                                                    answer_pos_X[5] = i % 6;
                                                    answer_pos_Y[5] = i / 6;
                                                    (*elementArray[i]).addCastedAmount();
                                                    break;
                                                }
                                            }
                                            answer_sliceKind[6] = 1;
                                            for(int i = 0; i < 36; i++){
                                                if( !(*elementArray[i]).isAnswer() )
                                                {
                                                    answer_pos_X[6] = i % 6;
                                                    answer_pos_Y[6] = i / 6;
                                                    (*elementArray[i]).addCastedAmount();
                                                    break;
                                                }
                                            }
                                            return true;

                                        }
                                        deCast(2, bestPosInArray4 % 6, bestPosInArray4 / 6);
                                    }
                                    deCast(2, bestPosInArray3 % 6, bestPosInArray3 / 6);
                                }
                                potential3[bestPosInArray3 / 6][bestPosInArray3 % 6] = false;
                            }
                            deCast(3, bestPosInArray2 % 6, bestPosInArray2 / 6);
                        }
                        potential2[bestPosInArray2 / 6][bestPosInArray2 % 6] = false;
                    }
                    deCast(3, bestPosInArray1 % 6, bestPosInArray1 / 6);
                }
                potential1[bestPosInArray1 / 6][bestPosInArray1 % 6] = false;
            }
            deCast(4, bestPosInArray0 % 6, bestPosInArray0 / 6);
        }
        potential0[bestPosInArray0 / 6][bestPosInArray0 % 6] = false;
    }
    //在以上情况都没有找到，返回false
    return false;
}


bool Map::canBeCasted(int size, int pos_x, int pos_y)//pos_x是列号，y是行号
{
    for (int i = pos_y; i < pos_y + size; i++) {
        for (int j = pos_x; j < pos_x + size; j++) {
            if ((*elementArray[i * 6 + j]).isFull()) {
                return false;
            }
        }
    }
    return true;
}

void Map::cast(int size, int pos_x, int pos_y)//pos_x,pos_y
{
    for (int i = pos_y; i < pos_y + size; i++) {//行号
        for (int j = pos_x; j < pos_x + size; j++) {//列号
            (*elementArray[i * 6 + j]).addCastedAmount();
        }
    }
}

bool Map::isAnswer()
{
    for (int i = 0; i < 36; i++) {
        if (!(*elementArray[i]).isAnswer())
            return false;
    }
    return true;
}

void Map::setMapInInt(int* a)
{
    for (int i = 0; i < 36; i++) {
        mapInInt[i] = a[i];
    }
}



void Map::resetPotential(QVector<QVector<bool>> &needReset)
{
    qDebug() << "reset";
    for (int i = 0; i < needReset.size(); i++) {
        for (int j = 0; j < needReset[i].size(); j++) {
            needReset[i][j] = true;
        }
    }
}

void Map::convertMapToElement(int mode)
{
    qDebug() << "start";
    for (int i = 0; i < 36; i++) {
        // if(elementArray[i] != nullptr){
        //     qDebug() << "delete";
        //     delete elementArray[i];
        //     elementArray[i] = nullptr;//防止内存泄露
        // }//但加在QT里会崩溃
        switch (mapInInt[i])
        {
        case 0:
            if (mode == competitionMode) {
                elementArray[i] = &circleInCompetition_ForChoose[i];
            }
            else if (mode == practiceMode) {
                elementArray[i] = &cross_ForChoose[i];
            }
            break;
        case 1:
        case 3:
            elementArray[i] = &triangle_ForChoose[i];
            break;
        case 2:
            if (mode == competitionMode) {
                elementArray[i] = &circleInCompetition_ForChoose[i];
            }
            else if (mode == practiceMode) {
                elementArray[i] = &circleInPractice_ForChoose[i];
            }
            break;
        case 4:
            elementArray[i] = &square_ForChoose[i];
            break;
        default:
            qDebug() << "error switch";
            break;
        }
    }
}

void Map::deCast(int size, int pos_x, int pos_y)
{
    for (int i = pos_y; i < pos_y + size; i++) {//行号
        for (int j = pos_x; j < pos_x + size; j++) {//列号
            (*elementArray[i * 6 + j]).decCastedAmount();
        }
    }
}


int Map::mostHungryArea(int sliceSize, QVector<QVector<bool>> potentialPos)
{
    float mostHungryValue = 1;
    int mostHungryPos = 1;//左上角
    //遍历计算，双层循环先定位，然后计算该区域的总和
    for (int i = 0; i < potentialPos.size(); i++) {//第i行
        for (int j = 0; j < potentialPos[i].size(); j++) {//第j列
            if (potentialPos[i][j] == true){
                float hungryValue = 0;
                //进入每一块自己的叠加前，判断一些成团的特殊情况
                //1.有三角形在边界（也即是先摸一摸边界），判断其周围还有没有同样饥饿的，每多一个加多一点饥饿感，但检测区域内有cross或者circle0状态的话要削弱一下
                if ((*elementArray[i * 6 + j]).getElementKind() == TRIANGLE//三角形
                        && (i == 0 || i == 5 || j == 0 || j == 5)//边界
                        && ((*elementArray[i * 6 + j]).getAmount() == 0)
                    || (*elementArray[i * 6 + j]).getAmount() == 2)//饥饿
                {	//下面的循环是看周围有没有
                    for (int row = i; row < i + sliceSize; row++) {//第row行
                        for (int column = j; column < j + sliceSize; column++) {//第column列
                            if ((*elementArray[i * 6 + j]).getElementKind() == TRIANGLE
                                    && ((*elementArray[i * 6 + j]).getAmount() == 0)
                                || (*elementArray[i * 6 + j]).getAmount() == 2)
                            {
                                hungryValue += 0.5;
                            }
                            else if ((*elementArray[i * 6 + j]).getElementKind() == CROSS
                                     || ((*elementArray[i * 6 + j]).getElementKind() == CIRCLEINCOMPETITION && (*elementArray[i * 6 + j]).getAmount() == 0))
                            {
                                hungryValue -= 2;
                            }
                        }
                    }
                }
                // //2.
                // if((*elementArray[i * 6 + j]).getElementKind() == SQUARE){
                //     for(int i =0; i < sliceSize; i++){
                //         for(int j =0; j < sliceSize; j++){
                //             if()//懒得写了，困，高铁上回家咯
                //         }
                //     }
                // }
                //开始计算单个的
                for (int row = i; row < i + sliceSize; row++) {//第row行
                    for (int column = j; column < j + sliceSize; column++) {//第column列
                        hungryValue += (*elementArray[row * 6 + column]).convertAmountToHungry();
                    }
                }
                if (hungryValue > mostHungryValue) {
                    mostHungryValue = hungryValue;
                    mostHungryPos = i * 6 + j;
                }
            }
        }
    }
    return mostHungryPos;
}

int Map::solveWays()
{
    int solveway = 0;
    int repeatTime = 0;
    for (int ai = 0; ai < 3; ai++) {
        for(int aj = 0; aj < 3; aj++ ) {
            cast(4, aj, ai);
            for (int bi = 0; bi < 4; bi++) {
                for (int bj = 0; bj < 4; bj++) {
                    cast(3, bj, bi);
                    for (int ci = 0; ci < 4; ci++) {
                        for (int cj = 0; cj < 4; cj++) {
                            cast(3, cj, ci);
                            for (int di = 0; di < 5; di++) {
                                for (int dj = 0; dj < 5; dj++) {
                                    cast(2, dj, di);
                                    for (int ei = 0; ei < 5; ei++) {
                                        for (int ej = 0; ej < 5; ej++) {
                                            cast(2, ej, ei);

                                            int amount = 0;
                                            for (int i = 0; i < 36; i++) {
                                                if (!(*elementArray[i]).isAnswer()) {
                                                    amount++;
                                                }
                                            }

                                            if (amount == 2 || amount == 1) {//如果小于两个，显然此时可以返回答案
                                                solveway++;
                                                if(solveway == 1){//第一个赋给答案，其它不管，仅计算
                                                    answer_sliceKind[0] = 4;
                                                    answer_sliceKind[1] = 3;
                                                    answer_sliceKind[2] = 3;
                                                    answer_sliceKind[3] = 2;
                                                    answer_sliceKind[4] = 2;
                                                    answer_sliceKind[5] = 1;
                                                    answer_sliceKind[6] = 1;

                                                    answer_pos_X[0] = aj;
                                                    answer_pos_X[1] = bj;
                                                    answer_pos_X[2] = cj;
                                                    answer_pos_X[3] = dj;
                                                    answer_pos_X[4] = ej;

                                                    answer_pos_Y[0] = ai;
                                                    answer_pos_Y[1] = bi;
                                                    answer_pos_Y[2] = ci;
                                                    answer_pos_Y[3] = di;
                                                    answer_pos_Y[4] = ei;

                                                    int x1,x2,y1,y2;
                                                    for(int i = 0; i < 36; i++){
                                                        if( !(*elementArray[i]).isAnswer() )
                                                        {
                                                            answer_pos_X[5] = i % 6;
                                                            answer_pos_Y[5] = i / 6;
                                                            x1 = i % 6;
                                                            y1 = i / 6;
                                                            (*elementArray[i]).addCastedAmount();
                                                            break;
                                                        }
                                                    }
                                                    for(int i = 0; i < 36; i++){
                                                        if( !(*elementArray[i]).isAnswer() )
                                                        {
                                                            answer_pos_X[6] = i % 6;
                                                            answer_pos_Y[6] = i / 6;
                                                            x2 = i % 6;
                                                            y2 = i / 6;
                                                            (*elementArray[i]).addCastedAmount();
                                                            break;
                                                        }
                                                    }
                                                    deCast(1,x1,y1);
                                                    deCast(1,x2,y2);
                                                }
                                            }
                                            else if (amount == 0) {
                                                int triangleLast = 0;
                                                int x,y;//放了之后的记录，避免影响其它解的判断
                                                for (int i = 0; i < 36; i++) {
                                                    if (!(*elementArray[i]).isFull()) {
                                                        triangleLast++;//剩两个1*1全给三角形的情况
                                                    }
                                                }
                                                if(solveway == 0){
                                                    answer_sliceKind[0] = 4;
                                                    answer_sliceKind[1] = 3;
                                                    answer_sliceKind[2] = 3;
                                                    answer_sliceKind[3] = 2;
                                                    answer_sliceKind[4] = 2;
                                                    answer_sliceKind[5] = 1;
                                                    answer_sliceKind[6] = 1;

                                                    answer_pos_X[0] = aj;
                                                    answer_pos_X[1] = bj;
                                                    answer_pos_X[2] = cj;
                                                    answer_pos_X[3] = dj;
                                                    answer_pos_X[4] = ej;

                                                    answer_pos_Y[0] = ai;
                                                    answer_pos_Y[1] = bi;
                                                    answer_pos_Y[2] = ci;
                                                    answer_pos_Y[3] = di;
                                                    answer_pos_Y[4] = ei;

                                                    for(int i = 0; i < 36; i++){
                                                        if( !(*elementArray[i]).isFull() )
                                                        {
                                                            x = i % 6;
                                                            y = i / 6;
                                                            answer_pos_X[5] = i % 6;
                                                            answer_pos_X[6] = i % 6;

                                                            answer_pos_Y[6] = i / 6;
                                                            answer_pos_Y[5] = i / 6;
                                                            (*elementArray[i]).addCastedAmount();
                                                            (*elementArray[i]).addCastedAmount();
                                                            break;
                                                        }
                                                    }
                                                    deCast(1,x,y);
                                                    deCast(1,x,y);
                                                solveway += triangleLast;
                                                }
                                            }
                                            deCast(2, ej, ei);
                                        }
                                    }
                                    deCast(2, dj, di);
                                }
                            }
                            deCast(3, cj, ci);
                        }
                    }
                    deCast(3, bj, bi);
                }
            }
            deCast(4, aj, ai);
        }
    }
    if(solveway == 0) return solveway;
    if(solveway % 4 != 0) return (solveway / 4 + 1);
    if(solveway % 4 == 0 && solveway != 0) return solveway / 4;// 两块3*3，两块2*2间彼此可以交换的情况
}


