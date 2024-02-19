# grymm1990.github.io

**OVERVIEW/SUMMARY**




--------------------------------------------------------------------------------------------------
**TABLE OF CONTENTS**
1. Professional Self-Assessment
2. Code Review
3. Enhancement 1: Software Design and Engineering
4. Enhancement 2: Algorithms and Data Structures
5. Enhancement 3: Databases


--------------------------------------------------------------------------------------------------
**1. PROFESSIONAL SELF-ASSESSMENT**

--------------------------------------------------------------------------------------------------
**2. CODE REVIEW**
https://youtu.be/8deYG7kNByo


--------------------------------------------------------------------------------------------------
**3. ENHANCEMENT 1: Software Design and Engineering**

**ARTIFACT SELECTION**
- **Artifact:** ABCU Advising Program
- **Description:** This program provides course list storage for the CS department at ABCU (fictional) to assist with admissions and administrative functions.
- **Justification:**  This artifact was included for the opportunity it provided for holistic application development and iterative improvement. As a complete application with all code available and minimal external library dependency, exercises in improvement would be easily comprehensible and understandable. Additionally, the initial state of the program (monolithic code) provided an excellent opportunity to exemplify program code structures and the interaction between multiple files and data structures.

**PROCESS**<br>
**Course Outcome Exemplified: #4 - Demonstrate an ability to use well-founded and innovative techniques, skills, and tools in computing practices for the purpose of implementing computer solutions that deliver value and accomplish industry-specific goals**<br>
Exemplification of this outcome is accomplished via the targeted implementation of a computer solution to the goal specified by the purpose of the program. Well-founded techniques were employed to do so, including the use of header and source files, formatted and standardized code and code structures. Individual functional components were abstracted out to human-readable functions, allowing the program’s sequence of events to be more self-evident. This facilitates future development and interpretation by future developers responsible for maintenance and improvements.<br><br>
**How artifact was improved:**
- The major class of BinarySearchTree was broken out to its own source and header files. The required structs of Node and Course were also relocated to the BinarySearchTree source file for proximal use.
- An additional class titled AdvisingProgram was created. All ancillary functions for the program were relocated here. Additionally, a main function titled executeProgram() was created to encompass the primary program loop. The remaining functionality in the primary source file has been reduced down to initial argument parsing, instantiation of the AdvisingProgram object, and execution of the main function.
- In order to further break down the main loop, the function of SearchAndPrintCourse() was added and the associated code was extracted.
- Library inclusions for the program were relocated to the baseline location requiring them. Any subsequent locations where these libraries are referenced are able to pull them via inclusion of the primary file.
By performing the actions above, the resulting code base is organized, more modular, and easier to interpret and understand.<br><br>
**Reflection**<br>
I found the refactoring process to be highly rewarding. While I had a certain sense of cleanliness initially building the program as one file, this excluded the prospects of enhancement or refactoring at the time. With that mechanism in place, the new code is much more organized. Not only do I find the new structure easier to visualize, the groundwork is now laid for the other enhancements pending on this artifact.<br>
Major challenges encountered during the refactoring included language-specific requirements for class structures and the use of pointers and references in a few new locations to facilitate functional operation.<br>
The result of execution has been a deeper understanding of the language used (C++) and a greater appreciation for planning out programming projects ahead of code implementation to facilitate future development.

--------------------------------------------------------------------------------------------------
**4. ENHANCEMENT 2: Algorithms and Data Structures**

**ARTIFACT SELECTION**
- **Artifact:** ABCU Advising Program
- **Description:** This program provides course list storage for the CS department at ABCU (fictional) to assist with admissions and administrative functions.
- **Justification:**  This artifact was included for the opportunity it provided for holistic application development and iterative improvement. As a complete application with all code available and minimal external library dependency, exercises in improvement would be easily comprehensible and understandable. In addition, this program was originally built to exemplify the use of flexible and efficient data structures; specifically the Binary Search Tree (BST) in this case. By adding new functionality and improving on existing functionality, the high performance of the BST could be either reinforced or invalidated.

**PROCESS**<br>
**Course Outcome Exemplified: #3 - Design and evaluate computing solutions that solve a given problem using algorithmic principles and computer science practices and standards appropriate to its solution, while managing the trade-offs involved in design choices**<br>
Exemplification of this outcome is accomplished via utilization of new purpose-built algorithms as well as the integration of existing logic within the program. Utilizing the concepts of abstraction and modularity, well-defined functions are created which support implementation of the intended functions while minimizing duplication of code or obfuscation of code functionality. Given that some functions would be redundant, overly convoluted or run contrary to the original purpose of the program, any function that fits these descriptors was not included, thereby exemplifying the management of trade-offs.<br><br>
**How artifact was improved:**<br>
Three new functions were added to the main menu of the program: 
- Add Course: This function allows the insertion of individual courses to the BST in active memory by defining the Course ID, Description, and Prerequisite Courses. Validation logic is included to preclude the insertion of Course ID’s already present in the tree utilizing existing search functionality. 
- Disable/Enable Course: This function allows the user to search for an existing Course ID and toggle the new “enabled” parameter in the Course data structure.
- Run Course Validation: This function iterates through the entire BST, validating that each prerequisite of each course is present and enabled using the preexisting Search functionality.. Any exceptions to this are noted.
Boolean value “enabled” was added to the Course struct to allow courses to be disabled at will without affecting the active memory data structure (future work with Database inclusion may facilitate a rebuilding of the BST if and when appropriate).
The function for loading data from a CSV file has been modified to check for the existence of a Course ID prior to insertion into the BST. This ensures that no duplicate Course ID’s are inserted while allowing the individual addition of courses to occur before or after the bulk data insertion of this function.<br>
Execution timers/tick counters added to the following functions:
- Printing of full course list
- Printing of individual courses<br><br>

**Course Validation**
- **Optimization:** with these timers added, evaluation of the efficiency and execution time of the program and its various functions is possible. The bulk course list CSV file was augmented to a total of 100 courses, the functionality was executed and the results analyzed. This produced execution times at worst directly proportional to the data size, with the longest execution taking 0.1 seconds or 99 ticks when running the full Course Validation function. This function is recursive through the list of courses in the BST as well as performing a search through the BST for each prerequisite of each course, providing the highest amount of computational demand currently offered. Such results show promise; considering that the course list for a given institution is unlikely to exceed a few thousand, expected maximum search times of a few seconds is reasonable.
- **Time Complexity:** All functions were produced with time complexities equal to or better than linear. Both functions that necessitated iteration through the entire list of courses are linear, while all others were logarithmic. The ValidateAllCourses() function is the exception, utilizing a logarithmic time inner function to search for the given prerequisites wrapped in a linear time function to fully iterate the course BST.
List of new class functions:
- BinarySearchTree::ToggleCourse()
- BinarySearchTree::ValidateAllCourses() (includes recursive function overload)
- AdvisingProgram::addCourse()
- AdvisingProgram::toggleCourse()
By performing the actions above, the resulting program exemplifies the design and evaluation of computing solutions that solve a given problem. Trade-offs for functionality versus complexity have been managed, and the overall program is more capable with no loss to efficiency or performance.<br><br>
**Reflection**<br>
Successful feature addition is always an enjoyable experience. While this particular development cycle did necessitate overcoming a few hurdles, none were insurmountable or overtly cumbersome and primarily revolved around language syntax mistakes. No major challenges were noted.
The result of this phase has been a greater appreciation for planning and preparation prior to execution of development; the fact that this stage went well can be primarily attributed to these acts.







--------------------------------------------------------------------------------------------------
5. ENHANCEMENT 3: Databases
