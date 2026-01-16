# 第21章（Architecture Evaluation）

------

## A) 必背定义（≥20个，按“1句定义 + 2关键点 + 1易错点”）

1. **Architecture Evaluation（架构评估）**

- 定义：对架构进行分析/评审，以判断其能否满足系统业务目标与质量属性目标。
- 关键点：①必须有“描述架构的工件”才能评估；②评估要回答是否满足 business goals。
- 易错点：把评估当成“代码评审/测试”。（评估对象是架构与其决策）

1. **Three Forms of Evaluation（三种评估形态）**

- 定义：设计者自评（designer）、同行评审（peers）、外部人员分析（outsiders）。
- 关键点：①designer/peer 往往发生在设计过程中；②outsider 多用于已完成的完整架构。
- 易错点：把 peer review 误写成 outsider review（两者目的/身份不同）。

1. **Evaluation by the Designer（设计者评估）**

- 定义：设计者每做关键决策或达到里程碑时，对选项与替代方案进行评估。
- 关键点：①属于 generate-and-test 的“test”；②分析深度取决于决策重要性与可选方案数量。
- 易错点：追求“完美最优”而过度分析；PPT强调 good enough 很多时候更重要。

1. **Generate-and-test（生成-测试式架构设计）**

- 定义：先生成候选架构/方案，再通过评估“测试”其后果是否可接受。
- 关键点：①评估是生成后必做的 test；②不该花超过其价值的时间。
- 易错点：把“test”理解为跑测试用例；这里是架构层面的分析/推理。

1. **Peer Review（同行评审）**

- 定义：像 code review 一样对候选架构（或可评审部分）进行评审，通常至少几小时到半天。
- 关键点：①可发生在设计过程任意时点；②用质量属性场景驱动 walkthrough。
- 易错点：把 peer review 变成“听架构师讲解会”，没有用场景逐一走查。

1. **Peer Review Steps（同行评审步骤）**

- 定义：用质量属性场景驱动评审：确定场景→架构展示→理解确认→逐场景走查→记录问题→决定修复或接受风险。
- 关键点：①提问先为“理解”；②真实问题要修复或明确接受其概率与后果。
- 易错点：只提“要改”，不写“由设计者+项目经理明确接受问题及其发生概率”。

1. **Analysis by Outsiders（外部评估/外部分析）**

- 定义：由相对项目“外部”的专家对架构进行更客观的分析，管理者更愿意听取其发现。
- 关键点：①outside 是相对概念（项目外/业务单元外/公司外）；②通常用于完整架构评估。
- 易错点：认为 outsider 一定是“公司外部”；PPT强调 outside 是相对。

1. **Contextual Factors for Evaluation（评估的情境因素）**

- 定义：影响评估组织与效果的一组因素：可用工件、结果可见范围、执行者、参与干系人、业务目标等。
- 关键点：①必须有架构描述工件；②评估过程要能引出关键干系人的目标与关切。
- 易错点：只写“谁来评估”，漏掉“business goals/谁看结果/哪些干系人参与”。

1. **ATAM (Architecture Tradeoff Analysis Method)**

- 定义：一种综合性的架构评估方法，通过质量属性场景揭示架构决策及其风险与权衡。
- 关键点：①评估者不必熟悉架构或业务目标，系统也不必已实现；②适用于干系人多的场景。
- 易错点：把 ATAM 当“性能评测方法”；它覆盖多质量属性的权衡分析。

1. **ATAM Evaluation Team（评估团队）**

- 定义：通常 3–5 人，外部于被评估项目，被认可为胜任、无偏的 outsiders。
- 关键点：①可能一人兼多角色；②外部团队更易被管理层接受其发现。
- 易错点：把评估团队写成“开发团队自己人”；ATAM强调外部且无偏。

1. **Project Decision Makers（项目决策者）**

- 定义：能代表项目发声或有权要求架构变更的人（通常含项目经理/客户代表等）。
- 关键点：①授权决策；②在 ATAM 中提供 business drivers 与决策输入。
- 易错点：把“普通开发人员”当 decision maker。

1. **Architect（架构师）**

- 定义：必须参与 ATAM，并解释架构如何支持高优先级场景。
- 关键点：①在 Step3 做架构展示；②在 Step6/8 逐场景解释决策如何实现需求。
- 易错点：认为 ATAM 可以“绕过架构师”；PPT明确架构师必须愿意参与。

1. **Architecture Stakeholders（架构干系人）**

- 定义：对架构“按承诺表现”有切身利益的人，其职责是提出具体的质量属性目标。
- 关键点：①包括开发/测试/集成/维护/性能工程师/用户/外部系统构建者等；②大型关键系统可达 12–15 人。
- 易错点：把 stakeholder 仅理解为“客户”。

1. **Evaluation Leader（评估负责人/评估领队）**

- 定义：在 Step1 介绍 ATAM 流程、解释大家将遵循的过程、回答问题并设定预期与上下文。
- 关键点：①用标准presentation概述步骤与输出；②确保后续活动有共同理解。
- 易错点：把 Step1 写成“介绍业务目标”（那是 Step2）。

1. **Business Drivers（业务驱动）**

- 定义：从业务视角给出系统背景与驱动：关键功能、约束、业务目标/上下文、主要干系人、ASRs。
- 关键点：①由 decision maker（理想是 PM/客户）陈述；②必须让所有参与者理解开发动机与约束。
- 易错点：只写业务目标，漏掉 constraints、stakeholders、architectural drivers。

1. **Architectural Drivers / ASRs（架构驱动/架构重要需求）**

- 定义：在 Step2 中被点名为 architectural drivers，即 architecturally significant requirements。
- 关键点：①决定架构走向的关键质量/约束需求；②会在后续场景分析中被追踪到决策。
- 易错点：把一般功能需求都当 ASR。

1. **Architectural Approaches（架构方法/架构策略）**

- 定义：为满足需求而采用的 patterns / tactics 等架构手段，是 ATAM 分析的核心对象。
- 关键点：①Step4 只做“识别与公开记录”；②后续用场景把 approach→决策→质量属性建立链接。
- 易错点：把 Step4 写成“评判好坏”；PPT说 simply catalogs。

1. **Utility Tree（质量属性效用树）**

- 定义：用树把质量目标具体化成场景叶子，并按重要性（H/M/L）排序，使需求可推理。
- 关键点：①场景填充叶子节点；②由评估团队与 decision makers 一起识别、细化、排序。
- 易错点：把 utility tree 写成“功能分解树/模块树”。

1. **Quality Attribute Scenario（质量属性场景）**

- 定义：以场景形式精确表达质量属性需求，ATAM 用它驱动分析与排序。
- 关键点：①在 utility tree 和 brainstorming 中都以 scenarios 表达；②“优先级场景”用于 Step6/8。
- 易错点：只写“性能要好/可用性要高”而不写成场景。

1. **Risk（架构风险）**

- 定义：在质量属性需求背景下，某个架构决策可能导致不良后果。
- 关键点：①在 Step6/8 被识别并记录；②形成风险缓解计划的基础。
- 易错点：把 risk 写成“进度风险/人员风险”；ATAM 的 risk 绑定“架构决策+质量场景”。

1. **Nonrisk（非风险）**

- 定义：经分析被认为“安全”的架构决策。
- 关键点：①同样需要记录（不是只有风险才记录）；②体现“哪些决策是稳妥的”。
- 易错点：以为 nonrisk 不重要；PPT把它列为 ATAM 输出之一。

1. **Sensitivity Point（敏感点）**

- 定义：对一个或多个质量属性有显著影响的架构决策点/参数点。
- 关键点：①Step6/8 识别并记录；②PPT示例：并发数据库客户端数影响吞吐。
- 易错点：把“任何参数”都当敏感点；要强调“marked effect”。

1. **Tradeoff Point（权衡点）**

- 定义：对多个质量属性产生显著影响、导致取舍的架构决策点。
- 关键点：①典型例：心跳频率↑→可用性↑但占用资源→性能可能↓；②是 ATAM 的关键发现之一。
- 易错点：只写“有权衡”，不写“影响哪些质量属性、为什么”。

1. **Risk Theme（风险主题）**

- 定义：将多个风险按共同底层问题/系统性缺陷归并成主题，若不处理会威胁业务目标。
- 关键点：①Step9 私下汇总形成；②每个主题要映射到受影响的 business drivers。
- 易错点：把 risk theme 当“风险列表”；主题是“提炼共因”。

1. **Mapping Decisions to Quality Requirements（决策—质量需求映射）**

- 定义：对每个被分析的质量场景，捕获哪些架构决策帮助实现它。
- 关键点：①形成可追踪证据链；②属于 ATAM 输出之一。
- 易错点：只输出“结论”，不输出“决策如何支撑场景”的链条。

1. **Intangible Outputs（无形输出）**

- 定义：ATAM 除了文档化输出，还带来社区感、开放沟通渠道、对架构强弱更整体的理解。
- 关键点：①难量化但持久；②提升架构师与干系人的沟通质量。
- 易错点：只写“发现风险”，忽略共识与沟通收益。

1. **Lightweight Architecture Evaluation（轻量级架构评估）**

- 定义：基于 ATAM、面向小型/低风险项目的低成本评估，可半天到一天完成，也可由内部人员完成。
- 关键点：①ATAM 约需 20–30 person-days（评估团队）+更多干系人投入；②轻量版降低仪式与成本但深度/客观性更低。
- 易错点：把轻量评估写成“随便开会”；PPT强调它仍基于 ATAM 步骤与阶段。

1. **Typical Agenda: 4–6 Hours（轻量评估典型时长）**

- 定义：轻量评估常以 4–6 小时议程组织，做到“一个下午完成”。
- 关键点：①人员更少且内部；②更快达成 shared understanding。
- 易错点：写成“固定 4 小时”；PPT是典型范围。

------

## B) 10个对比题答案（标准作答句式）

### 1）Designer Evaluation vs Peer Review

- **Designer**：设计者在关键决策/里程碑时评估候选与替代方案，是 generate-and-test 的 test；分析深度取决于决策重要性等。
- **Peer Review**：同行以质量属性场景驱动走查，可在设计过程任意时点进行，通常几小时到半天。
- **一句话结论**：designer 更“自我验证”，peer 更“第三方同侪校验”，同样以决策后果为中心。

### 2）Peer Review vs Outsider Analysis

- **Peer**：同团队/同级别同行评审候选架构部分即可，强调 walkthrough 场景。
- **Outsider**：相对项目外部的专家/团队，更客观且管理层更愿听，常用于完整架构。
- **结论**：peer 更轻量更频繁；outsider 更正式更“权威”。

### 3）ATAM vs Lightweight Architecture Evaluation

- **ATAM**：综合方法、适用于大/昂贵/高风险项目；评估团队投入可达 20–30 person-days，干系人投入更多。
- **Lightweight**：基于 ATAM，半天到一天，可全内部完成；更少人、更快共识，但深度/客观性较低。
- **结论**：同一“场景驱动分析内核”，区别是投入、深度与适用项目规模。

### 4）Risk vs Nonrisk

- **Risk**：可能导致不良后果的架构决策（在质量属性需求背景下）。
- **Nonrisk**：经分析 deemed safe 的架构决策。
- **结论**：二者都必须记录，且都来源于“场景驱动分析”。

### 5）Sensitivity Point vs Tradeoff Point

- **Sensitivity**：某决策/参数对质量属性有 marked effect（改一点影响很大）。
- **Tradeoff**：同一决策显著影响多个质量属性，存在取舍（如 heartbeat 频率影响 availability 与 performance）。
- **结论**：敏感点强调“强影响”；权衡点强调“多属性冲突”。

### 6）Utility Tree Scenarios vs Brainstormed Scenarios

- **Utility Tree**：与 decision makers 一起把质量目标细化成场景并排序（H/M/L），作为 Step6 输入。
- **Brainstorm**：更大范围干系人提出“角色视角”的操作性场景，投票排序，与 utility tree 对比看是否对齐。
- **结论**：utility tree 更“自上而下对齐驱动”；brainstorm 更“验真/发现遗漏”。

### 7）ATAM Step6 vs Step8

- **Step6**：分析 utility tree 中最高优先级场景，记录 risks/nonrisks/sensitivity/tradeoff。
- **Step8**：对 Step7 新产生并排序的高优先级场景做“同样活动”，通常覆盖 top 5–10。
- **结论**：Step8 = Step6 on newly generated scenarios。

### 8）Business Drivers vs Architectural Drivers (ASRs)

- **Business drivers**：业务视角系统概览：功能、约束、业务目标/上下文、干系人、ASRs。
- **Architectural drivers/ASRs**：其中最关键、会改变架构走向的架构重要需求（architecturally significant requirements）。
- **结论**：business drivers 是“大背景+动机”，ASRs 是“决定架构的关键钉子”。

### 9）Risk List vs Risk Themes

- **Risk list**：逐场景得到的具体风险（决策可能导致不良后果）。
- **Risk themes**：Step9 归并风险得到系统性缺陷主题，并映射到 business drivers。
- **结论**：list 是“散点”，theme 是“共因+管理层视角”。

### 10）Peer Review Outcomes vs ATAM Outcomes

- **Peer review**：记录问题并要求“修复或明确接受问题及发生概率”。
- **ATAM**：输出更体系化：utility tree、风险/非风险、敏感点/权衡点、风险主题、决策—质量需求映射等。
- **结论**：peer review 更偏“发现/处置问题”；ATAM 更偏“系统化证据链+权衡分析产物”。

------

## C) 6道简答题标准答案（可直接抄）

### 1）简答：本章给出的“三种架构评估方式”是什么？各自适用场景一句话说明。

**标准答案**：

- 三种方式：①设计者在设计过程中的评估；②设计过程中的同行评审；③架构完成后由外部人员分析。
- 设计者评估：每个关键决策/里程碑进行 generate-and-test 的“test”，重要决策多分析。
- 同行评审：候选架构或其可评审部分存在即可，通常几小时到半天，场景驱动走查。
- 外部分析：相对项目外部的专家更客观，管理层更愿听，常用于完整架构。

### 2）简答：进行架构评估要考虑哪些 Contextual Factors？

**标准答案（列点即可）**：

- 可用工件：必须存在描述架构的 artifact。
- 结果可见性：哪些评估结果对哪些人公开（全体参与或更私密）。
- 执行者：个人还是团队执行评估。
- 参与干系人：评估过程要能引出关键干系人的目标与关切，识别并确保其参与很关键。
- 业务目标：评估应回答系统是否满足 business goals。

### 3）简答：ATAM 的参与者有哪些？各自职责是什么？

**标准答案**：

- 评估团队（evaluation team）：外部于项目，通常 3–5 人，被认可为胜任、无偏的 outsiders，负责引导分析并产出结果。
- 项目决策者（project decision makers）：能代表项目或有权要求变更的人，提供业务视角与关键驱动并支持决策。
- 架构师（architect）：必须参与，展示架构并解释架构如何支持高优先级场景。
- 架构干系人（stakeholders）：提出具体质量属性目标与场景（如维护/用户/QA 等），参与场景脑暴与排序。

### 4）简答：请写出 ATAM 的核心步骤链（Step1–Step9）并说明 Step6/Step9 各自产出什么。

**标准答案**：

- Step1：评估负责人介绍 ATAM 流程、输出、上下文与预期。
- Step2：决策者从业务视角陈述 business drivers（功能、约束、业务目标/上下文、干系人、ASRs）。
- Step3：架构师展示架构（技术约束、外部交互、采用的 approaches/patterns/tactics，传达 essence）。
- Step4：评估团队识别并公开记录架构 approaches（patterns/tactics），作为后续分析基础。
- Step5：生成 utility tree，把质量目标细化为场景叶子并排序（H/M/L）。
- **Step6（产出重点）**：逐个分析最高优先级场景，记录相关决策，并识别/记录 risks、nonrisks、sensitivity points、tradeoff points，建立决策—质量需求链接。
- Step7：干系人脑暴并投票排序场景，与 utility tree 对比检验对齐；差异大可能本身构成风险。
- Step8：对新增高优先级场景重复 Step6 的分析活动（常覆盖 top 5–10）。
- **Step9（产出重点）**：私下将风险归并为 risk themes，并映射到受影响的 business drivers；向干系人汇报输出清单（approaches、场景与排序、utility tree、risks/nonrisks、敏感点/权衡点、risk themes）。

### 5）简答：Risk / Nonrisk / Sensitivity point / Tradeoff point 分别是什么？各举1个 PPT 例子说明。

**标准答案**：

- Risk：可能导致不良后果的架构决策（在质量需求背景下）。例：心跳频率影响故障检测时间，某些赋值会导致不可接受的响应。
- Nonrisk：经分析 deemed safe 的架构决策（可作为稳妥决策记录）。
- Sensitivity point：对质量属性有 marked effect 的决策点。例：并发数据库客户端数影响数据库每秒处理事务数。
- Tradeoff point：同时显著影响多个质量属性、存在取舍的决策点。例：心跳频率越高→可用性更好，但消耗更多处理与带宽→可能降低性能。

### 6）简答：为什么要提出 Lightweight Architecture Evaluation？它相对 ATAM 的优缺点是什么？

**标准答案**：

- 提出原因：完整 ATAM 是重大投入（评估团队约 20–30 person-days，架构师与干系人投入更多），只在大型/昂贵/高风险项目上才值得。
- 轻量评估定义：基于 ATAM，面向小型/低风险项目，可在一天甚至半天完成，可全内部人员执行。
- 优点：成本低、仪式感低、参与者少且内部→更快获得 shared understanding；可在项目中多次做（peer review 式）。
- 缺点：更低的 scrutiny 与 objectivity，可能不如 ATAM 深入。

