drop database library;
create database library;
use library;

-- 图书表
create table `book` (
    `id` varchar(30) comment'书号',
    `name` varchar(255),
    `detail` text,
    `kind` varchar(20) comment '类别',
    `publish` varchar(100) comment '出版社',
    `total` int default 0 comment '总数量',
    `num` int default 0 comment '在册数量',
    primary key (`id`)
);

-- 读者表
create table `user` (
    `id` int unsigned auto_increment,
    `name` varchar(10),
    `max_num` int unsigned comment '最大借阅图书数',
    `borrowing_num` int unsigned comment '正在借阅中的数目',
    primary key (`id`)
);

-- 假设一次借阅可借60天
-- 只能续借一次，一次30天
-- 借书表
create table `record` (
    `id` int unsigned auto_increment,
    `user_id` int unsigned,
    `book_id` varchar(30),
    `borrow_time` datetime comment '借阅时间',
    `reborrow_num` int default 0 comment '是否续借',
    `return_time` datetime comment '归还时间',
    primary key (`id`),
    foreign key (book_id) references book(id),
    foreign key (user_id) references user(id)
);

-- 罚款表
create table `fee_manage`(
    `id` int unsigned auto_increment,
    `user_id` int unsigned,
    `book_id` varchar(30),
    `is_ok` tinyint default 0 comment '是否交了罚金', -- 0为没交，1为交了
    `borrow_time` datetime comment '借阅日期', -- 用于计算罚金
    `reborrow_num` int comment '是否续借',
    `return_time` datetime comment '还书时间',
    `money` float comment '罚款金额',
    primary key (`id`),
    foreign key (user_id) references user(id),
    foreign key (book_id) references book(id)
);

-- 借书功能
-- ok
delimiter $
create trigger borrow_book_num
    after insert on record for each row
Begin
    select max_num-borrowing_num into @cnum -- 可借阅册数
    from user
    where id = new.user_id;

    if @cnum > 0 then
        update book
            set book.num = book.num-1
            where book.id = new.book_id;
        update user
            set borrowing_num = borrowing_num+1
            where user.id = new.user_id;
    END IF;
end $
delimiter ;

-- 借阅存储过程
-- ok
delimiter $
create procedure borrow_book(IN book_id varchar(30),IN user_id int unsigned)
begin
    insert into record(user_id,book_id,borrow_time) values(user_id, book_id, now());
end $
delimiter ;

-- 续借 查表，然后更新借阅表
-- ok
delimiter $
create procedure reborrow_book(IN book_id varchar(30),IN user_id int unsigned)
begin
    select reborrow_num into @renum
    from record
    where book_id = record.book_id and  record.user_id = user_id;

    select borrow_time + INTERVAL 60 DAY into @hastime
    from record
    where book_id = record.book_id and record.user_id = user_id;

    -- 可以续借的条件
    IF @renum = 0 and @hastime >= now() then
        update record
        set reborrow_num = 1
        where record.book_id = book_id and record.user_id = user_id;
    END IF ;
END $
delimiter ;

-- 还书
-- ok
delimiter $
create trigger return_book_num
    after update on record for each row
Begin
    -- 只有更新了归还时间才可以更新书本数量
    IF (new.return_time is not null) then
        update book
            set book.num = book.num+1
            where book.id = new.book_id;
        update user
            set borrowing_num = borrowing_num-1
            where user.id = new.user_id;
    END IF;
end $
delimiter ;

-- 存储过程，用于处理罚款问题的
-- ok
delimiter $
create procedure fee_compute(IN retime datetime,IN srtime datetime,OUT fee float)
begin
    set @day := (UNIX_TIMESTAMP(retime) - UNIX_TIMESTAMP(srtime))/(60*60*24);
    select 0.1*@day into fee;
end $
delimiter ;

-- 还书存储过程，一个是先通过book_id与user_id找到借阅记录
-- 更新归还时间，同时处理罚款问题
-- ok
delimiter $
create procedure return_book(IN book_id varchar(30),IN user_id int unsigned)
begin
    update record
    set return_time = now()
    where record.book_id = book_id and record.user_id = user_id;

    set @retime = now();

    select borrow_time + INTERVAL (60+30*reborrow_num) DAY into @srtime
    from record
    where record.book_id = book_id and record.user_id = user_id;

    -- 若超期需要罚款
    IF @retime > @srtime then
        call fee_compute(@retime,@srtime,@fee);
        select @fee;

        select borrow_time into @bortime
        from record
        where record.book_id = book_id and record.user_id = user_id;

        -- 交钱
        insert into fee_manage(user_id,book_id,borrow_time,return_time,money,is_ok) values
            (user_id,book_id,@bortime,@retime,@fee,1);
    END IF;
end $
delimiter ;

-- 存储过程
-- 查询指定读者借阅图书的情况
-- ok
delimiter $
create procedure user_book_pr(IN name varchar(255))
Begin
    select *
    from user join record
    where user.id = record.user_id and user.name = name;
end $
delimiter ;

-- 视图
create view query_book_info as
    select id,name,total,num
    from book;

-- 创建角色
create role borrow_r1;
grant insert
on record
to borrow_r1;

create role return_r2;
grant update
on record
to return_r2;
