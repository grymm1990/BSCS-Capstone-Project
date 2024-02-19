/*
* This class defines the primary program logic as well
* as ancillary functions used by the program
*/

#pragma once
#include "BinarySearchTree.h"
#include <sstream>
#include <fstream>
#include <time.h>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class AdvisingProgram
{
public:
    AdvisingProgram();
    void executeProgram(sql::Connection* conn);
    bool isNumeric(std::string str);
    void tokenize(std::string const& str, const char delim, std::vector<std::string>& out);
    void loadCourses(sql::Connection* conn, BinarySearchTree* courses);
    void searchAndPrintCourse(BinarySearchTree* courses);
    void addCourse(sql::Connection* conn, BinarySearchTree* courses);
    void toggleCourse(BinarySearchTree* courses);
    clock_t ticks;
};