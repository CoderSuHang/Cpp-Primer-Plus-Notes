#pragma once
// ch12_10_queue.h -- interface for queue
#ifndef CH12_10_QUEUE_H_
#define CH12_10_QUEUE_H_
// This queue will contain Customer items
class Customer
{
private:
	long arrive;
	int processtime;
public:
	Customer() { arrive = processtime = 0; }

	void set(long when);
	long when() const { return arrive; }
	int ptime() const { return processtime; }
};

typedef Customer Item;

class Queue
{
private:
// class scope definitions
    // Node is a nested structure definition local to this class
    struct Node { Item item; struct Node* next; };
    enum { Q_SIZE = 10 };
// private class members
    Node* front;
    Node* rear;
    int items;
    const int qsize;
    // preemptive definitions to prevent public copying
    Queue(const Queue& q) : qsize(0) { }
    Queue& operator=(const Queue& q) { return *this; }
public:
    Queue(int qs = Q_SIZE); // creat queue with a qs limit
    ~Queue();
    bool isempty() const;
    bool isfull() const;
    int queuecount() const;
    bool enqueue(const Item& item);
    bool dequeue(Item& item);
};
#endif