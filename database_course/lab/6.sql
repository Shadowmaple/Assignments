CREATE DATABASE `firstdb`;

USE `firstdb`;

CREATE TABLE `student` (
    `sid` VARCHAR(15) NOT NULL,
    `name` VARCHAR(15) NOT NULL DEFAULT '',
    `age` INT(8) DEFAULT 0,
    `sex` CHAR(1) NOT NULL CHECK(sex = '男' or sex = '女'), -- mysql中check不起作用
    `dept` VARCHAR(20) NOT NULL DEFAULT '' COMMENT '院系',

    PRIMARY KEY (`sid`)
);

CREATE TABLE `course` (
    `cid` VARCHAR(15) NOT NULL,
    `name` VARCHAR(25) NOT NULL DEFAULT '' UNIQUE,
    `teacher` VARCHAR(15) NOT NULL DEFAULT '',
    `size` INT(8) DEFAULT 0,
    `credit` INT(8) NOT NULL DEFAULT 0,

    PRIMARY KEY (`cid`)
);

CREATE TABLE `sc` (
    `id` INT AUTO_INCREMENT,
    `sid` VARCHAR(15) NOT NULL,
    `cid` VARCHAR(15) NOT NULL,
    `grade` SMALLINT DEFAULT 0,

    PRIMARY KEY (`id`),
    FOREIGN KEY `fk_sid` (`sid`) REFERENCES `student` (`sid`) ON UPDATE CASCADE ON DELETE CASCADE,
    FOREIGN KEY `fk_cid` (`cid`) REFERENCES `course` (`cid`) ON UPDATE CASCADE ON DELETE CASCADE
);
