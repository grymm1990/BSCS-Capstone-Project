#include "AdvisingProgram.h"

AdvisingProgram::AdvisingProgram() 
{
    ticks = clock();
}

void AdvisingProgram::executeProgram(sql::Connection* conn)
{
    //Initialize all variables
    BinarySearchTree* courses = new BinarySearchTree();
    bool coursesLoaded = false;
    std::string input;
    int choice = 0;

    //Main Loop
    while (choice != 9)
    {
        //print out main menu
        std::cout << std::endl << "  1. Load From Database." << std::endl;
        std::cout << "  2. Print Course List." << std::endl;
        std::cout << "  3. Print Course." << std::endl;
        std::cout << "  4. Add Course." << std::endl;
        std::cout << "  5. Disable/Enable Course." << std::endl;
        std::cout << "  6. Run Course Validation." << std::endl;
        std::cout << "  9. Exit" << std::endl << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> input;

        //input validation - check that input is a numerical value
        if (!isNumeric(input))
        {
            std::cout << input << " is not a valid option." << std::endl;
            continue;
        }
        else choice = stoi(input);

        switch (choice)
        {
        case 1:
            //Load Data Structure
            
            // Initialize a timer variable before loading courses
            ticks = clock();

            courses = new BinarySearchTree();
            loadCourses(conn, courses);
            coursesLoaded = true;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            std::cout << "time: " << ticks << " clock ticks" << std::endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
            break;

        case 2:
            //Print Course List
            if (!coursesLoaded)
            {
                std::cout << "Please load course data structure first." << std::endl;
                continue;
            }
            // Initialize a timer variable before printing courses
            ticks = clock();

            courses->PrintInOrder();

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            std::cout << "time: " << ticks << " clock ticks" << std::endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
            break;

        case 3:
            //Search for and Print Single Course
            
            searchAndPrintCourse(courses);
            break;

        case 4:
            //Add New Course
            addCourse(conn, courses);
            break;

        case 5:
            toggleCourse(courses);
            break;

        case 6:
            //Course Validation

            // Initialize a timer variable before validating courses
            ticks = clock();

            courses->ValidateAllCourses();

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            std::cout << "time: " << ticks << " clock ticks" << std::endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
            break;

        case 9:
            //exit program
            break;

        default:
            //input validation
            std::cout << choice << " is not a valid option." << std::endl;
            break;
        }
    }
    std::cout << "Thank you for using the course planner!" << std::endl;
}

bool AdvisingProgram::isNumeric(std::string str)
{
    for (unsigned int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}

//function to break up line into substrings using deliminator character
void AdvisingProgram::tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void AdvisingProgram::loadCourses(sql::Connection* conn, BinarySearchTree* courses)
{
    std::cout << "Loading from database..." << std::endl;

    sql::PreparedStatement* prepStatement;
    sql::ResultSet* result;

    // query to load courses from db
    prepStatement = conn->prepareStatement("SELECT * FROM course_database.courses");
    result = prepStatement->executeQuery();

    while (result->next())
    {
        Course course;

        course.courseId = result->getString(2);
        course.title = result->getString(3);

        //Check courses to ensure this course is not already present
        Course searchCourse = courses->Search(course.courseId);

        //course id will be "NONE" if the search did not find the input
        //if a course with the current ID was not found, add course to tree
        if (searchCourse.courseId == "NONE") courses->Insert(course);
    }

    // query to load prerequisites from db
    prepStatement = conn->prepareStatement("SELECT t1.course_id, t2.course_id FROM course_database.prerequisites t "
                                           "JOIN course_database.courses t1 ON t.course_id = t1.id "
                                           "JOIN course_database.courses t2 ON t.prerequisite_id = t2.id");
    result = prepStatement->executeQuery();

    while (result->next())
    {
        Node* searchNode = courses->GetNode(result->getString(1));

        if (searchNode != NULL)
        {
            searchNode->course.prerequisites.push_back(result->getString(2));
        }
    }

    delete prepStatement;
    delete result;
    
    std::cout << courses->Size() << " courses loaded." << std::endl;
}

void AdvisingProgram::searchAndPrintCourse(BinarySearchTree* courses)
{
    std::string searchString;
    Course searchCourse;

    std::cout << "What course do you want to know about? ";
    std::cin >> searchString;

    // Initialize a timer variable before loading courses
    ticks = clock();

    searchCourse = courses->Search(searchString);
    
    //course id will be "NONE" if the search did not find the input
    if (searchCourse.courseId == "NONE") std::cout << "Course not found." << std::endl;

    //course found; print the relevant information
    else
    {
        std::cout << searchCourse.courseId << ", " << searchCourse.title << std::endl;

        std::cout << "Prerequisites:";
        if (searchCourse.prerequisites.empty()) std::cout << "None" << std::endl;
        else
        {
            for (unsigned int i = 0; i < searchCourse.prerequisites.size(); i++)
            {
                std::cout << " " << searchCourse.prerequisites.at(i);
                if (i < searchCourse.prerequisites.size() - 1) std::cout << ",";
            }
            std::cout << std::endl;
        }
    }
    // Calculate elapsed time and display result
    ticks = clock() - ticks; // current clock ticks minus starting clock ticks
    std::cout << "time: " << ticks << " clock ticks" << std::endl;
    std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;

}

void AdvisingProgram::addCourse(sql::Connection* conn, BinarySearchTree* courses)
{
    std::string input;
    Course newCourse;
    int prerequisiteCount = 0;
    std::string prereqId;

    sql::PreparedStatement* prepStatement;
    sql::ResultSet* result;

    //Build new course based on user input
    std::cout << "Enter new course ID (ex: CSCI100): ";
    std::cin >> newCourse.courseId;

    //Check that new course ID is not already used in the database
    prepStatement = conn->prepareStatement("SELECT COUNT(*) FROM course_database.courses WHERE course_id = ?");
    prepStatement->setString(1, newCourse.courseId);
    result = prepStatement->executeQuery();

    if (result->next() != 0)
    {
        std::cout << "Course ID already exists." << std::endl;
        return;
    }

    std::cout << "Enter new course description (ex: Introduction to Computer Science): ";
    std::cin >> newCourse.title;
    std::cout << "Enter number of prerequisite courses: ";
    std::cin >> prerequisiteCount;
    
    for (int i = 0; i < prerequisiteCount; i++)
    {
        
        std::cout << "Enter prerequisite #" << i << " description (ex: MATH201): ";
        std::cin >> prereqId;

        // query to check that entered prerequisite course exists in the database
        prepStatement = conn->prepareStatement("SELECT COUNT(*) FROM course_database.courses WHERE course_id = ?");
        prepStatement->setString(1, prereqId);
        result = prepStatement->executeQuery();

        if (result->next() != 0)
        {
            newCourse.prerequisites.push_back(prereqId);
        }
        else
        {
            std::cout << "Course ID not found." << std::endl;
            return;
        }
    }

    std::cout << "Summary:" << std::endl;
    std::cout << newCourse.courseId << ", " << newCourse.title << std::endl;

    std::cout << "Prerequisites:";
    if (newCourse.prerequisites.empty()) std::cout << "None" << std::endl;
    else
    {
        for (unsigned int i = 0; i < newCourse.prerequisites.size(); i++)
        {
            std::cout << " " << newCourse.prerequisites.at(i);
            if (i < newCourse.prerequisites.size() - 1) std::cout << ",";
        }
        std::cout << std::endl;
    }

    std::cout << "Add course? (1. Yes, 2. Cancel): ";
    std::cin >> input;
    int choice; 

    if (!isNumeric(input))
    {
        std::cout << input << " is not a valid option." << std::endl;
        return;
    }
    else choice = stoi(input);

    switch (choice)
    {
    case 1:
        courses->Insert(newCourse);
        prepStatement = conn->prepareStatement("INSERT INTO course_database.courses (course_id, description) VALUES (?, ?)");
        prepStatement->setString(1, newCourse.courseId);
        prepStatement->setString(2, newCourse.title);
        prepStatement->execute();

        for (unsigned int i = 0; i < newCourse.prerequisites.size(); i++)
        {
            prepStatement = conn->prepareStatement("INSERT INTO course_database.prerequisites (course_id, prerequisite_id) "
                                                   "VALUES ( (SELECT id FROM course_database.courses WHERE course_id = ?), (SELECT id FROM course_database.courses WHERE course_id = ?) )");
            prepStatement->setString(1, newCourse.courseId);
            prepStatement->setString(2, newCourse.prerequisites.at(i));
            prepStatement->execute();
        }
        std::cout << std::endl;

        break;
    case 2:
        break;
    default:
        break;
    }
}

void AdvisingProgram::toggleCourse(BinarySearchTree* courses)
{
    std::string searchString;

    std::cout << "Enter course ID: ";
    std::cin >> searchString;

    //course id will be "NONE" if the search did not find the input
    if (courses->ToggleCourse(searchString))
    {
        std::cout << searchString << " Toggled." << std::endl;
    }
    else {
        std::cout << "Course not found." << std::endl;
    }

}