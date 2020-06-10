CREATE DATABASE `firstdb`;

USE `firstdb`;


create user 'mannix'@'host' identified by '123';
select user,host from mysql.user;

grant update, delete on firstdb.* to 'mannix'@'host';
flush privileges;
show grants for 'mannix'@'host';

grant all privileges on firstdb.* to 'mannix'@'host';
flush privileges;
show grants for 'mannix'@'host';

revoke all privileges on firstdb.* from 'mannix'@'host';
flush privileges;
show grants for 'mannix'@'host';

drop user 'mannix'@'host';
select user,host from mysql.user;
