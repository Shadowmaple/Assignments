
create database `library`;

create table `book` (
    `id` int unsigned auto_increment,
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
    `sid` varchar(20) comment '学号',
    `name` varchar(10),
    primary key (`id`)
);

create table `record` (
    `id` int unsigned auto_increment,
    `user_id` int unsigned,
    `book_id` int unsigned,
    `borrow_time` datetime comment '借阅时间',
    `must_return_time` datetime comment '需要归还时间',
    `reborrow_num` int default 0 comment '续借次数',
    `return_time` tinyint(1) comment '归还时间',
    `has_paied` tinyint(1) default 0 comment '是否交了罚金',
    primary key (`id`)
);
