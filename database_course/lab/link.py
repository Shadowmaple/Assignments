import pymysql

insert_sql = "INSERT INTO `account` (`name`, `num`) VALUES (%s, %s)"
select_sql = "select * from account"

# 数据库连接
conn = pymysql.connect(
    host = "localhost",
    user = "root",
    password = "root",
    database = "firstdb",
    charset = "utf8mb4"
)

cursor = conn.cursor()

# 查询
print("-- 查询 --")
cursor.execute(select_sql)
result = cursor.fetchall()
print(result)

# 插入数据
print("-- 插入数据：'王安石', 200")
cursor.execute(insert_sql, ('王安石', 200))
conn.commit()

# 查询
print("-- 查询 --")
cursor.execute(select_sql)
result = cursor.fetchall()
print(result)

cursor.close()
conn.close()
