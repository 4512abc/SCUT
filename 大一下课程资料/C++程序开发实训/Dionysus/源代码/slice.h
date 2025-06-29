#ifndef SLICE_H
#define SLICE_H

#include <QPixmap>
#include <QRect>
#include <QLabel>

class Slice
{
private:
    int sliceKind;//切片的种类，接受文件输入的一个数字，然后转化为相应的种类；
    QString SlicePixmapRoad;

    //int slice_x;
    //int slice_y;

    int sliceHasPutOn = 0;//利用一个Qlable完成当前已填入的树，设置在矩形边框的右上角即可

public:
    Slice();

    void setSliceKind(int i = 0);
    void setPixmapRoadInPractice();
    void setPixmapRoadInCompetition();
    void setPosition(int, int);
    void setPictureSize(int, int);

    //int getPosX(){return slice_x;}
    //int getPosY(){return slice_y;}
    int getSliceHasPutOn(){return sliceHasPutOn;}
    int getSliceKind(){return sliceKind;}
    QString getSlicePixmapRoad(){return SlicePixmapRoad;}

};

class sliceToPut
{
private:
    QString SliceToPutPixmapRoad;
    int sliceToPutKind = 1;
    bool hasPutv = 0;//没放就在滚动框里面添加一个
public:
    sliceToPut(){};

    void setPixmapRoad();
    void setSliceToPutKind(int);

    //接口
    int getSliceToPutKind(){return sliceToPutKind;}
    bool hasPut(){return hasPutv;}
    QString getSliceToPutRoad(){return SliceToPutPixmapRoad;}
};

#endif // SLICE_H
