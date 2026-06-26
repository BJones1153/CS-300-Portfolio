#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cctype>


using namespace std;

// Define course structure 
struct Course {
    string courseNumber;
    string courseTitle;

    vector<string> prereqs;

};

// Define BST node 
struct Node {
    Course course;

    Node* left;
    Node* right;


    // Constructor
    Node(Course aCourse) {
        course = aCourse;

        left = nullptr;
        right = nullptr;

    }


};

// Prototypes
Node* InsertCourse(Node* node, Course course);
Node* LoadCourses(string fileName, Node* root);
void DisplayMenu(Node*& root);
void InOrder(Node* node);
void PrintCourseList(Node* root);
Node* SearchCourse(Node* node, string courseNumber);
void PrintCourseInformation(Node* root, string courseNumber);
string Trim(string text);



string Trim(string text) {

    while (!text.empty() && isspace(text.front())) {
        text.erase(text.begin());
    }

    while (!text.empty() && isspace(text.back())) {
        text.pop_back();
    }

    return text;
}



// Function to load course information into program
Node* LoadCourses(string fileName, Node* root) {

    // Open the file
    ifstream file(fileName);

    // Check if file opened correctly


    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return root;
    }

    string line;

    // Read file line by line
    while (getline(file, line)) {

        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Split line into tokens by commas
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // Check to make sure line has a course number and title
        if (tokens.size() < 2) {
            cout << "Error: line is missing required field(s)." << endl;
            continue;
        }

        // Create course object
        Course course;

        // Clean up extra spaces
        course.courseNumber = Trim(tokens[0]);

        course.courseTitle = Trim(tokens[1]);

        // Store prerequisites
        for (int i = 2; i < tokens.size(); ++i) {

            string prereq = Trim(tokens[i]);

            // Ignore blank prerequisites
            if (prereq != "") {

                course.prereqs.push_back(prereq);
            }
        }

        // Add course to Binary Tree
        root = InsertCourse(root, course);
    }

    // Close file
    file.close();

    cout << "Courses loaded successfully." << endl;

    return root;
}

// Function to display and process menu commands
void DisplayMenu(Node* & root) {

    // Initialize user choice
    int userChoice = 0;

    string fileName;
    string courseNumber;

    // Keep showing menu until user exits
    while (userChoice != 9) {

        cout << endl;

        // Prompt user for choice
        cout << "Please choose from the following menu:" << endl;

        cout << "  1. Load data into program" << endl;

        cout << "  2. Display list of all courses" << endl;

        cout << "  3. Display course information" << endl;

        cout << "  9. Exit program" << endl;

        cout << endl;

        cin >> userChoice;

        // Option 1
        if (userChoice == 1) {
            

            cout << "Enter file name: ";
            cin.ignore();
            getline(cin, fileName);

            root = LoadCourses(fileName, root);
        }

        // Option 2
        else if (userChoice == 2) {

            PrintCourseList(root);
        }

        // Option 3
        else if (userChoice == 3) {

            cout << "Enter course number: ";

            cin >> courseNumber;

            PrintCourseInformation(root, courseNumber);
        }

        // Option 9
        else if (userChoice == 9) {

            cout << "Goodbye." << endl;
        }

        // Invalid input
        else {

            cout << "Invalid response." << endl;
        }
    }
}

// Add a given course to binary tree structure
Node* InsertCourse(Node* node, Course course) {


    if (node == nullptr) {
        return new Node(course);
    }


    if (course.courseNumber < node->course.courseNumber) {
        node->left = InsertCourse(node->left, course);
    }
    else {
        node->right = InsertCourse(node->right, course);
    }


    return node;
}

// Traverse BST in alphanumeric order
void InOrder(Node* node) {


    // Base case
    if (node == nullptr) {
        return;
    }


    // Left side of tree 
    InOrder(node->left);


    // Print 
    cout << node->course.courseNumber
        << ", "
        << node->course.courseTitle
        << endl;


    // Right side of tree 
    InOrder(node->right);
}

// Print all courses
void PrintCourseList(Node* root) {


    if (root == nullptr) {


        cout << "No courses loaded ." << endl;


        return;
    }


    cout << endl;


    cout << "Here is a sample schedule:" << endl;


    // Print courses in order
    InOrder(root);


    cout << endl;
}

// Search for course based on course num.
Node* SearchCourse(Node* node, string courseNumber) {


    // not found 
    if (node == nullptr) {
        return nullptr;
    }


    // Course was found
    if (node->course.courseNumber == courseNumber) {
        return node;
    }


    // left side
    if (courseNumber < node->course.courseNumber) {
        return SearchCourse(node->left, courseNumber);
    }


    // right side
    return SearchCourse(node->right, courseNumber);
}


// Print one course and its prereqs
void PrintCourseInformation(Node* root,
    string courseNumber) {


    // Find requested course
    Node* foundCourse =
        SearchCourse(root, courseNumber);


    // Course not found
    if (foundCourse == nullptr) {


        cout << "Course not found."
            << endl;


        return;
    }


    // Print selected course
    cout << endl;


    cout << foundCourse->course.courseNumber
        << ", "
        << foundCourse->course.courseTitle
        << endl;


    // Print prerequisites
    cout << "Prerequisites: ";


    // No prerequisites
    if (foundCourse->course.prereqs.empty()) {


        cout << "None";


    }
    else {


        for (int i = 0;
            i < foundCourse->course.prereqs.size();
            ++i) {


            // Search for prerequisite course
            Node* prereq =
                SearchCourse(
                    root,
                    foundCourse
                    ->course
                    .prereqs[i]
                );


            // Print number + title
            if (prereq != nullptr) {


                cout
                    << prereq->course.courseNumber
                    << " "
                    << prereq->course.courseTitle;


            }
            else {


                cout
                    << foundCourse
                    ->course
                    .prereqs[i];
            }


            if (i <
                foundCourse
                ->course
                .prereqs
                .size() - 1) {


                cout << ", ";
            }
        }
    }


    cout << endl;
}



int main()
{
    Node* root = nullptr;

    // Display menu to user
    DisplayMenu(root); 

    return 0;
}

