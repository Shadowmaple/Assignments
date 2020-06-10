CREATE DATABASE `firstdb`;

USE `firstdb`;

CREATE TABLE `books` (
    `id` CHAR(10),
    `title` VARCHAR(20) NOT NULL,
    `publish_name` VARCHAR(20) COMMENT '出版社名称',
    `page_num` INT,
    `price` SMALLINT,
    `publish_date` DATE,
    PRIMARY KEY (`id`)
);

insert into books values
('001', 'C语言程序设计', '清华大学出版社', 344, 34, '2015-01-12'),
('010', '深入理解计算机系统', '机械工业出版社', 734, 89, '2016-11-10'),
('020', '社会心理学', '人民邮电出版社', 504, 68, '2006-01-12');

select * from books;

update books set price = 139 where title = '深入理解计算机系统';

select * from books;

select * from books where page_num > 500;

select * from books order by price desc;

select * from books where title like '%计算机%';
