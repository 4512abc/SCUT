# 华南理工大学期末考试《面向对象分析与设计》试卷 2007A

## 一、单选题与填空题 (25分)

1. **Object-Oriented Technologies have the following benefits ( )**
   - A. Increased encapsulation
   - B. Decreased coupling between modules
   - C. High level of abstraction
   - D. All of the above

   > - **答案**: D. All of the above
   > - **解释**: 面向对象技术具有多种优点。封装性（Increased encapsulation）可以隐藏对象的内部细节，提高数据的安全性；模块间的耦合度（Decreased coupling between modules）会降低，使得系统更易于维护和扩展；同时具有较高的抽象级别（High level of abstraction），可以将复杂的现实世界抽象为类和对象。
   
2. **Which of the following statements are false? ( )**
   - A. A class can have a relationship to itself.
   - B. An object can have a relationship to other objects of the same class.
   - C. A class can have only one relationship to another class.
   - D. A relationship can exist with a cardinality of zero.

   > - 解释:
   >   - A 选项，一个类可以与自身有关系，例如链表节点类，每个节点可以指向前一个或后一个同类型的节点。
   >   - B 选项，一个对象可以与同类的其他对象有关系，比如多个学生对象之间可能存在朋友关系。
   >   - C 选项，一个类可以与另一个类有多种关系，例如继承关系、关联关系等。
   >   - D 选项，关系可以有基数为零的情况，例如一个班级可能暂时没有学生。
   
3. **Which of the following models could be supported by Rational Rose? ( )**
   - A. Business Use Case diagram
   - B. Use Case diagram
   - C. Activity diagram
   - D. Component diagram

   > 答案疑似存在问题
   >
   > - **答案**: A, B, C, D
   > - **解释**: Rational Rose 是一款强大的 UML 建模工具，支持多种 UML 图，包括业务用例图（Business Use Case diagram）、用例图（Use Case diagram）、活动图（Activity diagram）和组件图（Component diagram）。
   
4. **Which of the following are NOT TRUE about the use case diagram? ( )**
   - A. Use Case diagrams show the interactions between use cases and actors.
   - B. Use Case diagrams show which actors initiate use cases.
   - C. Use Case diagrams are used to show the flow of functionality through a use case.
   - D. Use Case diagrams illustrate that an actor receives information from a use case.

   > - **答案**: C. Use Case diagrams are used to show the flow of functionality through a use case.
   > - 解释:
   >   - A 选项，用例图展示了用例和参与者之间的交互。
   >   - B 选项，用例图可以显示哪些参与者启动用例。
   >   - C 选项，用例图主要展示用例和参与者之间的关系，而不是用例内部的功能流程，活动图用于展示功能流程。
   >   - D 选项，用例图可以说明参与者从用例中获取信息。
   
5. **A car has four wheels. The class car and the class wheel have what type of relationship? ( )**
   - A. Association
   - B. Aggregation
   - C. Inheritance
   - D. Realization

   > - **答案**: B. Aggregation
   > - **解释**: 聚合关系（Aggregation）表示整体和部分的关系，部分可以独立于整体存在。汽车和车轮是整体和部分的关系，车轮可以独立于汽车存在，所以是聚合关系。关联关系（Association）是一种更宽泛的关系；继承关系（Inheritance）是 “is a” 的关系；实现关系（Realization）是接口和实现类之间的关系。
   
6. **What is true about messages in scenarios? ( )**
   - A. The operation of the calling object.
   - B. The operation of the called object.
   - C. It is sent by the actor to the system.
   - D. It is sent by the system to the actor.

   > - **答案**: B. The operation of the called object.
   > - **解释**: 在场景中，消息通常是一个对象调用另一个对象的操作，所以消息与被调用对象的操作相关。A 选项，调用对象发起消息，但消息本身是关于被调用对象的操作；C 和 D 选项，消息一般是对象之间的交互，而不是参与者和系统之间直接发送消息。
   
7. **Dynamic model describes the system change with time. It includes:**
   - ______ ，____ and ______.

   > - **答案**: Statechart diagram, Sequence diagram, Activity diagram
   > - **解释**: 动态模型用于描述系统随时间的变化，状态图（Statechart diagram）展示对象的状态变化，顺序图（Sequence diagram）展示对象之间的交互顺序，活动图（Activity diagram）展示系统的活动流程。
   
8. **What are the four views in Rose Model?**
   > - **答案**: use - case view, logical view, component view and deployment view.
   > - **解释**: Rose 模型的四个视图分别是用例视图（use - case view）用于描述系统的功能需求；逻辑视图（logical view）用于描述系统的逻辑结构；组件视图（component view）用于描述系统的组件和它们之间的依赖关系；部署视图（deployment view）用于描述系统的物理部署。
   
9. **Which two UML diagrams can represent concurrent processing?**
   - sequence diagram and ____.

   > - **答案**: sequence diagram and activity diagram
   > - **解释**: 顺序图（Sequence diagram）可以通过并行消息来表示并发处理，活动图（Activity diagram）可以通过分叉和汇合来表示并发活动。
   
10. **The UML architecture is a four-layer metamodeling architecture. This architecture is a proven infrastructure for defining the precise semantics required by complex models, which include:**
    - meta-metamodel, metamodel, model and user objects.
    
    > - **答案**: sequence diagram and activity diagram
    > - **解释**: 顺序图（Sequence diagram）可以通过并行消息来表示并发处理，活动图（Activity diagram）可以通过分叉和汇合来表示并发活动。

---

## 二、概念解释及举例 (15分)

1. **Collaboration Diagrams**
   - Collaboration diagrams illustrate object interactions in a graph or network format, in which objects can be placed anywhere on the diagram.

     ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202506071628189.webp)
   
   > - **解释**: 协作图以图形或网络格式展示对象之间的交互，对象可以随意放置在图中。它强调对象之间的协作关系和消息传递。
   > - **举例**: 在一个电商系统中，顾客对象、订单对象和库存对象之间的交互可以用协作图表示，消息在这些对象之间传递，如顾客下单消息从顾客对象传递到订单对象，订单对象再向库存对象发送检查库存的消息。
   
2. **Use Cases**
   - A use case is a collection of related success and failure scenarios that describe actors using a system to support a goal. Use cases defined for a system are the basis for the entire development process.

     **用例是描述系统所执行的一系列顺序事件流，并且某个角色可以看到执行的结果。为系统定义的用例是整个开发过程的基础。**
   
   
   > - **解释**: 用例是一组相关的成功和失败场景的集合，描述了参与者使用系统来实现某个目标的过程。为系统定义的用例是整个开发过程的基础。
   > - **举例**: 在一个图书馆管理系统中，“借阅图书” 就是一个用例。参与者是读者，成功场景是读者输入图书信息，系统检查图书是否可借，如果可借则完成借阅操作；失败场景可能是图书已被借出，系统提示借阅失败。
   
3. **Association Relationship**
   - The semantic relationship between two or more classifiers that specifies connections among their instances.

   > - **解释**: 关联关系是两个或多个分类器之间的语义关系，指定了它们实例之间的连接。
   > - **举例**: 在一个学校系统中，学生类和课程类之间存在关联关系，一个学生可以选修多门课程，一门课程可以被多个学生选修。
   
4. **Encapsulation**
   - Encapsulation is a mechanism used to hide the data, internal structure, and implementation details of some element, such as an object or subsystem.

   > - **解释**: 封装是一种隐藏元素（如对象或子系统）的数据、内部结构和实现细节的机制。
   > - **举例**: 在一个银行账户类中，账户余额是一个私有属性，外部对象不能直接访问和修改，只能通过类提供的公共方法（如存款、取款方法）来操作账户余额，这样就隐藏了账户余额的具体实现细节。
   
5. **Generalization**
   - Generalization is a relationship among classes where one class shares the structure and/or behavior of one or more classes. It is an “is a kind of” relationship.
   
   > - **解释**: 泛化是类之间的一种关系，其中一个类共享一个或多个类的结构和 / 或行为，是一种 “is a kind of” 的关系。
   > - **举例**: 在一个动物类层次结构中，狗类和猫类都继承自动物类，狗和猫都是动物的一种，它们共享动物类的一些属性和方法，如进食、睡眠等。

---

## 三、 Draw class diagram for the following scenario. Be sure to include multiplicities on the ends of the connectors. (10 points)   (10分)

**Scenario: Mini Office**

- Each office has up to 10 members and 2 managers.
- Each manager has the  ir own room, while members are in the main hall.
- Each member has their own seat.
- Each seat has a unique ID number.

> - 类图设计思路:
>   - 定义三个类：Office（办公室）、Manager（经理）和 Member（成员）。
>   - Office 类与 Manager 类的关系是聚合关系，一个 Office 最多有 2 个 Manager，所以连接线上 Office 端的多重性是 1，Manager 端的多重性是 0..2。
>   - Office 类与 Member 类的关系也是聚合关系，一个 Office 最多有 10 个 Member，所以连接线上 Office 端的多重性是 1，Member 端的多重性是 0..10。
>   - Member 类与 Seat 类的关系是关联关系，一个 Member 有一个 Seat，一个 Seat 被一个 Member 使用，所以连接线上 Member 端的多重性是 1，Seat 端的多重性也是 1。
>   - Seat 类有一个属性：seatID（座位编号）。

---

## 五、面向对象建模 (40分)

1. **Write down all candidate objects and candidate actions in the following usage scenario (10 points):**
   - This is a student registration system. There are full-time and part-time students. Each class has a set of scheduled times and a number of credit hours. When a user tries to register for a class, the system checks their schedule for time-conflicts. If there is a conflict, an error is returned. If there is no error, then the system checks to see if the total number of hours including this class is no more than the maximum number of hours for a full-time student. If so, then the system returns an error. If no problems are found, the system registers the student for the class and informs the user of success.

2. **Produce a class diagram to model the system. (Make sure to include all objects and actions that you will need for the sequence diagram you will produce in part 3 below.) (15 points)**

3. **Produce a sequence diagram to model the success-case of this scenario (i.e., the sequence of actions performed when there are no errors.) Please label everything with meaningful names, or include a description of each label. (15 points)**

> ### 五、面向对象建模 (40 分)
>
> #### 1. **Write down all candidate objects and candidate actions in the following usage scenario (10 points):**
>
> - **候选对象**: Student（学生）、Class（课程）、RegistrationSystem（注册系统）
> - 候选动作:
>   - 学生：registerForClass（注册课程）
>   - 注册系统：checkSchedule（检查时间表）、checkCreditHours（检查学分）、registerStudent（注册学生）、informUser（通知用户）
>
> #### 2. **Produce a class diagram to model the system. (Make sure to include all objects and actions that you will need for the sequence diagram you will produce in part 3 below.) (15 points)**
>
> - 类图设计思路:
>   - 定义三个类：Student、Class 和 RegistrationSystem。
>   - Student 类有属性：studentType（学生类型，全职或兼职）、schedule（时间表）、totalCreditHours（总学分）。方法：registerForClass。
>   - Class 类有属性：scheduledTimes（课程时间）、creditHours（学分）。
>   - RegistrationSystem 类有方法：checkSchedule、checkCreditHours、registerStudent、informUser。
>   - Student 类和 Class 类之间是关联关系，一个学生可以注册多门课程，一门课程可以被多个学生注册。
>   - Student 类和 RegistrationSystem 类之间是关联关系，学生通过注册系统进行课程注册。
>
> #### 3. **Produce a sequence diagram to model the success - case of this scenario (i.e., the sequence of actions performed when there are no errors.) Please label everything with meaningful names, or include a description of each label. (15 points)**
>
> - 顺序图设计思路:
>   - 参与者是 User（用户），对象有 RegistrationSystem、Student 和 Class。
>   - 消息顺序：
>     1. User 向 RegistrationSystem 发送 registerForClass 消息，携带 Student 和 Class 对象。
>     2. RegistrationSystem 向 Student 发送 checkSchedule 消息，检查是否有时间冲突。
>     3. RegistrationSystem 向 Student 发送 checkCreditHours 消息，检查总学分是否超过限制。
>     4. 如果都通过检查，RegistrationSystem 向 Student 发送 registerStudent 消息，完成注册。
>     5. RegistrationSystem 向 User 发送 informUser 消息，通知注册成功。
