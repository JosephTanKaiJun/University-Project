/*
INDIVIDUAL ASSIGNMENT SUBMISSION

GROUP NUMBER : G050
PROGRAMME : CS
STUDENT ID : 2206494
STUDENT NAME : TAN KAI JUN
Submission date and time: 16-04-2024

*/



--Query 1 : Retrieve Customer Details by Email
SELECT CustomerName, Address, PhoneNumber
FROM Customer
WHERE Email = 'Lopez0703@gmail.com';

--Query 2 : List Restaurants Open Past 9 PM
SELECT RestaurantName, Address
FROM Restaurant
WHERE OpeningHour LIKE '%- 10:%' OR OpeningHour LIKE '%- 11:%';


--Stored procedure 1 : Add or Update Customer detail
CREATE OR REPLACE PROCEDURE AddCustomer(
    v_Customer_ID IN CHAR,
    v_Member_ID IN CHAR,
    v_CustomerName IN VARCHAR2,
    v_CustomerDOB IN DATE,
    v_PhoneNumber IN VARCHAR2,
    v_Email IN VARCHAR2,
    v_Address IN VARCHAR2)
IS
BEGIN
    INSERT INTO Customer VALUES (v_Customer_ID, v_Member_ID, v_CustomerName, v_CustomerDOB, v_PhoneNumber, v_Email, v_Address);
    COMMIT;
END;
/

--Example
BEGIN
    AddCustomer ('ABC1818168', 'M1616168', 'Tan Kai Jun', TO_DATE('23-04-2003', 'DD-MM-YYYY'), '012-3456789', 'tankaijun@gmail.com', '31900 Kampar, Perak');
END;
/

--Stored procedure 2 : Update Customer Email
CREATE OR REPLACE PROCEDURE UpdateCustomerEmail(
    v_Customer_ID IN CHAR,
    v_NewEmail IN VARCHAR2)
IS
BEGIN
    UPDATE Customer
    SET Email = v_NewEmail
    WHERE Customer_ID = v_Customer_ID;
    COMMIT;
END;
/

--Example
BEGIN
    UpdateCustomerEmail('ABC1818168', 'kaijuntan@gmail.com');
END;
/



--Function 1 : Get Total Revenue for a Restaurant
CREATE OR REPLACE FUNCTION CalculateRestaurantRevenue(v_Restaurant_ID IN CHAR)
    RETURN DECIMAL
IS
    v_Revenue DECIMAL(10,2);
BEGIN
    SELECT SUM(st.SalesAmount)
    INTO v_Revenue
    FROM Restaurant r
    JOIN MenuItem mi ON r.Restaurant_ID = mi.Restaurant_ID
    JOIN Orders o ON mi.MenuItem_ID = o.MenuItem_ID
    JOIN SalesTransaction st ON o.Order_ID = st.Order_ID
    WHERE r.Restaurant_ID = v_Restaurant_ID;
    RETURN v_Revenue;
END;
/

--Example
SELECT RestaurantName, CalculateRestaurantRevenue(Restaurant_ID) AS TotalRevenue
FROM Restaurant
WHERE Restaurant_ID = 'R001';


--Function 2 : Count orders for a customer
CREATE OR REPLACE FUNCTION CountCustomerOrders(v_Customer_ID IN CHAR)
    RETURN INT
IS
    v_Count INT;
BEGIN
    SELECT COUNT(*) INTO v_Count FROM Orders WHERE Customer_ID = v_Customer_ID;
    RETURN v_Count;
END;
/

--Example
SELECT CustomerName, CountCustomerOrders(Customer_ID) AS TotalOrders
FROM Customer
WHERE Customer_ID = 'ABC7832507';