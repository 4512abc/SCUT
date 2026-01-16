# Chapter 3: The Many Contexts of Software Architecture

“软件架构存在于四种 context：technical（质量属性需求达成）、project life cycle（任何过程都需执行架构相关活动）、business（满足多类 stakeholder 的 business goals）、professional（架构师所需能力与职责）。此外，架构的形成有其 influences，而架构存在又会影响架构师与组织并可能影响行业，形成 Architecture Influence Cycle。”

# 第3章：所有必背定义（≥15个，按“术语(EN) — 应试定义”给你）

> 说明：这份是“第3章主线术语”。有些定义会引用前面章节的标准表述（比如 architecture / view / structure），但都服务于本章答题。

1. **Context (of architecture)** — 架构所处的外部环境与约束集合，用来解释架构为何这样形成以及会如何演化。
2. **Technical context** — 与架构达成质量属性需求及所处技术生态（行业实践/工程技术栈）相关的上下文。
3. **Project life-cycle context** — 架构与软件开发生命周期各阶段/开发过程的关系；不论采用何方法，都要执行架构相关活动。
4. **Business context** — 架构/系统服务于业务目的；必须满足多个组织/角色的 business goals。
5. **Professional context** — 架构师在组织中的角色、职责与能力要求（沟通、谈判、领导、知识更新等）。
6. **Stakeholder** — 任何对系统成功“有利害关系（has a stake）”的人或组织。
7. **Constraint (on the project)** — 对项目的约束需要尽早明确其性质、来源与优先级，以便协商与取舍。
8. **Vested organizations** — 在系统生命周期中“对系统有利益相关”的组织（客户、开发组织、分包商、监管机构等），其目标会深刻影响架构。
9. **Business goal** — 组织获取/建设系统想达成的目的（利润、抢市场、提高生产力等）；并非都以“需求”形式出现。
10. **Higher purpose** — 质量属性需求应追溯到可用“added value（附加价值）”描述的更高层目的。
11. **Added value** — 质量属性带来的可解释业务收益（如“更快响应”用于差异化竞争并获取市场）。
12. **Architecture activities** — 不论开发过程如何，都会包含：①商业论证 ②理解 ASR ③创建/选择架构 ④文档与沟通 ⑤分析/评估 ⑥基于架构实现与测试 ⑦确保实现符合架构。
13. **Architecturally Significant Requirements (ASR)** — 对架构结构与质量属性达成有决定性影响的需求集合（本章用“ASR”作为活动②的对象）。
14. **Conformance (implementation conforms to architecture)** — 确保实现遵循架构所规定的设计决策（本章活动⑦）。
15. **Tradeoff** — 在不同 stakeholder 关注点与质量属性目标冲突时，通过协商优先级进行取舍。
16. **Influence (on architecture)** — business/social/technical 等因素对架构形成的推动力。
17. **Architecture Influence Cycle** — 架构受多重影响而产生；架构存在又影响环境并塑造未来架构的循环。
18. **Shrinkwrapped software** — 非定制、成本低（理想情况下质量高）的“通用包装软件”，会改变并影响人们对需求精确匹配的预期。
19. **Units of software (project units)** — 架构规定必须实现/获取并集成的软件单元，成为项目结构与团队划分的基础。
20. **Quality attribute requirements** — 技术上下文关注的核心：架构需帮助达成质量属性需求（如性能、可用性、可修改性等）。

> （到这里已经 20 个定义；考试足够覆盖第3章全范围。）

------

# 10个对比题：标准答案（完全应试写法）

> 你给的四个我放在前四个，其余补齐到10个。

## 1) **Structure vs View**

- **Structure**：软件/硬件中“元素集合本体”（元素及其关系在系统中真实存在）。
- **View**：面向 stakeholder 的“结构表示”，是对结构的文档化表达；**view 是 structure 的表示**。
- **一句话差异**：structure 是“客观存在”，view 是“为沟通而画/写出来”。

## 2) **Module vs Component**

- **Module**：实现单元/代码组织单元（偏开发/构建）。
- **Component**：运行时实体（偏执行/交互）。
- **关键关系**：一个 decomposition 的 module 可能映射为一个/部分/多个运行时 components，映射通常 many-to-many。

## 3) **Layer vs Tier**

- **Layer（分层）**：一种模块结构；layer 是提供“内聚服务”的抽象虚拟机，通过受控接口提供服务并按受控方式使用其他层。
- **Tier（分区/多层部署）**：一种执行/部署分组；tier 是“软件组件的逻辑分组”，用于把系统执行结构划分为若干可独立的组并通过通信介质连接。
- **一句话差异**：layer 解决“代码/职责的逻辑分层”，tier 解决“部署/执行的分区分组”。

## 4) **Pattern vs Tactic**

- **Tactic**：影响某个质量属性响应的“原子级设计决策”，聚焦单一质量属性响应。
- **Pattern**：可视为“tactics 的打包组合（package）”，用于解决一类反复出现的问题。
- **一句话差异**：tactic 更小、更直接；pattern 是多决策的组合并可用 tactic 进行增强。

## 5) **Functional requirement vs Quality attribute requirement**

- **Functional**：系统必须做什么/如何对运行时刺激反应。
- **Quality attribute**：对功能的“限定/标注”（多快、多稳、多安全、多易学等）。
- **差异**：功能说“做不做”，质量属性说“做得怎样”。

## 6) **Requirement vs Constraint**

- **Requirement**：系统应满足的需求（功能或质量属性）。
- **Constraint**：零自由度的设计决策——已经替你做掉了选择。
- **差异**：requirement 给目标；constraint 直接锁定方案空间。

## 7) **Business goal vs Requirement**

- **Business goal**：组织层目的（利润/抢市场/提高生产力等），很多不会以“需求”形式出现。
- **Requirement**：对系统行为/质量的具体要求，通常写进规格说明。
- **差异**：goal 是“为什么做/价值”；requirement 是“系统要满足什么”。

## 8) **Stakeholder vs Customer**

- **Stakeholder**：任何对系统成功有 stake 的人/组织（范围更大）。
- **Customer**：购买/委托系统的一类 stakeholder（只是其中之一）。
- **差异**：customer ⊂ stakeholder；只盯 customer 容易漏掉监管、维护组织、市场等关键诉求。

## 9) **Architecture vs (general) Design**

- **Architecture**：一种“特殊的设计”，在任何过程里都要被创建/选择、文档化、评估，并约束实现与演化。
- **Design**：更广义的设计活动（包含架构层与更细粒度层面）。
- **差异**：架构是设计的子集，关注能支撑推理与质量属性达成的关键结构与决策。

## 10) **Influence on architecture vs Influence of architecture**

- **Influence on architecture**：business/social/technical 等对架构形成的推动与约束。
- **Influence of architecture**：架构存在后对 technical/business/social 环境、组织与未来架构的反向塑造。
- **差异**：一个是“外因塑造架构”，一个是“架构塑造外部世界”，二者组成 cycle。

------

# 第3章：6道简答题标准答案（可直接背/抄）

## 简答1：本章说的软件架构有哪“四种 context”？各自关注什么？

**标准答案：**

- “软件架构存在于四种 context：
  ①Technical：包括达成质量属性需求；
  ②Project life cycle：无论采用何开发方法，都必须执行架构相关活动；
  ③Business：架构产出的系统需满足多类 stakeholder 的 business goals；
  ④Professional：架构师需具备特定技能/知识并承担相应职责。”

## 简答2：不管瀑布/迭代/敏捷/模型驱动，架构活动（architecture activities）有哪些？

**标准答案：**

- “任何开发过程都包含架构活动：
  1. Making a business case
  2. Understanding ASR
  3. Creating or selecting the architecture
  4. Documenting & communicating
  5. Analyzing/evaluating
  6. Implementing & testing based on the architecture
  7. Ensuring implementation conforms to the architecture。”

## 简答3：业务目标（business goals）如何影响架构？举“added value / higher purpose”的写法

**标准答案：**

- “系统为满足一个或多个组织的 business goals 而建，架构师需识别 vested organizations 及其目标；质量属性需求应追溯到能用 added value 描述的更高层目的（higher purpose），例如‘快响应’用于产品差异化并获取市场。并非所有 business goals 都会以 requirements 形式出现，也并非所有 goals 都影响架构。”

## 简答4：什么是 stakeholder？为什么要尽早识别并主动参与？

**标准答案：**

- “Stakeholder 是任何对系统成功有利害关系的人或组织；不同 stakeholder 有不同关注点。架构师应尽早识别并主动参与 stakeholder，以尽早理解约束的性质/来源/优先级，从而管理期望、协商优先级并做 tradeoff。”

## 简答5：架构如何影响项目组织与团队划分？

**标准答案：**

- “架构规定必须实现/获取并集成的软件单元（units of software），这些单元成为开发项目结构基础；团队围绕单元组建，开发、测试与集成活动围绕单元展开，团队结构进一步嵌入组织结构。”

## 简答6：解释 Architecture Influence Cycle（闭环写法）

**标准答案：**

- “软件架构是 business/social/technical 多重影响的结果；架构存在后会影响 technical/business/social 环境，并影响架构师与组织，进而塑造未来架构；这种‘外因塑造架构—架构反向塑造环境—环境再塑造未来架构’的闭环称为 Architecture Influence Cycle。”

