INSERT INTO tb_grade VALUES(1, "初一");
INSERT INTO tb_grade VALUES(2, "初二");
INSERT INTO tb_grade VALUES(3, "初三");

INSERT INTO tb_class VALUES(101, 1, "1班");
INSERT INTO tb_class VALUES(102, 1, "2班");
INSERT INTO tb_class VALUES(103, 1, "3班");
INSERT INTO tb_class VALUES(201, 2, "1班");
INSERT INTO tb_class VALUES(202, 2, "2班");
INSERT INTO tb_class VALUES(203, 2, "3班");
INSERT INTO tb_class VALUES(301, 3, "1班");
INSERT INTO tb_class VALUES(302, 3, "2班");
INSERT INTO tb_class VALUES(303, 3, "3班");
INSERT INTO tb_class VALUES(304, 3, "4班");


INSERT INTO tb_student VALUES(20190101,"王五", 101, 1, 13, "男", 13209080, "广东省广州市荔湾区桥中街道");


-- # 请根据以下的example 和 rule 生成 50 条随机语句
-- # 0. 这是一个学生信息表,其创建语句为
-- #    create table tb_student(
-- #    stuID varchar(20) NOT NULL PRIMARY KEY,
-- #    stuName varchar(20),
--     classID int,
--     gradeID int,
--     age int,
--     sex char(4),
--     phone char(20),
--     address varchar(100),
--     foreign key(gradeID) references tb_class(gradeID),
--     foreign key(classID) references tb_class(classID)
-- );
-- # 这个一个example: INSERT INTO tb_student VALUES(20190101,"王家驹", 101, 1, 13, "男", 13209080961, "广东省广州市荔湾区桥中街道");
-- # rule如下:
-- # 1. 这是一个学生数据库的学生信息表插入语句
-- # 2. 第一个插入的元素是studentID, 为int类型,是 表的主键,他的构造规则是根据学生的入学年份, 班级号,以及班里的排名决定
-- # 如20190101 是2019年入学的01班的01位同学. 排名的取值范围为[01, 45]
-- # 3. 第二个插入的元素是studentName,为char() 这个是个随机的中文姓名.
-- # 4. 第三个插入的元素是classID, 构成为年级加班级号,如101为1年级加01班, 年级的取值范围为[1,3],班级号的取值为[00,09];
-- # 5. 第四个插入的元素是gradeID, 为classID的首个数字.并且gradeID需要和入学年份绑定,如2019年对应grade = 1, 2018对应grade = 2
-- # 6. 第五个插入的元素是age为学生年龄,这是一群初中的学生,年龄根据情况随机波动.
-- # 7. 第六个插入的元素是sex, 为学生性别,有男和女两个选择.
-- # 8. 第七个插入的元素是phone, 随机生成一个中国地区的11位电话号码.
-- # 9. 第八个插入的元素是address, 随机在广东省广州市荔湾区随机生成一个地址.

INSERT INTO tb_student VALUES(20190105,"杨凯琳", 302, 3, 14, "女", 13589645820, "广东省广州市荔湾区山东村");
INSERT INTO tb_student VALUES(20180108,"陈婉婷", 201, 2, 14, "女", 13963541478, "广东省广州市荔湾区城北街");
INSERT INTO tb_student VALUES(20200106,"黄健宏", 101, 1, 13, "男", 13825984731, "广东省广州市荔湾区桥中街道");
INSERT INTO tb_student VALUES(20180209,"林凯莉", 202, 2, 14, "女", 13851234471, "广东省广州市荔湾区水西街道");
INSERT INTO tb_student VALUES(20200202,"邓俊锋", 102, 1, 13, "男", 13695873914, "广东省广州市荔湾区桥中街道");
INSERT INTO tb_student VALUES(20200305,"邓健华", 203, 2, 14, "男", 13384657320, "广东省广州市荔湾区水西街道");
INSERT INTO tb_student VALUES(20190104,"陈凯文", 301, 3, 14, "男", 13653827610, "广东省广州市荔湾区上九路");
INSERT INTO tb_student VALUES(20180201,"罗俊霞", 201, 2, 14, "女", 13571234678, "广东省广州市荔湾区城北街");
INSERT INTO tb_student VALUES(20190306,"黄俊博", 302, 3, 13, "男", 13897654310, "广东省广州市荔湾区山东村");
INSERT INTO tb_student VALUES(20180105,"罗俊丽", 201, 2, 14, "女", 13675829147, "广东省广州市荔湾区城北街");
INSERT INTO tb_student VALUES(20190309,"张凯瑶", 302, 3, 13, "女", 13712983451, "广东省广州市荔湾区山东村");
INSERT INTO tb_student VALUES(20190103,"郭婉琳", 301, 3, 14, "女", 13910354672, "广东省广州市荔湾区上九路");
INSERT INTO tb_student VALUES(20180203,"邓凯宇", 202, 2, 14, "男", 13859283945, "广东省广州市荔湾区水西街道");
INSERT INTO tb_student VALUES(20200208,"林俊宏", 102, 1, 13, "男", 13597263028, "广东省广州市荔湾区桥中街道");

INSERT INTO tb_student VALUES(20230305,"赵颖珊", 302, 3, 14, "女", 13632147896, "广东省广州市荔湾区石围塘街道");
INSERT INTO tb_student VALUES(20230103,"杨文静", 301, 3, 15, "女", 13724063925, "广东省广州市荔湾区岭南街道");
INSERT INTO tb_student VALUES(20230107,"卢新莹", 301, 3, 13, "女", 13634298563, "广东省广州市荔湾区桥中街道");
INSERT INTO tb_student VALUES(20230308,"杨雪莹", 302, 3, 14, "女", 13725698416, "广东省广州市荔湾区中山路街道");
INSERT INTO tb_student VALUES(20230304,"周美雪", 302, 3, 14, "女", 13248750164, "广东省广州市荔湾区桂花岗街道");
INSERT INTO tb_student VALUES(20230206,"韩艳", 302, 3, 14, "女", 13812654038, "广东省广州市荔湾区芳村街道");
INSERT INTO tb_student VALUES(20230303,"高天琪", 302, 3, 15, "男", 13748251609, "广东省广州市荔湾区桥中街道");
INSERT INTO tb_student VALUES(20230202,"龚锦莹", 302, 3, 14, "女", 13856312947, "广东省广州市荔湾区中山路街道");
INSERT INTO tb_student VALUES(20230301,"杨文杰", 302, 3, 14, "男", 13223148712, "广东省广州市荔湾区沙面街道");
INSERT INTO tb_student VALUES(20230105,"曹佳", 301, 3, 15, "女", 13765294318, "广东省广州市荔湾区中山路街道");
INSERT INTO tb_student VALUES(20230203,"叶倩蓉", 302, 3, 15, "女", 13752481306, "广东省广州市荔湾区岭南街道");
INSERT INTO tb_student VALUES(20230104,"蔡思敏", 301, 3, 13, "女", 13897642305, "广东省广州市荔湾区花地街道");
INSERT INTO tb_student VALUES(20230309,"马小静", 302, 3, 14, "女", 13223149678, "广东省广州市荔湾区中山路街道");
INSERT INTO tb_student VALUES(20210109,"邓翔", 202, 2, 14, "男", 13493755127, "广东省广州市荔湾区榄核街道");
INSERT INTO tb_student VALUES(20190135,"刘琦", 101, 1, 13, "女", 13767356452, "广东省广州市荔湾区芳村街道");
INSERT INTO tb_student VALUES(20220104,"杨露", 203, 2, 14, "女", 13847912538, "广东省广州市荔湾区桂花街道");
INSERT INTO tb_student VALUES(20180104,"林鸿铭", 102, 2, 14, "男", 13651793225, "广东省广州市荔湾区龙津西街道");
INSERT INTO tb_student VALUES(20190204,"郑钧", 102, 1, 14, "男", 13857693018, "广东省广州市荔湾区坑口街道");