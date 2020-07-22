// header defining the interface of the source.
#ifndef _QUEUE_H
#define _QUEUE_H

#include <Arduino.h>

// the definition of the queue class.
template<typename T> class Queue {
  public:
    Queue();								// init the queue (constructor)
    ~Queue();							// clear the queue (destructor)
    void	push(const T i);				// push an item to the queue.
    T 		pop();										// pop an item from the queue.
    T 		peek() const;							// get an item from the queue.
    bool 	isEmpty() const;				// check if the queue is empty.
    int 	count() const;					// get the number of items in the queue. 
    bool 	isFull() const;				// check if the queue is full.
    void 	setPrinter(Print& p);	// set the printer of the queue.

  private:
    void 	resize(const int s);					// resize the size of the queue.
    void 	error(const char * m) const;	// exit report method in case of error.
    static const int initialSize = 2;	// the initial size of the queue.
    Print* 	printer; 									// the printer of the queue.
    T*  	contents;    									// the array of the queue.
    int 	size;        									// the size of the queue.
    int 	items;       									// the number of items of the queue.
    int 	head;        									// the head of the queue.
    int 	tail;        									// the tail of the queue.
};

// init the queue (constructor).
template<typename T> Queue<T>::Queue() {
  size = 0;       // set the size of queue to zero.
  items = 0;      // set the number of items of queue to zero.
  head = 0;       // set the head of the queue to zero.
  tail = 0;       // set the tail of the queue to zero.
  printer = NULL; // set the printer of queue to point nowhere.
  // allocate enough memory for the array.
  contents = (T*)malloc(sizeof(T) * initialSize);
  // if there is a memory allocation error.
  if (contents == NULL) error("QUEUE: insufficient memory to initialize queue.");
  // set the initial size of the queue.
  size = initialSize;
}

// clear the queue (destructor).
template<typename T> Queue<T>::~Queue() {
  free(contents); // deallocate the array of the queue.
  contents = NULL; // set queue's array pointer to nowhere.
  printer = NULL;  // set the printer of queue to point nowhere.
  size = 0;        // set the size of queue to zero.
  items = 0;       // set the number of items of queue to zero.
  head = 0;        // set the head of the queue to zero.
  tail = 0;        // set the tail of the queue to zero.
}

// resize the size of the queue.
template<typename T> void Queue<T>::resize(const int s) {
  // defensive issue.
  if (s <= 0) error("QUEUE: error due to undesirable size for queue size.");
  // allocate enough memory for the temporary array.
  T* temp = (T*)malloc(sizeof(T) * s);
  // if there is a memory allocation error.
  if (temp == NULL) error("QUEUE: insufficient memory to initialize temporary queue.");
  // copy the items from the old queue to the new one.
  for (uint16_t i = 0; i < items; i++) temp[i] = contents[(head + i) % size];
  // deallocate the old array of the queue.
  free(contents);
  // copy the pointer of the new queue.
  contents = temp;
  // set the head and tail of the new queue.
  head = 0; 
  tail = items;
  // set the new size of the queue.
  size = s;
}

// add an item to the queue.
template<typename T> void Queue<T>::push(const T i) {
  // check if the queue is full.
  if (isFull()) resize(size * 2);// double size of array.
  // store the item to the array.
  contents[tail++] = i;
  // wrap-around index.
  if (tail == size) tail = 0;
  // increase the items.
  items++;
}

// remove an item from the queue.
template<typename T> T Queue<T>::pop() {
  if (isEmpty()) error("QUEUE: can't pop item from queue: queue is empty.");// check if the queue is empty.
  T item = contents[head++];// fetch the item from the array
  items--;// decrease the items
  if (head == size) head = 0;  // wrap-around index
  if (!isEmpty() && (items <= size / 4)) resize(size / 2);  // shrink size of array if necessary
  return item;// return the item from the array
}

// get the front of the queue.
template<typename T> T Queue<T>::peek() const {
  // check if the queue is empty.
  if (isEmpty ()) error("QUEUE: can't get the front item of queue: queue is empty.");
  // get the item from the array.
  return contents[head];
}

// check if the queue is empty.
template<typename T> bool Queue<T>::isEmpty() const {
  return items == 0;
}

// check if the queue is full.
template<typename T> bool Queue<T>::isFull() const {
  return items == size;
}

// get the number of items in the queue.
template<typename T> int Queue<T>::count() const {
  return items;
}

// set the printer of the queue.
template<typename T> void Queue<T>::setPrinter(Print& p) {
  printer = &p;
}

// exit report method in case of error.
template<typename T> void Queue<T>::error(const char* m) const {
  if (printer) printer->println(m);
}

#endif // _QUEUE_H