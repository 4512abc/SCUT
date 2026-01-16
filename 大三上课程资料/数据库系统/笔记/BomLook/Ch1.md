# Ch1

## Database Management System (DBMS)（数据库管理系统，DBMS）
> [!NOTE]
>
> **总结：数据库所拥有的相关部分**
>
> - 相互关联的数据集合
> - 用于访问数据的程序集合
> - 便捷且高效的使用环境

## University Database Example（大学数据库示例）
## Drawbacks of using file systems to store data（使用文件系统存储数据的缺点）
> [!NOTE]
>
> 文件系统作为数据库的缺点
>
> - 数据冗余与不一致性
> - 数据访问困难
> - 数据隔离
> - 完整性问题
> - 更新的原子性
> - 并发访问
> - 安全问题

## Levels of Abstraction（抽象层次）
> [!IMPORTANT]
>
> 数据库的抽象层次
>
> - 物理层：**描述记录的存储方式**
>
> - 逻辑层：描述数据库中**存储的数据及其相互关系**
>
> - 视图层：应用程序，**其隐藏了数据类型的细节**，为保障安全性，视图层还可以隐藏部分信息
>
> - 架构图：
>
>   ![image-20251119161150546](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251119161150546.png)



## Instances and Schemas（实例与模式）
> [!IMPORTANT]
>
> - Schema：数据库的逻辑结构
>   - **Physical schema**: database design at the physical level
>   - **Logical schema**: database design at the logical level
> - Instance：特定时间点下，数据库的实际内容
> - 类比：Schema 和 Instance 的关系，类似 Type 和 Variables
> - Physical Data Independence：修改物理模式而无需更改逻辑模式的能力
>   - 实现了多个模式的相互隔离
>   - 各个层次的模式接口明确定义



## Data Models（数据模型）
> [!important]
>
> 数据模型：用于描述以下内容的工具集合
>
> - 数据
> - 数据关系
> - 数据语义
> - 数据约束
>
> 分类：
>
> - 关系模型
> - E-R模型：用于数据库设计
> - 基于对象的数据模型
> - XML模型
> - 网状模型
> - 层次模型



## Relational Model（关系模型）
## Data Manipulation Language (DML)（数据操纵语言，DML）
> [!note]
>
> Data Manipulation Language：用于**访问和操纵按相应数据模型**组织的数据的语言
>
> 又称为查询语言，分类为：
>
> - 过程化：需要指定所需数据和获取方式
> - 非过程化：只需指定所需数据即可

## SQL
> [!important]
>
> SQL：广泛使用的非过程化DML
>
> 应用程序访问数据库的方式：
>
> 1. 使用支持 **嵌入式SQL 的语言扩展**
> 2. 支持将**SQL查询**发送至数据库的 **应用程序接口**

## Data Definition Language (DDL)（数据定义语言，DDL）
> [!note]
>
> Data Definition Language：用于定义数据库模式的规范表示法
>
> ==过程（？）：写一组DDL语言，DDL编译器将生成一组表模板，存储在数据字典中==
>
> 数据字典：可以理解为数据的蓝图，包含了数据的相关信息
>
> - 数据库模型
> - 完整性约束
>   - 主键
>   - 参照完整性
> - 授权

## Database Design（数据库设计）
> [!important]
>
> 设计数据库总体结构的过程：
>
> - 逻辑设计：确定数据库模型
>   - 目标：找到优质的关系模式集合
>   - 角度：
>     - 业务决策：哪些属性？
>     - 计算机决策：采用哪些关系模式？属性如何在各模式间分配？
> - 物理设计：决定数据库的物理布局（分布）

## Database Design?（数据库设计探讨？）

## Design Approaches（设计方法）
> [!note]
>
> 实体：可与其他部分区分的对象，通过一组属性描述
>
> 关系：多个实体间的关联
>
> 通过E-R图进行图形化表示

## The Entity-Relationship Model（实体-关系模型）
## Storage Management（存储管理）
>[!important]
>
>存储管理器：负责提供数据库中**存储的底层数据**与应用程序及提交给**系统的查询之间的接口**
>
>任务：
>
>- 与文件管理器进行交互
>- 高效存储、检索、更新数据
>
>问题：
>
>- 存储方法
>- 文件组织
>- 索引和哈希

### Query Processing（查询处理）
![image-20251119165915212](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251119165915212.png)

> [!important]
>
> 过程
>
> 1. Parsing and translation（解析与转换）
> 2. Optimization（优化）
> 3. Evaluation（执行）
>    - 多种方法
>      - 等价表达式
>      - 不同算法
>
> 目的：
>
> 1. 优化的好坏，对执行方式的成本消耗差距极大
> 2. 需要估算操作成本
>    - 依赖于数据库必须维护的关系 **的相关统计信息**
>    - 需要**估算中间结果的统计信息**，从而**计算复杂表达式的成本**

### Transaction Management（事务管理）
> [!important]
>
> 事务：数据库应用中**执行单一逻辑功能的一系列操作集合**
>
> 事务管理组件确保数据库**在系统故障（如电源故障、操作系统崩溃）和事务故障时仍保持一致（正确）状态**
>
> 并发控制管理器**控制并发事务间的交互，确保数据库一致性**

### Database Users and Administrators（数据库用户与管理员）
### Database System Internals（数据库系统内部结构）
### Database Architecture（数据库架构）
> [!note]
>
> 数据库架构：受底层计算机系统的影响
>
> - 集中式
> - 客户端-服务器模式
> - 并行模式
> - 分布式

### History of Database Systems（数据库系统发展史）

### 数据库系统发展史

- 20 世纪 50 年代至 60 年代初：
  - 采用磁带存储进行数据处理
  - 磁带仅支持顺序访问
  - 采用穿孔卡片（Punched cards）输入数据
  - 首个通用数据库管理系统是集成数据存储（网络数据模型），由通用电气公司的查尔斯・巴赫曼于 20 世纪 60 年代初设计，他于 1973 年获得图灵奖
- 20 世纪 60 年代末至 70 年代：
  - 硬盘支持直接访问数据
  - 网络模型和层次模型被广泛应用
  - 20 世纪 60 年代末，IBM 公司开发了 IMS 数据库管理系统（层次数据模型），目前仍用于 Travelocity 等网络旅游服务
  - E.F. 科德提出关系数据模型，并于 1981 年因此项工作获得 ACM 图灵奖
  - IBM 研究中心启动 System R 原型开发，加州大学伯克利分校启动 Ingres 原型开发
  - 实现了当时高性能的事务处理

- 20 世纪 80 年代：
  - 关系型原型研究演进为商业系统
  - SQL 成为行业标准
  - 吉姆・格雷因在数据库事务管理方面的贡献，于 1998 年获得图灵奖
  - 并行数据库系统和分布式数据库系统兴起
  - 面向对象数据库系统出现
- 20 世纪 90 年代：
  - 大型决策支持和数据挖掘应用涌现
  - 大型多 TB 级数据仓库出现
  - 网络电子商务兴起
- 21 世纪初：
  - XML 和 XQuery 标准确立
  - 自动化数据库管理应运而生
