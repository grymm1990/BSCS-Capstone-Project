// Enhancement 2 - Data Structures and Algorithms - Assessment
// 
// Execution of the various functions is done in order to suit the needs of the function and 
// to minimize execution times. In the interests of optimization, all functionality has been
// minimized to the code requireed to meet function definitions.
// In the cases of PrintInOrder() and the outer loop of ValidateAllCourses(), execution must 
// iterate through all items; therefore, a time complexity of O(n) is the only case possible. 
// In the case of Insert(), Search() and ToggleCourse(), the worst-case would be O(log n).
// The inner loop of ValidateAllCourses() also utilizes the Search() function, but once per
// prerequisite of the given course. While there is no hard limit on prerequisites, it is unlikely
// this number would exceed 4. This puts the time complexity of this loop as O(log n) if the 
// linear factor is dropped, resulting in a worse-case time complexity for ValidateAllCourses() 
// of O(log log n).


#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() {}

// Print all course ID's and descriptions
void BinarySearchTree::PrintInOrder()
{
    PrintInOrder(root);
}

// Recursive exectution of the BST using passed node reference
void BinarySearchTree::PrintInOrder(Node* node)
{
    //do nothing if the current node is null
    if (node == nullptr) return;

    //recursively print the left subtree, if it exists
    PrintInOrder(node->leftChild);

    //print the current node information
    std::string status = "";
    if (!node->course.enabled) status = " (DISABLED)";

    std::cout << node->course.courseId << ", " << node->course.title << status << std::endl;

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

Node* BinarySearchTree::GetNode(std::string courseId)
{
    Node* current = root;

    //localize courseId search and make all characters uppercase
    std::string str = courseId;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);

    //search for node
    while (current != nullptr)
    {
        // if node found
        if (str == current->key) return current;

        // if courseId than key, search left
        else if (str < current->key) current = current->leftChild;

        // else search right
        else current = current->rightChild;
    }

    return NULL; // node not found
}

bool BinarySearchTree::ToggleCourse(std::string courseId)
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
        if (str == current->key)
        {
            //toggle enabled flag and return success
            current->course.enabled = !current->course.enabled;
            return true;
        }
        // if courseId than key, search left
        else if (str < current->key) current = current->leftChild;

        // else search right
        else current = current->rightChild;
    }

    return false; // node not found, return failure
}

// Validate all course prerequisites exist
void BinarySearchTree::ValidateAllCourses()
{
    ValidateAllCourses(root);
}

// Recursive exectution of the BST using passed node reference
void BinarySearchTree::ValidateAllCourses(Node* node)
{
    //do nothing if the current node is null
    if (node == nullptr) return;

    //recursively validate the left subtree, if it exists
    ValidateAllCourses(node->leftChild);

    //if course enabled, check that all prerequisites exist
    if (node->course.enabled)
    { 
        for (int i = 0; i < node->course.prerequisites.size(); i++)
        {
            Course prereqCourse = Search(node->course.prerequisites.at(i));
            bool prerequisiteFoundAndEnabled = prereqCourse.courseId != "NONE" && prereqCourse.enabled;
            if (prerequisiteFoundAndEnabled)
            {
                std::cout << node->course.courseId << " VALIDATED." << std::endl;
            }
            else {
                std::cout << "PREREQUISITE MISSING - Course: " << node->course.courseId << " Prerequisite: " << node->course.prerequisites.at(i) << std::endl;
            }
        }
    }

    //recursively validate the right subtree, if it exists
    ValidateAllCourses(node->rightChild);
}

int BinarySearchTree::Size()
{
    return size;
}