CREATE DATABASE `firstdb`;

USE `firstdb`;

CREATE TABLE `student` (
    `sid` CHAR(9) PRIMARY KEY,
    `name` CHAR(20) UNIQUE,
    `sex` CHAR(2),
    `age` SMALLINT,
    `dept` CHAR(20)
);

CREATE TABLE `course` (
    `cid` CHAR(4) PRIMARY KEY,
    `name` CHAR(40),
    `pno` CHAR(4),
    `credit` SMALLINT
);

CREATE TABLE `sc` (
    `sid` CHAR(9),
    `cid` CHAR(4),
    `grade` INT(8),
    PRIMARY KEY (`sid`, `cid`),
    FOREIGN KEY `fk_sid` (`sid`) REFERENCES `student` (`sid`),
    FOREIGN KEY `fk_cid` (`cid`) REFERENCES `course` (`cid`)
);

-- DML

insert into student values
('s001', '陆舟', '男', 21, '计算机类'),
('s010', '杨广', '男', 24, '历史类'),
('s88', '谢道韫', '女', 16, '汉语言文学');

select * from student;
select * from student where sex = '男';

update student set age = 28 where name = '杨广';
select * from student;

delete from student where name = '陆舟';
select * from student;
