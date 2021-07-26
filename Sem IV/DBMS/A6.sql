CREATE TABLE Employee(EmployeeNo INT NOT NULL, EmployeeName VARCHAR(20) NOT NULL, Join_Date VARCHAR(10) NOT NULL, Designation VARCHAR(20) NOT NULL, Salary VARCHAR(20) NOT NULL, PRIMARY KEY(EmployeeNo));
INSERT INTO Employee VALUES(1, "Bill Dsouza", "09/31/2019", "Manager", "100000");
INSERT INTO Employee VALUES(2, "Aditya Kumar", "12/21/2013", "Senior Engineer", "200000");
INSERT INTO Employee VALUES(3, "Atharva Patil", "09/08/2019", "Engineer", "80000");
INSERT INTO Employee VALUES(4, "Raj Deshpande", "01/09/2018", "Receptionist", "50000");
INSERT INTO Employee VALUES(5, "Samiksha Agarwal", "01/09/2018", "Receptionist", "50000");
INSERT INTO Employee VALUES(6, "Harshal Singh", "01/30/2020", " Designer", "90000");
SELECT * FROM Employee;
CREATE TABLE EmployeeTable(EmployeeNo INT NOT NULL, EmployeeName VARCHAR(20) NOT NULL, Join_Date VARCHAR(10) NOT NULL, Designation VARCHAR(20) NOT NULL, Salary VARCHAR(20) NOT NULL, PRIMARY KEY(EmployeeNo));
DELIMITER //
CREATE TRIGGER aftIns
AFTER INSERT ON Employee FOR EACH ROW
BEGIN
	INSERT INTO EmployeeTable VALUES(NEW.EmployeeNo, NEW.EmployeeName, NEW.Join_Date, NEW.Designation, NEW.Salary);
END;
//
INSERT INTO Employee VALUES(7, "Harsh Jain", "04/30/2016", " Designer", "90000");
//
SELECT * FROM Employee;
//
SELECT * FROM EmployeeTable;
//
CREATE TRIGGER befUpd
BEFORE UPDATE ON Employee FOR EACH ROW
BEGIN
	INSERT INTO EmployeeTable VALUES(OLD.EmployeeNo, OLD.EmployeeName, OLD.Join_Date, OLD.Designation, OLD.Salary);
END;
//
UPDATE Employee SET Designation = "Regional Manager", Salary = 300000 WHERE EmployeeNo = 1;
//
SELECT * FROM Employee;
//
SELECT * FROM EmployeeTable;
//
CREATE TRIGGER aftDel
AFTER DELETE ON Employee FOR EACH ROW
BEGIN
	INSERT INTO EmployeeTable VALUES(OLD.EmployeeNo, OLD.EmployeeName, OLD.Join_Date, OLD.Designation, OLD.Salary);
END;
//
DELETE FROM Employee WHERE EmployeeNo = 2;
//
SELECT * FROM Employee;
//
SELECT * FROM EmployeeTable;
//
DELIMITER ;

