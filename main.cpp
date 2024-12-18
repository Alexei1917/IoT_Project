#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}


/*

有限状态机（FSM，Finite State Machine）简介
有限状态机是一种数学模型，用于表示一个系统在特定时间内的状态和状态之间的转移规则。它由一组状态、转移条件和动作组成，常用于控制系统、协议解析、游戏开发、人工智能等领域。

核心概念
1. 状态 (State)
系统的某种特定状态。例如：

一个电梯可能处于“停止”或“运行”状态。
TCP 协议可能处于“LISTEN”、“ESTABLISHED”状态。
2. 事件 (Event)
触发状态转换的外部或内部条件。例如：

电梯的“按键请求”。
网络中收到数据包的信号。
3. 状态转移 (Transition)
从一个状态转换到另一个状态的过程，由特定事件触发。例如：

电梯从“停止”状态转换到“运行”状态。
TCP 连接从“LISTEN”状态转换到“ESTABLISHED”状态。
4. 动作 (Action)
在状态转换过程中执行的特定任务。例如：

电梯启动电机。
TCP 发送 SYN 包。
有限状态机的形式化描述
一个有限状态机可以表示为五元组：
FSM = {S, Σ, δ, s₀, F}

S：状态的集合，例如 {State1, State2, State3}。
Σ：事件（输入）的集合。
δ：状态转移函数，定义某状态在某事件下转移到哪一状态。
s₀：初始状态。
F：终止状态的集合。
有限状态机的分类
1. 确定性有限状态机（DFA, Deterministic Finite Automaton）
每个状态针对同一事件只能有一个明确的转移目标状态。
应用场景：正则表达式匹配、网络协议实现等。
2. 非确定性有限状态机（NFA, Nondeterministic Finite Automaton）
一个状态针对同一事件可以有多个转移目标状态。
应用场景：更灵活的系统设计，理论分析。
有限状态机的工作原理
运行流程
系统启动时处于初始状态 s₀。
外部事件（输入）触发状态转移函数 δ。
状态机根据当前状态和事件决定转移到哪个状态。
如果当前状态是终止状态 F 中的一个，状态机结束。
有限状态机的优点
逻辑清晰：状态机将复杂的逻辑拆解为多个状态，便于理解和维护。
易扩展性：新增状态或事件时，只需增加相关状态转移规则。
高效率：状态和事件的逻辑非常明确，执行高效。

*/
