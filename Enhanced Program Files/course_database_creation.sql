DROP DATABASE IF EXISTS Course_Database;
CREATE DATABASE Course_Database;
USE Course_Database;

DROP TABLE IF EXISTS courses;
CREATE TABLE courses (
	id INT NOT NULL AUTO_INCREMENT,
    course_id VARCHAR(50),
    description VARCHAR(100),
    PRIMARY KEY(id)
);

DROP TABLE IF EXISTS prerequisites;
CREATE TABLE prerequisites (
	id INT NOT NULL AUTO_INCREMENT,
    course_id INT NOT NULL,
    prerequisite_id INT NOT NULL,
    PRIMARY KEY (id),
    FOREIGN KEY (course_id) REFERENCES courses(id),
    FOREIGN KEY (prerequisite_id) REFERENCES courses(id)
);