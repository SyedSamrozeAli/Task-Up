#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <iomanip>
using namespace std;

class node
{
public:
    int TaskID;
    string TaskName, TaskDescription, deadline, category;
    int TaskPriority;
    bool status;

    node()
    {
        this->TaskID = 0;
        this->TaskName = '\0';
        this->TaskDescription = '\0';
        this->category = '\0';
        this->deadline = '\0';
        this->status = false;
        this->TaskPriority = 0;
    }

    node(int TaskID, string TaskName, string TaskDescription, int TaskPriority, bool status, string deadline, string category)
    {
        this->TaskID = TaskID;
        this->TaskName = TaskName;
        this->TaskDescription = TaskDescription;
        this->deadline = deadline;
        this->status = status;
        this->TaskPriority = TaskPriority;
        this->category = category;
    }
};
class Stack
{

public:
    int *arr;
    int top, size;
    Stack(int size)
    {
        this->size = size;
        arr = new int[size];
        top = -1;
    }
    void push(int n)
    {
        if (size - top > 1)
        {
            top++;
            arr[top] = n;
        }
    }
    void pop()
    {

        if (top >= 0)
        {
            top--;
        }
    }
    int peek()
    {
        if (top >= 0)
        {
            return arr[top];
        }
    }
};

class PriorityQueue
{
    string getdate()
    {
        time_t now = time(nullptr);
        tm *ltm = localtime(&now);
        static char buffer[20];
        strftime(buffer, sizeof(buffer), "%d-%m-%Y", ltm);
        return buffer;
    }
    Stack extractDate(string &inputDate)
    {
        Stack sdate(6);
        istringstream date_stream(inputDate);
        string date_token;
        getline(date_stream, date_token, '-');
        sdate.push(stoi(date_token));
        getline(date_stream, date_token, '-');
        sdate.push(stoi(date_token));
        getline(date_stream, date_token, '-');
        sdate.push(stoi(date_token));
        return sdate;
    }
    bool isValidDate(string &inputDate)
    {
        Stack dateToken = extractDate(inputDate);

        string date = getdate();
        Stack recentDate = extractDate(date);

        int year = dateToken.peek();
        dateToken.pop();
        int month = dateToken.peek();
        dateToken.pop();
        int day = dateToken.peek();
        dateToken.pop();

        int r_year = recentDate.peek();
        recentDate.pop();
        int r_month = recentDate.peek();
        recentDate.pop();
        int r_day = recentDate.peek();
        recentDate.pop();

        if (year < r_year || month < r_month || day < r_day)
        {
            return false;
        }

        int maxDay = 31;
        if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            maxDay = 30;
        }
        else if (month == 2)
        {
            maxDay = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
        }

        if (day > maxDay)
        {
            return false;
        }

        return true;
    }

public:
    node **IncompleteTask;
    node **CompletedTask;
    int size;
    int I_current_size;
    int C_current_size;
    int idCtr;

    PriorityQueue()
    {
        size = 100;
        I_current_size = -1;
        C_current_size = -1;
        idCtr = 100;
        IncompleteTask = new node *[size];
        CompletedTask = new node *[size];
        for (int i = 0; i <= size; i++)
        {
            IncompleteTask[i] = NULL;
            CompletedTask[i] = NULL;
        }
    }
    void DisplayMenu()
    {
        int opt = 0, choice = 0;
        bool dateflag = false;
        string category;
        while (1)
        {
            cout << endl
                 << endl
                 << "\t\t\t\t\t\t\t ---------------------------  <- TASK UP ->  -----------------------------" << endl
                 << "\t\t\t\t\t\t\t|                                                                         |" << endl
                 << "\t\t\t\t\t\t\t|                                                                         |" << endl
                 << "\t\t\t\t\t\t\t| > Choose any option:                                                    |" << endl
                 << "\t\t\t\t\t\t\t|                                                                         |" << endl
                 << "\t\t\t\t\t\t\t|    1 >> Insert Task                                                     |" << endl
                 << "\t\t\t\t\t\t\t|    2 >> Delete Task                                                     |" << endl
                 << "\t\t\t\t\t\t\t|    3 >> Update Task                                                     |" << endl
                 << "\t\t\t\t\t\t\t|    4 >> Complete Highest Priority Task                                  |" << endl
                 << "\t\t\t\t\t\t\t|    5 >> See Current Priority Task                                       |" << endl
                 << "\t\t\t\t\t\t\t|    6 >> To see next Priority Task                                       |" << endl
                 << "\t\t\t\t\t\t\t|    7 >> Search Task                                                     |" << endl
                 << "\t\t\t\t\t\t\t|    8 >> Display Pending Tasks                                           |" << endl
                 << "\t\t\t\t\t\t\t|    9 >> Display Completed Task                                          |" << endl
                 << "\t\t\t\t\t\t\t|   10 >> Get Task Description                                            |" << endl
                 << "\t\t\t\t\t\t\t|   11 >> Visit Task Categories                                           |" << endl
                 << "\t\t\t\t\t\t\t|   12 >> Visit OverDue Tasks                                             |" << endl
                 << "\t\t\t\t\t\t\t|   13 >> Exit                                                            |" << endl
                 << "\t\t\t\t\t\t\t|                                                                         |" << endl
                 << "\t\t\t\t\t\t\t ------------------------------------------------------------------------- " << endl;

            do
            {
                cout << "\t\t\t\t\t\t\tChoice: ";
                cin >> ws;
                cin >> choice;
                switch (choice)
                {
                case 1:
                {
                    dateflag = false;
                    system("CLS");
                    InsertTask("Send Money to Zoya", "Zoya Wanted it for New property", 100, "3-12-2023", "Finances");
                    InsertTask("Saad's Wedding", "Go get it Boi!", 56, "1-1-2024", "Personal");
                    InsertTask("Hand over Report to Boss", "-", 80, "15-12-2023", "Work");
                    InsertTask("Submit Masters ki Fees", "-", 90, "12-12-2023", "Education");
                    InsertTask("Submit Automation Report", "Points to include 1-Intro\n 2-Why is it necessary for automation to be in society\n 3-Max 100 Words\n", 45, "12-1-2024", "Education");

                    string name, description, deadline;
                    int priority;
                    cout << endl
                         << endl
                         << "\n\t\t\t\t\t\t\t-------------------- Insert Task ----------------------" << endl
                         << "\t\t\t\t\t\t\t|                                                      |" << endl;
                    cout << "\t\t\t\t\t\t\t|                                                      |" << endl
                         << "\t\t\t\t\t\t\t| > Select your desired Category:                      |" << endl
                         << "\t\t\t\t\t\t\t|                                                      |" << endl
                         << "\t\t\t\t\t\t\t|   1 >> Work                                          |" << endl
                         << "\t\t\t\t\t\t\t|   2 >> Personal                                      |" << endl
                         << "\t\t\t\t\t\t\t|   3 >> Education                                     |" << endl
                         << "\t\t\t\t\t\t\t|   4 >> Finances                                      |" << endl
                         << "\t\t\t\t\t\t\t|   5 >> Other                                         |" << endl
                         << "\t\t\t\t\t\t\t|   6 >> Go Back                                       |" << endl
                         << "\t\t\t\t\t\t\t|                                                      |" << endl
                         << "\t\t\t\t\t\t\t ------------------------------------------------------ " << endl;
                    do
                    {
                        cout << "\t\t\t\t\t\t\tChoice: ";
                        cin >> opt;
                        if (opt == 1)
                        {
                            category = "Work";
                        }
                        else if (opt == 2)
                        {
                            category = "Personal";
                        }
                        else if (opt == 3)
                        {
                            category = "Education";
                        }
                        else if (opt == 4)
                        {
                            category = "Finances";
                        }
                        else if (opt == 5)
                        {
                            cout << "\t\t\t\t\t\t\tEnter category name: ";
                            cin >> ws;
                            getline(cin, category);
                        }
                        else if (opt == 6)
                        {
                            system("cls");
                            DisplayMenu();
                        }
                        else
                        {
                            cout << "\t\t\t\t\t\t\t Wrong input...Try Again!" << endl;
                        }
                    } while (opt < 1 || opt > 6);

                    cout << endl;
                    cout << "\t\t\t\t\t\t\tEnter Task Name: ";
                    cin >> ws;
                    getline(cin, name);
                    cout << "\t\t\t\t\t\t\tEnter Task Description: ";
                    cin >> ws;
                    getline(cin, description);
                    do
                    {
                        cout << endl
                             << "\t\t\t\t\t\t\tEnter Task Priority[1-100](100 being the highest and 1 being the lowest): ";
                        cin >> priority;
                        if (priority > 100 || priority < 1)
                        {
                            cout << "\t\t\t\t\t\t\t Invalid Task Priority!";
                        }
                    } while (priority < 1 || priority > 100);
                    do
                    {
                        cout << "\t\t\t\t\t\t\tEnter Task Deadline[dd-mm-yy]: ";
                        cin >> ws;
                        getline(cin, deadline);
                        if (isValidDate(deadline) == false)
                        {
                            cout << "\n\t\t\t\t\t\t\tInvalid date entered!" << endl;
                        }
                        else
                        {
                            dateflag = true;
                        }
                    } while (dateflag == false);

                    InsertTask(name, description, priority, deadline, category);
                    buildHeap();
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 2:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Removing Task ------------------\n\n";
                    int id;
                    DisplayAllTask();
                    cout << "\t\t\t\t\t\t\tEnter Task ID to delete: ";
                    cin >> id;
                    cout << endl;

                    if (removeTask(id))
                    {

                        cout << "\t\t\t\t\t\t\tSuccessfully deleted!";
                    }
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 3:
                {
                    system("CLS");
                    cout << endl
                         << endl
                         << "\n\t\t\t\t\t\t\t-------------------- Update Task ----------------------" << endl
                         << endl;
                    Update();
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 4:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Completed Tasks ------------------\n\n";
                    cout << endl;
                    markTaskasComplete();
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 5:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Highest Priority Task ------------------\n\n";
                    cout << endl;
                    getHighestTask();
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 6:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Next Highest Priority Task ------------------\n\n";
                    cout << endl;
                    getNextHighestTask();
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 7:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Search Task ------------------\n\n";
                    int id;
                    cout << "\t\t\t\t\t\t\tEnter The ID Of Task You Want To Search: ";
                    cin >> id;
                    int index = searchTask(id);
                    if (index != -1)
                    {
                        cout << endl;
                        displayHeading();
                        DisplaySingleTask(index);
                    }
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 8:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Displaying All Task ------------------\n\n";
                    cout << endl;
                    DisplayAllTask();
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 10:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Description of Task ------------------\n\n";
                    int TaskID;
                    DisplayAllTask();
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tEnter the ID of the task you want to view description of: ";
                    cin >> TaskID;
                    int index = searchTask(TaskID);
                    if (index != -1)
                    {
                        cout << endl;
                        getDescriptionofTask(index);
                        cout << endl;
                    }
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 9:
                {

                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- Displaying All Completed Task ------------------\n\n";
                    cout << endl;
                    DisplayCompletedTask();
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }

                case 11:
                {

                    system("CLS");
                    cout << endl
                         << endl
                         << endl
                         << endl;
                    cout << "\t\t\t\t\t\t\t-------------------------------------------------------" << endl;
                    cout << "\t\t\t\t\t\t\t|                                                      |" << endl
                         << "\t\t\t\t\t\t\t| > Select your desired Category:                      |" << endl
                         << "\t\t\t\t\t\t\t|                                                      |" << endl
                         << "\t\t\t\t\t\t\t|   1 >> Work                                          |" << endl
                         << "\t\t\t\t\t\t\t|   2 >> Personal                                      |" << endl
                         << "\t\t\t\t\t\t\t|   3 >> Education                                     |" << endl
                         << "\t\t\t\t\t\t\t|   4 >> Finances                                      |" << endl
                         << "\t\t\t\t\t\t\t|   5 >> Other                                         |" << endl
                         << "\t\t\t\t\t\t\t|   6 >> Go Back                                       |" << endl
                         << "\t\t\t\t\t\t\t|                                                      |" << endl
                         << "\t\t\t\t\t\t\t ------------------------------------------------------ " << endl;
                    do
                    {
                        cout << "\t\t\t\t\t\t\tChoice: ";
                        cin >> opt;
                        if (opt == 1)
                        {
                            category = "Work";
                        }
                        else if (opt == 2)
                        {
                            category = "Personal";
                        }
                        else if (opt == 3)
                        {
                            category = "Education";
                        }
                        else if (opt == 4)
                        {
                            category = "Finances";
                        }
                        else if (opt == 5)
                        {
                            cout << "\t\t\t\t\t\t\tEnter category name: ";
                            cin >> ws;
                            getline(cin, category);
                        }
                        else if (opt == 6)
                        {
                            system("cls");
                            DisplayMenu();
                        }
                        else
                        {
                            cout << "\t\t\t\t\t\t\t Wrong input...Try Again!" << endl;
                        }
                    } while (opt < 1 || opt > 6);
                    cout << endl;
                    displayHeading();
                    displaythroughCategory(category);
                    cout << endl
                         << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 12:
                {
                    system("CLS");
                    cout << "\n\t\t\t\t\t\t\t--------------- OverDue Tasks ------------------\n\n";
                    cout << endl;
                    getOverDueTasks();
                    cout << endl;
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                case 13:
                {
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tThankyou for using our service..Have a GOOD DAY :)";
                    cout << endl;
                    cout << endl;
                    exit(0);
                }
                default:
                {
                    cout << "\t\t\t\t\t\t\tWrong choice...Enter again!\n";
                    cout << endl;
                    cout << endl;
                    cout << "\t\t\t\t\t\t\tPress any key to continue.........";
                    getchar();
                    getchar();
                    break;
                }
                }
            } while (choice < 1 || choice > 12);
            system("CLS");
        }
    }
    void InsertTask(string TaskName, string TaskDescription, int TaskPriority, string deadline, string category)
    {
        if (I_current_size < size - 1)
        {
            node *newTask = new node(idCtr++, TaskName, TaskDescription, TaskPriority, false, deadline, category);
            IncompleteTask[++I_current_size] = newTask;
        }
        else
        {
            cout << "\t\t\t\t\t\t\t TaskUp is currently full!" << endl;
        }
    }
    void buildHeap()
    {
        int start = (I_current_size) / 2;
        for (int i = start; i >= 0; i--)
        {
            Heapify(i, I_current_size);
        }
    }

    node *DequeueTask()
    {
        if (I_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tScheduler EMPTY!" << endl;
            return NULL;
        }
        node *temp = IncompleteTask[0];
        IncompleteTask[0] = IncompleteTask[I_current_size];
        IncompleteTask[I_current_size] = NULL;
        I_current_size--;
        Heapify(0, I_current_size);
        return temp;
    }

    int searchTask(int TaskId)
    {
        int index = -1;
        for (int i = 0; i <= I_current_size; i++)
        {
            if (IncompleteTask[i]->TaskID == TaskId)
            {
                index = i;
                break;
            }
        }
        if (index != -1)
        {
            return index;
        }
        else
        {
            cout << endl;
            cout << "\t\t\t\t\t\t\tTask not found" << endl;
            return index;
        }
    }
    void getOverDueTasks()
    {
        bool flag = false;
        string date = getdate();
        Stack recentDate = extractDate(date);
        int r_year = recentDate.peek();
        recentDate.pop();
        int r_month = recentDate.peek();
        recentDate.pop();
        int r_day = recentDate.peek();
        recentDate.pop();
        displayHeading();
        for (int i = 0; i <= I_current_size; i++)
        {
            Stack dateToken = extractDate(IncompleteTask[i]->deadline);

            int year = dateToken.peek();
            dateToken.pop();
            int month = dateToken.peek();
            dateToken.pop();
            int day = dateToken.peek();
            dateToken.pop();

            if (year <= r_year)
            {
                if (month <= r_month)
                {
                    if (day <= r_day)
                    {
                        flag = true;
                        DisplaySingleTask(i);
                    }
                }
            }
        }
        if (flag == false)
        {
            cout << "\t\t\t\t\t\t\tNo overdue tasks!" << endl;
        }
    }
    void Update()
    {
        bool dateflag = false;
        if (I_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tScheduler EMPTY!" << endl;
            return;
        }
        string newname, newdescription, newDeadline, newCategory;
        int newPriority;
        bool flag = true;
        DisplayAllTask();
        cout << endl;

        cout << endl;
        cout << "\t\t\t\t\t\t\tEnter the ID of Task which you want to update: ";
        int id;
        cin >> id;
        int choice, opt;
        int updateIndex = searchTask(id);
        cout << "\n\t\t\t\t\t\t\t-------------------------------------------------------" << endl;
        cout << "\t\t\t\t\t\t\t|                                                      |" << endl
             << "\t\t\t\t\t\t\t| > Which field you want to update?                    |" << endl
             << "\t\t\t\t\t\t\t|                                                      |" << endl
             << "\t\t\t\t\t\t\t|   1 >> Task Name                                     |" << endl
             << "\t\t\t\t\t\t\t|   2 >> Task Description                              |" << endl
             << "\t\t\t\t\t\t\t|   3 >> Task Deadline                                 |" << endl
             << "\t\t\t\t\t\t\t|   4 >> Task Priority                                 |" << endl
             << "\t\t\t\t\t\t\t|   5 >> Task Category                                 |" << endl
             << "\t\t\t\t\t\t\t|                                                      |" << endl
             << "\t\t\t\t\t\t\t ------------------------------------------------------ " << endl;

        do
        {
            cout << "\t\t\t\t\t\t\tChoice: ";
            cin >> choice;
            cout << endl;
            cin.ignore();
            switch (choice)
            {
            case 1:
                cout << "\t\t\t\t\t\t\tEnter new Name: ";
                getline(cin, newname);
                IncompleteTask[updateIndex]->TaskName = newname;
                break;

            case 2:
                cout << "\t\t\t\t\t\t\tEnter new Description: ";
                getline(cin, newdescription);
                cout << endl;
                IncompleteTask[updateIndex]->TaskDescription = newdescription;
                break;

            case 3:
            {
                do
                {
                    cout << "\t\t\t\t\t\t\tEnter new Deadline: ";
                    cin >> ws;
                    getline(cin, newDeadline);
                    if (isValidDate(newDeadline) == false)
                    {
                        cout << "\n\t\t\t\t\t\t\tInvalid date entered!" << endl;
                    }
                    else
                    {
                        dateflag = true;
                    }
                } while (dateflag == false);

                IncompleteTask[updateIndex]->deadline = newDeadline;
                break;
            }
            case 4:
            {
                cout << "\t\t\t\t\t\t\tEnter new Priority: ";
                cin >> newPriority;
                IncompleteTask[updateIndex]->TaskPriority = newPriority;
                break;
            }
            case 5:
                cout << endl
                     << endl
                     << endl
                     << endl;
                cout << "\t\t\t\t\t\t\t-------------------------------------------------------" << endl;
                cout << "\t\t\t\t\t\t\t|                                                      |" << endl
                     << "\t\t\t\t\t\t\t| > Select your desired Category:                      |" << endl
                     << "\t\t\t\t\t\t\t|                                                      |" << endl
                     << "\t\t\t\t\t\t\t|   1 >> Work                                          |" << endl
                     << "\t\t\t\t\t\t\t|   2 >> Personal                                      |" << endl
                     << "\t\t\t\t\t\t\t|   3 >> Education                                     |" << endl
                     << "\t\t\t\t\t\t\t|   4 >> Finances                                      |" << endl
                     << "\t\t\t\t\t\t\t|   5 >> Other                                         |" << endl
                     << "\t\t\t\t\t\t\t|                                                      |" << endl
                     << "\t\t\t\t\t\t\t ------------------------------------------------------ " << endl;
                do
                {
                    cout << "\t\t\t\t\t\t\tChoice: ";
                    cin >> opt;
                    if (opt == 1)
                    {
                        newCategory = "Work";
                    }
                    else if (opt == 2)
                    {
                        newCategory = "Personal";
                    }
                    else if (opt == 3)
                    {
                        newCategory = "Education";
                    }
                    else if (opt == 4)
                    {
                        newCategory = "Finances";
                    }
                    else if (opt == 5)
                    {
                        cout << "\t\t\t\t\t\t\tEnter category name: ";
                        cin >> ws;
                        getline(cin, newCategory);
                    }
                    else
                    {
                        cout << "\t\t\t\t\t\t\t Wrong input...Try Again!" << endl;
                    }
                } while (opt < 1 || opt > 5);
                IncompleteTask[updateIndex]->category = newCategory;
                break;

            default:
                cout
                    << "\t\t\t\t\t\t\tWrong Input!"
                    << endl;
                flag = false;
            }
        } while (choice < 1 || choice > 4);

        if (flag)
        {
            cout << endl;
            displayHeading();
            DisplaySingleTask(updateIndex);
            cout << endl;
            cout << "\t\t\t\t\t\t\tSuccessfully Updated!" << endl;
        }
    }
    void PrioritizeUP(int child) // Like HeapifyUp
    {
        if (child <= 0)
            return;

        int parent = child / 2;
        if (IncompleteTask[parent]->TaskPriority > IncompleteTask[child]->TaskPriority)
            return;
        else
        {
            swap(IncompleteTask[parent], IncompleteTask[child]);
            PrioritizeUP(parent);
        }
    }
    void Heapify(int i, int I_current_size)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left <= I_current_size && IncompleteTask[left]->TaskPriority > IncompleteTask[largest]->TaskPriority)
        {
            largest = left;
        }

        if (right <= I_current_size && IncompleteTask[right]->TaskPriority > IncompleteTask[largest]->TaskPriority)
        {
            largest = right;
        }

        if (largest != i)
        {
            swap(IncompleteTask[i], IncompleteTask[largest]);
            Heapify(largest, I_current_size);
        }
    }
    void DisplayAllTask()
    {
        if (I_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tScheduler is Empty!" << endl;
            return;
        }
        displayHeading();
        for (int TaskIndex = 0; TaskIndex <= I_current_size; TaskIndex++)
        {
            DisplaySingleTask(TaskIndex);
        }
    }

    void DisplaySingleTask(int TaskIndex)
    {
        // cout << "\t\t\t\t\t\t\t" << TaskIndex + 1 << setw(15) << IncompleteTask[TaskIndex]->TaskID << setw(15) << IncompleteTask[TaskIndex]->TaskName << setw(15) << IncompleteTask[TaskIndex]->deadline << setw(15) << IncompleteTask[TaskIndex]->TaskPriority << setw(15) << IncompleteTask[TaskIndex]->category << setw(15);
        cout << "\t\t\t\t\t\t\t" << TaskIndex + 1 << setw(14) << IncompleteTask[TaskIndex]->TaskID << setw(30) << IncompleteTask[TaskIndex]->TaskName << setw(15) << IncompleteTask[TaskIndex]->deadline << setw(15) << IncompleteTask[TaskIndex]->category << setw(15);
        if (IncompleteTask[TaskIndex]->status)
            cout << "Completed" << endl;
        else
            cout << "Pending" << endl;
    }

    bool removeTask(int id)
    {
        if (I_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tScheduler is Empty!" << endl;
            return false;
        }
        int idx = searchTask(id);
        if (idx != -1)
        {
            for (int i = idx; i <= I_current_size; i++)
            {
                IncompleteTask[i] = IncompleteTask[i + 1];
            }
            I_current_size--;

            return true;
        }
        else
        {
            return false;
        }
    }
    void markTaskasComplete()
    {
        if (I_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tScheduler is EMPTY!" << endl;
            return;
        }
        IncompleteTask[0]->status = true;
        displayHeading();
        DisplaySingleTask(0);
        CompletedTask[++C_current_size] = DequeueTask();
    }
    void getHighestTask()
    {
        if (I_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tScheduler EMPTY!" << endl;
            return;
        }
        displayHeading();
        DisplaySingleTask(0);
        cout << endl;
        cout << "\t\t\t\t\t\t\tDescription: " << IncompleteTask[0]->TaskDescription << endl;
    }
    void getNextHighestTask()
    {

        if (I_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tScheduler EMPTY!" << endl;
            return;
        }
        if (IncompleteTask[1] != NULL && IncompleteTask[2] != NULL)
        {

            if (IncompleteTask[1]->TaskPriority > IncompleteTask[2]->TaskPriority)
            {
                displayHeading();
                DisplaySingleTask(1);
                cout << endl;
                cout << "\t\t\t\t\t\t\tDescription: " << IncompleteTask[1]->TaskDescription << endl;
            }
            else
            {
                displayHeading();
                DisplaySingleTask(2);
                cout << endl;
                cout << "\t\t\t\t\t\t\tDescription: " << IncompleteTask[2]->TaskDescription << endl;
            }
        }
        else if (IncompleteTask[1] != NULL)
        {
            displayHeading();
            DisplaySingleTask(1);
            cout << endl;
            cout << "\t\t\t\t\t\t\tDescription: " << IncompleteTask[1]->TaskDescription << endl;
        }
        else if (IncompleteTask[2] != NULL)
        {
            displayHeading();
            DisplaySingleTask(2);
            cout << endl;
            cout << "\t\t\t\t\t\t\tDescription: " << IncompleteTask[2]->TaskDescription << endl;
        }
        else
        {
            cout << "\t\t\t\t\t\t\tNo higher priority Task left!" << endl;
            return;
        }
    }
    void displayHeading()
    {
        cout << "\t\t\t\t\t\t\t"
             << "TaskIndex" << setw(10) << "TaskID" << setw(20) << "Name" << setw(20) << "Deadline" << setw(15) << "Category" << setw(13) << "Status" << endl;
        // cout << "\t\t\t\t\t\t\t" << "TaskIndex" << setw(10) << "TaskID" << setw(10) << "Name" << setw(18) << "Deadline" << setw(15) << "Priority" << setw(13) << "Category" << setw(13) << "Status" << endl;
    }
    void getDescriptionofTask(int index)
    {
        cout << "\t\t\t\t\t\t\tTask Name:  " << IncompleteTask[index]->TaskName << endl;
        cout << "\t\t\t\t\t\t\tDescription: " << IncompleteTask[index]->TaskDescription << endl;
    }

    void DisplayCompletedTask()
    {
        if (C_current_size == -1)
        {
            cout << "\t\t\t\t\t\t\tNo Completed Task yet!" << endl;
            return;
        }
        displayHeading();
        for (int TaskIndex = 0; TaskIndex <= C_current_size; TaskIndex++)
        {
            // cout << "\t\t\t\t\t\t\t" << TaskIndex + 1 << setw(15) << CompletedTask[TaskIndex]->TaskID << setw(15) << CompletedTask[TaskIndex]->TaskName << setw(15) << CompletedTask[TaskIndex]->deadline << setw(15) << CompletedTask[TaskIndex]->TaskPriority << setw(15) << IncompleteTask[TaskIndex]->category << setw(15);
            cout << "\t\t\t\t\t\t\t" << TaskIndex + 1 << setw(14) << CompletedTask[TaskIndex]->TaskID << setw(30) << CompletedTask[TaskIndex]->TaskName << setw(15) << CompletedTask[TaskIndex]->deadline << setw(15) << CompletedTask[TaskIndex]->category << setw(15);
            if (CompletedTask[TaskIndex]->status)
                cout << "Completed" << endl;
            else
                cout << "Pending" << endl;
        }
    }
    void displaythroughCategory(string category)
    {
        bool flag = false;
        for (int i = 0; i < I_current_size; i++)
        {
            if (IncompleteTask[i]->category == category)
            {
                flag = true;
                DisplaySingleTask(i);
            }
        }
        if (flag == false)
        {
            cout << endl
                 << "\t\t\t\t\t\t\tNo such Task related to this category exists!" << endl;
        }
    }

    ~PriorityQueue()
    {
        for (int i = 0; i < I_current_size; i++)
        {
            delete IncompleteTask[i];
        }
        delete[] IncompleteTask;
    }
};

int main()
{
    PriorityQueue p;
    system("color F0");
    system("CLS");
    p.DisplayMenu();

    return 0;
}