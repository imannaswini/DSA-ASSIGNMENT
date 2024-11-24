#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int processID;
    int burstTime;
    int remainingTime;
} Process;

typedef struct
 {
    Process* array;
    int front, rear, capacity;
} Queue;

// Function to initialize the queue
Queue* createQueue(int capacity) 
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (Process*)malloc(capacity * sizeof(Process));
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue* queue) 
{
    return queue->front == -1;
}

// Function to enqueue a process into the queue
void enqueue(Queue* queue, Process process)
 {
    if ((queue->rear + 1) % queue->capacity == queue->front) 
    {
        printf("Queue Overflow\n");
        return;
    }
    if (queue->front == -1)
        queue->front = 0;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = process;
}

// Function to dequeue a process from the queue
Process dequeue(Queue* queue) {
    Process process = queue->array[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % queue->capacity;
    }
    return process;
}

// Function to free the queue
void freeQueue(Queue* queue) {
    free(queue->array);
    free(queue);
}

// Function to display the Gantt Chart
void displayGanttChart(int processID, int start, int end) {
    printf("| P%d (%d-%d) ", processID, start, end);
}

// Main function implementing round robin scheduling
int main() {
    int n, timeQuantum, time = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process* processes = (Process*)malloc(n * sizeof(Process));
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].processID = i + 1;
    }

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    Queue* queue = createQueue(n);
    for (int i = 0; i < n; i++) {
        enqueue(queue, processes[i]);
    }

    printf("\nGantt Chart:\n");
    while (!isEmpty(queue)) {
        Process current = dequeue(queue);
        int executionTime = (current.remainingTime > timeQuantum) ? timeQuantum : current.remainingTime;
        displayGanttChart(current.processID, time, time + executionTime);
        time += executionTime;
        current.remainingTime -= executionTime;
        if (current.remainingTime > 0) {
            enqueue(queue, current);
        }
    }
    printf("|\n");

    free(processes);
    freeQueue(queue);
    return 0;
}
