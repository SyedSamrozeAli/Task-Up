# Task-Up

# - Description: 
The project is a user centric task scheduler utilizing a priority queue data structure, offering a user defined prioritization criteria providing a customizable and efficient task management 

# - Objective:  
The aim of the project is to develop an efficient task scheduler using priority queues. Task schedulers are crucial tools for organizing and managing daily tasks efficiently. The problem at hand is to create a system that can handle task insertion, removal, prioritization, and updates effectively. The unique thing about this project is that we have distinguished between deadline and priority by allowing the user to set priority according to their comfort and task execution, regardless of the deadline. 

# - Functionalities: 
Insertion of tasks with various parameters (name, description, priority, deadline, category). 
Dequeuing the highest priority task. 
Updating task details (name, description, deadline, category). 
Removal of tasks. 
Marking tasks as completed. 
Viewing Overdue tasks 
Displaying tasks based on priority, category, and completion status. 

 

# - Description about Used Data Structure Concept 

Priority Queue Implementation: The core data structure employed in this project is a Priority Queue, implemented as a max heap. A priority queue is ideal for managing tasks based on their priority levels, ensuring that the highest priority task is always processed first. 

Heap for Priority Queue:  The incomplete tasks are stored in a max heap to facilitate efficient insertion and removal of tasks based on their priority. The heap property ensures that the highest priority task is at the root, allowing for constant time access. 

Stack for Handling Task Deadlines: In the project, the stack data structure is employed to handle and compare task deadlines efficiently. When updating a task's details, especially its deadline, the project extracts date components (year, month, and day) using a stack. The stack efficiently manages the extraction and comparison of date components, ensuring accurate adjustments to the task priority based on deadline changes.  

Dynamic Arrays for Task Storage: Dynamic arrays play a pivotal role in the storage and management of tasks within the project. The IncompleteTask/CompletedTask array, responsible for holding the tasks in the scheduler, is dynamically allocated. This dynamic array facilitates the addition and removal of tasks without the need for a fixed, predefined size. The dynamic array's flexibility ensures efficient memory utilization, adapting to the changing number of tasks in the scheduler. 

# - Efficiency Analysis 

Time Complexity: 

Insertion (Enqueue): O(n)

Dequeue (Deletion of Highest Priority): O(n) 

Update: O(n) 

Search: O(n) 

Displaying All Tasks: O(n) 


Space Complexity: 

Heap Space: O(n) 

Stack Space: O(n) 

Other Data Structures: O(1) – (as mostly pointers)Constant space for auxiliary data structures. 
