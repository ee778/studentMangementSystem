
# create tb_class

DROP TABLE IF EXISTS tb_class;
create table tb_class (
    classID int NOT NULL PRIMARY KEY,
    gradeID int NOT NULL,
    className varchar(20) NOT NULL,
    foreign key(gradeID) references tb_grade(gradeID)
);



drop table if exists tb_grade;
create table tb_grade(
    gradeID int NOT NULL PRIMARY KEY,
    gradeName varchar(20) NOT NULL

);

drop table if exists tb_student;
create table tb_student(
    stuID varchar(20) NOT NULL PRIMARY KEY,
    stuName varchar(20),
    classID int,
    gradeID int,
    age int,
    sex char(4),
    phone char(20),
    address varchar(100),
    foreign key(gradeID) references tb_class(gradeID),
    foreign key(classID) references tb_class(classID)
);

drop table if exists tb_user;

create table tb_user (
    userName varchar(20) NOT NULL PRIMARY KEY,
    userPassword varchar(50)
);