# Chapter 18（Documenting Software Architectures）

------

## 一、必背定义（≥15个，给你 24 个）

> 记忆方法：这一章的定义分 6 组——**文档目的/受众**、**表示法**、**视图体系**、**选视图方法**、**视图模板**、**跨视图与质量属性/敏捷**。

1. **Architecture Documentation**：用于让需要架构的人“知道、看懂、能用（建/改/分析）”的架构说明材料；否则再好的架构也会“被误用/浪费”。
2. **Prescriptive vs. Descriptive（规范性 vs 描述性）**：架构文档对部分受众是“规定应该是什么（约束未来决策）”，对另一部分受众是“描述已经是什么（记录既有决策）”。
3. **Three Uses of Architecture Documentation（三大用途）**：**教育（Education）/沟通（Communication）/分析与建造基础（Basis for analysis & construction）**。
4. **Informal Notation（非正式表示法）**：用通用画图工具表达，语义主要靠自然语言解释，**无法形式化分析**。
5. **Semiformal Notation（半形式表示法）**：有标准图元与构造规则，但语义不完备，可做有限分析；**UML 属于此类**。
6. **Formal Notation（形式表示法）**：具有精确（通常数学化）语义，可对语法与语义做形式化分析；**ADL 支持工具自动化**。
7. **View（视图）**：对一组架构元素及其关系的、面向干系人的一致性表示（view 是结构的表示）。
8. **Principle of Architecture Documentation（文档化原则）**：文档化架构 = **文档化相关视图** + **补充跨多个视图的文档信息**。
9. **Module View（模块视图）**：元素是 **Modules（实现单元/责任集合）**；典型关系：**is-part-of、depends-on、is-a**；通常至少要有一个模块视图。
10. **C&C View（Component-and-Connector 视图）**：元素是 **Components（运行时处理单元/数据存储）** 与 **Connectors（交互通路）**；关系含 **attachments、interface delegation**；用于解释系统“如何运行”并推理运行时质量属性。
11. **Port / Role（端口/角色）**：组件通过 **ports** 与连接件交互；连接件用 **roles（接口）**说明组件如何使用连接件。
12. **Allocation View（分配视图）**：把软件元素映射到环境元素（部署节点/团队/目录/版本库等）；关系是 **allocated-to**；用于性能、可用性、安全等以及分布式开发/安装等推理。
13. **Quality View（质量视图）**：为特定干系人/关注点，把结构视图中相关部分抽取并打包成一个“质量专题视图”（如 security/communications/reliability/performance）。
14. **Stakeholder/View Table（干系人-视图表）**：选视图方法的 Step1：行=干系人，列=候选视图；填每格需求强度（none/overview/moderate/high）。
15. **Minimum View Set（最小视图集）**：至少应有 **≥1 module view**、**≥1 C&C view**；大型系统通常还要 **≥1 allocation view**。
16. **Primary Presentation（主呈现）**：一个视图中用该视图“词汇”表达你要传达的信息（元素与关系），通常是图；**最常见错误是没有 notation key（图例/语义键）**。
17. **Element Catalog（元素目录）**：解释主呈现中元素/关系：至少包含 **elements & properties、relations & properties、interfaces、behavior（不明显的行为）**。
18. **Context Diagram（上下文图）**：说明该视图所覆盖的系统部分与环境的关系，目的在于界定视图**范围（scope）**。
19. **Variability Guide（可变性指南）**：说明架构中**变体点（variation points）**如何被选择/配置，以及架构允许如何变化。
20. **Rationale（理由/论证）**：解释“为什么这么设计”，并给出设计合理性的论证；尤其要说明模式选择解决了什么问题、为何优于替代方案。
21. **Documentation Roadmap（文档路线图）**：告诉读者“文档有什么、在哪找”；并给出 view overview、使用场景等，帮助不同干系人快速定位信息。
22. **Mapping Between Views（跨视图映射）**：解释视图之间元素对应关系（一般是 many-to-many），常用表格记录，如 “is implemented by / implements / included in”。
23. **Behavior Documentation（行为文档）**：补充结构视图，描述元素如何交互；支持推理死锁、任务完成时间、最大内存消耗等；在模板里属于元素目录的一部分。
24. **Trace-oriented vs Comprehensive Behavior（轨迹型 vs 完整型行为表示）**：轨迹型=针对特定刺激/状态给出交互序列（用例/时序/活动等）；完整型=给出可推导所有路径的完整行为模型（如状态机）。

------

## 二、10个对比题（直接给“标准答案写法”）

> 你考试写对比题：按 **定义差异 → 适用场景 → 取舍/结论** 三句话写，最稳。

### 1) Prescriptive vs Descriptive

- **Prescriptive**：对未来决策施加约束，规定“应该是什么”。
- **Descriptive**：记录已做决策，描述“现在是什么”。

### 2) Informal vs Semiformal vs Formal notation

- **Informal**：语义靠自然语言，难分析但快。
- **Semiformal**：有标准图元规则（如 UML），分析能力有限。
- **Formal**：语义精确（ADL），可形式化分析但成本高。

### 3) View vs Structure

- **Structure**：元素本体（软件/硬件中真实存在的元素集合）。
- **View**：面向干系人的结构表示（元素+关系的表达）。

### 4) Module View vs C&C View

- **Module view**：静态实现单元与依赖/分解，偏“怎么组织代码与责任”。
- **C&C view**：运行时组件与连接件交互，偏“系统如何执行/通信”。

### 5) C&C Connector vs UML Connector（为什么 UML 线不够）

- **C&C connector**：可能很“rich”（子结构/属性/行为/接口角色）。
- **UML connector（线）**：表达能力不足（无子结构/属性/行为，角色接口难显式表示），需用 stereotype/端点标注/用组件代替或 tag 注解。

### 6) Allocation View vs C&C View

- **Allocation view**：软件元素→环境元素（部署/团队/版本/安装），回答“放在哪/谁负责”。
- **C&C view**：运行时交互结构，回答“运行时如何协作”。

### 7) Structural Views vs Quality View

- **Structural views**：模块/C&C/分配等“结构本体”。
- **Quality view**：围绕某质量关注点，把结构视图相关部分抽取重组，用来对安全/性能/可靠性等推理。

### 8) Primary Presentation vs Element Catalog

- **Primary presentation**：先把元素/关系“画出来/列出来”（主信息载体）。
- **Element catalog**：再把图里每个元素/关系“解释清楚”（属性、接口、行为等），否则图无法被正确使用。

### 9）Context Diagram vs Variability Guide

- **Context diagram**：界定视图范围与环境关系（scope）。
- **Variability guide**：说明变体点怎么选、架构允许怎么变（新增/替换组件等）。

### 10) Trace-oriented vs Comprehensive behavior

- **Trace-oriented**：给“某刺激+某状态”下的一条交互序列（用例/时序/活动等）。
- **Comprehensive**：给完整行为模型，可推导所有可能路径（典型：状态机）。

------

## 三、6道简答题标准答案（完全应试写法，可直接背抄）

### 1）题：架构文档的主要用途是什么？（写三条）

**标准答案：**
架构文档主要用于：（1）**教育**：帮助新成员/外部评估者/新架构师快速理解系统；（2）**沟通**：作为干系人之间（尤其架构师↔开发者、架构师↔未来架构师）的主要沟通载体；（3）**分析与建造基础**：作为实现蓝图（模块接口提供/使用关系），可登记未解决问题，并作为架构评估的基础。

### 2）题：非正式/半形式/形式表示法如何选择？（写“取舍”）

**标准答案：**
表示法选择需考虑取舍：**越形式化**通常成本更高、制作与理解更费时，但**歧义更小**、可支持更多分析；**越非正式**更易创建但保证更少。应根据要捕获和推理的重要问题选择合适表示法（不同表示法擅长表达的信息不同）。

### 3）题：架构文档至少应该包含哪些视图？为什么？

**标准答案：**
至少应包含：**至少一个模块视图（module view）\**与\**至少一个 C&C 视图**；对大型系统通常还需要**至少一个分配视图（allocation view）**。因为模块视图支撑代码构造/责任划分，C&C 视图支撑运行时交互与质量属性推理，而分配视图支撑部署/环境映射及性能、可用性、安全等分析。

### 4）题：如何系统地“选择要文档化的视图”？（写步骤法）

**标准答案：**
选择视图可按三步：
Step1 **建立干系人-视图表**：列出干系人与候选视图，并标注每格需求强度（none/overview/moderate/high）；
Step2 **合并视图减少数量**：找“边缘视图”（只要概览/受众很少）并与强势视图合并（如多种 C&C 视图常可合并；分解视图可与工作分配/实现/uses/layered 合并等）；
Step3 **排序与分阶段发布**：优先早发布分解视图；允许 breadth-first（先给概览再加细节），不必一次满足全部干系人100%。

### 5）题：一个视图应如何文档化？请写出模板的关键组成。

**标准答案：**
一个视图通常按模板组织：
(1) **Primary presentation**：展示该视图元素与关系（通常图形），必须给出 notation key（缺 key 是最常见错误）；
(2) **Element catalog**：解释图中元素/关系（元素属性、关系属性、接口、必要的行为说明）；
(3) **Context diagram**：说明与环境关系以界定 scope；
(4) **Variability guide**：说明变体点如何使用/允许如何变化；
(5) **Rationale**：解释为何如此设计并论证其合理性（含模式选择理由）。

### 6）题：敏捷/快速迭代下如何做架构文档？（写原则）

**标准答案：**
敏捷项目应：采用统一模板记录设计决策；**仅在某视图有明确干系人需求时才文档化**；信息何时出现就何时填模板（不要求一次填完）；只有当记录能让后续工作更容易/更便宜/更可能成功时才写；“够用即可”支撑继续写代码；不需要的章节可写 **N/A**；白板讨论形成的模型可拍照作为 primary presentation。

