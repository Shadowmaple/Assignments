create database `library` if not exists;

use `library`;

create table `book` (
    `id` varchar(30) comment '书号',
    `name` varchar(255),
    `detail` text,
    `kind` varchar(20) comment '类别',
    `publish` varchar(100) comment '出版社',
    `total` int default 0 comment '总数量',
    `num` int default 0 comment '在册数量',
    primary key (`id`)
);

create table `user` (
    `id` int unsigned auto_increment,
    `name` varchar(10),
    primary key (`id`)
);

-- 图书借阅记录
-- 若当前时间超过应当归还时间，即超期，需加罚金
-- 罚金的计算通过归还时间和需归还时间计算
create table `record` (
    `id` int unsigned auto_increment,
    `borrow_time` datetime comment '借阅时间',
    `must_return_time` datetime comment '需要归还时间',
    `reborrow_num` int default 0 comment '续借次数',
    `return_time` datetime(1) comment '归还时间',
    `has_paied` tinyint(1) default 0 comment '是否交了罚金',

    `user_id` int unsigned,
    `book_id` varchar(30),
    primary key (`id`),
    foreign key (`user_id`) references `user`(`id`),
    foreign key (`book_id`) references `book`(`id`)
);

-- 触发器，分别实现借书和还书时自动更新图书信息的在册数量
-- 借书时更新在册数量
delimiter /
create trigger t1 after insert
on `record` for each row
begin
    update `book` set `num` = `num` - 1
    where `id` = new.book_id;
end;
/
delimiter ;

-- 还书更新在册数量
delimiter /
create trigger t2 after update
on `record` for each row
begin
    update `book` set `num` = `num` + 1
    where `id` = new.book_id;
end;
/
delimiter ;


-- 视图，查询各种图书的书号、书名、总数和在册书
create view a as
select `id`, `name`, `total`, `num` from `book`;

-- 存储过程，查询指定读者借阅图书的情况
delimiter /
create procedure search (
    in `name` varchar(10),
)
begin
select record.* from `record` inner join `user`
where `user.id` = `record.user_id` and `user.name` = @name;
end;
/
delimiter ;

-- 创建角色，分别拥有图书的借阅和归还的权利
create role u1, u2;
grant insert on `record` to u1;
grant update on `record` to u2;
