USE `firstdb`;

select * from books;

select count(*) from books;

select AVG(price), SUM(page_num) from books;

select now();

select abs(-4), sqrt(256), rand(), pow(4,3), log10(100), sin(1.5);
