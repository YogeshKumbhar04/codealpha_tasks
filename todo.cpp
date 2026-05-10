#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Task {
public:
    string name;
    bool completed;
};

vector<Task> tasks;

// Save tasks to file
void saveTasks() {
    ofstream file("tasks.txt");
    for (int i = 0; i < tasks.size(); i++) {
        file << tasks[i].name << endl;
        file << tasks[i].completed << endl;
    }
    file.close();
}

// Load tasks from file
void loadTasks() {
    ifstream file("tasks.txt");
    if (!file) return;

    Task t;
    while (getline(file, t.name)) {
        file >> t.completed;
        file.ignore();
        tasks.push_back(t);
    }
    file.close();
}

// Add task
void addTask() {
    Task t;
    cout << "Enter task name: ";
    cin.ignore();
    getline(cin, t.name);
    t.completed = false;
    tasks.push_back(t);
    saveTasks();
    cout << "Task added successfully!\n";
}

// View tasks
void viewTasks() {
    if (tasks.empty()) {
        cout << "No tasks available.\n";
        return;
    }

    cout << "\n===== TASK LIST =====\n";
    for (int i = 0; i < tasks.size(); i++) {
        cout << i + 1 << ". ";
        if (tasks[i].completed)
            cout << "[Completed] ";
        else
            cout << "[Pending] ";

        cout << tasks[i].name << endl;
    }
}

// Mark task completed
void completeTask() {
    viewTasks();

    if (tasks.empty()) return;

    int num;
    cout << "Enter task number to mark as completed: ";
    cin >> num;

    if (num >= 1 && num <= tasks.size()) {
        tasks[num - 1].completed = true;
        saveTasks();
        cout << "Task marked as completed!\n";
    } else {
        cout << "Invalid task number.\n";
    }
}

// Main function
int main() {
    loadTasks();

    int choice;

    do {
        cout << "\n===== TO-DO LIST MENU =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task Completed\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                viewTasks();
                break;
            case 3:
                completeTask();
                break;
            case 4:
                cout << "Thank you!\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}