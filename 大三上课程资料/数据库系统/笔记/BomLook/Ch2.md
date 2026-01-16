# Ch2

## Example of a Relation（关系示例）
## Attribute Types（属性类型）
> [!NOTE]
>
> 属性的域：每个属性的合法值集合
>
> 要求：原子性，即属性值不可再分
>
> 特点：null 属于每一个域，且会给很多操作的定义带来复杂性



## Relation Schema and Instance（关系模式与实例）
> [!IMPORTANT]
>
> $A$：属性名字
>
> $D$：属性 $A$ 的取值范围
>
> $a$：范围 $D$ 中的一个元素
>
> $R=(A_1,A_2,A_3······A_n)$：一个关系模式
>
> 正式表述：给定集合 $D_1,D_2,D_3······D_n$， 关系 $r$ 是 $D_1 \times D_2 \times ······\times D_n$ 的子集，故一个关系是 $n$ 元组 $(a_1,a_2,a_3······a_n)$的集合，其中 $a_i \in D_i, \forall i \in \{1,2,3······n\}$

## Example of a Relation（关系示例）
## Relations are Unordered（关系是无序的）
## Database（数据库）
> [!note]
>
> 数据库是有多个关系组成的
>
> 设计糟糕的设计库可能会出现如下问题：
>
> - 信息重复
> - 使用 null 值

## Keys（键）
> [!important]
>
> Superkey：当 $K$ 属性的值，能够区分每个可能的关系 $R$ 中的唯一元组时，我们称 $K$ 为 Superkey
>
> CandidateKey：当 $K$ 是最小时，则 $K$ 为 Candiatekey
>
> PrimaryKey：CandiateKey 中的一个选为 PrimaryKey
>
> ForeignKey
>
> - 约束：在一个关系中出现的值，必须出现在另外一个关系中
>   - 分为参照关系（**Referencing** relation）和 被参照关系（**Referenced** relation）

## Schema Diagram for University Database（大学数据库模式图）
## Relational Query Languages（关系查询语言）
> [!note]
>
> 关系查询语言
>
> - 分类：过程化与非过程化
> - 纯语言
>   - 关系代数
>   - 元组关系计算
>   - 域关系计算
> - 关系运算符

## Selection of tuples（元组选择）
## Selection of Columns (Attributes)（列（属性）选择）
## Joining two relations – Cartesian Product（连接两个关系——笛卡尔积）

## Union of two relations（两个关系的并集）

## Set difference of two relations（两个关系的差集）
## Set Intersection of two relations（两个关系的交集）
## Joining two relations – Natural Join（连接两个关系——自然连接）
## Natural Join Example（自然连接示例）
> [!important]
>
> ## 关系运算符总结表
>
> | Symbol (Name)（符号（名称））           | Example of Use（使用示例）             | 功能描述                                                 |
> | --------------------------------------- | -------------------------------------- | -------------------------------------------------------- |
> | σ (Selection)（选择运算符）             | σ₍salary>85000₎(instructor)            | 返回输入关系中满足谓词条件的行                           |
> | Π (Projection)（投影运算符）            | Π₍ID, salary₎(instructor)              | 从输入关系的所有行中输出指定属性，去除重复元组           |
> | ⋈ (Natural Join)（自然连接运算符）      | instructor ⋈ department                | 输出两个输入关系中，在所有同名属性上值相同的行对         |
> | × (Cartesian Product)（笛卡尔积运算符） | instructor × department                | 输出两个输入关系的所有行对（无论同名属性上的值是否相同） |
> | ∪ (Union)（并集运算符）                 | Π₍name₎(instructor) ∪ Π₍name₎(student) | 输出两个输入关系的元组并集（相交的元素，只出现一次）     |