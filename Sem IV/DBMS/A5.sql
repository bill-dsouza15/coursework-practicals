CREATE TABLE Student_course(RollNo INT NOT NULL, Course VARCHAR(20) NOT NULL, Course_code INT NOT NULL, Semester INT NOT NULL, Total_marks INT NOT NULL, Percentage INT NOT NULL);
INSERT INTO Student_course VALUES(1, "DBMS", 10101, 2, 300, 50);
INSERT INTO Student_course VALUES(4, "TOC", 10103, 2, 400, 66);
INSERT INTO Student_course VALUES(2, "DBMS", 10101, 2, 400, 66);
INSERT INTO Student_course VALUES(5, "DBMS", 10101, 2, 450, 75);
INSERT INTO Student_course VALUES(1, "TOC", 10103, 2, 450, 75);
INSERT INTO Student_course VALUES(3, "DBMS", 10101, 2, 400, 66);
INSERT INTO Student_course VALUES(3, "TOC", 10103, 2, 480, 80);
INSERT INTO Student_course VALUES(4, "DBMS", 10101, 2, 420, 70);
INSERT INTO Student_course VALUES(2, "TOC", 10103, 2, 540, 90);
INSERT INTO Student_course VALUES(5, "TOC", 10103, 2, 570, 95);
SELECT * FROM Student_course;
DELIMITER //
CREATE OR REPLACE PROCEDURE perSort(IN co VARCHAR(20))
BEGIN
	DECLARE Distinction INT DEFAULT 0;
	DECLARE First_class INT DEFAULT 0;
	DECLARE Higher_sec INT DEFAULT 0;
	DECLARE Second_class INT DEFAULT 0;
	DECLARE Pass INT DEFAULT 0;
	DECLARE temp INT DEFAULT 0;
	DECLARE finished INT DEFAULT 0;
	DECLARE curs CURSOR FOR 
	SELECT Percentage FROM Student_course WHERE Course=co;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = 1;
	OPEN curs;
	dispVal: LOOP
	FETCH curs INTO temp;
	IF finished = 1 THEN 
	SELECT Distinction, First_class, Higher_sec, Second_class, Pass;
	LEAVE dispVal;
	END IF;
	IF temp<100 AND temp>=80 THEN SET Distinction:=Distinction+1;
	ELSEIF temp<80 AND temp>=70 THEN SET First_class:=First_class+1;
	ELSEIF temp<70 AND temp>=60 THEN SET Higher_sec:=Higher_sec+1;
	ELSEIF temp<60 AND temp>=50 THEN SET Second_class:=Second_class+1;
	ELSEIF temp<50 THEN SET Pass:=Pass+1;
	END IF;
	END LOOP dispVal;
	CLOSE curs;
END;
//
DELIMITER ;
CALL perSort('DBMS');

