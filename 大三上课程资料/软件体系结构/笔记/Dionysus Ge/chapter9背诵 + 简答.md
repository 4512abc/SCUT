# Chapter 9 Security

1. **攻击可以被刻画为对 CIA 的攻击**：对系统或其数据的 **Confidentiality / Integrity / Availability** 的攻击。Chapter 9
2. **因此安全战术大量围绕 CIA 展开**：你前面学的检测、访问控制、加密、隔离、审计等，本质都在支撑 CIA。Chapter 9
3. **Identify / Authenticate / Authorize 的作用**：它们的目的就是确定“哪些用户或系统有资格获得什么类型的访问”。Chapter 9
4. **关键结论（必背）**：**没有任何安全战术是万无一失的，系统会被攻破**；所以必须有战术来 **检测攻击、限制攻击扩散、并进行反应与恢复**。Chapter 9

> 这最后一句是本章卷面“高级感”的来源：
>  **Security ≠ 永不被攻破；Security = Detect + Resist + React + Recover（并且默认会被攻破）。**

------

## 一、Chapter 9 必背定义（28个，全部可直接默写）

### A. 核心概念

1. **Security（安全）**：系统在**仍提供授权访问**的前提下，保护数据与信息免受**未授权访问**的能力。
2. **Attack（攻击）**：对计算机系统采取的、意图造成伤害的行动；可表现为未授权访问/未授权修改/拒绝合法用户服务。
3. **Denial of Service, DoS（拒绝服务）**：攻击者试图使合法用户无法获得系统服务的攻击形式。

### B. CIA 三性 + 支撑属性

1. **CIA（安全三性）**：安全的三大特性：Confidentiality、Integrity、Availability。
2. **Confidentiality（机密性）**：数据或服务受到保护，不被未授权访问。
3. **Integrity（完整性）**：数据或服务不受未授权操纵/篡改。
4. **Availability（可用性）**：系统对合法使用保持可用，DoS不应阻止合法用户使用。
5. **Authentication（认证）**：验证交易双方身份，确认其确实是所声称的那一方。
6. **Authorization（授权）**：授予用户执行任务的权限/特权（决定其可访问、可修改什么）。
7. **Nonrepudiation（不可抵赖）**：发送方不能否认发送、接收方不能否认接收。

### C. 场景与审计

1. **Security (general) scenario（安全质量场景）**：用“刺激源-刺激-环境-工件-响应-响应度量”形式刻画安全需求（本章用该思路给出具体安全场景）。
2. **Audit trail（审计轨迹）**：系统维护可追溯记录，用于事后追踪与定位攻击行为（本章示例场景包含该要求）。
3. **Restore within a day（恢复时间要求）**：安全场景中的响应度量之一：要求在规定时间内恢复正确数据/服务（如“一天内恢复”）。

### D. 安全战术总框架（四类）

1. **Security tactics（安全战术）**：为实现安全目标而采取的架构设计决策集合；PPT将其组织为四类：Detect/Resist/React/Recover。
2. **Detect（检测）**：检测攻击是否发生/是否可疑。
3. **Resist（抵抗）**：在攻击发生前或发生时阻止/降低攻击成功概率。
4. **React（反应）**：检测到或怀疑攻击后进行止损措施（撤权、锁定、通知）。
5. **Recover（恢复）**：攻击或资源失败后恢复正确状态/服务，并保留可追溯证据。

### E. Detect 类战术（4个）

1. **Detect Intrusion（入侵检测）**：将系统内网络流量/服务请求模式与数据库中的恶意行为签名/已知模式进行比对。
2. **Detect Service Denial（DoS检测）**：将进入系统的流量模式/签名与已知DoS历史画像进行比对。
3. **Verify Message Integrity（消息完整性验证）**：用校验和/哈希等验证消息、资源文件、部署文件、配置文件的完整性。
4. **Detect Message Delay（消息延迟检测）**：检查消息交付耗时，以发现可疑的时间行为。

### F. Resist 类战术（8个）

1. **Identify Actors（识别行为体）**：识别所有外部输入的来源。
2. **Authenticate Actors（认证行为体）**：确保actor（用户/远程计算机）确实是其声称的对象。
3. **Authorize Actors（授权行为体）**：确保已认证actor有权访问/修改数据或服务。
4. **Limit Access（限制访问）**：限制对资源（内存、网络连接、访问点等）的访问。
5. **Limit Exposure（减少暴露面）**：通过尽可能少的访问点最小化系统攻击面（attack surface）。
6. **Encrypt Data（加密数据）**：对数据以及通信应用某种形式的加密。
7. **Separate Entities（隔离实体）**：通过不同服务器/不同网络、虚拟机，甚至“air gap（物理隔绝）”实现隔离。
8. **Change Default Settings（修改默认设置）**：强制用户更改默认分配的设置。

### G. React / Recover 类战术

1. **Revoke Access（撤销访问）**：一旦怀疑攻击，即使对通常合法的用户/用途，也要限制其对敏感资源的访问。
2. **Lock Computer（锁定资源）**：若出现重复失败访问尝试，则限制对该资源的访问。
3. **Inform Actors（通知相关方）**：怀疑或检测到攻击时，通知运维人员、其他人员或协作系统。
4. **Audit（审计）**：记录用户与系统动作及其影响，用于追踪行为并识别攻击者。
5. **Foolproof（万无一失）**：PPT结论：没有任何安全战术是万无一失的，系统终将被攻破，因此必须具备检测、限制扩散、反应与恢复。

> 你背这句就够“高级”：**No security tactic is foolproof; systems will be compromised; hence tactics exist to detect, limit spread, react, and recover.**

------

## 二、10个对比题：标准答案（按点写，直接得分）

### 1) Confidentiality vs Integrity vs Availability

- 机密性防“未授权访问”；完整性防“未授权篡改”；可用性防“合法用户用不了”（如DoS）。

### 2) Authentication vs Authorization

- 认证回答“你是谁/是不是你”；授权回答“你能做什么/能访问和修改什么”。

### 3) Attack vs Security

- 攻击是意图造成伤害的行动（未授权访问/修改/拒绝服务）；安全是系统在仍提供授权访问前提下抵御未授权访问的能力。

### 4) Detect vs Resist

- Detect：发现攻击（入侵/DoS/完整性破坏/延迟异常）；Resist：通过识别-认证-授权-限制访问/暴露、加密、隔离、改默认等降低攻击成功概率。

### 5) React vs Recover

- React：攻击被怀疑/检测到后立即止损（撤权、锁定、通知）；Recover：恢复正确服务/数据并保留审计以追溯与识别攻击者。

### 6) Detect Intrusion vs Detect Service Denial

- 入侵检测：请求/流量与恶意行为签名库比对；DoS检测：进入流量模式与已知DoS历史画像比对。

### 7) Verify Message Integrity vs Encrypt Data

- 完整性验证：用checksum/hash确认消息/配置/部署等未被篡改（对准Integrity）；加密：保护数据及通信不被未授权获取（对准Confidentiality）。

### 8) Limit Access vs Limit Exposure

- Limit Access：限制对资源（内存、连接、访问点等）的访问；Limit Exposure：减少访问点数量以最小化攻击面。

### 9) Separate Entities vs Change Default Settings

- 隔离实体：通过物理/网络/虚拟机/air gap形成安全边界限制扩散；改默认：强制更改默认配置以避免默认设置被利用。

### 10) Nonrepudiation vs Audit

- 不可抵赖：保证“发了/收了”事后不能否认；审计：记录用户与系统动作及影响，用于追踪与识别攻击者。

------

## 三、6道简答题：标准答案（完全应试写法）

### 1）简答：什么是安全？什么是攻击？

**答：**安全是系统保护数据与信息免受未授权访问、同时仍向授权人员与系统提供访问的能力。攻击是意图对系统造成伤害的行动，可表现为未授权访问数据或服务、未授权修改数据，或拒绝向合法用户提供服务（DoS）。

### 2）简答：安全的 CIA 三性分别是什么？各自防什么？

**答：**机密性（Confidentiality）防止未授权访问；完整性（Integrity）防止未授权操纵/篡改；可用性（Availability）保证合法使用可用，DoS不应阻止合法用户使用。

### 3）简答：安全战术为什么分 Detect / Resist / React / Recover？分别解决什么问题？

**答：**类比物理安全，可将战术归为四类：Detect用于发现攻击；Resist用于降低攻击成功概率（访问控制、减少攻击面、加密、隔离、改默认等）；React用于攻击被怀疑/检测到后止损（撤权、锁定、通知）；Recover用于恢复正确服务/数据并通过审计追溯与识别攻击者。

### 4）简答：列举并解释 4 个 Detect Attacks 战术。

**答：**(1) 入侵检测：将流量/请求模式与恶意签名库比对；(2) DoS检测：将进入流量与已知DoS画像比对；(3) 消息完整性验证：用checksum/hash验证消息、配置、部署等未被篡改；(4) 消息延迟检测：监测消息交付时间以发现可疑时间行为。

### 5）简答：列举并解释 6 个 Resist Attacks 战术。

**答：**(1) 识别行为体；(2) 认证行为体；(3) 授权行为体；(4) 限制访问资源（内存、连接、访问点等）；(5) 减少暴露面（最小化攻击面）；(6) 对数据与通信加密；也可通过隔离实体（含air gap）与修改默认设置进一步降低攻击成功概率。

### 6）简答：为什么说“没有安全战术是万无一失的”？系统应如何应对“终将被攻破”？

**答：**PPT指出没有任何安全战术是万无一失的，系统最终会被攻破；因此必须具备检测攻击、限制攻击扩散，并在攻击发生后采取反应与恢复措施（包括撤权/锁定/通知以及审计与恢复）。

------

