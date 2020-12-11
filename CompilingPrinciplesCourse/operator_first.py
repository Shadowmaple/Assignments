# coding:utf-8

""" 算符优先分析法 """

# 设定结束符号
ENDING = '$'

class Oper_First:
    grammar = []
    def __init__(self, input_str="", input_grammar=""):
        self.scanf_process(input_str, input_grammar)

    def scanf_process(self, input_str="", input_grammars=""):
        # 测试样例文法
        if input_grammars:
            grammar = input_grammars.split('\n')
            for index, g in enumerate(grammar):
                grammar[index] = g.split("->")
            if grammar[0][1][0] != ENDING:
                t = ['S']
                t.append(ENDING + str(grammar[0][0][0]) + ENDING)

                grammar.insert(0, t)
            # print(grammar)
            self.grammar = grammar
        else:
            self.grammar = [["S", "$E$"],
                            ["E", "E+T"],
                            ["E", "T"],
                            ["T", "T*F"],
                            ["T", "F"],
                            ["F", "(E)"],
                            ["F", "i"]]
        if input_str:
            self.input_str = input_str + ENDING
        else:
            self.input_str = "i+i" + ENDING

    def get_states(self):
        """ 返回所有文法串最左边的非终结符 """
        result = []
        for i in self.grammar:
            if i[0] not in result:
                result.append(i[0])
        return result

    def get_firstvt(self):
        """ 获取 FIRSTVT 集合 """
        states = self.get_states()
        # 初始化 FIRSTVT 表
        firstvt_table = {i:[] for i in states}
        for i in states:
            result = self.get_first_recursion(i)
            firstvt_table[i] = result
        return firstvt_table


    def get_first_recursion(self, target):
        """
        求目标非终结符的 First 集合
        P->a...或者P->Qa...
        """

        result = []
        for g in self.grammar:
            # 当前要推导的符号和式子相同
            if g[0] != target:
                continue

            # 判断是否为终结符号
            # P->a...
            if g[1][0].islower() or not g[1][0].isalpha():
                if g[1][0] not in result:
                    result.append(g[1][0])
            else:
                # P->Qa...
                # 若为非终结符号,进行递归查询
                # 若非终结符号为自身，则不进行递归查询
                if target != g[1][0]:
                    temp = self.get_first_recursion(g[1][0])
                    for i in temp:
                        if i not in result:
                            result.extend(i)
                # 若后续有终结符号，则也加入
                if len(g[1]) >= 2 and (g[1][1].islower() or not g[1][1].isalpha()):
                    if g[1][1] not in result:
                        result.append(g[1][1])
        return result

    def get_lastvt(self):
        """ 获取 LASTVT 集合 """

        states = self.get_states()
        lastvt_table = {i: [] for i in states}
        for i in states:
            result = self.get_last_recursion(i)
            lastvt_table[i] = result
        return lastvt_table

    def get_last_recursion(self, target):
        """
        求某非终结符的 LASTVT 集合
        P->...a或者P->...aQ
        """
        result = []
        for g in self.grammar:
            # 当前要推导的符号和式子相同
            if g[0] != target:
                continue
            # 判断是否为终结符号
            # P->...a
            if g[1][-1].islower() or not g[1][-1].isalpha():
                for i in g[1][-1]:
                    if i not in result:
                        result.extend(i)
            else:
                # P->...aQ
                # 若为非终结符号
                # 若非终结符号为自身，则不进行递归查询
                if target != g[1][-1]:
                    temp = self.get_last_recursion(g[1][-1])
                    for i in temp:
                        if i not in result:
                            result.extend(i)
                # 若后续有终结符号，则也加入
                if len(g[1]) >= 2 and (g[1][-2].islower() or g[1][-2].isalpha() == False):
                        if g[1][-2] not in result:
                            result.extend(g[1][-2])
        return result

    # 得到 firstvt、lastvt 所有终极符
    def get_terminal_states(self, firstvt, lastvt):
        state = []
        for i in firstvt.values():
            state += i
        for i in lastvt.values():
            state += i
        state = list(set(state))
        return state

    # 确定符号的位置
    def get_x_y(self, c_x, c_y, state):
        # 得到行坐标
        x, y = -1, -1
        for i in range(len(state)):
            if c_x == state[i]:
                x = i
        for i in range(len(state)):
            if c_y == state[i]:
                y = i
        return x, y

    def get_priority_table(self, firstvt, lastvt):
        """ 获取优先关系表 """

        # 标记该文法是否符合算法优先文法任一终结符号之间至多只有一种关系
        is_flag = True
        state = self.get_terminal_states(firstvt, lastvt)
        # 初始化预测分析表
        table = [["0" for col in range(len(state))] for row in range(len(state))]

        # 寻找 '=' 关系
        # P->...ab...或者P->...aQb...
        for g in self.grammar:
            # 得到该文法语句长度
            length = len(g[1])
            for i in range(len(g[1])):
                if i + 2 > length - 1:
                    break
                if (g[1][i] == g[1][i + 2] and g[1][i] == ENDING) or (g[1][i] == "(" and g[1][i + 2] == ")"):
                    x, y = self.get_x_y(g[1][i], g[1][i + 2], state)
                    if table[x][y] != "0":
                        is_flag = False
                    table[x][y] = "="
        # 寻找 '<' 关系
        # P->...aR...而R->b...或R->Qb...
        for g in self.grammar:
            # 得到该文法的长度
            length = len(g[1])
            for i in range(len(g[1])):
                # 若出现数字越界，跳出
                if i + 1 > length - 1:
                    break
                # 如果该符号是终结符号且下一位是非终结符号(右左)
                if g[1][i] in state and g[1][i + 1] not in state:
                    # 取出FIRSTVT的元素，对关系表进行修改
                    temp = firstvt[g[1][i + 1]]
                    for t in temp:
                        x, y = self.get_x_y(t, g[1][i], state)
                        if table[y][x] != "0":
                            is_flag = False
                        table[y][x] = "<"
        # 寻找 '>' 关系
        # P->...Rb...而R->...a或R->...aQ
        for g in self.grammar:
            # 得到该文法的长度
            length = len(g[1])
            for i in range(len(g[1])):
                # 若出现数字越界，跳出
                if i + 1 > length - 1:
                    break
                # 如果该符号是终结符号且下一位是非终结符号
                if g[1][i] not in state and g[1][i + 1] in state:

                    # 取出LASTVT的元素，对关系表进行修改
                    temp = lastvt[g[1][i]]
                    for t in temp:
                        x, y = self.get_x_y(t, g[1][i + 1], state)
                        if table[x][y] != "0":
                            is_flag = False
                        table[x][y] = ">"

        return table, state, is_flag

    def analysis_operator(self, table, state):
        """ 使用算符优先表分析输入串 """

        # 初始化分析S栈
        analyse_stack = []
        # 输入串栈
        input_stack = []
        # 对栈初始化，入栈
        analyse_stack.append(ENDING)
        input_stack.extend(list(reversed((self.input_str))))

        print("|{:^}|{:^9}|{:^4}|{:^4}|{:^7}|{:^6}|".format("步骤", "S栈", "优先关系", "当前符号", "输入流", "动作"))

        # 步骤
        step_count = 1
        # 获取输入串比较的当前符号
        cur_sign = input_stack[-1]
        input_stack.pop()

        while True:
            # 充当指针，指向当前栈内参与比较的元素，默认是栈顶
            indicator = len(analyse_stack) - 1
            # 如果为非终结符号，向栈底读取字符，直到读取到非终结字符
            while analyse_stack[indicator].isupper():
                indicator -= 1

            x, y = self.get_x_y(analyse_stack[indicator], cur_sign, state)
            relationship = table[x][y]

            # 判断进行的动作
            action = ""
            if (relationship == "<" or relationship == "=") and cur_sign != ENDING:
                action = "移进"
            elif relationship == ">":
                action = "归约"
            else:
                action = "结束"

            # 存入优先关系，当前符号和输入流
            cur_stack = "".join(analyse_stack)
            cur_input = "".join(list((reversed("".join(input_stack)))))

            # 输出 step
            print("|{:^4}|{:<10}|{:^8}|{:^8}|{:>10}|{:^6}|".format(
                    step_count, cur_stack, relationship, cur_sign, cur_input, action))

            # 如果运算栈内只剩下非终结符号一个，并且输入栈无符号，则归约成功
            if len(analyse_stack) == 2 and cur_sign == ENDING:
                break

            step_count += 1

            # 执行移入操作
            if action == "移进":
                analyse_stack.append(cur_sign)
                # 获取输入串比较的当前符号
                cur_sign = input_stack[-1]
                input_stack.pop()
            # 执行归约操作
            elif action == "归约":
                # 如果归约符号位于栈顶，则只将栈顶的非终结符号进行归约
                if indicator == len(analyse_stack) - 1:
                    analyse_stack.pop()
                    analyse_stack.append("N")
                # 如果不位于栈顶，则将运算符左右两边的符号一起进行归约
                else:
                    analyse_stack.pop()
                    analyse_stack.pop()
                    analyse_stack.pop()
                    analyse_stack.append("N")

        print('-'*56)

    def run(self):
        """ 运行 """

        print("进行构造的文法G[S]")
        for i in self.grammar:
            print("%s -> %s" % (i[0], i[1]))
        print('-'*50, end="\n\n")

        # 得到FIRSTVT集合
        firstvt = self.get_firstvt()
        print("FIRSTVT 集合:")
        for key, value in firstvt.items():
            print("FIRSTVT(%s) = {%s}" % (key, str(value)[1:-1]))
        print('-'*50, end="\n\n")

        # 得到LASTVT集合
        lastvt = self.get_lastvt()
        print("LASTVT 集合:")
        for key, value in lastvt.items():
            print("LASTVT(%s) = {%s}" % (key, str(value)[1:-1]))
        print('-'*50, end="\n\n")

        # 得到算符优先关系表
        table, states, valid = self.get_priority_table(firstvt, lastvt)
        if not valid:
            print("该文法不属于算符优先文法")
            return

        # 打印算符优先关系表
        print("%27s" % ("算符优先关系表") + '\n' + '-'*50)
        print("|" + " "*6, end="")
        for i in states:
            print("{:^7}".format(i), end="")
        print()
        for i in range(len(table)):
            print("|{:^6}|".format(states[i]), end="")
            # print("%7s" % table[i][0], end="")
            for x in table[i]:
                print("{:^6}|".format(x), end="")
            print("")
        print('-'*50 , end="\n\n")

        # 对输入串进行算符分析
        print("对输入串 %s 进行归约：" % (self.input_str) + '\n' + '-'*56)
        self.analysis_operator(table, states)


if __name__ == '__main__':
    op_frist = Oper_First("", "")
    op_frist.run()
