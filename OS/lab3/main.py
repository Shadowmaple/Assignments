""" 分区式存储管理算法实现 """

import copy


# 分区
class Block:
    addr = 0  # 开始地址
    size = 0  # 大小

    def __init__(self, addr: int, size: int) -> None:
        self.addr = addr
        self.size = size

    def __repr__(self) -> str:
        print("addr={}, size={}".format(self.addr, self.size))

    def show(self):
        print("开始地址 = {}，size = {}".format(self.addr, self.size))

    # 分配
    def allocate(self, size: int):
        self.addr += size
        self.size -= size


def allocate(area, requests, sort_key=None, sort_reverse=False):
    """ 分配 """

    for request in requests:
        area.sort(key=sort_key, reverse=sort_reverse)
        flag = False

        # 查找可分配的分区
        for block in area:
            if block.size < request:
                continue
            # 分配
            area.remove(block)
            if block.size > request:
                block.allocate(request)
                area.append(block)
            flag = True
            break

        if flag:
            print("分配 {} 成功".format(request))
        else:
            print("分配 {} 失败".format(request))


def first_match(area, requests):
    """ 首次适应算法 """

    print("\n********** 首次适应算法 ********** ")
    area = copy.deepcopy(area)

    # 分配
    # 关键字为地址升序序列
    allocate(area, requests, lambda x: x.addr)

    display_free_space(area)


def best_match(area, requests):
    """ 最佳适应算法 """

    print("\n********** 最佳适应算法 ********** ")
    area = copy.deepcopy(area)

    # 分配
    # 关键字按页面大小升序排列
    allocate(area, requests, lambda x: x.size)

    display_free_space(area)


def worst_match(area, requests):
    """ 最坏适应算法 """

    print("\n********** 最坏适应算法 ********** ")
    area = copy.deepcopy(area)

    # 分配
    # 关键字按页面大小降序排列
    allocate(area, requests, lambda x: x.size, True)

    display_free_space(area)


def display_free_space(area: list):
    """ 显示剩余空间 """
    area.sort(key=lambda x: x.addr)
    print("剩余空间：")
    for block in area:
        block.show()


if __name__ == "__main__":
    blocks = []
    n = int(input())
    addr = size = 0
    for i in range(n):
        addr, size = input().split()
        blocks.append(Block(int(addr), int(size)))

    requests = []
    n = int(input())
    for i in range(n):
        size = int(input())
        requests.append(size)

    first_match(blocks, requests)
    best_match(blocks, requests)
    worst_match(blocks, requests)


"""
测试用例：
3
0 300
350 200
700 162
4
200
150
90
80
"""
