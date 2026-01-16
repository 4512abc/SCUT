# Ch4

## Joined Relations（连接关系）
> [!note]
>
> 连接关系：一种笛卡尔积，要求两个关系中的元组满足匹配条件，同时说明了返回结果中包含的属性
>
> - 输入两个关系，输出一个关系
> - 用途：通常在from子句中作为子查询表达式使用

## Join operations – Example（连接操作——示例）
## Outer Join（外连接）
> [!important]
>
> 外连接：连接操作的扩展，使用 null 填充缺失/未匹配的属性
>
> 操作：先执行连接，再将一个关系中 未与另一个关系匹配的元组 添加到结果中
>
> 分类：
>
> - 左外连接：左关系为主，决定保留左边的表
> - 右外连接：右关系为主，决定保留右边的表
> - 全外连接：两边的表都保留

## Left Outer Join（左外连接）
## Right Outer Join（右外连接）

## Joined Relations（连接关系）
> [!important]
>
> - 连接类型——定义两个关系中未匹配的元组如何处理，即完整保留哪张表的数据
> - 连接条件——定义两个关系中的元组如何匹配，以及结果中包含哪些属性

## Full Outer Join（全外连接）
## Joined Relations – Examples（连接关系——示例）
> [!note]
>
> ```sql
> natural on <predicate> using (A1,A2,A3...An)
> ```
>
> 指定了 on \<predicate\> ，不进行重复列的筛除
>
> ![image-20251229100720278](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251229100720278.png)
>
> ![image-20251229100727611](C:\Users\APP\AppData\Roaming\Typora\typora-user-images\image-20251229100727611.png)

## Joined Relations – Examples（连接关系——示例）
## Views（视图）
> [!note]
>
> view 
>
> 目的：向特定用户**隐藏部分数据**
>
> 定义：**任何非概念模型中的关系**，若作为“虚拟关系”对用户可见，则称为视图

## View Definition（视图定义）
> [!important]
>
> 定义：
>
> ```sql
> create view v as <query expression>
> ```
>
> 其中，\<query expression\>为合法的SQL表达式，v为视图名称。
>
> 使用方法：通过视图名引用创建的虚拟关系
>
> 特点：不是通过执行查询表达式创建新关系，而是通过保存表达式，在查询时，再将表达式代入执行

## Example Views（视图示例）
## Views Defined Using Other Views（基于其他视图定义的视图）
> [!note]
>
> 可以基于已有视图，定义新的视图。
>
> 比方说已经定义视图 $A$，我们基于视图 $A$ 定义视图 $B$
>
> 视图展开：即将上述的 $B$ 视图中使用的 $A$ 视图定义，替换为其等效的SQL表达式，类似地，$A$ 视图可能由其他视图定义，由此可以逐层递归下去。
>
> 视图依赖：分为直接依赖，依赖或者递归
>
> - 直接依赖：即 $v_1$ 中直接使用了 $v_2$
> - 依赖：$v_1$ 中直接使用了 $v_2$ ，或者所使用的视图中依赖 $v_2$
> - 递归：视图依赖于自身
>
> 视图更新：
>
> - 向视图中插入新元组，将会转换为对应的关系元组
> - 要求：一般支持**更新简单视图**
>   - from 子句中**只包含一个数据库关系**
>   - select子句仅包含关系的属性名，**无表达式、聚合函数或distinct**
>   - 查询**无group by或having子句**
>   - 未在select子句中列出的属性可设为null
> - 无法完全更新：不满足 where 子句条件
>
> 物化视图：
>
> - 创建一个物理表，将视图所对应的查询的结果全部存储下来。可以理解为一个副本，或者一个实例化的”虚拟关系“，一个快照。
> - 注意事项
>   - 查询中所使用的关系进行了更新，则物化视图的结果则过期无效。
>   - 如果需要维护物化视图，则需要在每次更新关系时，同步更新视图

## View Expansion（视图展开）


## View Expansion（视图展开）
## Views Defined Using Other Views（基于其他视图定义的视图）

## Update of a View（视图更新）
## Some Updates cannot be Translated Uniquely（部分更新无法唯一转换）

## And Some Not at All（部分视图完全无法更新）
## Materialized Views（物化视图）
## Transactions（事务）

> [!note]
>
> 事务：定义为工作的单元
>
> 原子事务：要么完全执行、要么回滚
>
> 事务的特点：
>
> - 并发的事务是彼此隔离的
> - 事务是隐式开始的
> - 以 commit work 或 rollback work 结束
> - SQL 默认自动提交
> - 可关闭会话的自动提交

## Integrity Constraints（完整性约束）

- Integrity constraints guard against accidental damage to the database, by ensuring that authorized changes to the database do not result in a loss of data consistency.（完整性约束防止数据库意外损坏，确保授权的数据库修改不会导致数据一致性丢失）
- Examples（示例）:
  - A checking account must have a balance greater than $10,000.00（支票账户余额必须大于10000美元）
  - A salary of a bank employee must be at least $4.00 an hour（银行员工时薪至少4美元）
  - A customer must have a (non-null) phone number（客户必须有（非空的）电话号码）

> [!important]
>
> 完整性约束
>
> 目的：防止数据库意外损坏，确保授权的数据库修改不会导致数据一致性丢失
>
> 分类：
>
> - 单个关系上的完整性约束
>
>   - not null（非空）
>   - primary key（主键）
>   - unique：唯一约束指定属性 $A_1,A_2...A_m$ 构成候选键，允许其为空
>   - check (P), where P is a predicate（检查谓词P是否成立）
>
> - 参展完整性
>
>   - 确保一个关系中某一组属性的值，也出现在另外一个关系的某组属性中
>
>   - 定义：设 $A$ 为属性集合，$R$ 与 $S$ 为包含 $A$ 的两个关系，且 $A$ 是 $S$ 的主键，则 $R$ 中出现的所有 $A$ 值必须出现在 $S$ 中
>
>   - 级联操作：
>
>     - Example 1: 普通参照完整性（无级联）
>
>       ```sql
>       create table course (
>           course_id char(5) primary key,
>           title varchar(20),
>           dept_name varchar(20) references department -- 参照department表的dept_name
>       );
>       ```
>
>     - Example 2: 带级联操作的参照完整性
>
>       ```sql
>       create table course (
>           ...
>           dept_name varchar(20),
>           foreign key (dept_name) references department
>               on delete cascade -- 删除department中的元组时，级联删除course中的相关元组
>               on update cascade, -- 更新department中的dept_name时，级联更新course中的相关值
>           ...
>       );
>       ```
>
>     - Alternative actions to cascade: set null, set default（级联的替代操作：置空、设默认值）
>
>   - 自参照问题：
>
>     - 自参照约束可能在更新时违反约束问题，由于参照自己，所以这个约束违反形成了一个循环
>     - 解决方法：
>       - 初始时设置外键全为空，插入全部元组后再更新
>       - 延迟约束检查，一般不支持该操作

## Integrity Constraints on a Single Relation（单个关系上的完整性约束）
## Not Null and Unique Constraints（非空和唯一约束）
## The check clause（check子句）
## Referential Integrity（参照完整性）
## Cascading Actions in Referential Integrity（参照完整性中的级联操作）
## Examples for Referential Integrity (MySQL）（参照完整性示例（MySQL））
## Examples for Referential Integrity (MySQL）（参照完整性示例（MySQL））
## Examples for Referential Integrity (MySQL）（参照完整性示例（MySQL））
## Examples for Referential Integrity (MySQL）（参照完整性示例（MySQL））
## Integrity Constraint Violation During Transactions（事务中的完整性约束违反）
## Built-in Data Types in SQL（SQL中的内置数据类型）
> [!note]
>
> | 名称      | 说明                                                         |
> | --------- | ------------------------------------------------------------ |
> | date      | 日期类型，包含4位年份、月份和日期                            |
> | time      | 时间类型，包含时、分、秒                                     |
> | timestamp | 时间戳类型，包含日期和时间                                   |
> | interval  | 时间间隔类型，两个日期/时间/时间戳值相减得到时间间隔，时间间隔可与日期/时间/时间戳值相加 |

### Index Creation（索引创建）

> [!note]
>
> 索引：一种数据结构，用于加速索引属性值匹配的数据记录
>
> Example: 为学生表的ID属性创建索引
>
> ```
> create table student (
>     ID varchar(5),
>     name varchar(20) not null,
>     dept_name varchar(20),
>     tot_cred numeric(3,0) default 0,
>     primary key (ID)
> );
> 
> -- 为student表的ID属性创建索引
> create index studentID_index on student(ID);
> ```

## User-Defined Types（用户定义类型）
> [!note]
>
> create type 用于创建用户自定义的数据类型
>
> ```sql
> -- 定义Dollars类型（金额，12位数字，2位小数）
> create type Dollars as numeric(12,2) final;
> 
> -- 使用用户定义类型创建部门表
> create table department (
>     dept_name varchar(20),
>     building varchar(15),
>     budget Dollars -- budget属性类型为Dollars
> );S
> ```

## Domains（域）

> [!note]
>
> create domain语句创建用户定义域类型，可以指定约束
>
> Example：
>
> ```sql
> -- 定义person_name域（非空的20位字符）
> create domain person_name char(20) not null;
> 
> -- 定义degree_level域（仅允许学士、硕士、博士）
> create domain degree_level varchar(10)
>     constraint degree_level_test check (value in ('Bachelors', 'Masters', 'Doctorate'));
> ```

## Large-Object Types（大对象类型）
> [!note]
>
> Large-Object Types
>
> 分类：
>
> - 二进制大对象
> - 字符大对象
> - 查询返回的结构是指向大对象的指针

## Authorization（授权）

> [!note]
>
> | 类型   | 说明                             |
> | ------ | -------------------------------- |
> | Read   | 允许读取数据，不可修改           |
> | Insert | 允许插入新数据，不可修改现有数据 |
> | Update | 允许修改数据，不可删除           |
> | Delete | 允许删除数据                     |
>
> | 类型       | 说明                     |
> | ---------- | ------------------------ |
> | Index      | 允许创建和删除索引       |
> | Resources  | 允许创建新关系           |
> | Alteration | 允许添加或删除关系的属性 |
> | Drop       | 允许删除关系             |



## Authorization Specification in SQL（SQL中的授权指定）

> [!important]
>
> 授予权限
>
> - 语法：
>
>   ```sql
>   grant <privilege list>
>   on <relation name or view name> to <user list>
>   ```
>
> - \<user list\> is:
>
>   - a user-id
>
>   - public, which allows all valid users the privilege granted
>
>   - A role
>
> - 注意
>
>   - 不包含授予底层关系的任何权限
>   - 授权者必须拥有该权限

## Privileges in SQL（SQL中的权限）
> [!note]
>
> | 类型           | 说明                       |
> | -------------- | -------------------------- |
> | select         | 允许读取关系或通过视图查询 |
> | insert         | 允许插入元组               |
> | update         | 允许使用update语句更新     |
> | delete         | 允许删除元组               |
> | all privileges | 所有允许的权限的简写       |

## Revoking Authorization in SQL（SQL中的撤销授权）
> [!important]
>
> 撤销权限
>
> - 语法
>
>   ```sql
>   revoke <privilege list>
>   on <relation name or view name> from <user list>
>   ```
>
> - 注意事项
>
>   - 若同一用户通过不同授权者获得同一权限，撤销一次后可能仍保留该权限
>   - 所有依赖于被撤销权限的权限也会被撤销

## Roles（角色）
- Roles can be regarded as positions.（角色可视为职位）
  ```sql
  -- 创建instructor角色
  create role instructor;
  
  -- 将instructor角色授予用户Amit
  grant instructor to Amit;
  
  -- 授予instructor角色对takes表的查询权
  grant select on takes to instructor;
  
  -- 创建teaching_assistant角色
  create role teaching_assistant;
  
  -- 将teaching_assistant角色授予instructor角色（角色继承）
  grant teaching_assistant to instructor;
  
  -- 创建dean角色
  create role dean;
  
  -- 将instructor角色授予dean角色（角色链）
  grant instructor to dean;
  
  -- 将dean角色授予用户Wang
  grant dean to Wang;
  ```
- Instructor inherits all privileges of teaching_assistant.（instructor角色继承teaching_assistant角色的所有权限）
- Chain of roles: Wang → dean → instructor → teaching_assistant（角色链：Wang拥有dean的权限，dean继承instructor的权限，instructor继承teaching_assistant的权限）

> [!important]
>
> 创建角色
>
> - 用法
>
>   ```sql
>   create role instructor;
>   ```
>
> - 注意：
>
>   - 权限可以被授予给角色（职位）
>
>     ```sql
>     -- 授予instructor角色对takes表的查询权
>     grant select on takes to instructor;
>     ```
>
>   - 角色可以授予给用户，或者其他角色
>
>     ```sql
>     -- 创建teaching_assistant角色
>     create role teaching_assistant;
>             
>     -- 将teaching_assistant角色授予instructor角色（角色继承）
>     grant teaching_assistant to instructor;
>     ```

## Authorization on Views（视图的授权）
> [!important]
>
> 授权视图
>
> Example：
>
> ```sql
> -- 创建地质学系教师视图
> create view geo_instructor as
>     (select *
>      from instructor
>      where dept_name = 'Geology');
> 
> -- 授予geo_staff角色对该视图的查询权
> grant select on geo_instructor to geo_staff;
> ```
>
> - 注意
>
>   - 视图的授权独立于底层关系，即如果有视图的权限，没有关系的权限，还是可以执行视图的访问等合法行为
>
>   - 视图的创建者必须拥有底层关系的相关权限，否则将会创建失败
