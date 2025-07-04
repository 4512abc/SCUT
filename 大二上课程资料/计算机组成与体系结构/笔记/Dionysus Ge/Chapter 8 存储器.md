# 8.1 基本概念



- 存储器访问时间
  对存储器速度的一个有用衡量标准。从开始传输一个数据字的操作到结束传输所用的时间。
- 存储器周期时间
  两个连续的存储器操作开始时刻之间的最小时间延迟。
- 随机存取存储器（RAM）
- 高速缓冲存储器（cache memory）
- 虚拟存储器
- 块传输

# 8.2 随机存取存储器（RAM）

## 存储器芯片的内部结构



- 字线
- 位线
- 读 / 写电路
  片选信号（CS）
  读 / 写控制信号（）

## 静态存储器



- 静态存储器
- 静态随机存取存储器（SRAM）

##### 读

##### 写

##### 互补金属氧化物半导体单元（CMOS unit）



- 易失性

## 动态随机存取存储器



- 动态随机存取存储器（DRAM）
- 刷新
- 异步动态随机存取存储器

##### 快速页面模式

## 同步动态随机存取存储器



- 模式寄存器
- 列地址选通线（CAS line）
- 行地址选通线（RAS line）
- 存储器延迟
- 带宽
- 双倍数据速率同步动态随机存取存储器
  双倍数据速率同步动态随机存取存储器（DDR SDRAM）
- 兰巴斯（Rambus，一种内存技术）

## 大容量存储器结构

#### 静态存储器系统



- 芯片选择
- 控制线

#### 动态存储器系统



- 单列直插式内存模块（SIMM）
- 双列直插式内存模块（DIMM）

#### 存储器控制器



- 存储器控制器
- 请求

#### 刷新成本

#### 技术选择

# 8.3 只读存储器（ROM）



- 只读存储器

## 只读存储器（ROM）

## 可编程只读存储器（PROM）



- 可编程只读存储器

## 可擦除可编程只读存储器（EPROM）



- 可擦除可编程只读存储器

## 电可擦除可编程只读存储器（EEPROM）



- 电可擦除可编程只读存储器

## 闪存



- 闪存卡
- 闪存驱动器

# 8.4 直接存储器访问（DMA）



- 直接存储器访问
- DMA 控制器

# 8.5 存储器层次结构



- 处理器高速缓存 L1、L2、L3
- 主存储器
- 磁盘

# 8.6 高速缓存



- 局部性原理
- 高速缓存块
- 高速缓存行
- 映射函数
- 替换算法
- 高速缓存命中
  - 读或写命中
- 写
  - 写直达
  - 写回 / 回拷
    脏位，修改位
- 高速缓存未命中
  - 读未命中
    加载通过 / 早期重启
  - 写未命中

## 映射函数

### 直接映射

### 全相联映射



- 相联查找

### 组相联映射

### 过时数据



- 有效位
- 过时数据
- 刷新高速缓存
- 高速缓存一致性

## 替换算法



- 最近最少使用（LRU）
- LRU 替换算法

# 8.7 性能因素



- 性价比

## 命中率和未命中惩罚



- 命中率，未命中率

## 处理器芯片上的高速缓存

## 一些改进



- 写缓冲器
- 预取
- 无锁定高速缓存

# 8.8 虚拟存储器



- 虚拟地址
- 逻辑地址
- 存储器管理单元（MMU）

## 地址转换



- 页
- 虚拟页号（高位地址位）
- 偏移量（低位地址位）
- 页表
- 页框
- 页表基址寄存器

## 转换后备缓冲器（TLB）



- 转换后备缓冲器

## 缺页



一种方法：使用 LRU 算法策略在内存管理单元中替换页面

# 8.9 存储器管理请求



- 系统空间
- 用户空间
- 保护
- 管理模式
- 用户模式
- 特权指令

# 8.10 辅助 / 二级存储器

## 磁盘



- 相位编码
- 曼彻斯特编码
- 自同步

## 光盘（CD）



- 光盘
- 只读光盘（CD - ROM）

### 光盘技术



- 坑（pit）
- 岸（land）

### 只读光盘（CD - ROM）



- 扇区

### 可记录光盘（CD - R）



- 可记录光盘

### 可重写光盘（CR - RW）



- 可重写光盘
- 退火

## 数字多功能光盘（DVD）



- 数字多功能光盘

## 磁带



- 记录
- 文件
- 文件标记
- 首部
- 标识符