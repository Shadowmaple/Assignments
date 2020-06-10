CREATE DATABASE `firstdb`;

USE `firstdb`;

CREATE TABLE `account` (
    `id` INT AUTO_INCREMENT,
    `name` VARCHAR(15) NOT NULL,
    `num` INT(8) DEFAULT 0,
    `update_time` DATETIME,
    PRIMARY KEY (`id`)
);

-- 插入数据集
INSERT INTO `account` (`name`, `num`) VALUES ('小明', 10), ('小白', 5), ('小红', 40), ('老王', 100);

-- 创建 update before 触发器
delimiter /
create trigger `update_tri` before update
on `account` for each row
begin
set NEW.update_time = now();
end
/
delimiter ;


-- 操作

select * from account;
update account set num = 20 where name = '小白';
select * from account;


-- 删除触发器
drop trigger update_tri;