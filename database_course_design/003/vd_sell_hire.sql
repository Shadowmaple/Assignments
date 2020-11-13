drop database if exists vcdstore;
create database vcdstore;
use vcdstore;

create table vcd (
	`id` varchar(10) primary key,
	`name` varchar(20),
	`price` float comment '零售价',
	`kind` varchar(20) comment '类别',
	`number` int default 0 comment '库存量',
	`detail` text comment '其他信息'
);

create table customer (
	`id` varchar(10) primary key,
	`name` varchar(20),
	`contact` varchar(30) comment '联系方式'
);

create table purchase (
	`id` int unsigned auto_increment,
	`vid` varchar(10),
	`num` int comment '进货量',
	`time` datetime comment '入库时间',
	primary key(id),
	foreign key(vid) references vcd(id)
);

create table br_record (
	`id` int unsigned auto_increment,
	`vid` varchar(10),
	`cid` varchar(10),
	`num` int comment'出租数量',
	`btime` datetime comment '出租时间',
	`money` float comment '出租押金',
	`rtime` datetime comment '归还时间',
	`state` tinyint default 0 comment '状态，0未还',
	primary key(id),
	foreign key(vid) references vcd(id),
	foreign key(cid) references customer(id)
);

create table sell_record (
	`id` int unsigned auto_increment,
	`vid` varchar(10),
	`cid` varchar(10),
	`num` int comment '售卖数量',
	`money` float comment '支付总金额',
	`time` datetime comment '出售时间',
	primary key(id),
	foreign key(vid) references vcd(id),
	foreign key(cid) references customer(id)
);

-- 进货触发器
-- 只负责数据更新
delimiter $
create trigger in_vcd
	after insert on purchase for each row
Begin
	update vcd
	set vcd.number = vcd.number + new.num
	where vcd.id = new.vid;
End $
delimiter ;

-- 进货存储过程
-- 进新品种vcd
delimiter $
create procedure pur_new_vcd
	(IN vid varchar(10),IN name varchar(20),IN price float,IN kind varchar(20),IN num int)
Begin
	declare msg varchar(200);
	declare rvid varchar(10);
	select id into rvid
	from vcd
	where vcd.id = vid;

	if rvid is not null then
		set msg = "该vcd存在库存中,请使用pur_old_vcd存储过程更新";
		signal sqlstate 'HY000' set message_text = msg;
	end if;

	insert into vcd(`id`,`name`,`price`,`kind`,`number`) values
		(vid,name,price,kind,num);
	insert into purchase(`vid`,`num`,`time`) values(vid,num,now());
End $
delimiter ;

-- 进已经存在的品种
delimiter $
create procedure pur_old_vcd
	(IN vid varchar(10),IN num int)
Begin
	declare msg varchar(200);
	declare rvid varchar(10);
	select id into rvid
	from vcd
	where vcd.id = vid;

	if rvid is null then
		set msg = "该vcd不存在在库存中,请使用pur_new_vcd存储过程更新";
		signal sqlstate 'HY000' set message_text = msg;
	end if;

		insert into purchase(`vid`,`num`,`time`) values(vid,num,now());
	End $
delimiter ;


-- 零售
-- 要有判断，能不能卖
-- 登记记录+更新库存(触发器)
-- 计算价格
delimiter $
create trigger sell_vcd_num
	after insert on sell_record for each row
Begin
	update vcd
		set vcd.number = vcd.number - new.num
		where vcd.id = new.vid;
End $
delimiter ;

delimiter $
create procedure sell
	(IN vid varchar(10),IN cid varchar(10),IN num int)
Begin
	declare msg varchar(200);
	declare money float;
	select vcd.number into @num
	from vcd
	where vcd.id = vid;

	if @num < num then
		set msg = "库存不足，无法售出";
		signal sqlstate 'HY000' set message_text = msg;
	end if;

	select vcd.price*num into @money
	from vcd
	where vcd.id  = vid;

	insert into sell_record(`vid`,`cid`,`num`,`money`,`time`) values(vid,cid,num,@money,now());
End $
delimiter ;

-- 借阅
-- 判断库存
-- 计算押金
-- 登记信息
-- 更新库存 -- 触发器
delimiter $
create trigger bor_vcd_num
	after insert on br_record for each row
Begin
	update vcd
	set vcd.number = vcd.number-new.num
	where vcd.id = new.vid;
End $
delimiter ;

delimiter $
create procedure borrow_vcd
	(IN vid varchar(10),IN cid varchar(10),IN num int)
Begin
	declare msg varchar(200);

	select vcd.number into @num
	from vcd
	where vid = vcd.id;

	if @num < num then
		set msg = "库存不足，无法借阅";
		signal sqlstate'HY000' set message_text = msg;
	end if;

	select vcd.price*num into @money
	from vcd
	where vcd.id  = vid;

	insert into br_record(`vid`,`cid`,`num`,`btime`,`money`)
		values(vid,cid,num,now(),@money);
End $
delimiter ;

-- 归还
-- 判断是否超期//用 select
-- 登记信息
-- 更新库存 -- 触发器
delimiter $
create trigger re_vcd_num
	after update on br_record for each row
Begin
	update vcd
	set vcd.number = vcd.number + old.num
	where vcd.id = old.vid;
End $
delimiter ;

delimiter $
create procedure return_num
	(IN vid varchar(10),IN cid varchar(10))
Begin
	update br_record as br
	set state = 1,rtime = now()
	where vid = br.vid and cid = br.cid;

	select datediff(br.rtime, now()) into @day
	from br_record as br
	where vid = br.vid and cid = br.cid;

	if @day > 60 then
		select "租借超期，押金无法归还";
	end if;
End $
delimiter ;

-- 视图
create view vcd_have as
	select id,name,price,number
	from vcd;

-- 存储过程统计vcd的销售借阅情况
delimiter $
create procedure show_state(IN time1 datetime,IN time2 datetime)
Begin

create TEMPORARY table t1 as
select sell_r.vid as vid1, s_num, money,bor_r.vid as vid2,br_num
	from (select vid,sum(num) as s_num,sum(money) as money
		from
		(select *
			from sell_record as sr
			where time1 < sr.time and sr.time < time2) as t1
		group by vid) as sell_r left JOIN
		(select vid,sum(num) as br_num
		from
		(select *
			from br_record as br
			where br.state = 0 and time1 < br.btime and br.btime < time2) as t2
		group by vid) as bor_r on sell_r.vid = bor_r.vid
UNION
	select sell_r.vid as vid1, s_num, money,bor_r.vid as vid2,br_num
	from (select vid,sum(num) as s_num,sum(money) as money
		from
		(select *
			from sell_record as sr
			where time1 < sr.time and sr.time < time2) as t1
		group by vid) as sell_r right JOIN
		(select vid,sum(num) as br_num
		from
		(select *
			from br_record as br
			where br.state = 0 and time1 < br.btime and br.btime < time2) as t2
		group by vid) as bor_r on sell_r.vid = bor_r.vid;

	select vcd.id as vid, vcd.name as name, s_num, money, br_num
	FROM t1,vcd
  where t1.vid1 = vcd.id or t1.vid2 = vcd.id;

	drop table t1;
End $
delimiter ;
