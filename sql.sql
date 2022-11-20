CREATE DATABASE sys;
USE sys;
DROP TABLE student
CREATE TABLE student(
	`id` INT PRIMARY KEY,
	`name` VARCHAR(100),
	`age` INT,
	`classroom` VARCHAR(50)
);

INSERT INTO student
VALUE
(1,'Lucy',20,'1')

SHOW VARIABLES LIKE 'char%';

UPDATE student
SET NAME='KOBE',age=18,classroom='Two'
WHERE id=2;


SELECT  FROM student;