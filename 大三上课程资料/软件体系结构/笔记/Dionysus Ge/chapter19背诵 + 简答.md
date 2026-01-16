# 第19章（Architecture, Implementation, and Testing）

------

## 一、必背定义（≥18个）

> 格式：**术语(英文) — 一句话定义（应试版）— 关键词**

1. **Architecture as a blueprint — 架构作为蓝图**：架构是实现的“施工蓝图”，规定实现者要落地的结构与约束。— *blueprint, constraints*
2. **Embedding the design in the code — 将设计嵌入代码**：把架构结构/约束用代码内的注释与约定表达，使后续维护者与工具能关联代码与架构。— *comments, conventions, tool support*
3. **Architectural structure (layer/pub-sub/MVC/broker, …)**：实现者需要明确自己在实现哪种架构结构（如分层、发布订阅、MVC、Broker等）。— *structure awareness*
4. **Conventions — 项目约定**：团队对“如何在代码中记录架构结构”的统一规则，使工具可自动关联代码与架构。— *standardization, automation*
5. **Framework — 框架**：围绕特定主题组织的一组可复用类；程序员使用框架提供的服务（框架常隐含结构约束）。— *reusable classes, services*
6. **Ruby on Rails (example of framework)**：基于MVC、面向Web应用的框架，提供采集请求、访问数据库、渲染模板等能力。— *MVC, web, DB, templates*
7. **AUTOSAR (example of framework)**：面向汽车内部计算机的软件框架/标准化生态（体现领域约束）。— *automotive domain*
8. **Code template — 代码模板**：一组骨架代码，开发者只在指定位置填入应用特定部分。— *fixed places, fill-in*
9. **Failover protocol — 故障切换协议**：关键组件检测到故障后，通过主备切换流程维持服务连续性。— *failover, continuity*
10. **Switchover — 切换**：故障发生时将后台并行运行的备份副本提升为新的主副本的一次切换过程。— *promote secondary → primary*
11. **Primary — 主副本**：对外提供主服务、与客户端交互的主执行副本。— *serving, clients*
12. **Secondary — 备副本**：在其他处理器后台并行执行，用于在故障时接管成为新的主副本。— *background, parallel*
13. **Hot standby — 热备**：关键组件需要随时可接管的备份运行方式；要求统一使用模板并在固定位置填业务。— *hot standby, template enforcement*
14. **Architecture erosion — 架构侵蚀**：实现逐渐偏离已文档化架构的现象（代码与架构不一致）。— *drift, inconsistency*
15. **Build/check-in enforcement — 构建/提交强制约束**：把架构规则加入构建或提交流程，靠工具强制执行架构约束。— *tooling, enforce rules*
16. **Mark documentation out of date — 文档过期标记**：侵蚀发生时把文档标记为过期，以提升剩余可信内容的公信力。— *out of date, credence*
17. **Synchronization times — 同步时间点**：定期安排代码与架构文档同步对齐，减少侵蚀累积。— *scheduled alignment*
18. **Test harness — 测试支架/驱动框架**：驱动被测单元运行，并注入负载/故障/攻击以验证质量属性。— *drive, inject, observe*
19. **Unit test units — 单元测试单元**：由架构定义，被测“单元”是组件或模块，而非仅函数级。— *components/modules*
20. **Synthetic loads — 合成负载**：用人为构造的负载驱动被测单元，以测试性能等属性。— *performance*
21. **Fault injection — 故障注入**：注入依赖不响应等故障来测试可用性与异常处理行为。— *availability, dependency failure*
22. **Attack scenarios — 攻击场景**：在集成测试中由测试支架执行攻击用例，以验证安全性。— *security testing*
23. **System degradation — 长时间退化**：系统运行很久后因资源未释放或配置错误而出现性能/行为退化。— *resource leak, misconfiguration*
24. **Network effects — 网络效应**：小的性能/配置误差在大规模部署（上千台）下被放大造成严重退化。— *scale amplification*
25. **Self-aware systems — 自感知系统**：系统监控自身并对外暴露监控值，用于发现网络效应。— *monitor itself, values externally available*
26. **Test-driven development (TDD) — 测试驱动开发**：下一增量以满足预先定义的测试为目标进行开发。— *next increment, predetermined test*

------

## 二、10个对比题（标准答案）

1. **Framework vs Code Template（框架 vs 模板）**

- 框架：可复用类集合+服务，开发者在其机制与结构约束下开发。
- 模板：一段骨架代码，开发者只在固定位置填应用特定部分。
- 核心差异：框架是“运行/结构生态”；模板是“代码骨架插槽化”。

1. **Embedding design in code vs Using tools to enforce constraints（写进代码 vs 工具强制）**

- 写进代码：通过注释/约定表达结构约束，便于理解与关联。
- 工具强制：在 build/check-in 直接拦截违反架构规则的提交。
- 核心差异：前者偏“可理解/可追踪”，后者偏“可执行/硬约束”。

1. **Architecture erosion vs Causes of drift（侵蚀 vs 漂移原因）**

- 侵蚀：实现偏离文档化架构这一现象。
- 原因：实现者做出不一致决策，或架构未预见所有情况。
- 核心差异：侵蚀是结果；原因是过程中的决策偏差与未知情形。

1. **Mark documentation out of date vs Synchronization times（标记过期 vs 定期同步）**

- 标记过期：承认文档已不可信，保护剩余内容可信度。
- 定期同步：主动安排对齐时间，减少偏离累积。
- 核心差异：前者是“损害控制”；后者是“预防性治理”。

1. **Unit test vs Integration test（单元测 vs 集成测）**

- 单元测：架构定义单元（组件/模块）及其职责/交互，靠 harness 驱动并可做负载/故障注入。
- 集成测：在交互链条层面验证功能/性能/可用性/安全，并可执行攻击场景。
- 核心差异：单元测侧重“单元职责正确”；集成测侧重“协同交互正确+安全”。

1. **Synthetic loads vs Fault injection（合成负载 vs 故障注入）**

- 合成负载：人为构造压力来测性能。
- 故障注入：人为制造依赖不响应等故障来测可用性/容错。
- 核心差异：负载针对“性能”；注入针对“可用性/异常路径”。

1. **Fault injection vs Attack scenarios（故障注入 vs 攻击场景）**

- 故障注入：模拟故障（如依赖不响应）验证可用性。
- 攻击场景：模拟攻击验证安全性。
- 核心差异：目标质量属性不同（availability vs security）。

1. **Local variation vs Network effects（局部波动 vs 网络效应）**

- 局部波动：2% 性能下降在单机可能属正常范围。
- 网络效应：同样 2% 在上千台部署会被放大导致严重退化。
- 核心差异：是否处于大规模部署导致“误差放大”。

1. **Self-aware systems vs Ordinary testing（自感知 vs 常规测试）**

- 自感知：系统自监控并对外提供监控值，更易发现网络效应。
- 常规测试：小规模/离线测试往往难发现网络效应。
- 核心差异：可观测性范围不同（运行中全局 vs 小规模局部）。

1. **Test planning vs Test interpretation（测试计划 vs 结果解释）**

- 计划：架构师知道系统敏感区，能指导测什么。
- 解释：架构师知道监控值应当是什么水平，能解释偏差与风险。
- 核心差异：前者决定“测什么”；后者决定“测出来意味着什么”。

------

## 三、6道简答题（标准答案，可直接抄）

### 1）简答：本章给出的“保持代码与架构一致”的四种技术是什么？

**答：**

- 采用四种技术保持一致：①将设计嵌入代码（注释+约定）；②使用框架（复用类与服务并隐含结构约束）；③使用代码模板（固定骨架与插槽）；④通过一致性维护措施避免架构侵蚀。

### 2）简答：什么是架构侵蚀？为什么会发生？如何预防？

**答：**

- 架构侵蚀是实现逐渐偏离已文档化架构的现象。
- 原因：实现者做出彼此不一致或与架构不一致的决策；架构未预见开发中出现的全部情况。
- 预防：用工具在 build/check-in 强制架构规则；侵蚀发生时标记文档过期以维护剩余可信度；定期安排文档/代码同步时间点。

### 3）简答：什么是代码模板？以PPT的failover例说明模板流程要点。

**答：**

- 代码模板是一组骨架代码，开发者只在固定位置填应用特定部分。
- failover例：故障检测后进行切换——secondary（后台并行）提升为 primary；新 primary 与客户端重建；启动新 secondary 作为备份并向 primary 宣告；若 secondary 再故障则在其他处理器再启动新的 secondary。
- 流程要点：所有必须 hot standby 的关键组件统一使用同一模板；应用特定代码只能放在模板规定的固定位置。

## 4）简答：代码模板有哪些优势？（三点）

**答：**

- 同类组件以相似方式运行（行为一致）；
- 模板骨架只需调试一次即可复用；
- 复杂部分可由熟练人员完成并交给较少经验人员填业务。

### 5）简答：为什么“架构会影响单元测试与集成测试”？Test harness 能测什么？

**答：**

- 架构定义被测单元（组件/模块）及其职责与交互，因此单测/集成测依赖架构知识与 test harness。
- harness 能：驱动被测单元；用合成负载测性能；用故障注入测可用性（如依赖不响应）；集成测还可执行攻击场景测试安全；并可通过分配变更验证可修改性要求。

### 6）简答：什么是网络效应？为什么难发现？如何更容易发现？

**答：**

- 网络效应：小的性能/配置问题在上千台规模部署时被放大，导致严重退化；如 2% 性能下降单机可视为正常波动，但大规模会造成严重影响。
- 难发现原因：小规模测试难体现规模放大效应，且安装配置错误很常见并会触发（如消息经由中介转发引入额外延迟）。
- 发现方式：依靠自感知系统监控自身并对外提供监控值（values available externally）以定位网络效应。

