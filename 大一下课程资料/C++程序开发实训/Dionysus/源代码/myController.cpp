#include "myController.h"

void MyPushButton::zoom1()
{
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setStartValue(QRect(this->x(),this->y()+50,this->width(),this->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}
void MyPushButton::zoom2()
{
    //创建动态对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画时间间隔
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+50,this->width(),this->height()));
    //结束位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置缓和曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);
    //开始执行动画
    animation->start();
}

void inputDialog::input()
{
    this->setWindowTitle("自定义地图");
    this->setFixedSize(700,500);
    // 创建表格
    inputTable = new QTableWidget(6, 6, this);
    for (int i = 0; i < 6; ++i) {
        inputTable->setRowHeight(i, 70);
        for (int j = 0; j < 6; ++j) {
            QTableWidgetItem *item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            inputTable->setItem(i, j, item);
        }
    }

    // 创建确认按钮
    QPushButton *confirmButton = new QPushButton("确认", this);
    connect(confirmButton, &QPushButton::clicked, this, &inputDialog::accepted);
    confirmButton->setFixedWidth(200);
    // 创建取消按钮
    QPushButton *cancelButton = new QPushButton("取消", this);
    connect(cancelButton, &QPushButton::clicked, this, &inputDialog::reject);
    cancelButton->setFixedWidth(200);
    // 创建对话框布局
    QGridLayout *dialogLayout = new QGridLayout(this);
    dialogLayout->addWidget(inputTable, 0, 0, 1, 6);
    dialogLayout->addWidget(confirmButton, 1, 0);
    dialogLayout->addWidget(cancelButton, 1, 3);

    setLayout(dialogLayout);
    setModal(true);

}

int *inputDialog::getDataFromTable()
{
    // 获取表格数据
    int* arr = new int[36];
    // 初始化数组

    bool hasError = false;

    for (int row = 0; row < inputTable->rowCount(); ++row) {
        for (int column = 0; column < inputTable->columnCount(); ++column) {
            QTableWidgetItem *item = inputTable->item(row, column);

            if (item) {
                bool ok;
                int data = item->data(Qt::DisplayRole).toInt(&ok);
                if (ok) {
                    // 存储数据
                    arr[ row + column * 6] = data;
                } else {
                    hasError = true;
                    break;
                }
            } else {
                hasError = true;
                break;
            }
        }

        if (hasError) {
            QMessageBox::critical(nullptr, "地图输入错误", "地图漏填或填入了非数字");
            delete[] arr;
            return nullptr;
        }
    }
    return arr;
}

bool inputDialog::checkData()
{
    // 获取表格数据并检查
    for (int row = 0; row < inputTable->rowCount(); ++row) {
        for (int column = 0; column < inputTable->columnCount(); ++column) {
            QTableWidgetItem *item = inputTable->item(row, column);

            // 首先检查单元格是否有数据
            if (item) {
                // 尝试将单元格内容转换为int
                bool ok;
                int data = item->data(Qt::DisplayRole).toInt(&ok);
                if (ok) {
                    // 数据有效，进行范围检查
                    if (data < 0 || data > 4) {
                        QMessageBox::critical(nullptr, "地图输入错误", "地图填入了非0-4的数字");
                        return false;
                    }
                } else {
                    // 如果转换失败，说明单元格内容不是有效的整数
                    QMessageBox::critical(nullptr, "地图输入错误", "地图漏填");
                    return false;
                }
            } else {
                // 单元格为空
                QMessageBox::critical(nullptr, "地图输入错误", "地图漏填");
                return false;
            }
        }
    }

    return true;
}
