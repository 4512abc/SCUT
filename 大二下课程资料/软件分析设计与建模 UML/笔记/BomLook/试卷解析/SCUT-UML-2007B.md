# 华南理工大学期末考试《面向对象分析与设计》补考试卷 2007B

## 一、选择题 (15分)

1. **What is TRUE about Use Cases? (4 answers)**
   - A. Use case diagrams are the primary tool to document requirements.
   - B. Use cases provide the basis of communication between sponsors and developers in planning phase.
   - C. Use cases description provides a good source to identify domain concepts.
   - D. A fully-dressed use case should include both “whats” and “hows” so that they are ready for “realization”.
   - E. A use case is an interaction between a user and a system.
   - F. Use cases are not object-oriented.

   > - **答案**：A、B、C、E
   > - 解释：
   >   - **A 选项**：用例图是记录需求的主要工具，它能够清晰地展示系统的功能和用户与系统的交互，所以该选项正确。
   >   - **B 选项**：在规划阶段，用例为发起者（如客户）和开发者之间的沟通提供了基础，双方可以基于用例来理解系统的功能需求，该选项正确。
   >   - **C 选项**：用例描述中会涉及到系统相关的各种概念和操作，是识别领域概念的良好来源，该选项正确。
   >   - **D 选项**：一个完整的用例应该关注 “whats”（做什么），而不是 “hows”（怎么做），“hows” 是实现阶段的内容，该选项错误。
   >   - **E 选项**：用例本质上就是用户与系统之间的一种交互，该选项正确。
   >   - **F 选项**：用例是面向对象分析与设计中的重要概念，是面向对象的，该选项错误。
   
2. **Scenario: Prepare for an Event**
   - In preparation for a party, the chef will look at the menu. The chef requires a shopping list from each recipe on the selected menu. The system generates the shopping list of ingredients that he needs to buy. Then he just crosses off anything that he already has.
   - Because the chef is picky about his cooking utensils, he brings his own and doesn't like to depend on the clients to supply anything. In order to make sure that he doesn't forget anything, he uses the system to generate the list of utensils that he'll have to bring with him to the party.
   - He then proceeds to generate a to-do list for the day of the party based on the time that the dinner is to be ready. He finds this to be useful so that everything's ready at the specified time, and nothing is forgotten.
   - When creating the use cases related to the "Prepare for an Event" scenario, which of the following BEST represents the type of terminology that the use cases should contain?
     - A. Chef, menu, recipes, ingredients
     - B. End user, bill of fare, cooking specifications, food contents
     - C. Chef object, menu object, recipe object, ingredient object
     - D. Person record, menu print stream, recipe container, ingredient array

   > - **答案**：A
   > - **解释**：用例应该使用业务领域内的常用术语，这样便于业务人员和开发人员理解。A 选项中的 “Chef, menu, recipes, ingredients” 是该场景中自然且常用的术语，符合用例描述的要求。B 选项中的 “bill of fare”“cooking specifications”“food contents” 表述不够自然和常用；C 选项的 “object” 是编程概念，不适合用于用例描述；D 选项中的 “record”“print stream”“container”“array” 是更偏向技术实现的术语，也不适合用例描述。
   
3. **Which statements are true for use case relationships? (1 answer)**
   - A. An Include relationship means that a UseCase includes the behavior described in another UseCase.
   - B. An Extend relationship implies that a UseCase may extend the behavior described in another UseCase.
   - C. Generalization between UseCases means that the child is a more specific form of the parent. The child inherits all Features and Associations of the parent, and may add new Features and Associations.
   - D. All of the above
   - E. Only a) and b)
   - F. Only b) and c)

   > - **答案**：D
   > - 解释：
   >   - **A 选项**：包含（Include）关系表示一个用例包含另一个用例所描述的行为，通常是为了复用公共行为，该选项正确。
   >   - **B 选项**：扩展（Extend）关系意味着一个用例可以在特定条件下扩展另一个用例的行为，该选项正确。
   >   - **C 选项**：用例之间的泛化（Generalization）关系表示子用例是父用例的更具体形式，子用例继承父用例的所有特征和关联，并且可以添加新的特征和关联，该选项正确。所以选 D。
   
4. ==**Which of the following are TRUE about a deployment diagram? (3 answers)**==
   
   - A. Since there is always some kind of response to a message, the dependencies are two-way between deployment components.
   - B. Dependencies between deployment components tend to be the same as the package dependencies.
   - C. Deployment diagrams can be used to show physical modules of code.
   - D. Deployment diagrams can be used to show the physical distribution of a system across computers.
   
   > - **答案**：B、C、D
   > - 解释：
   >   - **A 选项**：部署组件之间的依赖不一定是双向的，有些组件可能只是单向依赖其他组件，该选项错误。
   >   - **B 选项**：部署组件之间的依赖关系通常与包依赖关系相似，因为它们都反映了系统不同部分之间的依赖情况，该选项正确。
   >   - **C 选项**：部署图可以展示代码的物理模块，如可执行文件、库等，该选项正确。
   >   - **D 选项**：部署图的一个重要用途就是展示系统在计算机之间的物理分布情况，该选项正确。
   
5. **Refer to the diagram to answer the question. What is the maximum concurrent threads that is possible in the activity diagram?**'

   ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202506071622822.webp)

   - A. 3
   - B. 2
   - C. 4
   - D. 1
   - E. 5
   
   > - **答案**：A
   > - **解释**：在活动图中，并发线程的数量取决于分叉（fork）节点的情况。从图中可以看出，最大的并发情况是同时有 3 个线程在执行，所以答案是 A。

---

## 二、填空题 (15分)

1. **Which UML diagram is specifically intended to describe the behavior of a single class?**

   > - **答案**：状态图（State Diagram）
   > - **解释**：状态图主要用于**描述一个对象或类在其生命周期内的各种状态以及状态之间的转换**，能够很好地展示单个类的行为。


2. **Explain the difference between composition and aggregation. How are each represented in UML?**

   > - **区别**：组合（Composition）是一种强的拥有关系，部分对象的生命周期依赖于整体对象，当整体对象被销毁时，部分对象也会被销毁；而聚合（Aggregation）是一种弱的拥有关系，部分对象可以独立于整体对象存在。
   > - **UML 表示**：组合用实心菱形加连线表示；聚合用空心菱形加连线表示。


3. **The UML architecture is a four-layer metamodeling architecture. This architecture is a proven infrastructure for defining the precise semantics required by complex models, which include (4 points):**（四个填空）

   > - **答案**：元元模型层（Meta - Meta Model Layer）、元模型层（Meta Model Layer）、模型层（Model Layer）、用户模型层（User Model Layer）
   > - **解释**：UML 的四层元建模架构由这四个层次组成，它们为定义复杂模型所需的精确语义提供了基础设施。


4. **UML provides three extension mechanisms: ____, ____, and TaggedValue. These mechanisms can be used separately or together to define new modeling elements that can have distinct semantics, characteristics, and notation relative to the built-in UML modeling elements specified by the UML metamodel.**

   > - **答案**：Stereotype（构造型）、Constraint（约束）
   > - **解释**：UML 提供的三种扩展机制分别是构造型、约束和标记值，它们可以用来定义新的建模元素。

---

## 三、指出下列图中的错误 (20分)

1. **Use Case Diagram: 业务用例模型 / 审核(0-100)**
   - ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202506071624957.webp)

2. **水陆运输 Use Case Model / 水路运输 Sequence Diagram**
   - ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202506071624239.webp)

---

## 五、设计题 (40分)

**Consider the following problem:**
- On the scut campus, students can apply for a consumed-card (消费卡). The card administrator would create a new consumed-card when receiving an application. The consumed-card can be used in the campus supermarket (校园超市). When the students consume with the card, the salesperson would deduct the money from the card. Also, the card administrator can deposit money into the card for the students. Imagine that you have been hired to develop the supporting software.

a) **Draw a UML use case diagram for the system. Include one example of either an “extends” or a “uses” relationship. (20 points)**

b) **Draw a class diagram for the system. (20 points)**



> ### 五、设计题
>
> #### a) UML 用例图
>
> - 答案思路：
>   - **参与者**：学生、卡管理员、销售员。
>   - **用例**：学生申请消费卡、卡管理员创建消费卡、学生使用消费卡消费、销售员扣除卡内金额、卡管理员为学生充值。
>   - **关系**：例如，“学生使用消费卡消费” 可以扩展 “学生申请消费卡”，表示只有申请了消费卡才能进行消费。
> - **绘制要点**：用矩形表示系统边界，将参与者用小人图标表示在系统边界外，用椭圆表示用例在系统边界内，用直线连接参与者和用例表示关联关系，用带箭头的虚线表示扩展或使用关系。
>
> #### b) 类图
>
> - 答案思路：
>   - **类**：Student（学生）、CardAdministrator（卡管理员）、Salesperson（销售员）、ConsumedCard（消费卡）、CampusSupermarket（校园超市）。
>   - 关系：
>     - Student 与 ConsumedCard 是关联关系，一个学生可以有一张消费卡。
>     - CardAdministrator 与 ConsumedCard 是关联关系，卡管理员可以管理消费卡。
>     - Salesperson 与 ConsumedCard 是关联关系，销售员可以操作消费卡进行扣款。
>     - ConsumedCard 与 CampusSupermarket 是关联关系，消费卡可以在校园超市使用。
> - **绘制要点**：用矩形表示类，矩形分为三部分，分别是类名、属性、方法。用连线表示类之间的关系，根据关系的类型（关联、聚合、组合等）使用不同的连线和端点符号。

