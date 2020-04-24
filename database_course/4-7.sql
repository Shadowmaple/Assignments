-- 建表
create table `staff` (
    `no` int comment '职工号',
    `name` varchar(20) comment '姓名',
    `age` int,
    `duty` varchar(50) comment '职务',
    `salary` int comment '工资',
    `department_no` int comment '部门号',
    primary key (`no`)
);

create table `department` (
    `no` int comment '部门号',
    `name` varchar(40),
    `manager` varchar(20) comment '经理',
    `addr` varchar(50),
    `phone` char(15),
    primary key (`no`)
);

/*
-- Q7
-- 1)
grant select on table staff, department to 王明;
-- 2)
grant insert, delete on table staff, department to 李勇;
-- 3)
grant select on table staff when user() = name to public;
-- 4)
grant select, update(salary) on table staff to 刘星;
-- 5)
grant alter table on table staff, department to 张新;
-- 6)
grant all privilages on table staff, department to 周平 with grant option;
-- 7)
create view v as
select max(salary), min(salary), average(salary)
from staff, department
where staff.department_no = department.id
group by staff.department_no;

grant select on v to 杨兰;

-- Q8
-- 1)
revoke select on table staff, department from 王明；
-- 2)
revoke insert, delete on table staff, department from 李勇；
-- 3)
revoke select on table staff when user() = name from public;
-- 4)
revoke select, update(salary) on table staff from 刘星；
-- 5)
revoke alter table on table staff, department from 张新;
-- 6)
revoke all privilages on table staff, department from 周平 cascade;
-- 7)
revoke select on v from 杨兰；
drop view v;
*/