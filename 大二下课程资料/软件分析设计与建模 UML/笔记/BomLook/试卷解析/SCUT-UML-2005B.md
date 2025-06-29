# 华南理工大学期末考试《软件设计分析与建模》试卷 2005B

## 一、选择题 (15分)

1. **During implementation, the development team decides to use a third-party utility to provide some of the required functionality. What OOAD artifact would MOST likely reflect this change?**
   
   - A. Activity diagram
   - B. Package diagram
   - C. State diagram
   - D. Interaction diagram
   
   > 1. **答案**：B
   >    - **解释**：在实现过程中使用第三方工具来提供部分所需功能，这会影响系统的组件结构和组织。包图（Package diagram）主要用于展示系统的模块化结构和包之间的依赖关系，能够反映引入第三方工具这种对系统结构的改变。活动图（Activity diagram）主要用于描述业务流程和操作步骤；状态图（State diagram）用于描述对象的状态变化；交互图（Interaction diagram）用于描述对象之间的交互过程，它们都不太能直接反映引入第三方工具这种结构上的改变。
   
2. **Scenario: Prepare for an Event**
   
   - In preparation for a party, the chef will look at the menu. The chef requires a shopping list from each recipe on the selected menu. The system generates the shopping list of ingredients that he needs to buy. Then he just crosses off anything that he already has.
   - Because the chef is picky about his cooking utensils, he brings his own and doesn't like to depend on the clients to supply anything. In order to make sure that he doesn't forget anything, he uses the system to generate the list of utensils that he'll have to bring with him to the party.
   - He then proceeds to generate a to-do list for the day of the party based on the time that the dinner is to be ready. He finds this to be useful so that everything's ready at the specified time, and nothing is forgotten.
   - When creating the use cases related to the "Prepare for an Event" scenario, which of the following BEST represents the type of terminology that the use cases should contain?
     - A. Chef, menu, recipes, ingredients
     - B. End user, bill of fare, cooking specifications, food contents
     - C. Chef object, menu object, recipe object, ingredient object
     - D. Person record, menu print stream, recipe container, ingredient array
   
   > - **解释**：用例描述应该使用与现实业务场景紧密相关、通俗易懂的术语。选项 A 中的 “Chef（厨师）, menu（菜单）, recipes（食谱）, ingredients（食材）” 都是在 “Prepare for an Event” 这个场景中自然出现且容易理解的业务术语。选项 B 中的 “End user（终端用户）” 表述过于宽泛，“bill of fare（菜单的专业术语）” 不够直观；选项 C 中的 “object（对象）” 是面向对象编程概念，不适合用例描述；选项 D 中的 “record（记录）, print stream（打印流）, container（容器）, array（数组）” 是技术实现层面的术语，不符合用例的业务描述要求。
   
3. ==**If a use case had a requirement "Calculate account balance," which OOAD artifact would be the BEST source for determining the name of the public method used to invoke the operation?**==
   
   - A. Use cases
   - B. Interaction diagrams
   - C. Class diagram
   - D. Activity diagram
   
   > - **答案**：C
   > - **解释**：类图（Class diagram）展示了系统中的类、类的属性和方法，以及类之间的关系。要确定执行 “Calculate account balance” 操作的公共方法名称，类图是最合适的选择，因为它明确显示了类及其方法。**用例（Use cases）主要描述系统的功能和用户与系统的交互，不涉及具体方法名称；交互图（Interaction diagrams）关注对象之间的消息传递和交互顺序；活动图（Activity diagram）描述业务流程和操作步骤，它们都不能直接确定方法名称。**
   
4. ==**Which of the following are TRUE about a deployment diagram? (3 Answers)**==
   
   - A. Since there is always some kind of response to a message, the dependencies are two-way between deployment components.
   - B. Dependencies between deployment components tend to be the same as the package dependencies.
   - C. Deployment diagrams can be used to show physical modules of code.
   - D. Deployment diagrams can be used to show the physical distribution of a system across computers.
   
   > 答案应该有问题
   >
   > - **答案**：B、C、D
   > - 解释：
   >   - **B 选项**：部署组件之间的依赖关系和包依赖关系有相似性，因为包是代码的逻辑组织，部署组件是代码的物理体现，它们在依赖关系上有一定的对应。
   >   - **C 选项**：部署图（Deployment diagram）可以展示代码的物理模块，如可执行文件、库文件等。
   >   - **D 选项**：部署图的重要作用之一就是展示系统在不同计算机之间的物理分布情况，例如服务器、客户端等。
   >   - **A 选项**：部署组件之间的依赖关系不一定是双向的，可能存在单向依赖，比如一个组件依赖另一个组件提供的服务但无需返回响应。
   
5. **Refer to the diagram to answer the question. What is the maximum concurrent threads that is possible in the activity diagram?**

   ![](https://cdn.jsdelivr.net/gh/BomLook/blog-pic@main/img/202506071622822.webp)

   - A. 3
   - B. 2
   - C. 4
   - D. 1
   - E. 5
   
   > - **解释**：在活动图中，并发线程数量由分叉（Fork）和汇合（Join）节点决定。从图中可以看出，最大并发情况是同时有 3 个活动并行执行，所以最大并发线程数是 3。

---

## 二、填空题 (15分)

1. **Which UML diagram is specifically intended to describe the behavior of a single class?**

   > - **答案**：状态图（State diagram）
   > - **解释**：状态图专门用于描述单个对象或类在其生命周期内的状态变化以及状态之间的转换，能够清晰地展示类的行为。

2. **Explain the difference between composition and aggregation. How are each represented in UML?**

   - _______________________________________________________________________
   - _______________________________________________________________________

   > - **答案**：组合（Composition）是一种**强聚合关系**，**部分对象的生命周期依赖于整体对象的生命周期**，当整体对象被销毁时，部分对象也会被销毁，在 UML 中用实心菱形表示，菱形指向整体对象；聚合（Aggregation）是一种**弱聚合关系**，**部分对象可以独立于整体对象存在**，整体对象只是部分对象的一个拥有者，在 UML 中用空心菱形表示，菱形指向整体对象。
   > - **解释**：这是 UML 中组合和聚合关系的基本定义和表示方法，通过这种区分可以准确描述类之间不同程度的关联关系。

3. **The UML metamodel is defined as one of the layers of a four-layer metamodeling architecture. This architecture is a proven infrastructure for defining the precise semantics required by complex models, which include:**

   - _____________, ______________, ______________ and user objects.

   > - **答案**：元元模型（Meta - metamodel）、元模型（Metamodel）、模型（Model）
   > - **解释**：UML 的四层元建模架构包括元元模型、元模型、模型和用户对象。元元模型定义了元模型的基本概念和规则；元模型基于元元模型定义了 UML 的各种建模元素；模型是使用 UML 元模型创建的具体系统模型；用户对象是系统中的具体实例。

4. **UML provides three extension mechanisms: __________, __________, and TaggedValue. These mechanisms can be used separately or together to define new modeling elements that can have distinct semantics, characteristics, and notation relative to the built-in UML modeling elements specified by the UML metamodel.**

   > - **答案**：构造型（Stereotype）、约束（Constraint）
   > - **解释**：UML 提供的三种扩展机制是构造型、约束和标记值（TaggedValue）。构造型用于定义新的建模元素类型；约束用于对建模元素的行为和属性进行限制；标记值用于为建模元素添加额外的信息。



---

## 四、简答题 (10分)

1. **Compare the difference between OOA and traditional structured analysis.**

   > - 答案：
   >   - **分析角度**：面向对象分析（OOA）从对象的角度出发，将系统看作是一组相互协作的对象集合，强调对象的封装、继承和多态特性，关注对象之间的交互和责任分配；传统结构化分析从功能的角度出发，将系统分解为多个功能模块，通过数据流图（DFD）等工具描述数据在系统中的流动和处理过程，强调功能的分解和模块化设计。
   >   - **建模方法**：OOA 使用 UML 等面向对象的建模语言，通过类图、对象图、用例图等多种图来描述系统的静态结构和动态行为；传统结构化分析使用数据流图、实体 - 关系图（ERD）等结构化建模工具，主要关注系统的功能和数据结构。
   >   - **可维护性和可扩展性**：OOA 由于其封装和继承特性，使得系统具有更好的可维护性和可扩展性，当需求发生变化时，可以更容易地修改和扩展系统；传统结构化分析随着系统规模的增大，功能模块之间的耦合度可能会增加，导致系统的可维护性和可扩展性较差。
   > - **解释**：通过从分析角度、建模方法以及可维护性和可扩展性这几个方面对比，可以清晰地看出面向对象分析和传统结构化分析的差异。这些差异决定了它们在不同类型系统开发中的适用性。

2. **How to discover the objects and actors in a system.**

   > - 答案：
   >   - 发现对象：
   >     - **名词分析**：从系统的需求文档、业务流程描述中提取名词，这些名词可能代表系统中的对象，例如 “客户”“订单”“产品” 等。
   >     - **行为分析**：根据系统的功能和操作，找出执行这些行为的主体，这些主体通常就是系统中的对象，例如 “客户下单”，“客户” 就是一个对象。
   >     - **边界分析**：考虑系统的边界，将与系统交互的外部实体和系统内部的功能模块抽象为对象。
   >   - 发现参与者（Actor）：
   >     - **外部交互**：找出与系统进行交互的外部实体，例如用户、其他系统、设备等，这些外部实体就是系统的参与者。
   >     - **业务角色**：根据业务流程，确定不同的业务角色，例如 “管理员”“收银员”“买家” 等，这些业务角色就是系统的参与者。
   > - **解释**：这些方法是在系统分析过程中常用的发现对象和参与者的方式。通过对系统的需求、行为和边界进行分析，可以准确地识别出系统中的对象和参与者，为后续的建模和设计工作奠定基础。

---

## 五、设计题 (40分)

**Scenario:**
- Suppose the shopping process uses a terminal in the store.

**(a) Use case: shopping**
- **Actor:** buyer, cashier
- **Description:** The buyer brings the goods to the post (cash desk). The cashier registers the goods information, calculates the amount, receives the cash, and gives change. Then the buyer leaves with his/her goods.

**(b) Use case: system managing**
- **Actor:** system administrator
- **Description:** The administrator turns on the power, checks the date and time, activates the users, and monitors the system status.

**Tasks:**
1. **Draw the system use case diagram.**
2. **Draw the system sequence diagrams.**
