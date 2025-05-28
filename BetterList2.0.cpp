#include <iostream>
#include <vector>
#include <string>

class Task{
    private:
    std::string taskName, taskDescription, taskDueDate;
    bool isCompleted = false;

    public:
    Task(std::string taskName, std::string taskDescription, std::string taskDueDate) : taskName(taskName), taskDescription(taskDescription), taskDueDate(taskDueDate){}
    std::string getName(){return taskName;}
    std::string getDescription(){return taskDescription;}
    std::string getDueDate(){return taskDueDate;}
    void setName(std::string taskName){this->taskName = taskName;}
    void setDescription(std::string taskDescription){this->taskDescription = taskDescription;}
    void setDueDate(std::string taskDueDate){this->taskDueDate = taskDueDate;}
    void markCompleted(){isCompleted = true;}

    void displayTask(){
        std::cout << "Name: " << this->taskName << " - " << ((this->isCompleted) ? "Completed" : "Pending") << "\nDescription: " << this->taskDescription << "\nDue: " << this->taskDueDate << "\n";
    }
};
class ToDoList{
    private:
    std::vector<Task> tasks;

    public:
    ToDoList(){}

    void displayTasks(){
        std::cout << "\nTasks: ";
        if(tasks.empty()){std::cout << "No tasks!\n"; return;}
        for(int i=0;i<tasks.size();i++){
            std::cout << "\n" << (i+1) << ": ";
             tasks[i].displayTask();
        }
    }

    void editTask(){
        int taskNumber;
        std::cout << "\nTasks: \n";
        for(int i=0;i<tasks.size();i++){
            std::cout << i+1 << ": " << tasks[i].getName() << "\n";
        }
        std::cin >> taskNumber;
        if(taskNumber >= 1 && taskNumber <= tasks.size()){
            Task& task = tasks[taskNumber-1];
            std::string newName, newDescription, newDueDate;
            std::cout << "Enter New Name (Current: " << task.getName() << "): ";
            std::cin.ignore();
            std::getline(std::cin, newName);
            std::cout << "Enter New Description (Current: " << task.getDescription() << "): ";
            std::getline(std::cin, newDescription);
            std::cout << "Enter new Due Date (Current: " << task.getDueDate() << "): ";
            std::getline(std::cin, newDueDate);

            task.setName(newName);
            task.setDescription(newDescription);
            task.setDueDate(newDueDate);
            std::cout << "Tasks updated successfully!\n";
        }
        else{
            std::cout << "Invalid Task Number!\n";
        }
    }

    void deleteTask(){
        int taskNumber;
        std::cout << "\nTasks: \n";
        for(int i=0;i<tasks.size();i++){
            std::cout << i+1 << ": " << tasks[i].getName() << "\n";
        }
        std::cin >> taskNumber;
        if(taskNumber >= 1 && taskNumber <= tasks.size()){
            tasks.erase(tasks.begin()+taskNumber-1);
            std::cout << "Task deleted successfully!\n";
        }
        else{
            std::cout << "Invalid Task Number!\n";
        }
    }

    void markAsCompleted(){
        int taskNumber;
        std::cout << "\nTasks: \n";
        for(int i=0;i<tasks.size();i++){
            std::cout << i+1 << ": " << tasks[i].getName() << "\n";
        }
        std::cin >> taskNumber;
        if(taskNumber >= 1 && taskNumber <= tasks.size()){
            tasks[taskNumber-1].markCompleted();
            std::cout << "Task Completed, Well done!\n";
        }
        else{
            std::cout << "Invalid Task!\n";
        }
    }

    void Menu(){
        std::cout << "\n   ______________________\n"
                  << "  |      To Do List      |\n"
                  << "----------------------------\n"
                  << "|1 Create Task.            |\n"
                  << "|2 Edit Task               |\n"
                  << "|3 Delete Task             |\n"
                  << "|4 Display Tasks           |\n"
                  << "|5 Complete Task           |\n"
                  << "|6 Exit                    |"
                  << "\n----------------------------\n";
    }

    void CreateTask(){
        std::string name, description, dueDate;
        std::cout << "Enter Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        std::cout << "Enter Description: ";
        std::getline(std::cin, description);
        std::cout << "Enter Due Date (DD-MM-YYYY): ";
        std::getline(std::cin, dueDate);
        tasks.emplace_back(name, description, dueDate);
        std::cout << "Task added!\n";
    }

    void run(){
        int choice;
        do{
        this->Menu();
        std::cout << "Enter your Choice: ";
        std::cin >> choice;
        switch(choice){
            case 1: this->CreateTask(); break;
            case 2: this->editTask(); break;
            case 3: this->deleteTask(); break;
            case 4: this->displayTasks(); break;
            case 5: this->markAsCompleted(); break;
            case 6: std::cout << "Good bye!\n"; break;
            default: std::cout << "Invalid input!\n"; choice = 0;
        }
        }
        while(choice != 6);
    }
};

int main(){
    ToDoList toDoList;
    toDoList.run();
}