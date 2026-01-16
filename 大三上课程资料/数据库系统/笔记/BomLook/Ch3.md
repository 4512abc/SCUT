# Ch3

## History（发展历史）
## Data Definition Language（数据定义语言）
> [!note]
>
> SQL DDL 作用：指定关系的相关信息，包括：
>
> - 每个关系的模式
>- 每个属性的值域
> - 完整性约束
> - 每个关系**需要维护的索引表**
> - 每个关系的**安全和授权信息**
> - 每个关系在**磁盘上的物理存储结构**

## Create Table Construct（创建表语句）
> [!important]
>
> 创建表语句：
>
> ```sql
> create table r (A1 D1, A2 D2, ..., An Dn,
>              (integrity-constraint1),
>              ...,
>              (integrity-constraintk))
> ```
>
> - $r$：关系名称
> - $A_i$：关系 $r$ 的模式的一个属性名称
> - $D_i$：属性 $A_i$ 的值域的一个数据类型
>
> 示例
>
> ```sql
> create table instructor (
>     ID char(5),
>     name varchar(20) not null,
>     dept_name varchar(20),
>     salary numeric(8,2)
> )
> ```
>
> ```sql
> insert into instructor values ('10211', 'Smith', 'Biology', 66000);
> insert into instructor values ('10211', null, 'Biology', 66000); -- 执行失败（name属性指定not null）
> ```

## Domain Types in SQL（SQL中的域类型）

> [!important]
>
> | 类型                  | 说明                                             |
> | --------------------- | ------------------------------------------------ |
> | char(n)               | 固定长度字符串，用户指定长度n                    |
> | varchar(n)            | 可变长度字符串，用户指定最大长度n                |
> | int                   | 整数（机器相关的有限整数子集)                    |
> | smallint              | 小整数（整数域类型的机器相关子集）               |
> | numertic(p,d)         | 定点数，用户指定精度p（总位数），d为小数点后位数 |
> | real,double precision | 浮点数和双精度浮点数，精度依赖机器               |
> | float(n)              | 浮点数，用户指定精度至少为n位                    |

## Integrity Constraints in Create Table（Create Table中的完整性约束）
> [!important]
>
> 完整性约束：
>
> - 非空值：not null
>
> - primary key：一般保证非空
>
> - foreign key：参考关系 $r$。
>
> - e.g:
>
>   ```sql
>   create table instructor (
>       ID char(5),
>       name varchar(20) not null,
>       dept_name varchar(20),
>       salary numeric(8,2),
>       primary key (ID), -- 主键约束（自动隐含not null）
>       foreign key (dept_name) references department -- 外键约束
>   )
>   ```
>
>   这里的 `foreign key (dept_name) references department`，声明dept_name为department表的主键。

## And a Few More Relation Definitions（更多关系定义示例）
## And more still（更多关系定义）
## Drop and Alter Table Constructs（删除和修改表语句）
> [!note]
>
> Drop and Alter Table Constructs（删除和修改表语句）
>
> - `drop table TABLE`：删除表及其中所有数据
> - `delete from TABLE`：删除表中的所有数据，但是保留表结构
> - `alter table`：
>   - `alter table r add A D`：向关系 r 中添加属性A，域为 D
>     - A 是要添加的属性名，D 是 A 的值域，对于新属性值，一般所有元组默认分配 null。
>   - `alter table r drop A`：删除关系 r 中的属性 A
>     - A 是关系 r 中要删除的属性名，一般，数据库不支持该操作

## Basic Query Structure（基本查询结构）
> [!important]
>
> SQL数据操纵语言（DML）支持查询信息、插入、删除和更新元组）
>
> 基本查询结构：
>
> ```
> select A1, A2, ..., An
> from r1, r2, ..., rm
> where P
> ```
>
> - $A_i$：表示属性
> - $r_i$：表示属性
> - $P$：表示谓词条件
> - 结果：关系 $r'$

## The select Clause（select子句）
> [!important]
>
> select 子句
>
> - 用于查询结果中所需要的属性，对应关系代数中的投影操作
>
>   Example: find the names of all instructors（示例：查询所有教师的姓名）
>
>   ```sql
>   select name
>   from instructor
>   ```
>
> - 特点：
>
>   - 不区分大小写
>   - 查询结果中允许存在重复元组
>
> - 操作：==asterisk 表示 *==
>
>   ```sql
>   # distince 用于去除重复
>   select distinct dept_name
>   from instructor
>           
>   # all 用于保留所有元组
>   select all dept_name
>   from instructor
>           
>   # * 用于保留所有属性
>   select *
>   from instructor
>           
>   # select 子句中支持 + - * / 操作
>   select ID, name, salary/12
>   from instructor
>   ```

## The where Clause（where子句）
> [!important]
>
> where 子句
>
> - 用于**指定查询结果需要满足的条件**，对应关系代数中的选择谓词（可以理解为一个过滤器，或者 if 判断）
>
> - 特点：
>   - 比较结果可通过逻辑连接词and、or、not组合，也可用于算术表达式的结果
>   
> - Example: To find all instructors in Comp. Sci. dept with salary > 80000（示例：查询计算机科学系薪资大于80000的所有教师）
>
>   ```sql
>   select name
>   from instructor
>   where dept_name = 'Comp. Sci.' and salary > 80000
>   ```

## The from Clause（from子句）
> [!important]
>
> from 子句
>
> - 用于指定查询所涉及的关系，对应关系代数中的笛卡尔积操作
>
> - 一般结合 where 子句使用
>
> - Example: Find the Cartesian product instructor × teaches（示例：查询instructor和teaches的笛卡尔积）
>
>   ```sql
>   select *
>   from instructor, teaches
>   ```

## Cartesian Product: instructor × teaches（笛卡尔积：instructor × teaches）
## Joins（连接操作）
## Natural Join（自然连接）
## Natural Join Example（自然连接示例）
## Natural Join (Cont.) schemas（自然连接（续）——模式注意事项）
> [!important]
>
> nature join
>
> 匹配所有公告属性相同的元组，且**每个公共列只保留一个副本**
>
> - 注意事项：可能会**将不关心的公告属性，也强制进行等值连接**
>   
>- Example：List the names of instructors along with the course ID of the courses that they taught.（查询教师姓名及其教授课程的课程编号）
> 
>  ```sql
>   -- 方式1：使用笛卡尔积+where条件
>   select name, course_id
>   from instructor, teaches
>   where instructor.ID = teaches.ID;
> 
>     -- 方式2：使用自然连接（等价于方式1）
>   select name, course_id
>   from instructor natural join teaches;
>  ```
> 
>- Example: List the names of instructors along with the titles of courses that they teach（示例：查询教师姓名及其教授课程的课程名称）
> 
>  - Incorrect version (makes course.dept_name = instructor.dept_name)（错误版本（会强制course.dept_name = instructor.dept_name））
> 
>    ```sql
>     select name, title
>     from instructor natural join teaches natural join course;
>    ```
> 
>  - Correct version 1（正确版本1）
> 
>    ```sql
>     select name, title
>     from instructor natural join teaches, course
>     where teaches.course_id = course.course_id;
>    ```
> 
>  - Correct version 2（正确版本2）
> 
>    ```sql
>     select name, title
>     from (instructor natural join teaches)
>          join course using(course_id); -- 使用using指定连接属性
>    ```



## The Rename Operation（重命名操作）

> [!important]
>
> rename
>
> - 支持对属性和关系进行重命名操作
>
>   ```sql
>   old-name as new-name
>   ```
>
> - as 关键字可以忽略：
>
>   ```sql
>   instructor as T === instructor T
>   ```



## String Operations（字符串操作）

> [!IMPORTANT]
>
> 字符串操作
>
> - 通过 like 匹配运算符实现，支持通过 % 和 _ 进行描述
>
>   - %：用于匹配任意子串（或者理解为任意多个字符）
>   - _：用于匹配任意单个字符
>
> - e.g：
>
>   ```sql
>   select name
>   from instructor
>   where name like '%dar%'
>   ```



## Ordering the Display of Tuples（元组排序显示）
> [!important]
>
> order by
>
> - 用于指定元组的排序显示，一般默认是升序
>
> - e.g：
>
>   ```sql
>   select distinct name
>   from instructor
>   order by name -- 按name升序排序（默认升序）
>   ```
>
> - 还可以指定降序，以及支持多个属性排序
>
>   ```sql
>   order by name desc # desc指定降序 asc指定升序
>             
>   order by dept_name, name # 先按照 dept_name 升序，在按照 name 升序
>   ```



## Where Clause Predicates（where子句谓词）

> [!important]
>
> where clause predicate
>
> - SQL 支持 between 比较运算符
>
> - Example: Find the names of all instructors with salary between \$ 90,000 and \$100,000  (that is, ≥ \$90,000 and ≤ \$100,000)（示例：查询薪资在90000至100000美元之间（即≥90000且≤100000）的所有教师姓名）
>
>   ```sql
>   select name
>   from instructor
>   where salary between 90000 and 100000
>   ```
>
> - Tuple comparison（元组比较）
>
>   ```sql
>   select name, course_id
>   from instructor, teaches
>   where (instructor.ID, dept_name) = (teaches.ID, 'Biology');
>   ```



## Set Operations（集合操作）

- Example 1: Find courses that ran in Fall 2009 or in Spring 2010（示例1：查询2009年秋季或2010年春季开设的课程）
  ```sql
  (select course_id from section where semester = 'Fall' and year = 2009)
  union -- 并集（自动去重）
  (select course_id from section where semester = 'Spring' and year = 2010)
  ```
  
- Example 2: Find courses that ran in Fall 2009 and in Spring 2010（示例2：查询2009年秋季和2010年春季都开设的课程）
  ```sql
  (select course_id from section where semester = 'Fall' and year = 2009)
  intersect -- 交集（自动去重）
  (select course_id from section where semester = 'Spring' and year = 2010)
  ```
  
- Example 3: Find courses that ran in Fall 2009 but not in Spring 2010（示例3：查询2009年秋季开设但2010年春季未开设的课程）
  ```sql
  (select course_id from section where semester = 'Fall' and year = 2009)
  except -- 差集（自动去重）
  (select course_id from section where semester = 'Spring' and year = 2010)
  ```

> [!important]
>
> union、intersect、except 集合操作**均自动去除重复元组**
>
> 如果需要保留所有重复元组，使用：union all、intersect all、except all
>
> 多集合操作规则：一个元组在 $r$ 中出现了 $m$ 次，在 $s$ 中出现了 $n$ 次，则
>
> - union all：$m+n$ 次
> - intersect all：$min(m,n)$ 次
> - except all：$max(0,m-n)$ 次



## Null Values（空值）
> [!important]
>
> null
>
> - 表示未知值或者不存在的值
>
> - 元组的某些属性可能会取空值
>
> - **所有涉及 null 的算术操作结果均为 null**
>
> - is null 用于检查是否为空值
>
>   ```sql
>   select name
>   from instructor
>   where salary is null
>   ```



## Null Values and Three Valued Logic（空值与三值逻辑）

> [!important]
>
> 任何与 null 的比较结果均为 unknown
>
> 基于真值 unknown 的三值逻辑规则，需要考虑具体情况。
>
> ![image-20251222210316906](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222210316906.png)
>
> 在 where 子句中，结果为 unknown 的谓词将被视为 False 





## Aggregate Functions – Group By（聚合函数——Group By子句）
> [!important]
>
> group by
>
> - 根据指定的属性构造分组，一般**作为聚合函数的辅助手段**（即从原来的单一元组集合上进行聚合，推广到多个元组集合上进行聚合）
>
> - 注意：**聚合函数外的属性必须出现在 group by** 子句中，否则会出现错误
>
>   ```sql
>   /* erroneous query */（错误查询）
>   select dept_name, ID, avg(salary)
>   from instructor
>   group by dept_name; -- 错误：ID未在group by中，也未被聚合
>   ```
>
> - 如果我们不需要聚集函数的话，实际上就不需要使用 group by了，这也解释了上面的注意原因



## Aggregate Functions – Having Clause（聚合函数——Having子句）

> [!important]
>
> having 子句用于聚合函数，其中 having 子句的谓词作用于分组后，where 子句的谓词作用于分组前。



## Null Values and Aggregates（空值与聚合函数）

> [!important]
>
> **聚合函数进行计算时，忽略 null 值**
>
> - 如果所选择计算的属性列中，都是 null 值（即没有一个是真实值），则计算结果为 null
>
> **除count(*)外**，所有聚合操作均忽略聚合属性为null的元组
>
> - 若集合中只有 null 值，count 返回 0



## SQL 关键字执行顺序（SQL Keyword Execution Order）

> [!important]
>
> ```sql
> from a, b
> where P1
> group by A1
> having P2
> select A1, agg_fun as X
> ORDER
> ```



## With Clause（With子句）

> [!note]
>
> with 子句：
>
> ```sql
> with max_budget (value) as
> 	(select max(budget)
> 	from department)
> 	
> select budget
> from department, max_budget
> where department.budget = max_budget.value;
> ```
>
> - **用于定义临时视图**，**仅在包含 with 子句的查询中有效**
>
> - 适合用于编写复杂查询，且大多数数据库支持该操作
>
>   ```sql
>   with dept _total (dept_name, value) as
>           (select dept_name, sum(salary)
>            from instructor
>            group by dept_name),
>          dept_total_avg(value) as
>          (select avg(value)
>          from dept_total)
>            
>   select dept_name
>   from dept_total, dept_total_avg
>   where dept_total.value > dept_total_avg.value;
>   ```



## Complex Queries using With Clause（使用With子句的复杂查询）

## Scalar Subquery（标量子查询）

> [!warning]
>
> Scalar Subquery
>
> - 用于**需要单个值的场景的子查询**，可以理解为返回结果只有一个数据对象（一个数字、一个字符串等），而不是向量形式（一组数字、一组字符串）
>
> - 如果将 其查询的结果 和 一个向量形式的数据进行比较，则会发生故障
>
> - Example: Find all instructors whose salary is less than the average salary of instructors（示例：查询薪资低于教师平均薪资的所有教师）
>
>   ```sql
>   # wrong
>   select *
>   from instructor
>   where salary < avg(salary); -- 错误：avg(salary)不能直接用于where子句，WHERE 是 “筛选单个行” 的工具，聚合函数是 “汇总一组行” 的工具，前者执行时后者还未产生结果，因此无法在 WHERE 中直接使用聚合函数。
>     
>   # correct
>   select *
>   from instructor
>   where salary < (select avg(salary) from instructor); -- 嵌套标量子查询
>   ```
>   
>   **补充说明：聚合函数的合法使用场景**
>   
>   聚合函数并非不能用，而是不能直接用在 `WHERE` 子句中，它的合法使用场景包括：
>   
>   1. `SELECT` 子句中（用于**返回汇总结果**）：`select avg(salary) as avg_sal from instructor;`
>   2. `HAVING` 子句中（用于**过滤分组后的结果**，`HAVING` 在聚合函数执行后生效）：`select dept_name, avg(salary) from instructor group by dept_name having avg(salary) > 8000;`
>   3. 子查询中（如第二个正确查询，先计算聚合结果再供外层使用）。



## Nested Subqueries（嵌套子查询）

> [!note]
>
> SQL 支持嵌套子查询，即在在一个 select-from-where 表达式中嵌套另外一个查询，常用于集合成员测试、集合比较和集合基数测试
>
> - Find courses offered in Fall 2009 and in Spring 2010（查询2009年秋季和2010年春季都开设的课程）
>
>   ```sql
>   select distinct course_id
>   from section
>   where semester = 'Fall' and year = 2009 and
>         course_id in (select course_id
>                       from section
>                       where semester = 'Spring' and year = 2010);
>   ```
>
> - Find courses offered in Fall 2009 but not in Spring 2010（查询2009年秋季开设但2010年春季未开设的课程）
>
>   ```sql
>   select distinct course_id
>   from section
>   where semester = 'Fall' and year = 2009 and
>         course_id not in (select course_id
>                           from section
>                           where semester = 'Spring' and year = 2010);
>   ```



## 嵌套查询，执行顺序（Nested Subquery Execution Order）

> [!note]
>
> ```sql
> select A1, A2
> from a, b
> where P1 (select
>        from c, d
>        where P2)
> ```
>
> 执行顺序：**绝大多数情况下是「由内向外」执行（先执行内层子查询，再执行外层主查询）；仅有一种特殊情况 ——「相关子查询（也叫关联子查询）」，会采用「外向内 + 循环匹配」的执行逻辑**。
>
> - 外查询（Outer query）: 直接呈现结果的代码（the code that directly returns the result）
> - 内查询（Inner query）: 提供额外筛选条件的代码（the code that provides additional filtering conditions）



## Example Query（查询示例）

## Set Comparison（集合比较）
## Definition of Some Clause（Some子句定义）
> [!note]
>
> some 子句
>
> - = some （为 true）等价于 in
> -  ≠ some （为 true）不等价于 not in）
>
> ![image-20251222214324594](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222214324594.png)

## Example Query（查询示例）
## Definition of All Clause（All子句定义）
> [!note]
>
> all 子句
>
> - ≠ all 等价于 not in
> - = all 不等价于 in
>
> ![image-20251222214355160](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222214355160.png)
>
> ![image-20251222214511040](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222214511040.png)

## Correlation Variables（相关变量）
> [!note]
>
> Correlated subquery and Correlation variables
>
> ![image-20251222214635930](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222214635930.png)
>
> - 相关子查询：内部子查询引用了外层查询的变量
> - 这些百年来称为 相关变量 or 相关名称



## Test for Empty Relations（空关系测试）
> [!important]
>
> exist 在参数子查询为非空时，返回 true
>
> - exists r 等价于 r 非空
> - not exists r 等价于 r 为空

## Not Exists（Not Exists示例）

方法：先选一个元组进行分析，分析逻辑关系，使用 SQL 表达。再推广到多个元组上（即一个关系模式上）。

![image-20251222215253954](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222215253954.png)

![image-20251222215300453](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222215300453.png)

![image-20251222215307224](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222215307224.png)

## Test for Absence of Duplicate Tuples（无重复元组测试）
> [!note]
>
> unique 用于测试子查询结果是否存在重复元组
>
> - 特殊情况：空集返回 true
>
> ![image-20251222215519345](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222215519345.png)

## Subqueries in the From Clause（From子句中的子查询）

![image-20251222215800350](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222215800350.png)

![image-20251222215806259](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/image-20251222215806259.png)

## Modification of the Database（数据库修改）

> [!important]
>
> - Deletion of tuples from a given relation（从指定关系中删除元组）
>
>   ```sql
>   delete from table t where p
>   ```
>
> - Insertion of new tuples into a given relation（向指定关系中插入新元组）
>
> - Updating values in some tuples in a given relation（更新指定关系中部分元组的值）

## Modification of the Database – Deletion（数据库修改——删除）
## Modification of the Database – Deletion（数据库修改——删除）
## 删除句子的构造（Deletion Statement Construction）

> [!important]
>
> Delete 子句的构造
>
> 1. 构造查询语句，选出要删除的记录（Construct a query to select the records to be deleted）
>
>    ```sql
>    select *
>    from r -- 注意这里只能接一张表；因此，常常需要嵌套子查询（Note: Only one table can be used here; thus, nested subqueries are often needed）
>    where p;
>    ```
>
> 2. 使用delete替换select *（Replace select * with delete）
>
>    ```sql
>    delete
>    from r
>    where p;
>    ```
>
> - Example: Delete all instructors whose salary is less than the average salary of instructors（示例：删除薪资低于教师平均薪资的所有教师）
>
>   ```sql
>   delete from instructor
>   where salary < (select avg(salary) from instructor);
>   ```

## Modification of the Database – Insertion（数据库修改——插入）

> [!important]
>
> inserction
>
> ```sql
> insert into table
> values()
> ```
>
> ```sql
> insert into table1 select * from table1
> ```
>
> select 语句会先进行检查，检查无误后再插入到关系中，防止引发问题（如没有主键）

## Modification of the Database – Updates（数据库修改——更新）

> [!important]
>
> 注意先后顺序
>
> Example: Increase salaries of instructors whose salary is over $100,000 by 3%, and all others receive a 5% raise（示例：薪资超过100000的教师加薪3%，其他教师加薪5%）
>
> - 方式1：两条update语句（Two update statements）
>
>   ```sql
>   update instructor
>   set salary = salary * 1.03
>   where salary > 100000;
>   
>   update instructor
>   set salary = salary * 1.05
>   where salary <= 100000;
>   ```
>
>   - The order is important（执行顺序至关重要）
>
> - 方式2：使用case语句（Using case statement，更优）
>
>   ```sql
>   update instructor
>   set salary = case
>                   when salary <= 100000 then salary * 1.05
>                   else salary * 1.03
>                end;
>   ```

