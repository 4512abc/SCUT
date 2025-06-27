#include "Cell.h"
#include <Qt>
#include <regex>
#include <utility>
#include <QPainter>
Cell::Cell(int init_row,int init_col,int init_value,std::string init_color):
    m_row(init_row),m_col(init_col),m_value(init_value),m_color(std::move(init_color))
{
    //设置小方块的大小
    setFixedSize(100,100);
}

int Cell::getRow()const    //获取行位置
{
    return m_row;
}

int Cell::getCol()const    //获取列位置
{
    return m_col;
}

int Cell::getValue()const  //获取数值
{
    return m_value;
}

std::string Cell::getColor()const   //获取颜色
{
    return m_color;
}

void Cell::set(int row,int col,int value,std::string color)     //对特定位置的方格进行设置颜色和数值
{
    this->m_row=row;
    this->m_col=col;
    this->m_value=value;
    this->m_color=std::move(color);     //std::move运算符：用于将资源从一个对象转移到另外一个对象
    update();
}

void Cell::setNum(int value)        //设置数值
{
    this->m_value=value;
    update();
}

void Cell::setColor(std::string color)      //设置颜色
{
    this->m_color=std::move(color);
    update();
}

void Cell::setNumAndColor(int value,std::string color)      //设置颜色和数字
{
    this->m_value=value;
    this->m_color=std::move(color);
    update();
}

//重载paintEvent，该函数作为Qt的事件处理槽函数，用于响应Cell对象的绘制事件。
void Cell::paintEvent(QPaintEvent *event)
{
    //使用Q_UNUSED宏忽略传入的QPaintEvent指针，表明在当前函数中未使用该事件对象。这有助于避免编译器警告关于未使用的变量。
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);            //设置QPainter的渲染提示，启用抗锯齿功能，使得绘制的图形边缘平滑。


    QString colorQString=QString::fromStdString(m_color);           //将std::string转换为QString
    QColor color;                                                   //解析RGB格式或者颜色名称
    std::regex rgbRegex(R"(rgb\((\d+),\s*(\d+),\s*(\d+)\))");       //接受的rgb格式
    std::smatch matches;                                            //接受的容器

    if(std::regex_match(m_color,matches,rgbRegex) && matches.size()==4)        //解析 RGB 格式
    {
        int r=std::stoi(matches[1]);
        int g=std::stoi(matches[2]);
        int b=std::stoi(matches[3]);
        color=QColor(r, g, b);
    }
    else        //否则直接赋值（也就是颜色的名词直接描绘颜色）
    {
        color=QColor(colorQString);       //解析颜色名称
    }

    //绘制小方块：使用QPainter的fillRect函数填充Cell的矩形区域（由rect()返回），颜色为从字符串m_color转换得到的QColor对象。
    //注意，m_color是一个std::string类型，通过QString::fromStdString将其转换为QString，进而转换为QColor，以符合QPainter的接口要求。
    painter.fillRect(rect(),color);

    //绘制文本：设置QPainter的画笔颜色为黑色，然后使用drawText函数在Cell的矩形区域内居中绘制文本。文本内容为m_value的数值形式。
    //m_value是一个整型变量，通过QString::number将其转换为字符串形式的数字。
    painter.setPen(Qt::black);
    QFont labelfont("Anonymous Pro",15);
    painter.setFont(labelfont);
    painter.drawText(rect(),Qt::AlignCenter,QString::number(m_value));
}


Cell& Cell::operator=(const Cell& copy)     //重载赋值运算符
{
    this->m_col=copy.getCol();
    this->m_row=copy.getRow();
    this->m_color=copy.getColor();
    this->m_value=copy.getValue();
    return *this;
}

Cell::Cell(const Cell& other):      //重载拷贝构造函数
    m_row(other.m_row),
    m_col(other.m_col),
    m_value(other.m_value),
    m_color(other.m_color)
{

}


bool Cell::operator!=(const Cell& answer)       //重载!=运算符
{
    if(m_color!=answer.m_color||m_value!=answer.m_value)
    {
        return true;
    }
    else return false;
}

