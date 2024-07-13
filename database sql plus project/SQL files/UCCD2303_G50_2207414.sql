GROUP NUMBER : G050
PROGRAMME : CS
STUDENT ID : 2207414
STUDENT NAME : LOH WEI JIA
Submission date and time: 16-04-2024

/* Query 1 */
1.Display the name of the menu item and price by Restaurant_ID. 

SELECT name, price
FROM menuitem m, restaurant r
WHERE r.restaurant_ID = m.restaurant_ID
AND r.restaurant_ID = 'R001';


/* Query 2 */
2. Display the employee which their age is equal or below 30.

SELECT employee_ID,(FirstName||''||LastName)AS"Employee Name", ROUND((SYSDATE-dob)/365.25) AS "Age" 
FROM employee 
WHERE (SYSDATE-dob)/365.25 <= 30;


/* Stored procedure 1 */
1.This procedure is to change the number of inventories.

CREATE OR REPLACE PROCEDURE updateInventory
(
id in CHAR,
numInv in NUMBER
)
IS
BEGIN
UPDATE Inventory
SET quantity = numInv
WHERE inventory_ID = id;
COMMIT;
END;
/

execute updateInventory('I005','10');

SELECT *
FROM inventory
WHERE inventory_ID='I005';





/* Stored procedure 2 */
2.Change Order date by using OrderID.

CREATE OR REPLACE PROCEDURE change_date
( 
current_OrderID IN CHAR, 
current_ODate IN TIMESTAMP
) 
IS 
BEGIN 
UPDATE Orders
SET Order_Time= current_ODate 
WHERE Order_ID = current_OrderID; 
COMMIT; 
END; 
/ 

EXECUTE change_date('OD0001', TO_DATE('16-04-2024 12:11:33', 'DD-MM-YYYY HH24:MI:SS')); 

SELECT*
FROM Orders
WHERE Order_ID='OD0001';



/* Function 1 */
1.To show the address of employee by using employeeID.

CREATE OR REPLACE FUNCTION showEmpAddress
(
E_ID CHAR
)
RETURN VARCHAR2
IS
e_address VARCHAR2(100);
BEGIN
SELECT Address
INTO e_address
FROM Employee
WHERE Employee_ID = E_ID;
RETURN E_address;
END;
/

SET SERVEROUTPUT ON;
DECLARE
Emp_ID CHAR(5);
Emp_address VARCHAR2(100);
BEGIN
Emp_ID := '&Emp_ID';
Emp_address := showEmpAddress(Emp_ID);
DBMS_OUTPUT.PUT_LINE('The address of '||Emp_ID||' is '||Emp_address||'.');
END;
/


/* Function 2 */
2.This function enables to count the total number of members.

CREATE OR REPLACE FUNCTION countMember
RETURN NUMBER 
IS 
totalMember NUMBER; 
BEGIN 
SELECT count(*) INTO totalMember
FROM Member;
RETURN totalMember; 
END; 
/ 

DECLARE 
total_Member NUMBER; 
BEGIN 
total_Member := countMember; 
DBMS_OUTPUT.PUT_LINE('The total number of the member is '||total_Member||'.'); 
END; 
/
