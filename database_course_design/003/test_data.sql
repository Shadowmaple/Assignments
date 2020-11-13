use vcdstore;

insert into vcd values
('1', '明日黄花', 33.3, '诗词', 233, '无'),
('2', '今天的花儿', 45, '乐曲', 100, '无'),
('3', '我的祖国', 29.8, '传统', 45, '无');

insert into customer values
('1', '小明', '13944444444'),
('2', '小黄', '');

-- 进货
-- 进货新品种
call pur_new_vcd('2', '今天的花儿', 45, '乐曲', 20);
call pur_new_vcd('5', '喧嚣', 18, '摇滚', 13);
-- 进货旧品种
call pur_old_vcd('2', 20);
call pur_old_vcd('55', 20);

-- 零售
call sell('1', '1', 40);
call sell('2', '2', 150);

-- 借阅
call borrow_vcd('3', '2', 5);
call borrow_vcd('3', '1', 50);

-- 归还
call return_num('3', '2');

-- 销售借阅情况
call show_state('2020-10-01 00:00:00', '2020-12-31 00:00:00');
