#include "Funny.h"
#include "qapplication.h"
#include "qlabel.h"
#include "qlineedit.h"
#include "qmessagebox.h"
#include "qpushbutton.h"
#include "qregularexpression.h"
#include <iostream>
#include <random>
#include <QFileDialog>
#include <queue>
#include <QGridLayout>
#include <QDir>
#include <QFile>
int getRandNum()
{
    std::random_device rd_operation;                                // 随机数发生器种子
    std::mt19937 gen_operation(rd_operation());                     // 使用Mersenne Twister算法生成伪随机数
    std::uniform_int_distribution<> dis_operation(1, 5);            // 均匀分布，范围为[1, 5]
    int num = static_cast<int>(dis_operation(gen_operation));       // 从分布中抽取一个整数并转换为Operation枚举值
    return num;
}

Funny::Funny(QWidget *parent)
    : QWidget{parent}
{
    m_size=9;
    m_cells=std::vector<std::vector<Cell>>(m_size,std::vector<Cell>(m_size));
    answers=std::vector<std::vector<Cell>>(m_size,std::vector<Cell>(m_size));

    setLayoutAndForm();
}

void Funny::setLayoutAndForm()
{
    QGridLayout *gridLayout=new QGridLayout();
    gridLayout->setSpacing(5);        //设置间距

    for(size_t i=0;i<m_size;i++){
        for(size_t j=0;j<m_size;j++){
            gridLayout->addWidget(&m_cells[i][j],i,j);
            m_cells[i][j].setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred); // 设置小方块的大小策略为Preferred
            m_cells[i][j].setFixedSize(50, 50); // 设置小方块的固定大小为100x100像素
        }
    }
    // 设置布局的对齐方式为居中对齐
    gridLayout->setAlignment(Qt::AlignCenter);

    QGridLayout *answerLayout=new QGridLayout();
    answerLayout->setSpacing(5);


    for(size_t i=0;i<m_size;i++){
        for(size_t j=0;j<m_size;j++){
            answerLayout->addWidget(&answers[i][j],i,j);
            answers[i][j].setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
            answers[i][j].setFixedSize(50,50);
        }
    }
    //设置布局的对齐方式为居中对齐
    answerLayout->setAlignment(Qt::AlignCenter);

    QString globalStylesheet=R"(
        QPushButton {
        background-color: transparent;
        border: 2px solid white;
        border-radius: 10px;
        color: white;
        font-family: 'Microsoft YaHei';
        font-weight: bold;
        font-size: 20px
        }
        QPushButton:hover {
        background-color: rgba(255, 255, 255, 0.1);
        }
        QPushButton:pressed {
        background-color: rgba(255, 255, 255, 0.3);
        }
        QPushButton::icon {
        padding-right: 10px;
        }
        QPushButton#myButton {
        border: 2px solid rgba(0, 0, 0, 0.2);
        box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.4);
        }
    )";

    // 设置窗口的布局        
    QPushButton *button1=new QPushButton("左旋转");
    QIcon icon1(":/icons/resource/icons/lamb-left.png");
    button1->setIcon(icon1);
    button1->setIconSize(QSize(40,40));
    button1->setStyleSheet(globalStylesheet);
    button1->setFixedSize(180,60);

    QPushButton *button2=new QPushButton("右旋转");
    QIcon icon2(":/icons/resource/icons/lamb-right.png");
    button2->setIcon(icon2);
    button2->setIconSize(QSize(40,40));
    button2->setStyleSheet(globalStylesheet);
    button2->setFixedSize(180,60);

    QPushButton *button3=new QPushButton("燃烧");
    QIcon icon3(":/icons/resource/icons/火pixel.png");
    button3->setIcon(icon3);
    button3->setIconSize(QSize(40,40));
    button3->setStyleSheet(globalStylesheet);
    button3->setFixedSize(180,60);

    QPushButton *button4=new QPushButton("撤回");
    QIcon icon4(":/icons/resource/icons/金币pixel.png");
    button4->setIcon(icon4);
    button4->setIconSize(QSize(40,40));
    button4->setStyleSheet(globalStylesheet);
    button4->setFixedSize(180,60);

    QPushButton *button5=new QPushButton("导入新地图");
    QIcon icon5(":/icons/resource/icons/灯泡pixel.png");
    button5->setIcon(icon5);
    button5->setIconSize(QSize(40,40));
    button5->setStyleSheet(globalStylesheet);
    button5->setFixedSize(180,60);

    QPushButton *button6=new QPushButton("导入旧地图");
    QIcon icon6(":/icons/resource/icons/宝箱pixel.png");
    button6->setIcon(icon6);
    button6->setIconSize(QSize(40,40));
    button6->setStyleSheet(globalStylesheet);
    button6->setFixedSize(180,60);

    QPushButton *backButton=new QPushButton("返回",this);
    QIcon backIcon(":/icons/resource/icons/钥匙pixel.png");
    backButton->setIcon(backIcon);
    backButton->setIconSize(QSize(40,40));
    backButton->setStyleSheet(globalStylesheet);
    backButton->setFixedSize(180,60);


    submitButton=new QPushButton("提交");
    QIcon submitIcon(":/icons/resource/icons/放大镜pixel_.png");
    submitButton->setIcon(submitIcon);
    submitButton->setIconSize(QSize(40,40));
    submitButton->setStyleSheet(globalStylesheet);
    submitButton->setFixedSize(180,60);

    savingButton=new QPushButton("保存");
    QIcon savingIcon(":/icons/resource/icons/心pixel.png");
    savingButton->setIcon(savingIcon);
    savingButton->setIconSize(QSize(40,40));
    savingButton->setStyleSheet(globalStylesheet);
    savingButton->setFixedSize(180,60);

    //连接按钮 执行四个基本操作：左旋转 右旋转 燃烧 撤回
    connect(backButton,&QPushButton::clicked,this,&Funny::onBackButtonClicked);

    connect(button1,&QPushButton::clicked,this,&Funny::left_rotate);
    connect(button2,&QPushButton::clicked,this,&Funny::right_rotate);
    connect(button3,&QPushButton::clicked,this,&Funny::burn);
    connect(button4,&QPushButton::clicked,this,&Funny::undo);

    //下载导入新地图 或者导入已经存在的旧地图
    connect(button5,&QPushButton::clicked,this,&Funny::loadImage);
    connect(button6,&QPushButton::clicked,this,&Funny::loadExit);

    //保存地图
    connect(savingButton,&QPushButton::clicked,this,&Funny::dialogGenerate);

    QPushButton *helpButton=new QPushButton("提示");
    QIcon helpIcon(":/icons/resource/icons/星星pixel.png");
    helpButton->setIcon(helpIcon);
    helpButton->setIconSize(QSize(40,40));
    helpButton->setStyleSheet(globalStylesheet);
    helpButton->setFixedSize(150,60);

    connect(helpButton,&QPushButton::clicked,this,&Funny::help);

    Vlayout=new QVBoxLayout();
    Vlayout->addStretch(1);

    paintingLayout=new QHBoxLayout;

    paintingLayout->addStretch(1);
    paintingLayout->addLayout(gridLayout);
    paintingLayout->addStretch(1);
    paintingLayout->addLayout(answerLayout);
    paintingLayout->addStretch(1);

    Vlayout->addLayout(paintingLayout);
    Vlayout->addStretch(1);

    Hlayout1=new QHBoxLayout;
    Hlayout1->addStretch(1);
    Hlayout1->addWidget(button1);
    Hlayout1->addStretch(1);
    Hlayout1->addWidget(button2);
    Hlayout1->addStretch(1);
    Hlayout1->addWidget(button3);
    Hlayout1->addStretch(1);
    Hlayout1->addWidget(button4);
    Hlayout1->addStretch(1);

    Hlayout2=new QHBoxLayout;
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(button5);
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(button6);
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(savingButton);
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(submitButton);
    Hlayout2->addStretch(1);
    Hlayout2->addWidget(helpButton);
    Hlayout2->addStretch(1);

    Vlayout->addLayout(Hlayout1);
    Vlayout->addStretch(1);
    Vlayout->addLayout(Hlayout2);
    Vlayout->addStretch(1);
    Vlayout->addWidget(backButton);
    Vlayout->addStretch(1);
    setLayout(Vlayout);
}

void Funny::setGame()
{
    helps.clear();
    std::random_device rd_operation;     // 随机数发生器种子
    std::mt19937 gen_number(rd_operation());   // 使用Mersenne Twister算法生成伪随机数
    std::uniform_int_distribution<> dis_operation(0,2);     // 生成操作类型

    m_size=9;

    int maxNumber=0;
    for(int i=0;i<m_size;i++)
    {
        for(int j=0;j<m_size;j++)
        {
            maxNumber=std::max(maxNumber,m_cells[i][j].getValue());
        }
    }


    std::queue<FunnyOperation> opt;
    FunnyOperation last;
    while(true)
    {
        FunnyOperation op=FunnyOperation(dis_operation(gen_number));
        if(op==FunnyOperation::BURN && last!=op)
        {
            if(maxNumber==0)   break;
            maxNumber--;
            opt.push(op);
            helps.push_back(op);
        }
        else if(op==FunnyOperation::BURN && last==FunnyOperation::BURN)
        {
            continue;
        }
        else
        {
            opt.push(op);
            helps.push_back(op);
        }
        last=op;
    }
    calculateHelp();

    size_t row=m_size;
    size_t col=m_size;
    std::vector<std::vector<Cell>> rotated;
    std::vector<std::vector<Cell>> question;
    rotated=std::vector(col, std::vector<Cell>(row));
    question=m_cells;

    while(opt.size())
    {
        FunnyOperation now=opt.front();
        opt.pop();
        switch(now)
        {
        case FunnyOperation::LEFT_ROTATE:
        {
            for(int i=0;i<row;++i)
            {
                for(int j=0;j<col;++j)
                {
                    rotated[col-j-1][i]=question[i][j];
                }
            }
            question=rotated;
            break;
        }
        case FunnyOperation::RIGHT_ROTATE:
        {
            for(int i=0;i<row;++i)
            {
                for(int j=0;j<col;++j)
                {
                    rotated[j][row-i-1]=question[i][j];
                }
            }
            question=rotated;
            break;
        }
        case FunnyOperation::BURN:
        {
            for(size_t i=row-1;i>0;--i)
            {
                for(size_t j=0;j<col;++j)
                {
                    if(i==row-1)
                    {
                        if(question[i][j].getValue()!=1 && question[i-1][j].getValue()==1)
                        {
                            question[i][j].setNum(1);
                        }
                    }
                    if(question[i-1][j].getValue()>1)
                    {
                        question[i][j].setNum(question[i-1][j].getValue()-1);
                        question[i-1][j].setNum(1);
                        question[i][j].setColor(question[i-1][j].getColor());
                    }
                }
            }
            break;
        }
        }
    }
    answers=question;
    //提交按钮 判断答案
    connect(submitButton,&QPushButton::clicked,this,&Funny::judge);
    update();
}

void Funny::left_rotate()
{
    // 旋转矩阵
    size_t row=m_size;
    size_t col=m_size;

    std::vector<std::vector<Cell>> rotated(col, std::vector<Cell>(row));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            rotated[col - j - 1][i] = m_cells[i][j];
        }
    }

    // 更新历史状态
    // 将操作后的矩阵存入栈中
    m_cellsHistory.push(rotated);

    // 更新当前的矩阵
    m_cells=rotated;
    update();
}

void Funny::right_rotate()
{
    // 旋转矩阵
    size_t row=m_size;
    size_t col=m_size;
    std::vector<std::vector<Cell>> rotated(col, std::vector<Cell>(row));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            rotated[j][row - i - 1] = m_cells[i][j];
        }
    }
    // 更新历史状态
    // 将操作后的矩阵存入栈中
    m_cellsHistory.push(rotated);

    // 更新当前的矩阵
    m_cells=rotated;
    update();
}

void Funny::burn()
{
    // 燃烧矩阵
    // 根据游戏规则，可以理解为，先判断当前方格内的值是否为1，如果是，则不会向下burn，
    // 否则，向下burn，同时将burn后的数值变为1，位于其正下方的方格的颜色也会发生相应的改变
    // 根据游戏规则，由下向上遍历
    // 考虑到特判情况，位于最下面的一行无法往下流动，所以当其数值不为1时，burn后也会自动转化为1
    size_t row=m_size;
    size_t col=m_size;
    for (size_t i = row - 1; i > 0; --i)
    {
        for (size_t j = 0; j < col; ++j)
        {
            if(i == row - 1 )
            {
                if(m_cells[i][j].getValue() != 1 && m_cells[i - 1][j].getValue() == 1)
                {
                    m_cells[i][j].setNum(1);
                }
            }
            if(m_cells[i - 1][j].getValue() > 1)
            {
                m_cells[i][j].setNum(m_cells[i - 1][j].getValue() - 1);
                m_cells[i - 1][j].setNum(1);
                m_cells[i][j].setColor(m_cells[i - 1][j].getColor());
            }
        }
    }
    m_cellsHistory.push(m_cells);
    update();
}

void Funny::undo()
{
    if (m_cellsHistory.size() == 1)
    {
        qDebug() << "No more undo" << Qt::endl;
        return;
    }
    if (m_cellsHistory.size() > 1)
    {
        m_cellsHistory.pop();
        m_cells = m_cellsHistory.top();
        qDebug() << "Undo successfully" << Qt::endl;
        qDebug() <<"stack size: "<<m_cellsHistory.size()<< Qt::endl;
    }
    else
    {
        qDebug() <<"Unsuccessful"<< Qt::endl;
    }
    update();
}

inline QColor parseRGB(const QString &rgbStr)
{
    static QRegularExpression rx(R"(rgb\((\d+),\s*(\d+),\s*(\d+)\))");
    QRegularExpressionMatch match = rx.match(rgbStr);
    if (match.hasMatch())
    {
        int r = match.captured(1).toInt();
        int g = match.captured(2).toInt();
        int b = match.captured(3).toInt();
        return QColor(r, g, b);
    }
    else
    {
        throw std::invalid_argument("Invalid RGB string format");
    }
}

inline bool compareRgb(const QString &rgbStr1, const QString &rgbStr2) {
    QColor color1 = parseRGB(rgbStr1);
    QColor color2 = parseRGB(rgbStr2);

    qDebug()<<color1.red()<<color1.green()<<color1.blue();
    qDebug()<<color2.red()<<color2.green()<<color2.blue();

    int red=abs(color1.red()-color2.red());
    int green=abs(color1.green()-color2.green());
    int blue=abs(color1.blue()-color2.blue());
    if(red<=15 && green<=15 && blue<=15)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void Funny::judge()
{
    std::cout<<"judging\n";
    for(size_t i=0;i<m_size;i++)
    {
        for(size_t j=0;j<m_size;j++)
        {
            if(compareRgb(QString::fromStdString(m_cells[i][j].getColor()),QString::fromStdString(answers[i][j].getColor())))
            {
                qDebug()<<m_cells[i][j].getColor();
                qDebug()<<answers[i][j].getColor();
                WA();
                return;
            }
        }
    }
    if(m_cells[0][0].getValue()==0)
    {
        return;
    }
    AC();
    return;
}

void Funny::WA()
{
    waDialog=new WADialog(nullptr);
    connect(waDialog,&WADialog::backToMain,this,&Funny::onBackButtonClicked);
    waDialog->exec();
    return;
}

void Funny::AC()
{
    acDialog=new ACDialog();
    connect(acDialog,&ACDialog::backToMain,this,&Funny::onBackButtonClicked);
    acDialog->exec();
    return;
}

void Funny::onBackButtonClicked()
{
    helps.clear();
    while(m_cellsHistory.size())
    {
        m_cellsHistory.pop();
    }
    emit backToMain();
    for(size_t i=0;i<m_size;i++)
    {
        for(size_t j=0;j<m_size;j++)
        {
            m_cells[i][j].setNum(0);
            answers[i][j].setNum(0);
            m_cells[i][j].setColor("rgb(255, 255, 255)");
            answers[i][j].setColor("rgb(255, 255, 255)");
        }
    }
}

QImage Funny::Mosaic(const QImage &sourceImage,int blockSize)       //马赛克算法，对原有的图片进行处理,转化为马赛克风格
{
    QImage mosaicImage=sourceImage;
    int width=sourceImage.width();
    int height=sourceImage.height();

    for(int y=0; y<height;y+=blockSize)
    {
        for(int x=0;x<width;x+=blockSize)
        {
            // 计算块内的平均颜色
            int red=0, green=0,blue=0,pixelCount=0;
            for(int yy=y;yy<y+blockSize && yy<height;yy++)
            {
                for(int xx=x; xx<x+blockSize && xx<width;xx++)
                {
                    QColor color=sourceImage.pixelColor(xx,yy);
                    red+=color.red();
                    green+=color.green();
                    blue+=color.blue();
                    ++pixelCount;
                }
            }
            red/=pixelCount;
            green/=pixelCount;
            blue/=pixelCount;

            QColor averageColor(red,green,blue);

            // 将块内所有像素设置为平均颜色
            for(int yy=y;yy<y+blockSize && yy<height;yy++)
            {
                for(int xx=x; xx<x+blockSize && xx<width;xx++)
                {
                    mosaicImage.setPixelColor(xx,yy,averageColor);
                }
            }
        }
    }
    return mosaicImage;
}

void Funny::loadImage()
{
    QString fileName=QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp)"));
    if (!fileName.isEmpty())
    {
        helps.clear();
        qDebug()<<fileName;
        QImage sourceImage(fileName);
        int blockSize=sourceImage.height()/9;
        QImage mosaicImage=Mosaic(sourceImage, blockSize);              //对原有的图像进行马赛克处理

        m_size=9;
        qDebug()<<"success mosaic";
        for(int i=0;i<m_size;i++)                                       //转化为想要的rgb格式
        {
            for(int j=0;j<m_size;j++)
            {
                QColor color=mosaicImage.pixelColor(i*blockSize,j*blockSize);
                QString colorQString = QString("rgb(%1, %2, %3)")
                                           .arg(color.red())
                                           .arg(color.green())
                                           .arg(color.blue());

                // 将 QString 转换为 std::string
                std::string colorStdString=colorQString.toStdString();
                m_cells[j][i].setColor(colorStdString);                 //设置m_cells数组
                m_cells[j][i].setNum(getRandNum());
            }
        }
        while(m_cellsHistory.size())
        {
            m_cellsHistory.pop();
        }
        m_cellsHistory.push(m_cells);
        setGame();
    }
}

void Funny::loadExit()                              //导入已经存在的地图
{
    helps.clear();
    QString path=QApplication::applicationDirPath();
    QString defaultDir=path+"/PlayerMap";  // 指定默认文件夹路径
    QString fileName=QFileDialog::getOpenFileName(this, "Open File", defaultDir, "Bin file(*.bin)");

    if (fileName.isEmpty()) {
        QMessageBox::critical(this, "错误", "你没有导入任何地图");
    }

    QFile file(fileName);
    QDataStream in(&file);
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical() << "无法打开文件进行录入";
        return;
    }
    QString m_cells_color;
    int m_cells_num;
    for(size_t i=0;i<m_size;i++)
    {
        for(size_t j=0;j<m_size;j++)
        {

            in>>m_cells_num;
            m_cells[i][j].setNum(m_cells_num);
        }
    }
    for(size_t i=0;i<m_size;i++)
    {
        for(size_t j=0;j<m_size;j++)
        {
            in>>m_cells_color;
            m_cells[i][j].setColor(m_cells_color.toStdString());
        }
    }

    QString answer_color;
    int answer_num;
    for(size_t i=0;i<m_size;i++)
    {
        for(size_t j=0;j<m_size;j++)
        {

            in>>answer_num;
            answers[i][j].setNum(answer_num);
        }
    }
    for(size_t i=0;i<m_size;i++)
    {
        for(size_t j=0;j<m_size;j++)
        {
            in>>answer_color;
            answers[i][j].setColor(answer_color.toStdString());
        }
    }
    file.close();
    while(m_cellsHistory.size())                //注意将原来的栈清空
    {
        m_cellsHistory.pop();
    }
    m_cellsHistory.push(m_cells);
    //提交按钮 判断答案
    connect(submitButton,&QPushButton::clicked,this,&Funny::judge);
    update();
}


void Funny::dialogGenerate()
{
    m_dialog=new QDialog(this);
    m_dialog->setWindowTitle("请设定地图名");
    QVBoxLayout *dialogLayout=new QVBoxLayout(m_dialog);
    dialogLayout->addWidget(new QLabel("输入地图名",m_dialog));

    inputLineEdit=new QLineEdit(m_dialog);
    dialogLayout->addWidget(inputLineEdit);

    QPushButton *sureButton=new QPushButton("确认",m_dialog);
    connect(sureButton,&QPushButton::clicked,this,&Funny::saving);

    dialogLayout->addWidget(sureButton);
    m_dialog->setLayout(dialogLayout);

    m_dialog->show();
}

void Funny::saving()                //执行将地图进行保存的工作
{
    QString inputName=inputLineEdit->text();
    if(inputName=="")
    {
        QMessageBox::critical(nullptr,"错误","文件名为空，请重新输入文件名");
        inputLineEdit->setFocus();
    }
    else
    {
        QDir dir("./PlayerMap");
        if(!dir.exists())
        {
            qDebug()<<"文件夹不存在";
        }
        QString fileName=inputLineEdit->text()+".bin";
        QString filePath=dir.filePath(fileName);
        QFile file(filePath);
        QDataStream out(&file);
        if(!file.open(QIODevice::WriteOnly))
        {
            qDebug()<<"错误 无法将趣味模式的地图写入";
            return;
        }
        for(size_t i=0;i<m_size;i++)
        {
            for(size_t j=0;j<m_size;j++)
            {
                out<<m_cells[i][j].getValue();
            }
        }
        for(size_t i=0;i<m_size;i++)
        {
            for(size_t j=0;j<m_size;j++)
            {
                out<<QString::fromStdString(m_cells[i][j].getColor());
            }
        }


        for(size_t i=0;i<m_size;i++)
        {
            for(size_t j=0;j<m_size;j++)
            {
                out<<answers[i][j].getValue();
            }
        }
        for(size_t i=0;i<m_size;i++)
        {
            for(size_t j=0;j<m_size;j++)
            {
                out<<QString::fromStdString(answers[i][j].getColor());
            }
        }
        file.close();
        QMessageBox::information(nullptr,"成功","地图已经成功保存");
        m_dialog->close();
        return;
    }

}

void Funny::help()
{
    if(helps.size())
    {
        if(Finals.empty() || checkIsAllOne())
        {
            QMessageBox::information(nullptr,"提示","所有提示已经提供完毕");
            return;
        }
        FunnyOperation topOperation=Finals.front();
        switch(topOperation)
        {
        case FunnyOperation::BURN:
            QMessageBox::information(nullptr,"提示","下一步操作是燃烧\n注意：玩家请按照提示操作，不要做与提示不符的操作，否则只能撤回");
            break;
        case FunnyOperation::LEFT_ROTATE:
            QMessageBox::information(nullptr,"提示","下一步操作时左旋转\n注意：玩家请按照提示操作，不要做与提示不符的操作，否则只能撤回");
            break;
        case FunnyOperation::RIGHT_ROTATE:
            QMessageBox::information(nullptr,"提示","下一步操作时右旋转\n注意：玩家请按照提示操作，不要做与提示不符的操作，否则只能撤回");
            break;
        }
        Finals.pop_front();
    }
    else
    {
        QMessageBox::information(nullptr,"提示","抱歉，目前没有提示");
    }
}

void Funny::calculateHelp()
{
    Finals.clear();
    int lefts=0;
    int rights=0;
    for(int i=0;i<helps.size();i++)
    {
        if(helps[i]==FunnyOperation::BURN)
        {
            int cnt=lefts-rights;
            cnt%=4;
            if(cnt==0)
            {
            }
            else if(cnt>0)
            {
                if(cnt==3)
                {
                    Finals.push_back(FunnyOperation::RIGHT_ROTATE);
                }
                else
                {
                    for(int j=1;j<=cnt;j++)
                    {
                        Finals.push_back(FunnyOperation::LEFT_ROTATE);
                    }
                }
            }
            else
            {
                cnt=abs(cnt);
                if(cnt==3)
                {
                    Finals.push_back(FunnyOperation::LEFT_ROTATE);
                }
                for(int j=1;j<=cnt;j++)
                {
                    Finals.push_back(FunnyOperation::RIGHT_ROTATE);
                }
            }
            Finals.push_back(FunnyOperation::BURN);
            lefts=0;
            rights=0;
        }
        else if(helps[i]==FunnyOperation::LEFT_ROTATE)
        {
            lefts++;
        }
        else if(helps[i]==FunnyOperation::RIGHT_ROTATE)
        {
            rights++;
        }
    }
}

bool Funny::checkIsAllOne()
{
    for(int i=0;i<m_size;i++)
    {
        for(int j=0;j<m_size;j++)
        {
            if(m_cells[i][j].getValue()!=1)     return false;
        }
    }
    return true;
}
