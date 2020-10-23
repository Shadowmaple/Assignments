-- 读者表
insert into user(`name`, `max_num`, `borrowing_num`)
values("小明",8,0), ("小红",8,0), ("小张",8,0);

-- 图书表
insert into book values
("b01","全球通史",null,"history","清华大学出版社",10,10),
("b02","MySQL知会必会",null,"IT","清华大学出版社",10,10),
("b03","英文演讲",null,"language","清华大学出版社",10,10);

-- 记录
insert into record(`user_id`, `book_id`, `borrow_time`, `reborrow_num`, `return_time`) values
(1, "b02", "2020-10-20 09:00:01", 0, null),
(2, "b02", "2020-10-20 17:02:01", 0, null),
(2, "b03", "2020-10-21 20:20:59", 0, null),
(3, "b03", "2018-10-21 20:20:59", 0, null);

-- update record set return_time = "2020-10-21 00:00:00" where user_id = 1 and book_id = "b02";

-- 借阅
call borrow_book("b01", 2);
call borrow_book("b03", 2);
select * from book;
select * from user;
select * from record;

-- 续借
call reborrow_book("b02", 2);

-- 归还
call return_book("b03", 3);
select * from fee_manage;

-- 查询指定读者借阅图书的情况
call user_book_pr("小明");
