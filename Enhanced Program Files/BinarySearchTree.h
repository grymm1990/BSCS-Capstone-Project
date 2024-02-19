/*
* This class defines the Binary Search Tree (BST) used as a data structure
* for the program, including all functions required to enable full program
* functionality. Additionally, it defines the basic structs used by the BST.
*/

#pragma once
#include <iostream>
#include <algorithm>
#include <vector>

// struct of a course and its defining elements
struct Course {
    std::string courseId = "NONE"; // unique identifier
    std::string title;
    std::vector <std::string> prerequisites;
    bool enabled = true;
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
    Course Search(std::string courseId);
    Node* GetNode(std::string courseId);
    bool ToggleCourse(std::string courseId);
    void ValidateAllCourses();
    void ValidateAllCourses(Node* node);
    int Size();
};