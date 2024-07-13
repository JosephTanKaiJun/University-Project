/*
File to submit by each member: G0999_9999999.sql

INDIVIDUAL ASSIGNMENT SUBMISSION
Submit one individual report with SQL statements only (*.docx)
and one sql script (*.sql for oOacle)

Template save as "G999_YourStudentID.sql"
e.g. G001_999999.sql

GROUP NUMBER : G050
PROGRAMME : CS
STUDENT ID : 2206931
STUDENT NAME : ONG BOON SIANG
Submission date and time: 16-04-2024

Your information should appear in both files one individual report docx & one individual sql script, then save as G01_99ACB999999.zip
Should be obvious different transaction among the members

*/



/* Query 1 */

SELECT SUM(Amount) AS "Total Sales"
FROM Payment;


/* Query 2 */

SELECT Member_ID, StartDate
FROM Member
WHERE TO_NUMBER(TO_CHAR(StartDate, 'YYYY')) < 2020;


/* Stored procedure 1 */
CREATE OR REPLACE PROCEDURE AddMenuItem(
    v_MenuItem_ID IN INT,
    v_Restaurant_ID IN CHAR,
    v_Name IN VARCHAR2,
    v_Price IN DECIMAL,
    v_Description IN VARCHAR2)
IS
BEGIN
    INSERT INTO MenuItem (MenuItem_ID, Restaurant_ID, Name, Price, Description) 
    VALUES (v_MenuItem_ID, v_Restaurant_ID, v_Name, v_Price, v_Description);
    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
END;
/

Example:
BEGIN
    AddMenuItem (009, 'R001', 'Grilled Salmon', 10.99, 'Salmon fillet marinated in lemon herb seasoning, grilled to perfection.');
END;
/



/* Stored procedure 2 */
CREATE OR REPLACE PROCEDURE RemoveMenuItem(
    v_MenuItem_ID IN INT)
IS
BEGIN
    DELETE FROM MenuItem 
    WHERE MenuItem_ID = v_MenuItem_ID;
    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An error occurred: ' || SQLERRM);
END;
/

Example:
BEGIN
    RemoveMenuItem(
        v_MenuItem_ID => 009
    );
END;
/



/* Function 1 */
CREATE OR REPLACE FUNCTION count_customer
RETURN NUMBER  
IS  
total_customer NUMBER;  
BEGIN  
SELECT count(*) INTO total_customer 
FROM Customer; 
RETURN total_customer;  
END;  
/ 
    
DECLARE  
totalcustomer NUMBER;  
BEGIN  
totalcustomer := count_customer;  
DBMS_OUTPUT.PUT_LINE('The total number of the customer is '||totalcustomer||'.');  
END;  
/


/* Function 2 */
CREATE OR REPLACE FUNCTION get_employee_age (e_id IN CHAR)
RETURN NUMBER
IS
e_age NUMBER;
BEGIN
SELECT TRUNC(MONTHS_BETWEEN(SYSDATE, DOB)/12)
INTO e_age
FROM Employee
WHERE Employee_ID = e_id;
RETURN e_age;

END;
/

Example:
SELECT get_employee_age('E4165') AS employee_age FROM dual;