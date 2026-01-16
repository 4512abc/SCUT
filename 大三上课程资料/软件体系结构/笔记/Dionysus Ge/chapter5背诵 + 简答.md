# 第5章（Availability）

“可用性关注故障发生时系统仍能被使用：故障需被识别/预防并触发响应，响应强度随业务关键性与故障类型而变。为了把可用性 tactics 落到架构上，可用性设计应沿7类设计决策逐项检查：职责分配、协调模型、数据模型、映射关系、资源管理、绑定时间与技术选型；其中协调模型贯穿检测、恢复与预防全过程。”

------

## 一、必背定义（≥15个）

1. **Availability（可用性）**：软件在需要时“在那里并准备好执行任务”的性质；在此广义视角下包含通常所说的 reliability。
2. **Reliability（可靠性）**：系统持续交付符合规格服务的能力；可用性在可靠性基础上加入“恢复/修复”。
3. **Recovery / Repair（恢复/修复）**：故障发生后采取措施使系统重新达到可提供服务的状态（可用性区别于仅讨论可靠性的关键点）。
4. **Service outage time（服务中断时间）**：服务不可用的时间；可用性的根本目标是通过缓解 faults 来最小化 outage time。
5. **Failure（失效）**：系统不再交付与其规格一致的服务；该失效对系统参与者可观察。
6. **Fault（故障/缺陷）**：单个或组合 fault 具有导致 failure 的潜力。
7. **Availability tactics（可用性战术）**：使系统“能经受 faults”从而让服务仍符合规格；把 faults 阻止为 failures，或至少限制影响并使 repair 变得可能。
8. **Detect faults（故障检测类战术）**：通过检测系统各组件的“signs of life（生命迹象）”来识别故障。
9. **Ping/Echo**：节点间异步请求/响应消息对，用于判断可达性及网络路径往返时延。
10. **Monitor（监控器）**：监控系统其它部分健康状态的组件；可检测网络或共享资源故障/拥塞等。
11. **Heartbeat（心跳）**：系统监控器与被监控进程之间周期性消息交换。
12. **Timestamp（时间戳检测）**：用于检测事件序列错误，主要用于分布式消息传递系统。
13. **Sanity checking（合理性检查）**：基于内部设计/系统状态/信息性质，检查组件操作或输出的有效性/合理性。
14. **Condition monitoring（条件监测）**：检查进程/设备条件，或验证设计时的假设。
15. **Voting（投票）**：检查复制组件是否产生相同结果；变体包括 replication、functional redundancy、analytic redundancy。
16. **Exception detection（异常检测）**：检测会改变正常执行流的系统条件，如 system exception、parameter fence、parameter typing、timeout。
17. **Self-test（自检）**：组件执行自检过程以验证其正确运行。
18. **Recover from faults（故障恢复类战术）**：通过重试操作或维持冗余数据/计算等方式恢复服务。
19. **Protection group（保护组）**：一组节点，一个或多个为 active，其余为冗余 spare。
20. **Active redundancy / Hot spare（主动冗余/热备）**：保护组所有节点并行接收并处理相同输入，使备用保持与 active 同步状态。
21. **Passive redundancy / Warm spare（被动冗余/温备）**：仅 active 处理输入；其职责之一是定期向备用发送状态更新。
22. **Cold spare（冷备）**：备用平时不在役；发生 fail-over 后启动 power-on-reset 再投入服务。
23. **Exception handling（异常处理）**：报告或处理异常；可通过纠正原因并重试来掩蔽 fault。
24. **Rollback（回滚）**：回到先前已知良好状态。
25. **Rollback line（回滚线）**：回滚所恢复到的“已知良好状态”参考线。
26. **Software upgrade / In-service upgrade（在线升级）**：以不影响服务的方式对可执行代码镜像进行在役升级。
27. **Retry（重试）**：当 failure 为瞬时（transient）时，重试可能成功。
28. **Ignore faulty behavior（忽略错误行为）**：当判定某来源消息为伪造/异常时，忽略其发送消息。
29. **Degradation（降级）**：在组件失效时维持最关键功能，丢弃不关键功能。
30. **Reconfiguration（重配置）**：将责任重新分配给仍在运行的资源，尽可能保持功能。
31. **Reintroduction（再引入）**：先前失败或在线升级后的组件重新回到 active 角色的策略集合。
32. **Shadow（影子运行）**：组件以 shadow mode 运行预定义时间后再恢复 active 角色。
33. **State resynchronization（状态重同步）**：配合热备/温备，将状态信息从 active 发送到 standby。
34. **Escalating restart（分级重启）**：通过改变重启粒度来恢复故障，并最小化受影响服务范围。
35. **Non-stop forwarding（不停转发）**：监督面与数据面分离；监督失效时仍按已知路由转发，之后恢复并校验协议信息。
36. **Prevent faults（故障预防类战术）**：通过移除元素出役或限制故障范围等手段避免/抑制 faults。
37. **Removal from service（出役）**：临时将组件置为 out-of-service 以缓解潜在系统失效。
38. **Transactions（事务）**：将分布式异步消息下的状态更新打包，保证 atomic、consistent、isolated、durable。
39. **Predictive model（预测模型）**：监控进程健康，确保在标称参数内运行；发现预示未来 faults 的条件则采取纠正动作。
40. **Exception prevention（异常预防）**：通过掩蔽 fault 或用 smart pointers/ADT/wrappers 等防止系统异常发生。
41. **Increase competence set（扩大能力集合）**：将更多情况（包括 faults）纳入组件正常处理范围。
42. **Availability summary 句（总结性定义）**：可用性=故障发生时系统仍可用；fault 必须被识别（或被预防）并触发响应，响应从“忽略”到“像没发生一样继续运行”。
43. **Coordination model（协调模型）**：可用性三类 tactics 都涉及协调模型。

> 若你想把“Design Checklist 的7类设计决策”也当作本章背诵骨架：Allocation of responsibilities / Coordination model / Data model / Management of resources / Mapping among architectural elements / Binding time / Choice of technology。

------

## 二、10个对比题标准答案（应试写法）

1. **Fault vs Failure**

- Fault：具有导致 failure 的潜力（原因/缺陷）。
- Failure：系统不再交付与规格一致的服务，且对参与者可观察（结果/现象）。

1. **Reliability vs Availability**

- Reliability：关注持续正确提供服务（不出错）。
- Availability：在可靠性基础上加入 recovery/repair，并以最小化 outage time 为核心（出错也能恢复、尽快可用）。

1. **Detect faults vs Prevent faults**

- Detect：通过“生命迹象”等机制识别故障。
- Prevent：通过出役或限制故障范围等方式避免/抑制 faults。

1. **Ping/Echo vs Heartbeat**

- Ping/Echo：异步请求/响应对，用于可达性与RTT检测。
- Heartbeat：监控器与被监控进程周期性交换消息，用于持续健康探测。

1. **Monitor vs Heartbeat**

- Monitor：负责监控健康状态的“组件”（主体）。
- Heartbeat：监控过程中使用的“周期性交换机制”（手段）。

1. **Voting vs Sanity checking**

- Voting：基于冗余副本输出一致性检查（复制/功能/解析冗余）。
- Sanity checking：基于内部设计/状态/信息性质判断输出是否合理。

1. **Active redundancy (Hot spare) vs Passive redundancy (Warm spare)**

- Hot：所有节点并行处理相同输入，备用保持同步状态，切换快、资源成本高。
- Warm：仅 active 处理，定期向备用同步状态，成本较低、切换较慢。

1. **Warm spare vs Cold spare**

- Warm：备用平时接收周期性状态更新。
- Cold：备用平时不在役，故障后才 power-on-reset 再上线，恢复更慢但省资源。

1. **Retry vs Rollback**

- Retry：针对 transient failure，重试操作争取成功。
- Rollback：回到“已知良好状态（rollback line）”消除错误状态影响。

1. **Degradation vs Reconfiguration**

- Degradation：保关键功能、丢次要功能（功能取舍）。
- Reconfiguration：将责任重新分配给仍可用资源，尽量维持原功能集合（结构/责任重分配）。

------

## 三、6道简答题标准答案（完全应试写法）

### 1）什么是可用性？与可靠性有什么关系？

**标准答案：**
可用性指系统在需要时可用，尤其是在故障发生时仍能被使用；它包含通常所说的可靠性，并在可靠性基础上加入恢复/修复的概念，从而通过缓解 faults 来最小化服务中断时间。

### ==2）解释 fault、failure，并说明可用性战术的目标。==

**标准答案：**
Failure 是系统不再交付与规格一致的服务且可被参与者观察；Fault 是具有导致 failure 潜力的原因或缺陷。可用性战术的目标是让系统经受 faults，使服务保持符合规格：阻止 faults 演变为 failures，或至少限制其影响并使修复成为可能。

### 3）可用性 tactics 如何分类？每类写2个例子。

**标准答案：**
可用性 tactics 分为：Detect faults、Recover from faults、Prevent faults。检测类依赖生命迹象探测（如 ping/echo、heartbeat、monitor、自检等）；恢复类通过重试或冗余/重配置等恢复服务（如 retry、rollback、热/温/冷备、degradation、reconfiguration 等）；预防类通过出役或限制故障范围等（如 removal from service、transactions、predictive model、exception prevention 等）。

### ==4）简述保护组与热/温/冷备的区别，并说明它们解决的可用性问题。==

**标准答案：**
保护组是一组节点，一个或多个为 active，其余为冗余 spare。热备为并行处理相同输入并保持同步状态；温备仅 active 处理并向备用周期性同步状态；冷备平时不在役，fail-over 后执行 power-on-reset 再上线。它们通过冗余与切换机制在资源故障时保持/恢复服务，减少中断时间。

### ==5）为什么需要“再引入（reintroduction）”？列举两种再引入战术并解释。==

**标准答案：**
组件修复或在线升级后直接恢复 active 可能带来状态不一致或再次触发故障，因此需要再引入策略以降低风险。Shadow 让组件先以影子模式运行一段时间再转正；State resynchronization 将 active 状态同步给 standby/修复后组件；（也可用 escalating restart 或 non-stop forwarding 以缩小影响面）。

### ==6）写出三种“预防类”可用性战术，并各用一句说明其作用。==

**标准答案：**
Removal from service：将潜在故障组件临时出役以缓解未来失效。
Transactions：对分布式异步状态更新进行事务化打包，保证原子性/一致性/隔离性/持久性。
Predictive model：监控健康状态并在发现故障前兆时采取纠正措施；（也可写 exception prevention / increase competence set）。

