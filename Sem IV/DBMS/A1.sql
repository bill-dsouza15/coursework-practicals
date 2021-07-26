USE Staff_info;
CREATE TABLE Employee(EmployeeNo INT NOT NULL AUTO_INCREMENT, EmployeeName VARCHAR(20) NOT NULL, Birth_Date VARCHAR(10) NOT NULL, Join_Date VARCHAR(10) NOT NULL, Designation VARCHAR(20) NOT NULL, Salary VARCHAR(20) NOT NULL, PRIMARY KEY(EmployeeNo));
INSERT INTO Employee(EmployeeName, Birth_Date, Join_Date, Designation, Salary) VALUES("Bill Dsouza", "03/08/1992", "09/31/2019", "Manager", "100000");
INSERT INTO Employee(EmployeeName, Birth_Date, Join_Date, Designation, Salary) VALUES("Aditya Kumar", "12/16/1978", "12/21/2013", "Senior Engineer", "200000");
INSERT INTO Employee(EmployeeName, Birth_Date, Join_Date, Designation, Salary) VALUES("Atharva Patil", "05/31/1990", "09/08/2019", "Engineer", "80000");
INSERT INTO Employee(EmployeeName, Birth_Date, Join_Date, Designation, Salary) VALUES("Raj Deshpande", "08/03/1989", "01/09/2018", "Receptionist", "50000");
INSERT INTO Employee(EmployeeName, Birth_Date, Join_Date, Designation, Salary) VALUES("Samiksha Agarwal", "11/15/1993", "01/09/2018", "Receptionist", "50000");
INSERT INTO Employee(EmployeeName, Birth_Date, Join_Date, Designation, Salary) VALUES("Harshal Singh", "03/30/1992", "01/30/2020", " Designer", "90000");
DESC Employee;
SELECT * FROM Employee;
CREATE UNIQUE INDEX EmpNoName ON Employee(EmployeeNo, EmployeeName);
SHOW INDEXES FROM Employee; 
CREATE VIEW EmpPersonal AS SELECT EmployeeNo, EmployeeName, Birth_Date FROM Employee;
SELECT * FROM EmpPersonal;
RENAME TABLE Employee TO Employee_Orig;
SHOW TABLES;
DROP INDEX EmpNoName ON Employee_Orig;
SHOW INDEXES FROM Employee_Orig;
DROP TABLE Employee_Orig;
SHOW TABLES;


