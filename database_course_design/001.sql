create table `student` (
    `sno` varchar(20) unique,
    `sname` varchar(20) not null,
    `sex` char(1),
    `dept` varchar(10),
    `birth` date,
    `age` int
);

create table `course` (
    `cno` varchar(20) unique,
    `cname` varchar(20) not null,
    `tno` varchar(20)
);

create table `teacher` (
    `tno` varchar(20),
    `tname` varchar(20),
    `dept` varchar(20) comment '系'
);

create table `sc` (
    `sno` varchar(20),
    `cno` varchar(20),
    `tno` varchar(20),
    `grade` int,

    foreign key(`sno`) references `student`(`sno`),
    foreign key(`cno`) references `course`(`cno`)
);

-- query

select `sname`, `sno`, `dept` from `student`;

select `sname`, `birth` from `student`;

select * from `student` where `sname` like '欧阳%' and length(sname) = 3;

select * from `student` where `sname` like '__晨%';
