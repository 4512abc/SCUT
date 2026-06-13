#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

vector<int> gen_instruction_sequence(int N_instr = 320) {
    /*生成长度为 N_instr 的指令地址序列
     *参数：
     *N_instr：指令地址长度，默认 320 条
     *return：
     *指令地址序列
     */
    vector<int> seq(N_instr);
    srand((unsigned)time(nullptr));// 使用当前时间作为随机种子

    seq[0] = rand() * (N_instr - 1) / RAND_MAX;// 第一条指令的随机地址
    for (int i = 1; i < N_instr; ++i) {
        double p = rand() / (double)RAND_MAX;  //生成 0~1之间的概率
        int prev = seq[i-1];  //上一条指令地址
        if (p < 0.50) {
            // 顺序执行(50% 情况)
            seq[i] = (prev + 1) % N_instr;
        } else if (p < 0.75) {
            // 前区跳转(25% 情况)
            seq[i] = rand() * (prev + 1) / RAND_MAX;
        } else {
            // 后区跳转(25% 情况)
            if (prev + 2 >= N_instr) { //如果越界，则在整个区间随机
                seq[i] = rand() % N_instr;
            } else {
                seq[i] = prev + 2 + rand() * (N_instr - (prev + 2)) / RAND_MAX;
            }
        }
    }
    return seq;
}

vector<int> addr_to_page(const vector<int>& seq, int instr_per_page = 10) {
    /* 将指令地址序列转换为页号序列，每 10 条指令为一页
     *参数：
     *seq：指令地址的序列
     *instr_per_page：每一页包含多少条指令
     *return:
     *页号序列
     */

    vector<int> pages;
    pages.reserve(seq.size()); //预留空间提高效率
    for (int addr : seq) {
        pages.push_back(addr / instr_per_page); // 地址除以每页指令数，得到页号
    }
    return pages;
}

int simulateFIFO(const vector<int>& pages, int capacity) {
    /*
     *FIFO 页面置换模拟
     *参数：
     *pages: 页号序列
     *capacity: 页框数
     *return:
     *缺页次数
     */
    queue<int> q; //队列维护内存中的页面顺序
    unordered_map<int,bool> in_mem;// 记录页面是否在内存中
    int faults = 0;
    for (int p : pages) {
        if (!in_mem[p]) { //页面不在内存中，即缺页
            faults++;
            if ((int)q.size() == capacity) {// 判断内存是否已满，如是弹出队首页面
                int old = q.front(); q.pop();
                in_mem[old] = false;
            }
            q.push(p);// 将当前页面加入队尾
            in_mem[p] = true;
        }
    }
    return faults;
}

int simulateLRU(const vector<int>& pages, int capacity) {
    /*
     *LRU 页面置换模拟
     *参数：
     *pages:页号序列
     *capacity:页框数
     *return：
     *缺页次数
     */
    list<int> lru; //双向链表存放页面，前端为最近使用
    unordered_map<int, list<int>::iterator> pos;// 存放页面在链表中的迭代器
    int faults = 0;
    for (int p : pages) {
        auto it = pos.find(p);
        if (it == pos.end()) {
            // 缺页
            faults++;
            if ((int)lru.size() == capacity) {
                // 内存满，淘汰最久未使用页面
                int old = lru.back();
                pos.erase(old);
                lru.pop_back();
            }
        } else {
            // 命中，将页面移到链表前端
            lru.erase(it->second);
        }
        lru.push_front(p); //将当前页面放入前端，并更新迭代器
        pos[p] = lru.begin();
    }
    return faults;
}

int simulateOPT(const vector<int>& pages, int capacity) {
    /*
     *模拟OPT最佳页面置换
     *参数：
     *pages:页号序列
     *capacity:页框数
     *return：
     *缺页次数
     */
    vector<int> mem;//内存中页面列表
    int faults = 0;
    int N = pages.size();

    for (int i = 0; i < N; ++i) {
        int p = pages[i];

        if (find(mem.begin(), mem.end(), p) != mem.end()) {//判断是否命中
            continue;
        }
        // 缺页
        faults++;
        if ((int)mem.size() < capacity) { // 判断是否未满，是则加入
            mem.push_back(p);
        } else {
            // 已满，找未来最晚使用的页面
            int victim = 0, farthest = i + 1;
            for (int j = 0; j < (int)mem.size(); ++j) {
                int q = mem[j];
                int next_use = N;
                for (int k = i + 1; k < N; ++k) {//查找该页面下一次使用的位置
                    if (pages[k] == q) { next_use = k; break; }
                }
                if (next_use > farthest) {
                    farthest = next_use;
                    victim = j;
                }
            }
            mem[victim] = p; //用新页面替换
        }
    }
    return faults;
}

int simulateNRU(const vector<int>& pages, int capacity) {
    /*
     *模拟NRU非最近使用页面置换
     *参数：
     *pages:页号序列
     *capacity:页框数
     *return：
     *缺页次数
     */
    vector<int> mem; // 内存中页面列表
    vector<bool> refbit;//参考位数组
    int faults = 0;
    for (int p : pages) {
        auto it = find(mem.begin(), mem.end(), p);
        if (it != mem.end()) {
            // 判断是否命中，如是，设置参考位为 true
            refbit[it - mem.begin()] = true;
            continue;
        }
        // 如未命中
        faults++;
        if ((int)mem.size() < capacity) {// 判断是否未满，如是，加入页面并设置参考位
            mem.push_back(p);
            refbit.push_back(true);
        } else {
            // 如已满，寻找参考位为false 的页面淘汰
            int victim = -1;
            for (int i = 0; i < (int)mem.size(); ++i) {
                if (!refbit[i]) { victim = i; break; }
            }
            if (victim < 0) {
                // 若所有页面都被访问过，选择第一个作为牺牲页
                victim = 0;
            }
            mem[victim] = p;
            //替换并重置参考位
            fill(refbit.begin(), refbit.end(), false);
            refbit[victim] = true;
        }
    }
    return faults;
}

int main() {
    const int N_INSTR = 320;// 指令总数
    const int INSTR_PER_PAGE = 10;//每页指令数
    auto seq = gen_instruction_sequence(N_INSTR);//生成指令序列
    auto pages = addr_to_page(seq, INSTR_PER_PAGE);  // 转换为页号序列

    cout << fixed << setprecision(2);//设置输出格式：两位小数
    cout << "  页框    FIFO(%)   LRU(%)    OPT(%)    NRU(%)\n";
    for (int cap = 4; cap <= 32; ++cap) {
        int f_fifo = simulateFIFO(pages, cap);
        int f_lru  = simulateLRU(pages, cap);
        int f_opt  = simulateOPT(pages, cap);
        int f_nru  = simulateNRU(pages, cap);

        //命中率 = (1 - 缺页次数/总指令数) * 100%
        double h_fifo = (1.0 - f_fifo / double(N_INSTR)) * 100;
        double h_lru  = (1.0 - f_lru  / double(N_INSTR)) * 100;
        double h_opt  = (1.0 - f_opt  / double(N_INSTR)) * 100;
        double h_nru  = (1.0 - f_nru  / double(N_INSTR)) * 100;

        cout << setw(5) << cap << "     "<< setw(6) << h_fifo << "   "<< setw(7) << h_lru  << "   "<< setw(7) << h_opt  << "   "<< setw(7) << h_nru  << "\n";
    }
    return 0;
}
