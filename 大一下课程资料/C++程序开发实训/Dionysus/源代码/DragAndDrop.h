#ifndef DRAGANDDROP_H
#define DRAGANDDROP_H

#include <QLabel>
#include <QPixmap>
#include <QMimeData>
#include <QDrag>
#include <QDropEvent>
#include <QPoint>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneEvent>
#include <QGraphicsBlurEffect>
#include <QGraphicsItem>
#include <QPaintEvent>
#include <QPainter>

#include "config.h"
class DraggableLabel : public QLabel
{
    Q_OBJECT
private:
    QPoint m_startPos;
    QPoint m_dragPosition;
    int pictureSize = 4;
    bool m_dragging = false; // 判断是否可以开始拖动
    int m_dragThreshold = 50; // 拖动阈值（像素）
public:
    DraggableLabel(QWidget *parent = nullptr);
    //设置根据类信息可视化的set函数
    void setPictureSize(int);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

};


class DroppableLabel : public QLabel
{
    Q_OBJECT
private:
    int sliceKind;
    int hasDropOn = 0;
    int point_X;
    int point_Y;
    int posInGrid_X;//从零开始
    int posInGrid_Y;
    int sliceCheckCenter = SLICECHECKCENTER;

public:
    DroppableLabel(QWidget *parent = nullptr);
    // //重写setPixmap函数，无法重写，故把pixmap开放成public成员了
    // QPixmap pixmap;
    void setPosInGrid(int);
    void setSliceKind(int a){sliceKind = a;}
    bool isDroppable(int sliceKind);

    int getPosInGrid_X(){return posInGrid_X;}
    int getPosInGrid_Y(){return posInGrid_Y;}
    int getHasDropOn(){return hasDropOn;}
    int getSliceKind(){return sliceKind;}
    void addSlicePutOn(int a){hasDropOn +=a;}//可以实现加减
    void updatePlayScene();//写成单个成员是无法实现修改的，那么要写成槽函数的形式了，发送信号给playWidget吧,不过在此处也要进行修改hasDropOn成员，便于存储以及检查答案，Qlabel是文本不太好操作
    //改名为updateplayscene，两个信号都发送，直接发送好了，没必要

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
signals:
    void TargetSliceChanged(int sliceKind,int numberInArray,int point_x, int point_y, int delta =1);//再把序号传入，好像没有必要，也是要连接每一个类对象，算了
    void SliceToPutDropped(int sliceKind,int change = -1);
};

#endif
