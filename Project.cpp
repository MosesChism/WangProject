#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept> // For invalid_argument


using namespace std;

// Structure to represent an alumnus
struct Alumnus {
  string name;
  string email;
  string degree;
  //string courses[3]; // Example: 3 courses
  int graduationYear;

  // Function to display alumnus information (non-const member function)
  // Made the function const to prevent unintended modifications
  void display() const {
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Degree: " << degree << endl;
   /* cout << "Courses: ";
    for (const string& course : courses) {
      cout << course << " ";
    }*/
    cout << endl;
    cout << "Graduation Year: " << graduationYear << endl;
  }
};

// Structure for a course (optional)
struct Course {
  string name;
  // ... (additional course information)
};

// Template class for stack (using a linked list)
template <typename T>
class Stack {
private:
  struct Node {
    T data;
    Node* next;
  };
  Node* top;

public:
  Stack() {
    top = nullptr;
  }

  void push(T data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->next = top;
    top = newNode;
  }

  T pop() {
    if (isEmpty()) {
      throw runtime_error("Stack underflow");
    }
    Node* temp = top;
    T data = temp->data;
    top = top->next;
    delete temp;
    return data;
  }

  T peek() const {
    if (isEmpty()) {
      throw runtime_error("Stack underflow");
    }
    return top->data;
  }

  bool isEmpty() const {
    return top == nullptr;
  }
};

// Function to partition the alumni vector based on graduation year (quicksort helper)



   // Function to partition the alumni vector based on graduation year (quicksort helper)
int partition(vector<Alumnus>& alumni, int low, int high) {
  Alumnus pivot = alumni[high];
  int i = low - 1;

  for (int j = low; j < high; j++) {
    if (alumni[j].graduationYear >= pivot.graduationYear) {
      i++;
      swap(alumni[i], alumni[j]);
    }
  }
  swap(alumni[i + 1], alumni[high]);
  return i + 1;
}

// Recursive quicksort implementation to sort alumni by graduation year (descending)
void quickSort(vector<Alumnus>& alumni, int low, int high) {
  if (low < high) {
    int pivotIndex = partition(alumni, low, high);
    quickSort(alumni, low, pivotIndex - 1);
    quickSort(alumni, pivotIndex + 1, high);
  }
}

// Function to add a new alumnus to the database (including BST insertion - optional)
void addAlumnus(vector<Alumnus>& alumni) {
  Alumnus newAlumnus;

  cout << "Enter alumnus information:" << endl;
  cout << "Name: ";
  getline(cin, newAlumnus.name);
  cout << "Email: ";
  getline(cin, newAlumnus.email);
  cout << "Degree: ";
  getline(cin, newAlumnus.degree);
/*
  for (int i = 0; i < 3; i++) { // Example: Input for 3 courses
    cout << "Course " << (i + 1) << ": ";
    getline(cin, newAlumnus.courses[i]);
  }*/
  cout << "Graduation Year: ";
  cin >> newAlumnus.graduationYear;
  cin.ignore(); // Consume newline character

  alumni.push_back(newAlumnus);

  // Optional: BST insertion (replace with your BST implementation)
  // You'll need to implement the necessary functions for insertion,
  // search, and traversal based on your chosen BST implementation.
}

int main() {
  vector<Alumnus> alumni;

  // Pre-defined alumni (optional)
  alumni.push_back({"Alice Smith", "alice.smith@example.com", "Computer Science",2020});
  alumni.push_back({"Bob Johnson", "bob.johnson@example.com", "Electrical Engineering",2018});
  alumni.push_back({"Charlie Brown", "charlie.brown@example.com", "Mathematics", 2022});
  alumni.push_back({"David Lee", "david.lee@example.com", "Mechanical Engineering",2019});
  alumni.push_back({"Emily Wilson", "emily.wilson@example.com", "Biology",2021});
  alumni.push_back({"Frank Garcia", "frank.garcia@example.com", "History",2017});
  alumni.push_back({"Grace Miller", "grace.miller@example.com", "English Literature",2023});
  alumni.push_back({"Henry Hernandez", "henry.hernandez@example.com", "Business Administration",2020});
  alumni.push_back({"Isabella Jones", "isabella.jones@example.com", "Psychology",2018});
  alumni.push_back({"Jacob Williams", "jacob.williams@example.com", "Computer Science",2022});

  int choice;
  do {
    cout << "\nAlumni Management System" << endl;
    cout << "1. Add Alumnus" << endl;
// cout << "2. Search Alumnus (by Graduation Year)" << endl;
    cout << "3. Display Alumni (Sorted by Graduation Year - Descending)" << endl;
    cout << "4. Display Alumni in Reverse Order (optional - using Stack)" << endl; // Using linked list stack
    cout << "5. Exit" << endl;
    cout << "Enter your choice (1-5): ";
    cin >> choice;
    cin.ignore(); // Consume newline character

    switch (choice) {
      case 1:
        addAlumnus(alumni);
        break;

      case 3:
        if (!alumni.empty()) {
          // Sort alumni by graduation year (descending)
          quickSort(alumni, 0, alumni.size() - 1);

          cout << "\nAlumni List (Sorted by Graduation Year - Descending):" << endl;
          for (const Alumnus& alumnus : alumni) {
            // Corrected: Use const reference to avoid modifying alumnus object
            alumnus.display();  // Call display() with const reference
            cout << endl;
          }
        } else {
          cout << "No alumni found in the database." << endl;
        }
        break;

      case 4: {
        Stack<Alumnus> alumniStack;  // Create a stack using the Stack class

        // Option 1: Push sorted alumni from vector (avoids unnecessary sorting)
        for (const Alumnus& alumnus : alumni) {
          alumniStack.push(alumnus); // Push by value (copy)
        }

        // Option 2: Sort alumni here and then push (less efficient)
        // ... (sort alumni)
        // for (const Alumnus& alumnus : alumni) {
        //   alumniStack.push(alumnus);
        // }

        if (!alumniStack.isEmpty()) {
          cout << "\nAlumni List (Reverse Order - using Stack):" << endl;
          while (!alumniStack.isEmpty()) {
            // Corrected: Use const reference to avoid modifying popped element
            const Alumnus& alumnus = alumniStack.pop();  // Get const reference
            alumnus.display();
            cout << endl;
          }
        } else {
          cout << "No alumni found in the database." << endl;
        }
        break;
      }

      case 5:
        cout << "Exiting Alumni Management System." << endl;
        break;

      default:
        cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
    }
  } while (choice != 5);

  return 0;
}