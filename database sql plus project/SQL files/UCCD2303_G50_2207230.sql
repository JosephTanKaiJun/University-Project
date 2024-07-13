GROUP NUMBER : G50
PROGRAMME : CS
STUDENT ID : 2207230
STUDENT NAME : HO KAH MUN
Submission date and time: 16-4-2024

/* Query 1 */
1.Find the total amount of payment of each customer 

SELECT CustomerName, 'RM'||to_char(max(amount),'9999.99') AS "TOTAL"
FROM customer c, payment p
WHERE c.customer_id=p.customer_id
GROUP by CustomerName
ORDER by 2;



/* Query 2 */
2.Display the employee_ID and employee name who live in Penang

SELECT employee_ID AS "ID" , (FirstName||' '||LastName) AS "Employee Name"
FROM employee
WHERE address LIKE '%Penang';



/* Stored procedure 1 */
1.  Modify the price of menu item by using the ID of menu item if the current price of food has dropped or rised.

CREATE OR REPLACE PROCEDURE updateMenuItemPrice
(
id in INT, 
current_price IN NUMBER
)
IS
BEGIN
UPDATE menuitem
SET price=current_price
WHERE MenuItem_id=id;
COMMIT;
END;
/

EXECUTE updateMenuItemPrice('007', 25.00);



/* Stored procedure 2 */
2. This procedure is used to update the position of the Employee

CREATE OR REPLACE PROCEDURE update_emp_position
 (
Emp_id IN VARCHAR2,
positionId IN VARCHAR2
)
IS
BEGIN
Update Employee
SET Position_ID = positionId
WHERE Employee_ID = Emp_id;
COMMIT;
END;
 /

EXECUTE update_emp_position('E7810','P002');



/* Function 1 */
1. Function helps to calculate the average payment.

SET SERVEROUTPUT ON
CREATE OR REPLACE FUNCTION CalPaymentAvg
RETURN VARCHAR2
IS
averagePayment VARCHAR2(10);
BEGIN
SELECT to_char(AVG(amount),'999.99') 
INTO averagePayment 
FROM Payment;
RETURN averagePayment;
END;
/
 

DECLARE
average_payment VARCHAR2(10);
BEGIN
average_payment := CalPaymentAvg();
DBMS_OUTPUT.PUT_LINE('The average of all the payment amount is RM'||average_payment);
END;
/


/* Function 2 */
2. This function is used to find the position of the employees.

CREATE OR REPLACE FUNCTION findposition
(
P_EmpID VARCHAR2
)
RETURN VARCHAR2
IS
E_Position VARCHAR2(100);
BEGIN
SELECT PositionName
INTO E_Position
FROM Employee e, Position p
WHERE e.Position_ID = p.Position_ID
AND Employee_ID = P_EmpID;
RETURN E_Position;
END;
/
 
SET SERVEROUTPUT ON
DECLARE
E_ID CHAR(5);
E_PositionName VARCHAR2(100);
BEGIN
E_ID := '&E_ID';
E_PositionName := findposition(E_ID);
DBMS_OUTPUT.PUT_LINE(chr(10));
DBMS_OUTPUT.PUT_LINE('The position of the employee ID '||E_ID||' is '||E_PositionName||'.');
END;
/
