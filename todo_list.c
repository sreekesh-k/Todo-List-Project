#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

struct Task
{
    int taskid;
    char title[20];
    char description[100];
    struct Task *next;
};
struct Task *todoList = NULL;
int taskid = 0;
char taskDescription[100];
char title[20];
void quote()
{
    srand(time(NULL));
    const char *welcomeQuotes[] = {
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
    printf("%s\n", welcomeQuotes[randomquote]);
}

void lod()
{
    int i;
    const char *anim[] = {".", "..", "..."};
    system("cls");
    for (i = 0; i < 6; i++)
    {
        printf("\rLoading %s", anim[i % 3]);
        Sleep(150);
        system("cls");
    }
}
struct Task *addTask(struct Task *head, const char *title, const char *description)
{
    struct Task *newTask = (struct Task *)malloc(sizeof(struct Task));
    newTask->taskid = ++taskid;
    strncpy(newTask->description, description, sizeof(newTask->description));
    strncpy(newTask->title, title, sizeof(newTask->title));
    newTask->next = head;
    return newTask;
}

int displayTasks(struct Task *head)
{
    if (head == NULL)
    {
        printf("Nothing in your list :(\n");
        return -1;
    }
    printf("Todo List\n");
    printf("SNO  ID  TITLE\n");
    struct Task *current = head;
    int taskNumber = 1;

    while (current != NULL)
    {
        printf("%d.  [%d] %s:\n", taskNumber, current->taskid, current->title);
        printf("%s\n\n", current->description);
        current = current->next;
        taskNumber++;
    }
    printf("____________________________________________\n\n");
    return 0;
}
struct Task *removeTask(struct Task *head, int e)
{

    if (head->taskid == e)
    {
        printf("%d: %s is removed from the list\n", e, head->title);
        head = head->next;
        return head;
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
            printf("%d: %s is removed from the list\n", e, t->next->title);
            t->next = t->next->next;
            return t;
        }
        else
        {
            printf("Check id again not found\n");
        }
    }
}
int add(int ch)
{

    while (ch == 1)
    {
        while (getchar() != '\n')
            ;
        printf("1:Add Task To Your List\n");
        printf("___________________________________________\n");
        printf("Enter Title: ");
        fgets(title, sizeof(title), stdin);
        title[strcspn(title, "\n")] = '\0';
        int i;
        for (i = 0; title[i] != '\0'; i++)
        {
            title[i] = toupper(title[i]);
        }
        printf("Enter Description: ");
        fgets(taskDescription, sizeof(taskDescription), stdin);
        taskDescription[strcspn(taskDescription, "\n")] = '\0';
        todoList = addTask(todoList, title, taskDescription);
        printf("List is updated:)\n1:Add another task\t2:Back\nCHOICE:");
        scanf("%d", &ch);
        if (ch == 2)
            break;
    }
    return 0;
}

int disp(int ch)
{
    printf("2:View Tasks\n");
    printf("___________________________________________\n");
    ch = displayTasks(todoList);
    if (ch == -1)
    {
        printf("what are we waiting for lets add something new in our list?\n");
        printf("1:Add task\t2:Later\nCHOICE:");
        scanf("%d", &ch);
        if (ch == 1)
        {
            add(ch);
        }
        else
            return -1;
    }
    else
    {

        printf("Great start keep adding tasks and lets complete them together\n");
        printf("1.Back\nCHOICE:");
        scanf("%d", &ch);
        if (ch == 1)
            return -1;
    }
}

/*int delete(int ch)
{

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
            while (ch == 1)
            {
                system("cls");
                while (getchar() != '\n')
                    ;
                printf("1:Add Task To Your List\n");
                printf("___________________________________________\n");
                printf("Enter Title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = '\0';
                int i;
                for (i = 0; title[i] != '\0'; i++)
                {
                    title[i] = toupper(title[i]);
                }
                printf("Enter Description: ");
                fgets(taskDescription, sizeof(taskDescription), stdin);
                taskDescription[strcspn(taskDescription, "\n")] = '\0';
                todoList = addTask(todoList, title, taskDescription);
                printf("List is updated:)\n1:Add another task\t2:Back\nCHOICE:");
                scanf("%d", &ch);
                if (ch == 2)
                    menu();
            }
        }
        else
            menu();
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
            if (ch == 2)
                menu();
            else
            {
                system("cls");
                ch = displayTasks(todoList);
                if (ch = -1)
                    break;

                printf("Enter the id of the task that you want to remove: ");
                scanf("%d", &ch);
                todoList = removeTask(todoList, ch);
                ch = 1;
            }
        }
    }
}*/
void menu()
{
    lod();
    int ch = 0;
    printf("TACT- MENU\n");
    printf("___________________________________________\n");
    printf("1:Add Task To Your List    2:View Tasks\n");
    printf("3:Manage My List           4:Exit\n");
    printf("___________________________________________\nCHOICE:");
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        system("cls");
        ch = add(ch);
        if (ch == 0)
        {
            menu();
        }
        break;
    case 2:
        lod();
        ch = disp(ch);
        if (ch == -1)
        {
            menu();
        }
        break;
    case 3:
        lod();
        // ch = delete (ch);
        break;
    case 4:
        system("cls");
        printf("See You Later (a reminder will be send incase if you forget to complete tasks on list before time)");
        Sleep(3000);
        break;
    default:
        printf("PLEASE SELECT FROM THE ABOVE OPTION");
        Sleep(2000);
        menu();
        break;
    }
}
int main()
{
    system("cls");
    printf("WELCOME TO TACT Todolist\n");
    Sleep(2000);
    quote();
    Sleep(3000);
    menu();

    struct Task *current = todoList;
    while (current != NULL)
    {
        struct Task *next = current->next;
        free(current);
        current = next;
    }

    return 0;
}
