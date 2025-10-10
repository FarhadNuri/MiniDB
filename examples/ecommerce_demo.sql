-- E-commerce Database Demo
-- Demonstrates an online store management system

-- Create e-commerce tables
CREATE TABLE customers (id, name, email, city, signup_date)
CREATE TABLE products (id, name, price, stock, category)
CREATE TABLE orders (id, customer_id, product_id, quantity, order_date)

-- Insert customer data
INSERT customers VALUES (1, John_Doe, john@email.com, New_York, 2023-01-15)
INSERT customers VALUES (2, Jane_Smith, jane@email.com, Los_Angeles, 2023-02-20)
INSERT customers VALUES (3, Mike_Johnson, mike@email.com, Chicago, 2023-03-10)
INSERT customers VALUES (4, Sarah_Wilson, sarah@email.com, Houston, 2023-04-05)

-- Insert product data
INSERT products VALUES (101, iPhone_14, 999, 50, Electronics)
INSERT products VALUES (102, MacBook_Pro, 1999, 25, Electronics)
INSERT products VALUES (103, Nike_Shoes, 120, 100, Fashion)
INSERT products VALUES (104, Coffee_Maker, 89, 75, Home)
INSERT products VALUES (105, Bluetooth_Speaker, 79, 60, Electronics)

-- Insert order data
INSERT orders VALUES (1, 1, 101, 1, 2023-05-01)
INSERT orders VALUES (2, 2, 102, 1, 2023-05-02)
INSERT orders VALUES (3, 1, 103, 2, 2023-05-03)
INSERT orders VALUES (4, 3, 104, 1, 2023-05-04)
INSERT orders VALUES (5, 4, 105, 1, 2023-05-05)

-- Business queries
SELECT * FROM products WHERE category = Electronics ORDER BY price
SELECT * FROM customers WHERE city = New_York
SELECT * FROM orders WHERE customer_id = 1

-- Inventory management
UPDATE products SET stock = 45 WHERE id = 101
UPDATE products SET price = 1899 WHERE name = MacBook_Pro

-- Customer analysis
SELECT * FROM customers ORDER BY signup_date
SELECT * FROM orders ORDER BY order_date

-- Product analysis
SELECT * FROM products WHERE stock < 30
SELECT * FROM products ORDER BY price

EXIT