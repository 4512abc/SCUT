#ifndef CELL_H
#define CELL_H

#include <QObject>
#include <QWidget>
#include <Qt>
#include <string>
class Cell:public QWidget
{
    Q_OBJECT
public:
    Cell(int init_row=0,int init_col=0,int init_value=0,std::string init_color="White");    //默认构造函数
    [[nodiscard]]int getRow()const;                         //获取行位置
    [[nodiscard]]int getCol()const;                         //获取列位置
    [[nodiscard]]int getValue()const;                       //获取数值
    [[nodiscard]]std::string getColor()const;               //获取颜色
    Cell& operator=(const Cell&);                           //重载=运算符
    bool operator!=(const Cell&);                           //重载！=运算符
    Cell(const Cell&);                                      //拷贝构造函数
    void setNum(int value);                                 //设置数字
    void setColor(std::string color);                       //设置颜色
    void setNumAndColor(int value,std::string color);       //设置颜色和数字
    void set(int row,int col,int value,std::string color);  //对某一个特定位置的方格设置颜色和数值
    void paintEvent(QPaintEvent *event)override;            //重载paintevent函数
private:
    int m_row;                  //行坐标
    int m_col;                  //列坐标
    int m_value;                //数值
    std::string m_color;        //颜色
};

#endif // CELL_H
