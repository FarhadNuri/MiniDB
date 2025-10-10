-- Basic Database Operations Test
-- This file tests fundamental CRUD operations

-- Create a users table
CREATE TABLE users (id, name, email, age)

-- Insert test data
INSERT users VALUES (1, Alice, alice@email.com, 25)
INSERT users VALUES (2, Bob, bob@email.com, 30)
INSERT users VALUES (3, Charlie, charlie@email.com, 28)
INSERT users VALUES (4, Diana, diana@email.com, 22)

-- Test SELECT operations
SELECT * FROM users
SELECT * FROM users WHERE name = Alice
SELECT * FROM users WHERE age = 30

-- Test UPDATE operations
UPDATE users SET age = 26 WHERE name = Alice
SELECT * FROM users WHERE name = Alice

-- Test DELETE operations
DELETE FROM users WHERE name = Charlie
SELECT * FROM users

-- Test ORDER BY
SELECT * FROM users ORDER BY name
SELECT * FROM users ORDER BY age

EXIT