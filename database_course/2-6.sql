-- 建表
CREATE DATABASE `sql_course_test`;
USE `sql_course_test`;

CREATE TABLE `S` (
    `SNO` CHAR(10) NOT NULL,
    `SNAME` VARCHAR(50) NOT NULL,
    `STATUS` INT NOT NULL,
    `CITY` VARCHAR(10) NOT NULL COMMENT '城市',

    PRIMARY KEY (`SNO`)
);

CREATE TABLE `P` (
    `PNO` CHAR(10) NOT NULL,
    `PNAME` VARCHAR(20) NOT NULL,
    `COLOR` CHAR(5) NOT NULL,
    `WEIGHT` INT NOT NULL,

    PRIMARY KEY (`PNO`)
);

CREATE TABLE `J` (
    `JNO` CHAR(10) NOT NULL,
    `JNAME` VARCHAR(20) NOT NULL,
    `CITY` VARCHAR(10) NOT NULL,

    PRIMARY KEY (`JNO`)
);

CREATE TABLE `SPJ` (
    `SNO` CHAR(10),
    `PNO` CHAR(10),
    `JNO` CHAR(10),
    `QTY` INT COMMENT '供应数量',

    KEY `IDX_SNO` (`SNO`),
    KEY `IDX_PNO` (`PNO`),
    KEY `IDX_JNO` (`JNO`)
);

-- 插入数据

INSERT INTO `S` VALUES
('S1', '精益', 20, '天津'),
('S2', '盛锡', 10, '北京'),
('S3', '东方红', 30, '北京'),
('S4', '丰泰盛', 20, '天津'),
('S5', '为民', 30, '上海');

INSERT INTO `P` VALUES
('P1', '螺母', '红', 12),
('P2', '螺栓', '绿', 17),
('P3', '螺丝刀', '蓝', 14),
('P4', '螺丝刀', '红', 14),
('P5', '凸轮', '蓝', 40),
('P6', '齿轮', '红', 30);

INSERT INTO `J` VALUES
('J1', '三建', '北京'),
('J2', '一汽', '长春'),
('J3', '弹簧厂', '天津'),
('J4', '造船厂', '天津'),
('J5', '机车厂', '唐山'),
('J6', '无线电厂', '常州'),
('J7', '半导体厂', '南京');

INSERT INTO `SPJ` VALUES
('S1', 'P1', 'J1', 200),
('S1', 'P1', 'J3', 700),
('S1', 'P1', 'J4', 100),
('S1', 'P2', 'J2', 400),
('S2', 'P3', 'J1', 200),
('S2', 'P3', 'J2', 500),
('S2', 'P3', 'J4', 400),
('S2', 'P3', 'J5', 400),
('S2', 'P5', 'J1', 100),
('S2', 'P5', 'J2', 200),
('S3', 'P1', 'J1', 200),
('S3', 'P3', 'J1', 100),
('S4', 'P5', 'J1', 200),
('S4', 'P6', 'J3', 200),
('S4', 'P6', 'J4', 100),
('S5', 'P2', 'J4', 300),
('S5', 'P3', 'J1', 200),
('S5', 'P6', 'J2', 200),
('S5', 'P6', 'J4', 500);
