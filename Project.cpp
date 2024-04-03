#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept> // For invalid_argument

using namespace std;

// Structure to represent an alumnus
struct Alumnus {
  string name;
  string email;
  string degree;
  string company;
  int graduationYear;

  // Function to display alumnus information (non-const member function)
  void display() {
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Degree: " << degree << endl;
    cout << "Company: " << company << endl;
    cout << "Graduation Year: " << graduationYear << endl;
  }
};

// Structure for a binary search tree node
struct Node {
  Alumnus data;
  Node* left;
  Node* right;
};

// Class for the binary search tree
class BST {
public:
  Node* root;

  BST() {
    root = nullptr;
  }

  // Function to insert a new alumnus into the BST
  void insert(Alumnus alumnus) {
    if (root == nullptr) {
      root = new Node{alumnus, nullptr, nullptr};
      return;
    }

    Node* current = root;
    while (true) {
      if (alumnus.graduationYear < current->data.graduationYear) {
        if (current->left == nullptr) {
          current->left = new Node{alumnus, nullptr, nullptr};
          break;
        } else {
          current = current->left;
        }
      } else {
        if (current->right == nullptr) {
          current->right = new Node{alumnus, nullptr, nullptr};
          break;
        } else {
          current = current->right;
        }
      }
    }
  }

  // Function to search for an alumnus with a specific graduation year (optional)
  Node* search(int graduationYear) {
    if (root == nullptr) {
      return nullptr; // Tree is empty
    }

    Node* current = root;
    while (current != nullptr) {
      if (graduationYear == current->data.graduationYear) {
        return current; // Found
      } else if (graduationYear < current->data.graduationYear) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return nullptr; // Not found
  }

  // Function to perform an in-order traversal (optional)
  void displayInOrder(Node* current) {
    if (current != nullptr) {
      displayInOrder(current->left);
      current->data.display();
      displayInOrder(current->right);
    }
  }
};

// Template class for stack (can store any data type)
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

// Function to add a new alumnus to the database (including BST insertion)
void addAlumnus(vector<Alumnus>& alumni, BST& bst) {
  Alumnus newAlumnus;

  cout << "Enter alumnus information:" << endl;
  cout << "Name: ";
  getline(cin, newAlumnus.name);
  cout << "Email: ";
  getline(cin, newAlumnus.email);

  cout << "Degree: ";
  getline(cin, newAlumnus.degree);
  cout << "Company: ";
  getline(cin, newAlumnus.company);
  cout << "Graduation Year: ";
  cin >> newAlumnus.graduationYear;
  cin.ignore(); // Consume newline character

  alumni.push_back(newAlumnus); // Add to vector (optional)
  bst.insert(newAlumnus);   // Insert into BST
}

int main() {
  vector<Alumnus> alumni;

   Alumnus alumnus1;
    alumnus1.name = "John Doe";
    alumnus1.email = "john.doe@example.com";
    alumnus1.degree = "Computer Science";
    alumnus1.company = "ABC Tech";
    alumnus1.graduationYear = 2020;
    alumni.push_back(alumnus1);

    Alumnus alumnus2;
    alumnus2.name = "Jane Smith";
    alumnus2.email = "jane.smith@example.com";
    alumnus2.degree = "Business Administration";
    alumnus2.company = "XYZ Finance";
    alumnus2.graduationYear = 2022;
    alumni.push_back(alumnus2);

  BST bst; // Declare the BST object

 bst.insert(alumnus1);
    bst.insert(alumnus2);
  int choice;
  do {
    cout << "\nAlumni Management System" << endl;
    cout << "1. Add Alumnus" << endl;
    cout << "2. Search Alumnus (by Graduation Year)" << endl; // (optional)
    cout << "3. Display Alumni (In-Order Traversal)" << endl; // (optional)
    cout << "4. Display Alumni in Reverse Order (using Stack)" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice (1-5): ";
    cin >> choice;
    cin.ignore(); // Consume newline character

    switch (choice) {
      case 1:
        addAlumnus(alumni, bst);
        break;

      case 2: {
        int searchYear;
        cout << "Enter graduation year to search: ";
        cin >> searchYear;
        cin.ignore();

        Node* searchResult = bst.search(searchYear);
        if (searchResult != nullptr) {
          cout << "Alumnus Found!" << endl;
          searchResult->data.display();
        } else {
          cout << "Alumnus not found in the database." << endl;
        }
        break;
      }

      case 3:
        cout << "\nAlumni List (In-Order):" << endl;
        bst.displayInOrder(bst.root);
        break;

      case 4: {
        Stack<Alumnus> alumniStack; // Create a stack of Alumnus objects

        // Push all alumni onto the stack
        for (Alumnus& alumnus : alumni) {
          alumniStack.push(alumnus);
        }

        // Pop and display alumni in reverse order
        while (!alumniStack.isEmpty()) {
          Alumnus alumnus = alumniStack.pop();
          alumnus.display();
          cout << endl;
        }

        break;
      }

      case 5:
        cout << "Exiting Alumni Management System." << endl;
        break;

      default:
        cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
    }
  } while (choice != 0);

  return 0;
}