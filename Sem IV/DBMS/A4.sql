CREATE TABLE Employee(EmployeeNo INT NOT NULL, EmployeeName VARCHAR(20) NOT NULL, Join_Date VARCHAR(10) NOT NULL, Designation VARCHAR(20) NOT NULL, Salary INT NOT NULL, PRIMARY KEY(EmployeeNo));
INSERT INTO Employee VALUES(1, "Bill Dsouza", "31/09/2019", "Manager", 100000);
INSERT INTO Employee VALUES(2, "Aditya Kumar", "21/12/2013", "Senior Engineer", 200000);
INSERT INTO Employee VALUES(3, "Atharva Patil", "08/09/2019", "Engineer", 80000);
INSERT INTO Employee VALUES(4, "Raj Deshpande", "09/01/2018", "Receptionist", 50000);
INSERT INTO Employee VALUES(5, "Samiksha Agarwal", "09/01/2018", "Receptionist", 50000);
INSERT INTO Employee VALUES(6, "Harshal Dsouza", "30/01/2020", " Designer", 90000);
SELECT * FROM Employee;
SELECT EmployeeNo, EmployeeName, Salary FROM Employee ORDER BY Salary DESC LIMIT 5;
DELIMITER //
CREATE OR REPLACE PROCEDURE salSort()
BEGIN
	DECLARE EmpNo INT DEFAULT 0; 
	DECLARE EmpName VARCHAR(20);
	DECLARE EmpSalary INT DEFAULT 0;
	DECLARE finished INT DEFAULT 0;
	DECLARE curs CURSOR FOR SELECT EmployeeNo, EmployeeName, Salary FROM Employee ORDER BY Salary DESC LIMIT 5;
	DECLARE CONTINUE HANDLER FOR NOT FOUND SET finished = 1;
	OPEN curs;
	dispVal: LOOP 
	FETCH curs into EmpNo,EmpName,EmpSalary;
	IF finished = 1 THEN 
	LEAVE dispVal;
	END IF;
	SELECT EmpNo, EmpName, EmpSalary;
	END LOOP dispVal;
	CLOSE curs;
END;
//
DELIMITER ;
CALL salSort();

