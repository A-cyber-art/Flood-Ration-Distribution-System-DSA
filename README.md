# Flood Ration Distribution System 🚁📦

## 📖 Project Overview
This project aims to facilitate the fair and rapid distribution of ration packets during natural disasters like floods. It systematically manages victim registration, urgent help requests, and ration allocation using core Data Structures. Each data structure is implemented to solve a specific real-world logistical challenge, ensuring no victim is left out and resources are managed efficiently.

## 🎯 Problem Statement & Objectives
During flood disasters, manual distribution often leads to mismanaged records, unfair allocation, and delayed responses to critical cases. This system replaces manual inefficiencies with a fast, reliable, and user-friendly automated structure. 
* Build a reliable system for ration management.
* Utilize core DSA concepts to organize records.
* Prioritize urgent cases (infants, medical emergencies).
* Prevent common errors like duplicate entries or accessing empty stock.

## 🧠 Data Structures Used
* **Linked List:** Maintains the sequence of registered victims in their original order of registration for sequential processing and display.
* **Binary Search Tree (BST):** Organizes victims by their CNIC numbers, enabling $O(\log n)$ time complexity for rapid searching and deletion among hundreds of records.
* **Stack (LIFO):** Handles urgent priority cases (infants/medical). The most recent urgent case is processed first. Also used to track the delivery path to trace volunteers.
* **Queue (FIFO):** Manages the ration stock. Ensures that the earliest added packets are distributed first to the eligible victims in line.
* **Recursion:** Utilized for tree traversals (e.g., Inorder) and verifying complete coverage of victims without missing records.

## ⚙️ Key Features & Functions
1. `RegisterVictim()`: Adds details to BST and Linked List.
2. `SearchVictimByCNIC()`: Rapid lookup using BST.
3. `DisplayAllVictims()`: Iterates through the Linked List.
4. `AddRationPacket()` & `DistributeRation()`: Manages stock via Queue.
5. `FindHighestPriorityVictim()`: Traverses BST for priority cases.
6. `ProcessUrgentRequest()`: Pushes urgent cases to the Stack.
7. `TrackDeliveryPath()`: LIFO tracking for delivery volunteers.
8. `DeleteVictimByCNIC()`: Removes completed records seamlessly.

## 🛡️ Error Handling
* Avoids duplicate CNIC entries before insertion.
* Queue underflow checks before ration distribution.
* Stack underflow checks for urgent requests.
* Meaningful user prompts instead of program crashes.
