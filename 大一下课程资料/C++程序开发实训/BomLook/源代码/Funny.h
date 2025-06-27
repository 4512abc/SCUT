#ifndef FUNNY_H
#define FUNNY_H

#include <QWidget>
#include <stack>
#include "Cell.h"
#include "WADialog.h"
#include "ACDialog.h"
#include "qboxlayout.h"
#include "qlineedit.h"

enum class FunnyOperation {
    LEFT_ROTATE,  // 左旋转操作
    RIGHT_ROTATE, // 右旋转操作
    BURN          // 燃烧操作
};
class Funny : public QWidget
{
    Q_OBJECT
public:
    explicit Funny(QWidget *parent = nullptr);
    void onBackButtonClicked();                                 //用于响应返回按钮的点击的槽函数
    void setLayoutAndForm();                                    //设置和调整布局
    void setGame();                                             //设置生成游戏
    void left_rotate();                                         //左旋转操作
    void right_rotate();                                        //右旋转操作
    void burn();                                                //燃烧操作
    void undo();                                                //回撤操作
    void judge();                                               //判断操作
    void WA();                                                  //响应WA的函数，提示用户答案错误
    void AC();                                                  //响应AC的函数，提示用户答案正确
    QImage Mosaic(const QImage &sourceImage,int blockSize);     //对图像进行处理的马赛克算法
    void help();                                                //提示功能
    void calculateHelp();                                       //产生提示功能
    bool checkIsAllOne();                                       //检查是否全部为1
private slots:
    void loadImage();                                           //导入图片
    void loadExit();                                            //下载已经存在的地图
    void saving();                                              //保存地图
    void dialogGenerate();                                      //设置地图的名字
signals:
    void backToMain();
private:
    size_t m_size;                                              //地图的尺寸大小
    std::vector<std::vector<Cell>> m_cells;                     //玩家操作的地图
    std::vector<std::vector<Cell>> answers;                     //答案地图
    std::stack<std::vector<std::vector<Cell>>> m_cellsHistory;  //用于存放操作历史记录的栈
    QDialog *m_dialog;                                          //提示输入地图名字的对话框
    QLineEdit *inputLineEdit;                                   //输入栏
    WADialog *waDialog;                                         //WADialog
    ACDialog *acDialog;                                         //ACDialog
    QVBoxLayout *Vlayout;
    QHBoxLayout *paintingLayout;
    QHBoxLayout *Hlayout1;
    QHBoxLayout *Hlayout2;
    QPushButton *submitButton;
    QPushButton *savingButton;
    QVector<FunnyOperation> helps;                              //帮助提示
    QVector<FunnyOperation> Finals;                             //最后的提示操作
};

#endif // FUNNY_H
