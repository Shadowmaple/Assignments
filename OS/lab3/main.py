""" 分区式存储管理算法实现 """


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
        print("开始 {} 大小 {}".format(self.addr, self.size))

    # 分配
    def allocate(self, size: int):
        self.addr += size
        self.size -= size


# 首次适应算法
def first_match(area, requests):
    for request in requests:
        area.sort(key=lambda x: x.addr)
        # print([x.addr for x in area])
        flag = False
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

    print("剩余空间：")
    for block in area:
        block.show()


# 最佳适应算法
def best_match(area, requests):
    for request in requests:
        # 按分区大小升序排列
        area.sort(key=lambda x: x.size)
        flag = False
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

    print("剩余空间：")
    area.sort(key=lambda x: x.addr)
    for block in area:
        block.show()


# 最坏适应算法
def worst_match(area, requests):
    for request in requests:
        # 按分区大小降序排列
        area.sort(key=lambda x: x.size, reverse=True)
        flag = False
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

    print("剩余空间：")
    area.sort(key=lambda x: x.addr)
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

    # first_match(blocks, requests)
    # best_match(blocks, requests)
    worst_match(blocks, requests)


"""
3
0 300
350 200
700 112
4
150
200
90
80
"""
