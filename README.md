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
**Artifact:** ABCU Advising Program
**Description:** This program provides course list storage for the CS department at ABCU (fictional) to assist with admissions and administrative functions.
**Justification:**  This artifact was included for the opportunity it provided for holistic application development and iterative improvement. As a complete application with all code available and minimal external library dependency, exercises in improvement would be easily comprehensible and understandable. Additionally, the initial state of the program (monolithic code) provided an excellent opportunity to exemplify program code structures and the interaction between multiple files and data structures.

**PROCESS**
**Course Outcome Exemplified: #4 - Demonstrate an ability to use well-founded and innovative techniques, skills, and tools in computing practices for the purpose of implementing computer solutions that deliver value and accomplish industry-specific goals**
Exemplification of this outcome is accomplished via the targeted implementation of a computer solution to the goal specified by the purpose of the program. Well-founded techniques were employed to do so, including the use of header and source files, formatted and standardized code and code structures. Individual functional components were abstracted out to human-readable functions, allowing the program’s sequence of events to be more self-evident. This facilitates future development and interpretation by future developers responsible for maintenance and improvements.
**How artifact was improved:**

The major class of BinarySearchTree was broken out to its own source and header files. 

The required structs of Node and Course were also relocated to the BinarySearchTree source file for proximal use.

An additional class titled AdvisingProgram was created. All ancillary functions for the program were relocated here. Additionally, a main function titled executeProgram() was created to encompass the primary program loop. The remaining functionality in the primary source file has been reduced down to initial argument parsing, instantiation of the AdvisingProgram object, and execution of the main function.

In order to further break down the main loop, the function of SearchAndPrintCourse() was added and the associated code was extracted.

Library inclusions for the program were relocated to the baseline location requiring them. Any subsequent locations where these libraries are referenced are able to pull them via inclusion of the primary file.

By performing the actions above, the resulting code base is organized, more modular, and easier to interpret and understand. 

**Reflection**
I found the refactoring process to be highly rewarding. While I had a certain sense of cleanliness initially building the program as one file, this excluded the prospects of enhancement or refactoring at the time. With that mechanism in place, the new code is much more organized. Not only do I find the new structure easier to visualize, the groundwork is now laid for the other enhancements pending on this artifact.
Major challenges encountered during the refactoring included language-specific requirements for class structures and the use of pointers and references in a few new locations to facilitate functional operation.  
The result of execution has been a deeper understanding of the language used (C++) and a greater appreciation for planning out programming projects ahead of code implementation to facilitate future development.

--------------------------------------------------------------------------------------------------
4. ENHANCEMENT 2: Algorithms and Data Structures








--------------------------------------------------------------------------------------------------
5. ENHANCEMENT 3: Databases
