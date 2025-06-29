
#include "Zoo.h"
#include "Zoo.cpp"
#include <iostream>
using namespace std;

int main()//测试一个成年人的活动
{
    Zoo zoo;
    zoo.openZoo();
    //zoo.getAdult(1).buyZooTicket();   此处未get地址，故修改无效
    // Adult adult1;
    // cout << "moneyOwned: " << adult1.getMoneyOwned() << endl;
    // adult1.generateChildren();
    // cout << "childrenAmount:" << adult1.getChildrenNumber()  << endl;
    // //测试买票
    // adult1.buyZooTicket();
    // cout << "After buy zoo ticket, moneyOwned: " << adult1.getMoneyOwned() << endl;
    // //测试买食物
    // adult1.buyFood(zoo.getFoodSeller());
    // cout << adult1.getChildrenNumber() << endl;

    // //测试发食物
    // adult1.distributeFood();
    // cout << "after distribution child has ";
    // cout << adult1.getChildren().at(0).invokePeanuts().getAmount();
    // cout << " peanuts" << endl;
    // //测试喂食物
    // adult1.getChildren().at(0).feed(zoo.getElephantEnclosure(), adult1.getChildren().at(0).invokePeanuts().getAmount());
    // cout << "after feeding child has ";
    // cout << adult1.getChildren().at(0).invokePeanuts().getAmount();
    // cout << " peanuts" << endl;
    // //测试喂超出食量 ok
    // adult1.getChildren().at(0).invokePeanuts().setAmount(3000);
    // adult1.getChildren().at(0).feed(zoo.getElephantEnclosure(), adult1.getChildren().at(0).invokePeanuts().getAmount());
    // if(zoo.getElephantEnclosure().getElephant().Full()) cout << "elephant is full" << endl;
    // cout << "after feeding child has ";
    // cout << adult1.getChildren().at(0).invokePeanuts().getAmount();
    // cout << " peanuts" << endl;
    // //测试围栏能否正常超过阈值
    // cout << "after feeding one time, enclosure's dirty level become: " << zoo.getElephantEnclosure().getDirtyLevel();
    // zoo.getElephantEnclosure().getElephant().setEatenFood(0);
    // adult1.getChildren().at(0).feed(zoo.getElephantEnclosure(), adult1.getChildren().at(0).invokePeanuts().getAmount());
    // cout << " after feeding two times, enclosure's dirty level become: " << zoo.getElephantEnclosure().getDirtyLevel() << endl;
    // zoo.getElephantEnclosure().getElephant().setEatenFood(0);
    // adult1.getChildren().at(0).feed(zoo.getElephantEnclosure(), adult1.getChildren().at(0).invokePeanuts().getAmount());
    // cout << " after feeding three times, enclosure's dirty level become: " << zoo.getElephantEnclosure().getDirtyLevel() << endl;
    // //测试zookeeper是否能够清理
    // zoo.getZooKeeper().checkAndCloseEnclosure(zoo.getElephantEnclosure());
    // if(zoo.getElephantEnclosure().getCloseTimes() == 1) cout << "zookeeper closed the enclosure" << endl;

    // cout << "--------" << endl;
    // zoo.getZooKeeper().cleaning(&zoo.getElephantEnclosure()); //此处要传入地址用于指针接收
    // cout << "after cleaning, the enclosure";
    // if(zoo.getElephantEnclosure().returnOpenStatus())
    //     cout << "opened, dirt:" << zoo.getElephantEnclosure().getDirtyLevel() << endl;
    // else cout << "closed" << endl;
    // cout << "elephant had eaten: " << zoo.getElephantEnclosure().getElephant().getEatenFood() << endl;
    // //测试买食物超过foodseller已有量
    // adult1.setMoney(40000,0);

    // adult1.buyFood(zoo.getFoodSeller());
    // cout << "foodseller now has " << zoo.getFoodSeller().getPeanut().getAmount() << "peanuts"
    //     <<", MoneyOwned: " << zoo.getFoodSeller().getMoneyOwned() << endl;
    //测试模拟一天,测试状态码
    //zoo.simulateOneDay();
    //测试全过程
    zoo.simulateAllProcess();
}
