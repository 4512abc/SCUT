# 第20章（Architecture Reconstruction and Conformance）

------

## A. 必背定义（20个，闭卷可直接默写）

> 统一格式：**术语(英文) — 一句话定义 — 关键点2条 — 常见误区1条**

1. **Architecture reconstruction（架构重建）** — 从现有系统工件/运行信息中恢复架构表示，用于理解、文档化与一致性检查。

- 关键点：目的包括“补文档 + 查一致性”。
- 关键点：as-built 由系统工件逆向得到。
- 误区：把它当成“只画几张图”。

1. **Architecture conformance（一致性/符合性）** — 检查系统“实际建成的架构”是否符合“设计意图/设计架构”。

- 关键点：对比对象通常是 as-built vs as-designed。
- 关键点：可通过约束/关系 + 工具检测违例。
- 误区：只做代码规范检查就说“符合性通过”。

1. **As-built architecture（建成架构）** — 由已有系统工件（源码/脚本/trace 等）逆向得到的“真实实现结构”。

- 关键点：可能与文档不一致。
- 关键点：是 conformance 检查的事实基准。
- 误区：把旧文档当作 as-built。

1. **As-designed architecture（设计架构）** — 架构师意图中的“应然结构与约束”。

- 关键点：往往需要额外补充“关系与约束”以反映设计意图。
- 关键点：用于对照 as-built 做 conformance。
- 误区：认为 as-designed 一定“已经在代码里显式存在”。

1. **View（视图）** — 一组从某类来源抽得的原始架构信息集合（raw information set）。

- 关键点：来源可含源码、构建脚本、运行 trace。
- 关键点：单个 view 往往不完整/不够准确，需要融合。
- 误区：把 view 等同于“最终架构视图文档”。

1. **Raw view extraction（原始视图抽取）** — 分析已有设计/实现工件，构建一个或多个“原始模型/视图”。

- 关键点：服务于“整体文档化”或“回答特定架构问题”。
- 关键点：取舍来自“理想要什么信息”与“工具能抽什么”。
- 误区：上来就追求完美全量抽取，导致信息爆炸。

1. **Static information（静态信息）** — 只观察系统工件（artifact）得到的信息。

- 关键点：典型来自源码、头文件、build files。
- 关键点：可能看不到运行时才出现的拓扑/连接关系。
- 误区：认为静态分析足以得到完整架构。

1. **Dynamic information（动态信息）** — 通过观察系统运行获得的信息。

- 关键点：可由 profiling、instrumentation、runtime traces、AOP 监控得到。
- 关键点：能捕获运行时连接器/调用路径等。
- 误区：把动态信息当成“性能测试数据”，忽略其架构意义。

1. **Late binding（晚绑定）** — 架构相关关系在源码中不完全显式，需到运行时才能确定。

- 关键点：常见来源：多态、函数指针、运行时参数化、插件、broker 介导交互等。
- 关键点：导致“必须融合静态+动态”。
- 误区：只把晚绑定理解成“动态链接库”。

1. **Database construction（重建数据库构建）** — 将抽取到的 raw 信息标准化并填充到重建数据库。

- 关键点：raw views 往往“过细”，不利于架构理解，需要后续抽象。
- 关键点：数据库用于生成权威架构文档并支撑操作/聚合。
- 误区：把它当成“随便存文件”。

1. **Reconstruction database（重建数据库）** — 存放标准化抽取事实、便于聚合/抽象/分析的底座。

- 关键点：信息量大，手工处理易错；工具常封装 DB。
- 关键点：自建 workbench 往往需自己选 DB 与内部表示。
- 误区：认为“数据库=最终架构”，忽略后续融合与验证。

1. **White noise view（白噪声视图）** — 展示某类关系“全量连接”的图：准确但不有用。

- 关键点：信息过载导致无法看出结构与抽象。
- 关键点：需要 collapse 细节 + show abstractions 才能可用。
- 误区：看到连接多就以为“分析更严谨”。

1. **Collapse information（折叠信息）** — 把过细粒度细节隐藏/合并，以提升可读性。

- 关键点：例：把方法细节“藏进”类定义。
- 关键点：目标是从“事实噪声”走向“结构理解”。
- 误区：把折叠当成“删数据”，导致丢失可追溯性。

1. **Show abstractions（展示抽象）** — 通过聚合/抽象让关键结构显性化（如层、对象簇、关键连接）。

- 关键点：例：呈现业务对象与 UI 对象的整体连接、识别 layers。
- 关键点：抽象是为了支持推理/检查，而不是“画好看”。
- 误区：抽象只做命名，不做关系与边界。

1. **View fusion（视图融合）** — 操作并组合一个或多个抽取视图，生成 fused views。

- 关键点：单视图可能不完整/不准，融合提高整体准确性。
- 关键点：典型：静态调用视图 + 动态调用视图互补。
- 误区：把融合理解为“把两张图叠一起”。

1. **Fused view（融合视图）** — 融合后的视图，承载更整体的结构信息并服务分析。

- 关键点：融合的产物常引出新的聚合/抽象/聚类。
- 关键点：可被进一步精炼或被否定。
- 误区：认为 fused view 一次生成就定稿。

1. **Hypothesis about the architecture（架构假设）** — 在融合阶段形成的“对系统架构的推断性解释”。

- 关键点：会被可视化以便分析与验证。
- 关键点：没有统一完成标准：够支撑干系人分析即可。
- 误区：把假设当成事实，不做验证。

1. **Architectural analysis（架构分析）** — 测试架构假设是否正确/是否符合设计意图，发现违例并迭代修正。

- 关键点：假设表现为“架构元素（如层）+ 关系/约束”。
- 关键点：不符合则回到前面阶段重复。
- 误区：只做一次检测，不迭代。

1. **Violation（违例）** — 实现中出现了违反架构约束/关系的依赖或连接。

- 关键点：例如分层规则禁止的依赖、对不可访问组件的依赖。
- 关键点：工具可自动报告（如层到 JUnit 的依赖弧）。
- 误区：把违例当成“代码风格问题”。

1. **Dynamic violation（动态违例）** — 运行时才暴露的、违反 C&C 假设/约束的连接器或交互路径。

- 关键点：可通过 instrumentation + 动态分析发现（如 AspectJ 监控）。
- 关键点：有些动态违例仅靠源码分析难发现。
- 误区：只做静态抽取就宣布“无违例”。

------

## B. 10个对比题（标准答案，可直接写卷面）

1. **Architecture reconstruction vs Architecture conformance**

- Reconstruction：从工件逆向恢复 as-built 与架构表示；
- Conformance：用恢复结果对照 as-designed 的约束/意图，检测是否符合。

1. **As-built vs As-designed**

- As-built：从现有工件/trace 逆向得到的现实结构；
- As-designed：设计意图中的应然结构（需补充约束/关系）。

1. **Static information vs Dynamic information**

- Static：看 artifacts；优点覆盖全源码，缺点看不到运行时拓扑；
- Dynamic：看运行；优点捕获晚绑定关系，缺点可能覆盖不全。

1. **Late binding vs Early binding（就本章语境）**

- Late binding：关系/拓扑运行时确定，源码不完全显式；
- Early binding：关系在静态工件中就能确定与抽取。

1. **Raw view extraction vs View fusion**

- Raw extraction：从工件抽“事实视图”；
- View fusion：把多视图互补信息融合成“架构假设/抽象视图”。

1. **Database construction vs View fusion**

- Database construction：标准化入库，解决“数据大、操作繁琐易错”；
- View fusion：在库上做聚合/抽象/聚类，形成可检验的假设视图。

1. **White noise view vs Useful architectural view**

- White noise：全量连接，准确但不可用；
- Useful view：折叠细节、突出抽象（如层、关键连接与边界）。

1. **View fusion vs Architectural analysis**

- Fusion：生成假设与可视化；
- Analysis：引入设计意图约束，测试假设并找违例，不对就迭代。

1. **Violation vs Dynamic violation**

- Violation：一般指静态结构依赖违反约束（如层→JUnit）；
- Dynamic violation：运行时发现的连接器/交互违反 C&C 假设（如运行时 database write connector）。

1. **Tool vs Workbench（重建语境）**

- Tool：单个抽取/分析工具（扫源码、分析脚本或 trace）；
- Workbench：开放可集成的框架，使新增工具不破坏既有工具/数据。

------

## C. 6道简答题（标准答案模板）

### 1）为什么需要架构重建？（Why reconstruction?）

**标准答案：**

- 当你接手已有系统但不了解其架构时（未记录/文档丢失/文档与实现不同步），为了维护系统并在演化中保持既有质量属性，需要通过架构重建恢复可用的架构表示与事实基础。

### 2）架构重建的目的有哪些？（Purposes）

**标准答案：**

- （1）在文档不存在或严重过期时，用恢复出的架构表示作为架构文档化基础；
- （2）确保 as-built 与 as-designed 的一致性（conformance），即从系统工件逆向得到 as-built，并与设计意图对照检查。

### 3）写出本章“四阶段流程”，并说明每步产出/作用

**标准答案：**

- ① Raw view extraction：从源码、build scripts、trace 等抽取元素与关系，得到若干基础视图；
- ② Database construction：将 raw 信息标准化入库，为后续聚合与权威文档生成打底；
- ③ View fusion：融合多视图，形成更准确的 fused views（架构假设/抽象/聚类）；
- ④ Architectural analysis：引入关系与约束（设计意图），测试假设并检测违例；不正确则迭代回前序步骤。

### 4）为什么必须融合静态与动态信息？（Static + Dynamic）

**标准答案：**

- 静态抽取仅观察工件，可能缺失由晚绑定导致的架构关系；动态信息通过观察运行捕获运行时拓扑与调用/连接器信息，但可能覆盖不全。故应融合静态与动态以获得更准确的系统视图，并可借助 profiling、instrumentation、runtime traces 或 AOP 监控获取动态信息。

### 5）如何进行“架构一致性检查/找违例”？（Finding violations）

**标准答案：**

- 先通过融合得到架构假设（元素如 layers）并由架构师补充设计意图中的关系与约束；再将实现中抽取的依赖与这些约束比对，工具可自动检测并报告违反分层/不可访问组件等约束的依赖（例如层到 JUnit 的依赖弧），据此定位并修复。

### 6）本章给的重建“实施指南”是什么？（Guidelines）

**标准答案：**

- （1）在启动项目前先明确目标与问题清单；
- （2）先获得一个粗粒度系统表示来指导抽取与生成哪些视图，识别 layers 是良好起点；
- （3）旧文档可能不准，必要时应放弃；工具只能加速，不能全自动完成；必须有熟悉系统的人员（架构师/维护者/开发者）参与。

