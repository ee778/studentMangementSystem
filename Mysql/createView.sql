DROP VIEW IF EXISTS v_classinfo;
CREATE VIEW v_classinfo
AS
    select tb_class.classID AS classID,
           tb_grade.gradeID AS gradeID,
           tb_grade.gradeName AS gradeName,
           tb_class.className AS className
from (tb_class join tb_grade)
where (tb_class.gradeID = tb_grade.gradeID);

# 不需要加 ‘’

DROP VIEW IF EXISTS v_studentinfo;
CREATE VIEW v_studentinfo
AS
    select tb_student.stuID AS stuID,
           tb_student.stuName AS stuName,
           tb_student.age AS age,
           tb_student.sex AS sex,
           tb_student.phone AS phone,
           tb_student.address AS address,
           tb_class.className AS className,
           tb_grade.gradeName AS gradeName
FROM ((tb_student join tb_class) join tb_grade)
WHERE ((tb_student.classID = tb_class.classID) and (tb_student.gradeID = tb_grade.gradeID));



