-- Advanced Database Operations Test
-- This file tests complex scenarios and edge cases

-- Create multiple tables
CREATE TABLE products (id, name, price, category)
CREATE TABLE orders (id, product_id, quantity, customer)

-- Insert product data
INSERT products VALUES (1, Laptop, 999.99, Electronics)
INSERT products VALUES (2, Mouse, 29.99, Electronics)
INSERT products VALUES (3, Desk, 199.99, Furniture)
INSERT products VALUES (4, Chair, 149.99, Furniture)

-- Insert order data
INSERT orders VALUES (1, 1, 2, John)
INSERT orders VALUES (2, 2, 5, Alice)
INSERT orders VALUES (3, 1, 1, Bob)
INSERT orders VALUES (4, 3, 1, Alice)

-- Test complex queries
SELECT * FROM products ORDER BY price
SELECT * FROM products WHERE category = Electronics
SELECT * FROM orders WHERE customer = Alice

-- Test updates with conditions
UPDATE products SET price = 899.99 WHERE name = Laptop
SELECT * FROM products WHERE name = Laptop

-- Test multiple operations
UPDATE orders SET quantity = 3 WHERE customer = John
DELETE FROM products WHERE category = Furniture
SELECT * FROM products
SELECT * FROM orders

-- Test edge cases
CREATE TABLE empty_table (col1, col2)
SELECT * FROM empty_table

EXIT