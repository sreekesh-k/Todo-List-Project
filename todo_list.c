#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

// structure for a task
struct Task
{
    int taskid;
    int complete;
    char title[20];
    char description[100];
    struct Task *next;
};
struct Task *todoList = NULL; // head of the linked list of tasks
// Global variables are used so that all functions has its acces
int taskid = 0;
char taskDescription[100];
char title[20];
int points = 0; // tracks points
void quote()    // For Displaying random quotes in the start of the program
{
    srand(time(NULL));
    const char *welcomeQuotes[] = {// used char pointer which points to an array of char
                                   "Welcome to TACT - Making Life Easier, One Click at a Time!",
                                   "Hello and welcome to TACT. Get ready to boost your productivity.",
                                   "Welcome to TACT. Where your tasks find their perfect home.",
                                   "Greetings! You're now entering the world of TACT.",
                                   "Welcome aboard! Let's sail through your day with TACT.",
                                   "Hello there! TACT is ready to assist you.",
                                   "Welcome to a new level of organization with TACT.",
                                   "Get comfortable, because TACT is here to help.",
                                   "Welcome to the future of task management with TACT.",
                                   "Greetings, fellow organizer! TACT is at your service."};

    int randomquote = rand() % (sizeof(welcomeQuotes) / sizeof(welcomeQuotes[0]));
    printf("%s\n", welcomeQuotes[randomquote]); // random Quote generator refered from chat gpt
}

void lod() // Simple Loading Animation
{
    int i;
    const char *anim[] = {".", "..", "..."};
    system("cls"); // clears terminal
    for (i = 0; i < 6; i++)
    { // goal = loading. loading.. loading...
        printf("\rLoading %s", anim[i % 3]);
        Sleep(150);
        system("cls");
    }
}

struct Task *addTask(struct Task *head, const char *title, const char *description)
{
    /*Refered from javapoint website, new way to use pointers to connect nodes
       node is passed as an argument, new node is allocated, new nodes next is head
       returned new node, which gives us head= new node
       almost similar to a linked stack where top is used in such way*/
    struct Task *newTask = (struct Task *)malloc(sizeof(struct Task));
    newTask->taskid = ++taskid;
    newTask->complete = 0;
    strncpy(newTask->description, description, sizeof(newTask->description));
    strncpy(newTask->title, title, sizeof(newTask->title));
    newTask->next = head;
    return newTask;
}

int displayTasks(struct Task *head) // print all tasks
{
    // simple display functions
    if (head == NULL)
    {
        printf("Nothing in your list :(\n");
        return -1; /*returns a -1 , which is used in if condition in the function which calls this function*/
    }
    printf("Todo List\n\n");
    struct Task *current = head;
    while (current != NULL)
    {
        // print [x] for completed task
        if (current->complete == 1)
            printf("[x]%d. %s:\n", current->taskid, current->title);

        else
            printf("[ ]%d. %s:\n", current->taskid, current->title);
        printf("%s\n\n", current->description);
        current = current->next;
        printf("____________________________________________\n");
    }

    return 0;
}

int completedTasks(struct Task *head) // Print completed tasks only
{
    // copy past of above display function with few changes
    if (head == NULL)
    {
        printf("Nothing in your list :(\n");
        return -1;
    }
    printf("Todo List\n\n");
    struct Task *current = head;
    while (current != NULL)
    {
        if (current->complete == 1)
        {
            printf("[x]%d. %s:\n", current->taskid, current->title);
            printf("%s\n\n", current->description);
            current = current->next;
            printf("____________________________________________\n");
        }
        else
            break;
    }

    return 0;
}

struct Task *removeTask(struct Task *head, int e) // removing tasks from list
{
    // no need to check for the head = null case as it is handled in the function which calls this function
    if (head->taskid == e)
    {
        printf("%d: %s is removed from the list\n", e, head->title);
        head = head->next;
        return head;
    }
    else
    { // basic deletion
        struct Task *t = head;
        while (t->next->taskid != e && t->next->next != NULL)
        {
            t = t->next;
        }
        if (t->next->taskid == e)
        {
            printf("%d: %s is removed from the list\n", e, t->next->title);
            if (t->next->complete == 0)
                --points; // points are reduced when they delete a task which is not complṇeted
            t->next = t->next->next;
            return t;
        }
        else
        {
            printf("Check id again not found\n");
            return head; /*used return type because insert was also return type, just in case if in future */
        }
    }
}

void mark(struct Task *head, int e) // marking the completed function
{
    // same delete function with statements changed
    if (head->taskid == e)
    {
        head->complete = 1;
    }
    else
    {
        struct Task *t = head;
        while (t->next->taskid != e && t->next->next != NULL)
        {
            t = t->next;
        }
        if (t->next->taskid == e)
        {
            t->next->complete = 1;
            ++points; // points increase when task completed
        }
        else
        {
            printf("Check id again not found\n");
        }
    }
}

int add(int ch)
{
    // this function calls the main insert function and prints the "add to your list" menu
    while (ch == 1)
    {
        system("cls");
        while (getchar() != '\n')
            ;
        printf("1:Add Task To Your List\n");
        printf("___________________________________________\n");
        printf("Enter Title: ");
        fgets(title, sizeof(title), stdin); // used fgets to get entire line
        title[strcspn(title, "\n")] = '\0'; // changed \n to \0 because \0 is string termination character(reduces error)
        int i;
        for (i = 0; title[i] != '\0'; i++)
        {
            title[i] = toupper(title[i]); // title is made to uppercase
        }
        printf("Enter Description: ");
        fgets(taskDescription, sizeof(taskDescription), stdin);
        taskDescription[strcspn(taskDescription, "\n")] = '\0';
        todoList = addTask(todoList, title, taskDescription);             // main add
        printf("List is updated:)\n1:Add another task\t2:Back\nCHOICE:"); // for adding again and again (ch will be 1 check while loop)
        scanf("%d", &ch);
        if (ch == 2)
            break; // going back
    }
    return ch; /*return type is used because it is needed for getting required output for below function
                 eg: when list displayed, if it has no tasks itll ask if u want to add now and this function is called*/
}

int disp(int ch)
{ // this function calls the main display finction and prints "display" menu
    printf("1:View Tasks\n");
    printf("___________________________________________\n");
    ch = displayTasks(todoList); // main display
    if (ch == -1)                // if -1 is returned there are no elements
    {
        printf("what are we waiting for lets add something new in our list?\n");
        printf("1:Add task\t2:Later\nCHOICE:");
        scanf("%d", &ch);
        if (ch == 1)
        {
            ch = add(ch);  // adds until it returns from add function
            system("cls"); // comes back to disp
            ch = disp(ch); // displays again to get new added elements
        }
    }
    else
    {
        printf("\n1.Back\nCHOICE:");
        scanf("%d", &ch);
    }
    return ch; // escaping from recussion line 224 and for manipulation in below functions
}

int compdisp(int ch)
{
    // calls the main completed task printing function and prints menu for comepletd task
    // same as disp function
    printf("2:Completed Tasks Tasks\n");
    printf("___________________________________________\n");
    ch = completedTasks(todoList);
    if (ch == -1)
    {
        printf("what are we waiting for lets add something new in our list?\n");
        printf("1:Add task\t2:Later\nCHOICE:");
        scanf("%d", &ch);
        if (ch == 1)
        {
            ch = add(ch);
            system("cls");
            ch = compdisp(ch);
        }
    }
    else
    {
        printf("\n1.Back\nCHOICE:");
        scanf("%d", &ch);
    }
    return ch;
}

int delete(int ch)
{ // this function calls the main delete function and prints delete menu
    // while to keep deleting until user decides
    while (ch == 1)
    {
        system("cls");
        printf("3:Manage My List\n");
        printf("___________________________________________\n");
        ch = displayTasks(todoList); // displays the data first
        if (ch == -1)                //-1 means empty same as in display
        {
            printf("what are we waiting for lets add something new in our list?\n");
            printf("1:Add task\t2:Later\nCHOICE:"); // if no data suggests to add
            scanf("%d", &ch);
            if (ch == 1)
            {
                ch = add(ch); // adds and comes back to delete menu
                system("cls");
                ch = delete (1); // delete func called reccusively to delete elements
                // same as in display
            }
        }
        else
        {
            ch = 1;
            while (ch == 1)
            {
                printf("Enter the id of the task that you want to remove: ");
                scanf("%d", &ch);
                todoList = removeTask(todoList, ch);
                printf("1.Delete again?\t2.Back\nCHOICE:");
                scanf("%d", &ch);
                if (ch == 1)
                    ch = delete (ch); // delete again ...long recussion found after drawing the memory allocation on a book
            }
            return ch; // to stop the recussion
        }
    }
    return ch;
}

int completed(int ch)
{
    // calls the marking as complete mark() function and prints "completed list menu"
    // same as the above delete function
    while (ch == 1)
    {
        system("cls");
        printf("3:Manage My List\n");
        printf("___________________________________________\n");
        ch = displayTasks(todoList);
        if (ch == -1)
        {
            printf("what are we waiting for lets add something new in our list?\n");
            printf("1:Add task\t2:Later\nCHOICE:");
            scanf("%d", &ch);
            if (ch == 1)
            {
                ch = add(ch);
                system("cls");
                ch = completed(1);
            }
        }
        else
        {
            ch = 1;
            while (ch == 1)
            {
                printf("Enter the id of the task that you want to Mark as completed: ");
                scanf("%d", &ch);
                mark(todoList, ch);
                system("cls");
                ch = displayTasks(todoList);
                printf("1.Mark again?\t2.Back\nCHOICE:");
                scanf("%d", &ch);
                if (ch == 1)
                    ch = completed(ch);
            }
            return ch;
        }
    }
    return ch;
}

void menu()
{
    lod();
    int ch = 0;
    while (ch != 5)
    { // Show menu until ch is 5 ie user inputs 5
        system("cls");
        printf("TACT- MENU\n");
        printf("___________________________________________\n");
        printf("1:Add Task To Your List    2:View Tasks\n");
        printf("3:Manage My List           4:View Points\n5:Exit\n");
        printf("___________________________________________\nCHOICE:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            system("cls");
            ch = add(ch);
            break;
        case 2: // TASKS
            system("cls");
            printf("VIEW TASKS\n");
            printf("___________________________________________\n");
            printf("1:All Tasks    2:Completed Tasks\n3:Back\n");
            printf("___________________________________________\nCHOICE:");
            scanf("%d", &ch);
            switch (ch)
            {
            case 1:
                ch = disp(ch); // display all tasks
                break;
            case 2:
                ch = compdisp(1); // displaying tasks which are completed
                break;
            case 3:
                break;
            }
            break;
        case 3: // MANAGE TASKS
            lod();
            printf("MANAGE TASKS\n");
            printf("___________________________________________\n");
            printf("1:Delete    2:Mark tasks as completed\n3:Back\n");
            printf("___________________________________________\nCHOICE:");
            scanf("%d", &ch);
            switch (ch)
            {
            case 1:
                ch = delete (ch); // deleting̥
                break;
            case 2:
                ch = completed(1); // marking as complete
                break;
            case 3:
                break;
            }
            break;
        case 4: // POINTS
            system("cls");
            printf("You have %d point(s)", points);
            Sleep(3000);
            if (points == 0)
            {
                printf("Complete tasks to earn points\n");
                Sleep(1000);
                printf("Note:deleting tasks before completing will reduce points\n");
                Sleep(3000);
            }
            break;
        case 5: // EXIT
            system("cls");
            printf("See You Later (a reminder will be send incase if you forget to complete tasks on list before time)");
            Sleep(3000);
            break;
        default:
            printf("PLEASE SELECT FROM THE ABOVE OPTION");
            Sleep(2000);
            break;
        }
    }
}

int main()
{
    system("cls"); // for clearing terminal
    printf("WELCOME TO TACT Todolist\n");
    Sleep(2000); // delay
    quote();
    Sleep(3000);
    menu(); // starts here

    // trying to free memmory
    struct Task *current = todoList;
    while (current != NULL)
    {
        struct Task *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
