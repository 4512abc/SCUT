#include "player.h"

Player::Player() {
    account = "游客";
    password = "null";
    dormitoryNumber = "gzwzw";
    phoneNumber = "gzwzw";
    accountIndex = INT_MAX;//达到最大数量时候有bug，anyway

}
void Player::reInitialize()
{
    account = "游客";
    password = "null";
    dormitoryNumber = "gzwzw";
    phoneNumber = "gzwzw";
    accountIndex = INT_MAX;//达到最大数量时候有bug，anyway
}
Player &Player::operator=(const Player &other)//重载一下，怕浅拷贝漏了东西
{
    // 更好的实现方式是使用引用
    if (this != &other) { // 防止自我赋值
        account = other.account;
        password = other.password;
        accountIndex = other.accountIndex;
        StartPos = other.StartPos;

        dormitoryNumber = other.dormitoryNumber;
        phoneNumber = other.phoneNumber;

        practiceGameRecords = other.practiceGameRecords;
        competitionGameRecords = other.competitionGameRecords;

    }
    return *this;

}

bool Player::setAccount(QString accountString)
{
    //还没有加入限制条件、判断逻辑，暂时不管
    //12位以内数字+字母,无空格
    //不可与先前的账号重复，读一下文件
    QFile file(ACCOUNTLISTROAD);
    file.open(QIODevice::ReadOnly);
    if(file.isOpen()){
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_6_5);
        Player player;
        while (!file.atEnd()) {
            in >> player;
            if(player.getAccount() == accountString){
                return false;//账号重复
            }
        }
    }

    //bool hasSpacing;
    for(int i = 0;i < accountString.size()-1;i++)//此处i要减一
    {
        if(accountString[i] == ' ')
        return false;
    }
    if(accountString.size()>=1&& accountString.size() <= 12)
    {
        account = accountString;
        return true;
    }
    else return false;
}
bool Player::setPassword(QString passwordString)
{
    //6-18位密码，数字+字母，无空格
    for(int i = 0;i < passwordString.size()-1;i++)
    {
        if(passwordString[i] == ' ')
        return false;
    }
    if(passwordString.size() >= 6 && passwordString.size() <= 18)
    {
        password = passwordString;
        return true;
    }
    else return false;
}


QDataStream &operator<<(QDataStream &out, const Player &player) {
    out << player.accountIndex << player.account << player.password
        << player.StartPos
        << player.dormitoryNumber  << player.phoneNumber;  // 将所有成员变量写入流
    return out;
}

QDataStream &operator>>(QDataStream &in, Player &player) {
    in >> player.accountIndex >> player.account >> player.password
        >> player.StartPos
        >> player.dormitoryNumber >> player.phoneNumber;                              // 从流中读取成员变量
    return in;
}
