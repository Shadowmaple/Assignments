""" 页面调度算法的模拟实现 """

# 内存块数
block_num = 3

def FIFO(pages):
    print("\n********* FIFO *********")
    blocks = []
    count = 0 # 缺页次数
    for page in pages:
        # 页命中
        if page in blocks:
            continue

        # 缺页
        count += 1
        # 内存块已满，需淘汰页
        # 移除第一个
        if len(blocks) >= block_num:
            print("淘汰页号：" + blocks[0])
            blocks = blocks[1:]
        blocks.append(page)

    print("缺页次数={}，缺页率={:.2f}".format(count, count/len(pages)))


def LRU(pages):
    """
    最近最少使用调度算法
    """
    print("\n********* LRU *********")
    blocks = []
    count = 0
    for page in pages:
        # 页命中
        if page in blocks:
            # 将该页面放到最后
            blocks.remove(page)
            blocks.append(page)
            continue

        # 缺页
        count += 1
        # 内存块已满，需淘汰页
        # 移除第一个
        if len(blocks) >= block_num:
            print("淘汰页号：" + blocks[0])
            blocks = blocks[1:]
        blocks.append(page)

    print("缺页次数={}，缺页率={:.2f}".format(count, count/len(pages)))


if __name__ == '__main__':
    # 获取待转入的页面序列
    pages = input().split()

    FIFO(pages)
    LRU(pages)


"""
测试用例：
1 2 3 4 1 2 5 1 2 3 4 5
"""
