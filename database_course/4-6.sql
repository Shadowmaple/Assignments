-- 建表
create table `student` (
    `sid` int comment '学号',
    `name` varchar(20),
    `sex` tinyint(1),
    `addr` varchar(50),
    `class_no` varchar(20),
    primary key (`sid`)
);

create table `class` (
    `no` int comment '班级号',
    `name` varchar(20),
    `headmaster` varchar(20) comment '班主任',
    `monitor` varchar(20) comment '班长',
    primary key (`no`)
);

-- answer
-- 1)
grant all privileges on studentclass to U1 with grant option;
grant all privileges on class to U1 with grant option;
-- 2)
grant select, update(addr) on student to U2;
-- 3)
grant select on class to public;
-- 4)
create role R1;
grant select, update on student to R1;
-- 5)
grant R1 to U1 with grant option;
