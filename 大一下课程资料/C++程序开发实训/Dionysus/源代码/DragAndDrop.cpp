#include "DragAndDrop.h"

DraggableLabel::DraggableLabel(QWidget *parent)
    : QLabel(parent)
{
    setAttribute(Qt::WA_TranslucentBackground); // 透明背景，以便拖放时可见
    setAcceptDrops(true); // 启用拖放接受
    setMouseTracking(true); // 跟踪鼠标移动
    setCursor(Qt::OpenHandCursor); // 设置手型光标
}

void DraggableLabel::setPictureSize(int size)
{
    pictureSize = size;
}

void DraggableLabel::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    }
    QLabel::mousePressEvent(event);
}

void DraggableLabel::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->pos() - m_startPos;//计算鼠标移动的距离
        if (!m_dragging && delta.manhattanLength() < m_dragThreshold){
            return;}//小于启动拖动的距离就不执行拖动
        m_dragging = true;
        // 创建拖动图像
        QPixmap originalPixmap = pixmap(Qt::ReturnByValue);
        QPixmap scaledPixmap = originalPixmap.scaled(originalPixmap.size() * pictureSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        if (scaledPixmap.isNull())
            return;
        //scaledPixmap.fill(Qt::transparent); // 先填充全透明

        // 创建一个QPainter对象
        QPainter p(&scaledPixmap);
        p.setRenderHint(QPainter::Antialiasing); // 提升绘制质量

        // 设置透明度
        int alphaValue = 57; // 0是完全透明，255是完全不透明
        QColor color(0, 0, 0, alphaValue); // 使用颜色的Alpha通道设置透明度

        // 用带有透明度的颜色填充
        p.fillRect(scaledPixmap.rect(), color);

        // 关闭QPainter
        p.end();

        QImage image = scaledPixmap.toImage();
        for (int y = 0; y < image.height(); ++y) {
            QRgb *line = reinterpret_cast<QRgb*>(image.scanLine(y));
            for (int x = 0; x < image.width(); ++x) {
                QRgb pixel = line[x];
                line[x] = qRgba(qRed(pixel), qGreen(pixel), qBlue(pixel), qAlpha(pixel) * 0.7 * 255);//0.5是透明度
            }
        }
        QPixmap newPixmap = QPixmap::fromImage(image);

        // 设置 MIME 类型，此处设置为更改过的图片吧，便于根据大小修改，
        // MIME类型可以同时传输文字和图片
        QMimeData *mimeData = new QMimeData;
        mimeData->setImageData(newPixmap.toImage());
        mimeData->setData("application/x-int-data", QByteArray::number(pictureSize));
        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        // 实现拖动逻辑

        drag->setPixmap(newPixmap); // 使用处理后的图像
        drag->setHotSpot(QPoint(scaledPixmap.rect().center())); // 热区设置在图像的中心，让图像跟随鼠标箭头
        drag->exec();
    } else {
        QLabel::mouseMoveEvent(event);
    }
}

DroppableLabel::DroppableLabel(QWidget *parent): QLabel(parent)
{
    setAcceptDrops(true); // 启用拖放接受
    setMouseTracking(true); // 跟踪鼠标移动
}



void DroppableLabel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasImage()) {
        event->acceptProposedAction(); // 接受拖放动作
    } else {
        event->ignore();
    }
}

void DroppableLabel::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasImage()&& event->mimeData()->hasFormat("application/x-int-data"))
    {
        // QImage image = event->mimeData()->imageData().value<QImage>();
        // QPixmap pixmap = QPixmap::fromImage(image);
        QByteArray pictureSize = event->mimeData()->data("application/x-int-data");
        int sliceToPutKind = pictureSize.toInt();

        //判断位置是否可以放下
        QPoint dropPos = event->pos();
        point_Y = dropPos.x();
        point_X = dropPos.y();

        if( isDroppable(sliceToPutKind) )
        {
            qDebug() << "Drop Position: " << dropPos;
            //更新targetSlice
            emit TargetSliceChanged(sliceToPutKind,( posInGrid_X *6 + posInGrid_Y ),point_X,point_Y,1);
            //更新sliceToPut
            emit SliceToPutDropped(sliceToPutKind);

            event->acceptProposedAction(); // 接受拖放动作
        }

    } else {
        event->ignore(); // 如果数据类型不匹配，则忽略拖放事件
    }
}

void DroppableLabel::setPosInGrid(int pos)
{
    posInGrid_X = pos / 6;
    posInGrid_Y = pos % 6;
}

bool DroppableLabel::isDroppable(int sliceKind)
{
    //换种方法，根据种类而定
    switch (sliceKind) {
    case 1:
        return true;
        break;
    case 2:
        if(posInGrid_X == 0){
            if(posInGrid_Y == 0){//左上角
                if(point_X < sliceCheckCenter || point_Y < sliceCheckCenter){
                    return false;
                }
                else return true;//左上角方格的右下角，可放置
            }
            else if(posInGrid_Y == 5){//右上角
                if( point_X > sliceCheckCenter || point_Y < sliceCheckCenter){
                    return false;
                }
                else return true;
            }
            else{//其余非角落的顶端
                if(point_Y > sliceCheckCenter) return true;
                else return false;
            }
        }
        if(posInGrid_X == 5){
            if(posInGrid_Y == 0){//左下角
                if(point_X < sliceCheckCenter || point_Y > sliceCheckCenter){
                    return false;
                }
                else return true;//左上角方格的右下角，可放置
            }
            else if(posInGrid_Y == 5){//右下角
                if( point_X > sliceCheckCenter || point_Y > sliceCheckCenter){
                    return false;
                }
                else return true;//右上角的左下角
            }
            else{//其余非角落的顶端
                if(point_Y < sliceCheckCenter) return true;
                else return false;
            }
        }
    case 3:
        //如果在边缘一层
        if(posInGrid_X == 5 || posInGrid_X == 0 || posInGrid_Y == 5 || posInGrid_Y == 0){
            return false;
        }
        //在倒数第二层及以上，其实都可以放，并且都是加周围的格子，不用管了
        else return true;
        break;
    case 4:
        //边缘层不可以，倒数第二层角落可以

        //如果在边缘一层
        if(posInGrid_X == 5 || posInGrid_X == 0 || posInGrid_Y == 5 || posInGrid_Y == 0){
            return false;
        }
        //在倒数第二层
        if(posInGrid_X == 1 || posInGrid_X == 4 || posInGrid_Y == 1 || posInGrid_Y ==4)
        {
            //上层
            if(posInGrid_X == 1)
            {
                if(posInGrid_Y == 1){//左上角
                    if(point_X < sliceCheckCenter || point_Y < sliceCheckCenter){
                        return false;
                    }
                    else return true;
                }
                if(posInGrid_Y == 4 ){//右上角
                    if(point_X < sliceCheckCenter && point_Y > sliceCheckCenter){
                        return true;
                    }
                    else return false;
                }
                else{
                    if(point_Y > sliceCheckCenter) return true;
                    else return false;
                }
            }
            //下层
            if(posInGrid_X == 4)
            {
                if(posInGrid_Y == 1){//左下角
                    if(point_X < sliceCheckCenter || point_Y > sliceCheckCenter){
                        return false;
                    }
                    else return true;
                }
                if(posInGrid_Y == 4){//右下角
                        if(point_X > sliceCheckCenter || point_Y > sliceCheckCenter){
                            return false;
                        }
                        else return true;
                }
                else{
                    if(point_Y < sliceCheckCenter) return true;
                    else return false;
                }
            }
            //左层
            if(posInGrid_Y == 1){
                if(point_X > sliceCheckCenter) return true;
                else return false;
            }
            //右层
            if(posInGrid_Y == 4){
                if(point_X < sliceCheckCenter) return true;
                else return false;
            }
        }
        break;
    default:
        return false;

    }
}




