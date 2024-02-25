/* ABCU Advising Program Enhanced
* Author: Nicholas Hahn
* Date: 1/28/2024
* Last Updated: 2/11/2024
*
* Program created to store courses for the CS department at ABCU
* to assist in admissions and administrative functions.
*   
* 
* Enhancement  1 - Software Design and Engineering
* This first enhancement is focused on improvements to the design
* and engineering aspects of the program. The primary improvements
* were focused on breaking up the initial monolithic code file into
* separate program files with header files.
* 
* Additionally, some functionality in the main loop was broken out
* to functions to make the main loop function more readable.
* 
* Program logic was also broken out to a separate class (AdvisingProgram)
* to keep the main program entry point (main) clean.
* 
* 
* Enchancement 2 - Databases
* This enhancement establishes connection to and integration with a MySQL 
* database. This database provides storage of all courses and a means of 
* logging course dependencies using relational database principles.
* 
* The following functions have been altered:
*   - main(): added db connection and validation catch
*   - AdvisingProgram::executeProgram(): Load Data Structure renamed Load From 
      Database. Each load now wipes the BST before rebuilding off of db entries.
*   - AdvisingProgram::loadCourses(): loading mechanism now pulls courses and 
*     prerequisites from the MySQL database.
*   - AdvisingProgram::addCourse(): new validations for new course and prerequisites
*     now query the database to ensure they don't exist and exist, respectively. 
*     Additionally, the insertion now adds the new course to the database as well as 
*     the BST.
* 
* The following function has been added:
*   - connectAndValidateUser(): this function provides a credential validation gate for 
*     the program to run based on whether or not the user-provided credentials are valid
*     in the database.
*   - BinarySearchTree::GetNode(): this function works the same as the Search() function,
*     except that it returns the Node* the course is attached to. This was required to 
*     facilitate setting Course.prerequisites during loading.
*/

#include "AdvisingProgram.h"
#include <conio.h>

const std::string SERVER = "tcp://127.0.0.1:3306";

sql::Connection* getDBConnection()
{
    sql::Driver* driver;
    std::string user, pass;
    sql::Connection* conn;
    char ch;
    const char ENTER = 13;

    //print header and prompt user for credentials
    std::cout << "Welcome to the Course Planner. Please enter database credentials." << std::endl << std::endl;
    std::cout << "Username: ";
    std::cin >> user;
    std::cout << "Password: ";

    // basic password obfuscation in interface
    while ((ch = _getch()) != ENTER)
    {
        pass += ch;
        std::cout << '*';
    } 
    std::cout << std::endl;

    try
    {
        driver = get_driver_instance();
        conn = driver->connect(SERVER, user, pass);
        std::cout << "Server Connection Validated!" << std::endl;
        return conn;
    }
    catch (sql::SQLException e)
    {
        std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
        system("pause");
        exit(1);
    }
}

// Main Program entry
int main(int argc, char* argv[])
{
    
    // Instantiation of the main AdvisingProgram class
    AdvisingProgram* program = new AdvisingProgram();

    // database connection and validation
    sql::Connection* conn = getDBConnection();
    
    if (conn != NULL)
    {
        program->executeProgram(conn);

        conn->close();
        delete conn;
    }
    return 0;
}