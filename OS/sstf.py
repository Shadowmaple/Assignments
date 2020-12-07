r = [86, 147, 91, 177, 94, 150, 102, 175, 130]
now = 143
count = 0

def getRecent():
    num = r[0]
    for i in range(1, len(r)):
        if abs(r[i]-now) < abs(num-now):
            num = r[i]
    r.remove(num)
    return num

while len(r) != 0:
    num = getRecent()
    print(num)
    count += abs(now-num)
    now = num

print("移动磁道数：", count)

