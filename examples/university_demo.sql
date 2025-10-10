-- University Database Demo
-- Demonstrates a complete university management scenario

-- Create tables for university system
CREATE TABLE students (id, name, major, gpa, year)
CREATE TABLE courses (id, name, credits, department)
CREATE TABLE enrollments (student_id, course_id, grade, semester)

-- Insert student data
INSERT students VALUES (1001, John_Smith, Computer_Science, 3.8, Junior)
INSERT students VALUES (1002, Alice_Johnson, Mathematics, 3.9, Senior)
INSERT students VALUES (1003, Bob_Wilson, Physics, 3.6, Sophomore)
INSERT students VALUES (1004, Carol_Brown, Computer_Science, 3.7, Junior)

-- Insert course data
INSERT courses VALUES (CS101, Intro_to_Programming, 3, Computer_Science)
INSERT courses VALUES (CS201, Data_Structures, 4, Computer_Science)
INSERT courses VALUES (MATH301, Calculus_III, 4, Mathematics)
INSERT courses VALUES (PHYS201, Quantum_Physics, 3, Physics)

-- Insert enrollment data
INSERT enrollments VALUES (1001, CS101, A, Fall2023)
INSERT enrollments VALUES (1001, CS201, B+, Fall2023)
INSERT enrollments VALUES (1002, MATH301, A, Fall2023)
INSERT enrollments VALUES (1003, PHYS201, A-, Fall2023)
INSERT enrollments VALUES (1004, CS101, A-, Fall2023)

-- Query examples
SELECT * FROM students ORDER BY gpa
SELECT * FROM students WHERE major = Computer_Science
SELECT * FROM courses WHERE department = Computer_Science
SELECT * FROM enrollments WHERE grade = A

-- Update student information
UPDATE students SET year = Senior WHERE name = Bob_Wilson
UPDATE students SET gpa = 3.85 WHERE id = 1001

-- Show final results
SELECT * FROM students ORDER BY name
SELECT * FROM enrollments ORDER BY student_id

EXIT