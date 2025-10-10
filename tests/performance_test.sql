-- Performance Test for Database Engine
-- Tests performance with larger datasets

-- Create a large table for performance testing
CREATE TABLE performance_test (id, name, category, value, timestamp)

-- Insert multiple rows to test performance
INSERT performance_test VALUES (1, Item_001, Category_A, 100, 2023-01-01)
INSERT performance_test VALUES (2, Item_002, Category_B, 200, 2023-01-02)
INSERT performance_test VALUES (3, Item_003, Category_A, 150, 2023-01-03)
INSERT performance_test VALUES (4, Item_004, Category_C, 300, 2023-01-04)
INSERT performance_test VALUES (5, Item_005, Category_B, 250, 2023-01-05)
INSERT performance_test VALUES (6, Item_006, Category_A, 175, 2023-01-06)
INSERT performance_test VALUES (7, Item_007, Category_C, 400, 2023-01-07)
INSERT performance_test VALUES (8, Item_008, Category_B, 225, 2023-01-08)
INSERT performance_test VALUES (9, Item_009, Category_A, 125, 2023-01-09)
INSERT performance_test VALUES (10, Item_010, Category_C, 350, 2023-01-10)

-- Test various query patterns
SELECT * FROM performance_test
SELECT * FROM performance_test WHERE category = Category_A
SELECT * FROM performance_test WHERE value = 200
SELECT * FROM performance_test ORDER BY value
SELECT * FROM performance_test ORDER BY name

-- Test updates on larger dataset
UPDATE performance_test SET value = 500 WHERE category = Category_C
SELECT * FROM performance_test WHERE category = Category_C

-- Test deletes
DELETE FROM performance_test WHERE value = 100
SELECT * FROM performance_test ORDER BY id

EXIT