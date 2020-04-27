create table `student` (
    `sid` int comment '学号',
    `name` varchar(20),
    `birthday` datetime,
    `department` varchar(20) comment '系名',
    `class_no` int comment '班号',
    `dormitory` varchar(10) comment '宿舍地点',
    primary key (`sid`)
);

create table `class` (
    `no` int comment '班号',
    `major` varchar(20) comment '专业',
    `department` varchar(20) comment '系名',
    `size` int comment '人数',
    `time` datetime comment '入校年份',
    primary key (`no`)
);

create table `department` (
    `no` int comment '系号',
    `name` varchar(15),
    `addr` varchar(20) comment '办公室地点',
    `number` int comment '人数',
    primary key (`no`)
) comment '系';

create table `association` (
    `id` int auto_increament,
    `name` varchar(20),
    `time` datetime comment '成立年份',
    `addr` varchar(20) comment '地点',
    `size` int comment '人数',
    primary key (`id`)
) comment '学会';