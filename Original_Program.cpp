
/* ABCU Advising Program
* Author: Nicholas Hahn
* Date: 4/15/2022
*
* Program created to store courses for the CS department at ABCU
* to assist in admissions and administrative functions.
*
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>
#include "AdvisingProgram.h"

// define structure to hold course information
struct Course {
    std::string courseId = "NONE"; // unique identifier
    std::string title;
    std::vector <std::string> prerequisites;
};

// internal structure for tree node
struct Node {
    Course course;
    std::string key = "";
    Node* rightChild = nullptr;
    Node* leftChild = nullptr;

    Node() {}

    Node(Course course)
    {
        this->course = course;
        key = course.courseId;
    }
};

class BinarySearchTree
{
    int size = 0;

private:
    Node* root = nullptr;

public:
    BinarySearchTree();
    void PrintInOrder();
    void PrintInOrder(Node* node);
    void Insert(Course course);
    Course Search(std::string bidId);
    int Size();
};

BinarySearchTree::BinarySearchTree() {}

void BinarySearchTree::PrintInOrder()
{
    PrintInOrder(root);
}

void BinarySearchTree::PrintInOrder(Node* node)
{
    //do nothing if the current node is null
    if (node == nullptr) return;

    //recursively print the left subtree, if it exists
    PrintInOrder(node->leftChild);

    //print the current node information
    std::cout << node->course.courseId << ", " << node->course.title << std::endl;

    //recursively print the right subtree, if it exists
    PrintInOrder(node->rightChild);
}

void BinarySearchTree::Insert(Course course)
{
    //create new node from bid
    Node* newNode = new Node(course);

    // if root equal to null ptr, insert newNode as root
    if (root == nullptr) root = newNode;

    //otherwise, recursively find insert point
    else
    {
        //start at the root
        Node* currentNode = root;
        while (currentNode != nullptr)
        {
            //if key is less than current key, go left
            if (newNode->key < currentNode->key)
            {
                // if left is null, insert there and exit loop
                if (currentNode->leftChild == nullptr)
                {
                    currentNode->leftChild = newNode;
                    currentNode = nullptr;
                }
                //otherwise, change current node to that child and repeat
                else currentNode = currentNode->leftChild;
            }
            //otherwise, go right
            else
            {
                // if right is null, insert there and exit loop
                if (currentNode->rightChild == nullptr)
                {
                    currentNode->rightChild = newNode;
                    currentNode = nullptr;
                }
                //otherwise, change current node to that child and repeat
                else currentNode = currentNode->rightChild;
            }
        }

    }
    size++;
}

Course BinarySearchTree::Search(std::string courseId)
{
    Course course;
    //initialize at root
    Node* current = root;

    //localize courseId search and make all characters uppercase
    std::string str = courseId;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    //search for node
    while (current != nullptr)
    {
        // if node found
        if (str == current->key) return current->course;

        // if courseId than key, search left
        else if (str < current->key) current = current->leftChild;

        // else search right
        else current = current->rightChild;
    }

    return course; // node not found
}

int BinarySearchTree::Size()
{
    return size;
}

//check if string is a numerical value
bool isNumeric(std::string str)
{
    for (unsigned int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false; //when one non numeric value is found, return false
    return true;
}

//function to break up line into substrings using deliminator character
void tokenize(std::string const& str, const char delim, std::vector<std::string>& out)
{
    size_t start;
    size_t end = 0;

    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

void loadCourses(std::string csvPath, BinarySearchTree* courses) {
    std::cout << "Loading CSV file " << csvPath << "..." << std::endl;

    std::vector<std::string> lines;

    std::string line;
    std::ifstream file(csvPath);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }

    //for each line from the input file
    for (unsigned int i = 0; i < lines.size(); i++)
    {
        //generate vector of strings by deliminating the line
        std::vector<std::string> out;
        tokenize(lines.at(i), ',', out);

        //if size of the vector is less than 2, the line was not formatted correctly
        if (out.size() < 2)
        {
            std::cout << "Invalid line found in course file: " << std::endl;
            std::cout << lines.at(i) << std::endl;
            continue;
        }

        //Generate Course from line data
        Course course;

        course.courseId = out.at(0);
        course.title = out.at(1);

        //loop through prerequisites and add
        for (unsigned int j = 2; j < out.size(); j++)
        {
            course.prerequisites.push_back(out.at(j));
        }

        // add course to tree
        courses->Insert(course);
    }
    std::cout << courses->Size() << " courses loaded." << std::endl;
}

int main(int argc, char* argv[])
{
    // process command line arguments
    std::string csvPath;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "Courses.csv";
    }

    //print header
    std::cout << "Welcome to the Course Planner." << std::endl;

    // Define a timer variable
    clock_t ticks;

    // Define and initialize an empty binary search tree
    BinarySearchTree* courses = new BinarySearchTree();

    bool coursesLoaded = false;
    Course searchCourse;
    std::string searchString;
    std::string input;
    int choice = 0;

    while (choice != 9)
    {
        searchString = "";
        //print out main menu
        std::cout << std::endl << "  1. Load Data Structure." << std::endl;
        std::cout << "  2. Print Course List." << std::endl;
        std::cout << "  3. Print Course." << std::endl;
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

            courses = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadCourses(csvPath, courses);
            coursesLoaded = true;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            std::cout << "time: " << ticks << " clock ticks" << std::endl;
            std::cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << std::endl;
            break;
            break;

        case 2:
            //Print Course List
            if (!coursesLoaded)
            {
                std::cout << "Please load course data structure first." << std::endl;
                continue;
            }
            courses->PrintInOrder();
            break;

        case 3:
            //Print Course
            if (!coursesLoaded)
            {
                std::cout << "Please load course data structure first." << std::endl;
                continue;
            }
            std::cout << "What course do you want to know about? ";
            std::cin >> searchString;

            //search for course with input-matching id
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
            break;

        case 9:
            //exit program
            break;

        default:
            //input validation - digit is not a specified option
            std::cout << choice << " is not a valid option." << std::endl;
            break;
        }
    }

    std::cout << "Thank you for using the course planner!" << std::endl;

    return 0;
}