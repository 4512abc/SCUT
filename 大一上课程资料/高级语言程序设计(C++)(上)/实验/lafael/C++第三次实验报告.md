##                                                                                                                                            C++第三次实验报告

###                                                                                                                           Task  1     精灵模拟

实验要求： 

请设计一个精灵类Spirit，要求实现对精灵的各类属性进行编辑，实现精灵间的互动，显示位置等操作；

```c++
#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<thread>
using namespace std;
int a[123][123];
class Spirit
{
private:
    string name;
    int x, y;
    int health;
    bool aliveState = 1;
    int attack;
    int defense;
public:
    static int number;
    static int aliveNumber;
    void writeIn(string n, int a1, int b, int h, int at, int de)
    {
        name = n;
        x = a1, y = b;
        health = h;
        aliveState = 1;
        attack = at;
        defense = de;
        number++;
        aliveNumber++;
        a[a1][b]++;
    }
    void getspirit()
    {
        int s, d, f; string q; int at, de;
        cout << "Cin the spirit'name " << endl;
        cin >> q;
        cout << "Cin the x,y, one by one" << endl;
        cin >> s >> d;
        cout << "Cin the attack,defense,health " << endl;
        cin >> at >> de >> f;
        this->writeIn(q, s, d, f, at, de);
    }
    void takeDamage(int damage)
    {
        if (aliveState == 1)
        {
            health -= defense - damage;
            if (health <= 0)
            {
                aliveState = 0;
                health = 0;
            }
            aliveNumber--;
        }
    }
    int setPosition(int x1, int y1)
    {
        if (x1 < 25 && y1 < 25)
        {
            x = x1, y = y1;
        }
        else
        {
            cout << "Wrong information,x and y should small than 100" << endl;
            cout << "cin your x,y" << endl;
            cin >> x1 >> y1;
            setPosition(x1, y1);
        }
    }
    int getPositionX()
    {
        return x;
    }
    int getPositionY()
    {
        return y;
    }
    string getName()
    {
        return name;
    }
    int getHealth()
    {
        return health;
    }
    int getNumber()
    {
        return number;
    }
    int getAliveNumber()
    {
        return aliveNumber;
    }
    int getDefense()
    {
        return defense;
    }
    int getAttack()
    {
        return attack;
    }
    void getInfo()
    {
        cout << "Name is " << getName() << " \n     ";
        cout << "p.x is " << getPositionX() << " \n     ";
        cout << "p.y is " << getPositionY() << " \n     ";
        cout << "Health is " << getHealth() << " \n     ";
        cout << "Now we have " << getNumber() << " spirits\n     ";
        cout << "Now there are " << getAliveNumber() << " alive\n     ";
    }
    void map()
    {
        for (int i = 0; i <= 25; i++)
        {
            for (int y = 0; y <= 25; y++)
            {
                if (i == 0) { cout << y << "   "; continue; }
                if (y == 0) { cout << i << "   "; continue; }
                if (a[i][y] == 0)
                    cout << "O   ";
                else cout << "*   ";
            }
            cout << endl;
        }
    }
};
int Spirit::number = 0;
int Spirit::aliveNumber = 0;
int main()
{
    cout << "Welcome to spirit's country\n";
    cout << "Give the number you want to create\n";
    srand(time(0));
    Spirit spirit[1235];
    int n; cin >> n;
    for (int i = 1; i <= n; i++)
        spirit[i].getspirit();
    for (int i = n + 1; i <= 40; i++)
    {
        int a1 = rand() % 35 + 1;
        int a2 = rand() % 25 + 1;
        int a3 = rand() % 925 + 1;
        int a4 = rand() % 5 + 1;
        string a = "SpiritNpc" + to_string(i);
        spirit[i].writeIn(a, a1, a2, 100, a3, a4);
    }
    spirit[1].map();
    cout << "Chose the one you want attack \n";
    cout << "Put the x,y in\n";
    int as, ada, d = 0;
    cin >> as >> ada;
    for (int i = 1; i <= 25; i++)
    {

        if (spirit[i].getPositionX() == as && spirit[i].getPositionY() == ada)
        {
            spirit[i].takeDamage(spirit[1].getAttack());
            if (spirit[i].getHealth() == 0)
                cout << "spirit die\n";
            cout << " you attack he ,the hurt is " << spirit[1].getAttack() - spirit[i].getDefense();
            break;
        }
    }
}
```

运行结果如下：

```c++
Welcome to spirit's country
Give the number you wang to create
1
Cin the spirit'name
lafael
Cin the x,y, one by one
5 5
Cin the attack,defense,health
99 99 99
0   1   2   3   4   5   6   7   8   9   10   11   12   13   14   15   16   17   18   19   20   21   22   23   24   
1   O   O   O   O   O   O   O   O   O   O   *   O   O   *   O   O   O   O   *   O   O   *   O   O   O
2   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O   O
3   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O   O   O   O
4   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
5   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   *   O   *   O   O   O
6   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O   O   O   O
7   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O
8   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O
9   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
10   O   O   O   O   O   O   *   O   *   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O
11   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
12   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
13   O   O   O   O   O   *   O   O   *   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
14   O   O   O   O   *   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O
15   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
16   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
17   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O   O   O   O
18   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O
19   O   *   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
20   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
21   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O
22   O   O   O   O   O   *   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O
23   O   O   O   O   O   O   O   O   O   O   O   O   *   O   O   O   O   O   O   O   O   *   O   O   O
24   O   O   O   O   *   O   O   O   O   *   O   O   O   O   *   *   O   O   O   O   O   *   O   O   O
25   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   O   
Chose the one you want attack
Put the x y in
1 11
 you attack he ,the hurt is 94
```

通过对地图添加x，y轴，实现了直接找到对方的操作，避免了通过名字索敌的麻烦。

此外，可在调出精灵面板时进行修改，使地图显示自身周围的人。

还可设置递归，在std::this_thread::sleep_for(std::chrono::seconds(3));的基础上逐步开始模拟，直到alive number为0；
