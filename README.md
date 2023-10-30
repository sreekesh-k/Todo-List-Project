# Todo-List-Project
Using basic data structures like linked list and stack, i have created a simple todolist 
# PROJECT DETAILS 
1. PROJECT TITLE: 
Todo List (name of my todo list is TACT)
2. PROJECT AIM: 
To create a digital tool that helps individuals or teams organize, manage, and keep track of 
their tasks and responsibilities efficiently. 
3. FUNCTIONALITY: 
Task Creation 
Task Display 
Task Editing 
Task Completion 
Sorting and Filtering 
Task Priority 
Categories or Labels 
4. DATA STRUCTURE USED FOR THE IMPLEMENTATION: 
Linked list (linked stack and linked queue) 
5. REASON FOR CHOOSING THE SPECIFIC DATA (ANSWER FOR THE ABOVE QUESTION) 
STRUCTURE FOR THE IMPLEMENTATION: 
Used For: Lists of tasks or items that require frequent insertions and deletions. 
Why: Linked lists excel in dynamic task management because they allow efficient insertion 
and deletion of tasks. Each task is stored in a node, and nodes are linked together, making it 
easier to maintain the list's structure. And it will be memory efficient if we use linked list for 
the project. 
6. SIMILAR SOLUTIONS PRESENT:
Microsoft To-Do, Todoist, Google Keep 
7. NOVELTY/CREATIVITY IN YOUR PROJECT: 
On completion of the task, user will get points which will motivate the user to complete their 
tasks on time. On time completion, before time completion points varies. Also failing to 
complete the task will result in negative points. 
Users can use this to compare their level (based on points) with other people. Can be used in 
an office to see which employee has most performance

# WHAT IS UNIQUE? 
1. Added a small loading screen and other animation to get a real application like feel. 
2. Added points:
>  +Completing task will increase the points.
> +If a task is deleted before its completion, user will lose points as it is 
   assumed that the user could complete the task. 
3. In this to-do list I have tried to show the function call stack in the following way: 
> - When there is no task, and user tries to delete, manage or view the tasks 
  It will ask suggestion like “Would you like to add task”. Then it calls the 
  add function from the view function.

  |add()| 
  | --------|
  |view()|
  |menu()|
  |main()|
> + Now if we select ‘back’ from the add function, it will take us back to the view menu.
>* Similarly there is a function stack maintained for each menu functions, to 
    provide a good user experience. 
 



