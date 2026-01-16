# Chapter13 patterns and tactics

------

# A. 必背定义（≥20个，全部一口气背）

> 格式：**术语（英文）— 一句话定义 — 卷面关键点（2–3条）**

1. **Architectural Pattern（架构模式）** — 在特定 **Context** 下，对反复出现的 **Problem** 给出可复用的 **Solution**。

- 关键点：Solution 要规定元素类型、连接机制、拓扑、语义约束。
- 关键点：模式是“成套设计决策包”，带来已知属性/取舍。

1. **Context（情境）** — 一个模式适用的反复出现的系统环境/条件。

- 关键点：说明“为何会遇到该问题”。
- 关键点：不写 context 会导致“套错模式”。

1. **Problem（问题）** — 在该情境下抽象出的、反复出现的设计难题。

- 关键点：通常与质量属性目标（可修改性、可用性等）相关。
- 关键点：要写成“设计需要解决的矛盾”。

1. **Solution（解决方案）** — 成功解决该问题的抽象架构方案。

- 关键点：必须包含元素类型、连接机制、拓扑、语义约束。

1. **Element Types（元素类型）** — 模式中允许出现的构件类别（如 repository/process/object 等）。

- 关键点：写答案要点名“有哪些元素”。

1. **Interaction Mechanisms（交互机制）** — 元素间通信/协作方式（method call / events / messages 等）。

- 关键点：连接件不仅是线，带协议/语义。

1. **Topological Layout（拓扑布局）** — 元素如何排列连接形成结构（链式、星型、分层等）。
2. **Semantic Constraints（语义约束）** — 对拓扑/行为/交互施加的规则，用于保证模式性质。
3. **Layer Pattern（分层模式）** — 将模块组织成层并限制层间 **allowed-to-use** 单向依赖的模块模式。

- 关键点：模块只属于一层；allowed-to-use 不成环。
- 关键点：弱点：复杂度/性能损耗。

1. **Allowed-to-use Relation（允许使用关系）** — 定义上层可使用下层服务的单向依赖规则。

- 关键点：禁止循环依赖。

1. **Broker Pattern（代理/中介模式）** — 用 broker 作为中介实现 client 与 server 的位置透明/动态绑定的 C&C 模式。

- 关键点：常含 client-side proxy / server-side proxy 做编解码与通信细节。
- 关键点：弱点：延迟、瓶颈、单点故障、安全与测试风险。

1. **Proxy（代理）** — 代表一端与 broker 通信，负责 marshaling/sending/unmarshaling。
2. **MVC Pattern（Model-View-Controller）** — 将交互式系统分为 Model/View/Controller，通过通知机制协调状态变化以支持 UI 可变与多视图一致。

- 关键点：关系含 notifies；model 不应直接与 controller 交互。
- 关键点：弱点：对简单 UI 可能过度复杂；工具包不匹配。

1. **Model（MVC）** — 表示应用数据/状态（及其相关逻辑/接口）。
2. **View（MVC）** — 展示模型的一部分并与用户交互的 UI 组件。
3. **Controller（MVC）** — 在 Model 与 View 间中介，管理交互并将用户动作映射为状态变化与更新。
4. **Pipe-and-Filter Pattern（管道-过滤器）** — 用 filter 链对数据进行连续变换，filter 由 pipe 连接的数据流模式。

- 关键点：pipe 保序、不改变数据；单一源→单一目标。
- 关键点：约束：端口连接；数据类型一致。

1. **Filter（过滤器）** — 从输入端口读取数据并变换为输出端口写出的数据。
2. **Pipe（管道）** — 将一个 filter 输出端口的数据传给另一个 filter 输入端口；保序、不改数据。
3. **Client-Server Pattern（客户-服务器）** — client 通过 request/reply 调用 server 提供的共享服务以实现集中控制与复用的分布式模式。

- 关键点：弱点：服务器瓶颈/单点；功能划分决策难改。

1. **Request/Reply Connector（请求-应答连接件）** — 采用请求/应答协议的数据连接件；关键性质包括本地/远程、是否加密。
2. **Peer-to-Peer Pattern（P2P）** — peers 对等直接交互且不允许任何 peer 或其集合成为系统健康关键点的分布式模式。

- 关键点：attachments 可在运行时变化。
- 关键点：弱点：安全、一致性、可用性、备份恢复更复杂。

1. **SOA Pattern（Service-Oriented Architecture）** — providers 发布服务接口，consumers 在不了解实现细节下发现并调用服务以实现跨平台/跨组织互操作。

- 关键点：常含 ESB、registry、orchestration。
- 关键点：弱点：复杂、服务演化不可控、中间件性能开销/无性能保证。

1. **ESB（Enterprise Service Bus）** — SOA 中介，负责消息路由与转换。
2. **Registry of Services（服务注册表）** — 注册服务并支持运行时发现。
3. **Orchestration Server（编排服务器）** — 以业务流程/工作流语言协调多个服务交互。
4. **Publish-Subscribe Pattern（发布订阅）** — publisher announce 事件，subscriber subscribe 事件集合，事件分发器将事件派发给订阅者，实现身份解耦。

- 关键点：弱点：延迟、可预测性差、顺序/交付不保证。

1. **Shared-Data Pattern（共享数据/仓库）** — 多个 data accessors 围绕 shared-data store 读写持久数据实现协作的模式。

- 关键点：约束：accessor 只能与 store 交互。
- 关键点：弱点：瓶颈/单点；围绕数据模型紧耦合。

1. **Map-Reduce Pattern** — infrastructure + map + reduce 组成的大规模并行数据分析模式：infrastructure 负责部署、排序与故障恢复；map 做 extract/transform；reduce 做 load/汇总。

- 关键点：约束：文件集合；map 无状态且不互通；唯一通信是 <key,value>。

1. **Multi-Tier Pattern（多层级部署）** — 将执行/部署结构组织为多个 **tier**（组件的逻辑分组），用于分布式部署。

- 关键点：关系：is part of / communicates with / allocated to。
- 关键点：约束：组件只属于一个 tier。

1. **Tier（部署层/执行层）** — 运行时/部署视角下的组件逻辑分组（可映射到计算平台）。
2. **Tactic（战术）** — 比 pattern 更简单的设计手段，用于达成/增强特定质量属性目标。
3. **Patterns are built from tactics（模式由战术构成）** — pattern 像分子，tactic 像原子；模式通常可分解为多个战术组合。
4. **Tactics augment patterns（战术增强模式）** — 模式对真实系统描述不足，需要用战术补强模式弱点或达成额外质量属性。
5. **Tactic interactions（战术交互）** — 一个战术有 pluses 与 minuses；用新战术缓解副作用会引入新副作用，直到副作用可忽略为止。

------

# B. 10个对比题标准答案（完全应试写法）

1. **Pattern vs Tactic**

- Pattern 是在特定 context 下针对 recurring problem 的可复用 solution（成套决策包）；tactic 是更细粒度的质量属性手段。模式通常由多个战术组成，且真实系统往往需要用战术增强模式以满足具体质量目标。

1. **Layer vs Tier**

- Layer 是模块视角的分层与 allowed-to-use 依赖约束；Tier 是部署/执行视角的逻辑分组（组件归属、跨 tier 通信、映射到平台）。因此 layer 解决代码/职责分离与依赖控制，tier 解决部署划分与运行时资源隔离。

1. **Client-Server vs Peer-to-Peer**

- Client-Server 交互不对称，server 提供共享服务并可能成为瓶颈/单点；P2P peers 对等且设计目标是不让任何 peer 或其集合成为系统健康关键点，但安全、一致性、可用性与备份恢复治理更复杂。

1. **Client-Server vs SOA**

- Client-Server 多强调集中服务请求/应答；SOA 面向跨平台/跨组织互操作，以服务契约为核心，常引入 ESB/registry/orchestration 以及 SOAP/REST/消息连接件；SOA 构建与治理更复杂，服务演化不可控且中间件带来性能开销/缺乏性能保证。

1. **Broker vs Client-Server**

- 二者都可用于分布式服务调用；Broker 通过 broker 中介（及代理）实现位置透明与动态绑定，进一步降低 client 与 server 耦合，但引入额外间接导致延迟/瓶颈，且 broker 可能单点并带来安全与测试风险。

1. **Publish-Subscribe vs Client-Server**

- PubSub 通过事件分发解耦发布者与订阅者身份并支持动态加入退出，但通常增加延迟、交付时间可预测性差且顺序/交付不保证；Client-Server 便于集中控制与复用，但 server 易瓶颈/单点且功能划分难改。

1. **Publish-Subscribe vs Shared-Data**

- PubSub 以事件分发为中心，协作通过消息通知实现；Shared-Data 以持久数据存储为中心，协作通过读写共享数据实现。前者弱点偏向顺序/交付保证与延迟可预测性，后者弱点偏向 store 瓶颈/单点与数据模型耦合。

1. **Pipe-and-Filter vs Map-Reduce**

- Pipe&Filter 是通用的数据流变换链，pipe 负责保序传递且不改变数据；Map-Reduce 由 infrastructure 统一部署、排序/分组并故障恢复，开发者仅实现 map（extract/transform）与 reduce（load/汇总）。MR 依赖文件集合、map 无状态与 <key,value> 约束以实现大规模并行。

1. **MVC vs Layered**

- MVC 面向交互式系统，将 model/view/controller 分离并通过通知机制协调状态变化；Layered 面向模块分解，强调 allowed-to-use 单向依赖以控制变更传播。MVC 更强调运行时交互与 UI 可变，Layered 更强调职责分离与依赖纪律。

1. **Shared-Data vs Broker**

- Shared-Data 通过共享数据存储中介访问者协作，风险是 store 瓶颈/单点与 schema 耦合；Broker 通过 broker 中介转发请求实现位置透明与动态绑定，风险是 broker 延迟/瓶颈/单点与安全/测试复杂度。二者共同点是“中介化”，代价通常是性能与可用性治理压力。

------

# C. 6道简答题标准答案（完全卷面写法）

## 1) 什么是架构模式？一个模式的解决方案应包含哪些内容？

**答**：架构模式是在特定 context 下针对 recurring problem 的可复用 solution。该 solution 通常规定元素类型、交互连接机制、组件拓扑布局，并给出覆盖拓扑/行为/交互机制的语义约束，以保证方案可推理、可复用。

------

## 2) MVC 模式解决什么问题？其关键关系与约束是什么？

**答**：MVC 面向交互式系统中 UI 频繁变化与多视图一致性需求，将系统分为 model（数据/状态与相关逻辑）、view（展示与交互）、controller（中介并协调交互）。其关键关系为 notifies（状态变化通知）；约束包括至少存在 model/view/controller，且 model 不应直接与 controller 交互，以降低 UI 流程对业务核心的耦合。

------

## 3) Pipe-and-Filter 的元素、约束与主要优缺点是什么？

**答**：Pipe&Filter 由 filters 与 pipes 组成；filter 从输入端口读取数据并变换后写到输出端口，pipe 将一个 filter 的输出传递到另一个 filter 的输入并保持数据项顺序且不改变数据。约束是 pipe 连接输出端口到输入端口且相连 filters 对数据类型达成一致。优点是变换步骤可复用、可组合且可流水线并行；缺点常体现在数据转换/缓冲带来的性能与调试复杂度。

------

## 4) Client-Server 的主要弱点是什么？为什么“功能划分”难以更改？

**答**：Client-Server 的服务器可能成为性能瓶颈与单点故障；此外功能在客户端或服务器端的划分决策通常复杂且系统建成后变更代价高。原因是功能划分会固化接口形态、数据交互与部署假设，改变划分往往涉及系统范围的结构与协议调整。

------

## 5) SOA 的典型元素与主要风险是什么？

**答**：SOA 典型包含 service providers、service consumers、ESB、registry of services、orchestration server，并通过 SOAP/REST/异步消息等连接件实现互操作。主要风险包括：系统构建与治理复杂、独立服务演化不可控导致版本兼容风险，以及中间件带来性能开销、服务可能成瓶颈且通常缺乏性能保证。

------

## 6) 解释“模式与战术的关系”以及“战术交互为何会形成链式递归”。

**答**：模式由多个战术构成，模式提供结构骨架但对真实系统往往描述不足，需要通过战术增强以满足特定质量属性并缓解模式弱点。战术具有 pluses 与 minuses：引入战术 A 改善某质量属性会产生副作用，从而引入战术 B 缓解该副作用，但 B 又带来新的副作用，形成链式递归；当新增战术的副作用小到可忽略时，该增强过程停止。

