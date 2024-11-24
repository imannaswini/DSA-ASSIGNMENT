/*
Problem Statement: 
You have been tasked with implementing a circular queue data structure using linked storage in C language. The queue 
should include a header node that stores the number of nodes in the queue, as well as the largest and smallest values 
currently present in the queue. Implement the following operations for this circular queue: 
1. Initialize Queue: Write a function to initialize an empty circular queue with a header node. The header node should 
have its count initialized to 0, and largest and smallest initialized to appropriate values. 
2. Enqueue: Write a function to enqueue an integer value into the circular queue. Update the header node's count, 
largest, and smallest accordingly. 
3. Dequeue: Write a function to dequeue an element from the circular queue. Update the header node's count, largest, 
and smallest appropriately. 
4. Get Largest Value: Write a function to retrieve the largest value from the circular queue. 
5. Get Smallest Value: Write a function to retrieve the smallest value from the circular queue. 
6. Display Queue: Write a function to display the elements of the circular queue, starting from the front.
_____________________________________________________________________________________________________________________*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
// Define the structure for a queue node
struct Node 
{
 int data;
 struct Node* next;
};
// Define the structure for the header node
struct header
 {
 int count;
 int largest;
 int smallest;
 struct Node* front;
 struct Node* rear;
};
// Function to initialize an empty circular queue
struct header* initializeQueue() 
{
 struct header* header = (struct header*)malloc(sizeof(struct header));
 header->count = 0;
 header->largest = INT_MIN;
 header->smallest = INT_MAX;
 header->front = NULL;
 header->rear = NULL;
 return header;
}
// Function to enqueue an integer value into the circular queue
void enqueue(struct header* header, int value)
 {
 struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
 newNode->data = value;
 if (header->count == 0) 
{
 header->front = newNode;
 header->rear = newNode;
 newNode->next = newNode; // Points to itself in a circular manner
 }
  else 
{
 newNode->next = header->front;
 header->rear->next = newNode;
 header->rear = newNode;
 }
 // Update header information
 header->count++;
 if (value > header->largest)
 {
 header->largest = value;
 }
 if (value < header->smallest) 
{
 header->smallest = value;
}
 //printf(“enqueue: %d\n”, value);
 printf("enqueue:%d\n",value);
}
// Function to dequeue an element from the circular queue
void dequeue(struct header* header) 
{
 if (header->count == 0)
 {
 //printf(“Queue is empty, cannot dequeue.\n");
 printf("Queue is empty, cannot dequeue.\n");
 return;
 }
 int removedValue = header->front->data;
 struct Node* temp = header->front;
 if (header->count == 1) 
{
 header->front = NULL;
 header->rear = NULL;
 header->largest = INT_MIN;
 header->smallest = INT_MAX;
 } 
else 
{
 header->front = header->front->next;
 header->rear->next = header->front;
 
 // Update largest and smallest values
 if (removedValue == header->largest || removedValue == header->smallest) 
{
 struct Node* current = header->front;
 header->largest = INT_MIN;
 header->smallest = INT_MAX;
 int i;
 //for(i=0; i< header->count – 1;i++) 
 for(i=0;i<header->count-1;i++)
{
 if (current->data > header->largest) header->largest = current->data;
 if (current->data < header->smallest) header->smallest = current->data;
 current = current->next;
 }
 }
 }
 free(temp);
 header->count--;
 printf("Dequeue: %d\n", removedValue);
}
// Function to get the largest value from the circular queue
int getLargestValue(struct header* header)
 {
 if (header->count == 0)
 {
 printf("Queue is empty.\n");
 return INT_MIN;
 }
 return header->largest;
}
// Function to get the smallest value from the circular queue
int getSmallestValue(struct header* header)
 {
 if (header->count == 0) 
{
 printf("Queue is empty.\n");
 return INT_MAX;
 }
 return header->smallest;
}
// Function to display the elements of the circular queue
void displayQueue(struct header* header)
 {
 if (header->count == 0) 
{
 printf("Queue is empty.\n");
 return;
 }
 struct Node* current = header->front;
 printf("Queue elements:\n");
 int i;
 for (i = 0; i < header->count; i++) 
{
 printf("%d\n", current->data);
 current = current->next;
 }
 //printf("\n");
}
// Main function to test the circular queue implementation
int main() 
{
 struct header* queue = initializeQueue();
 enqueue(queue, 10);
 enqueue(queue, 20);
 enqueue(queue, 5);
 enqueue(queue, 30);
 displayQueue(queue);
 printf("Largest value: %d\n", getLargestValue(queue));
 printf("Smallest value: %d\n" ,getSmallestValue(queue));
 dequeue(queue);
 displayQueue(queue);
 printf("Largest value: %d\n", getLargestValue(queue));
 printf("Smallest value: %d\n", getSmallestValue(queue));
 return 0;
}