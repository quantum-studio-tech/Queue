// header defining the interface of the source.
#ifndef _QUEUE_H

  #define _QUEUE_H

  #if ARDUINO >= 100
    #include <Arduino.h>
  #else
    #include "WProgram.h"
  #endif

  /// The definition of the queue class.
  template<typename T> class Queue {
    public:
      Queue();                      // init the queue (constructor)
      ~Queue();                     // clear the queue (destructor)
      void	push(const T i);        // push an item to the queue.
      T 		pop();                  // pop an item from the queue.
      T 		peek() const;           // get an item from the queue.
      bool 	isEmpty() const;        // check if the queue is empty.
      int 	count() const;          // get the number of items in the queue. 
      bool 	isFull() const;         // check if the queue is full.
      //void 	setPrinter(Print& p);   // set the printer of the queue.

    private:
      void 	resize(const int s);          // resize the size of the queue.
      void 	error(const char * m) const;  // exit report method in case of error.
      static const int initialSize = 2;   // the initial size of the queue.
      //Print* 	printer; 									  // the printer of the queue.
      T*  	contents;                     // the array of the queue.
      int 	size;                         // the size of the queue.
      int 	items;                        // the number of items of the queue.
      int 	head;                         // the head of the queue.
      int 	tail;                         // the tail of the queue.
  };
  
  /// Init the queue (constructor).
  template<typename T> Queue<T>::Queue() {
    size = 0;                                       // set the size of queue to zero.
    items = 0;                                      // set the number of items of queue to zero.
    head = 0;                                       // set the head of the queue to zero.
    tail = 0;                                       // set the tail of the queue to zero.
    printer = NULL;                                 // set the printer of queue to point nowhere.
    contents = (T*)malloc(sizeof(T) * initialSize); // allocate enough memory for the array.
    if (contents == NULL)                           // if there is a memory allocation error.
      //error("QUEUE: insufficient memory to initialize queue.");
      return;
    size = initialSize;                             // set the initial size of the queue.
  }

  /// Clear the queue (destructor).
  template<typename T> Queue<T>::~Queue() {
    free(contents);   // deallocate the array of the queue.
    contents = NULL;  // set queue's array pointer to nowhere.
    printer = NULL;   // set the printer of queue to point nowhere.
    size = 0;         // set the size of queue to zero.
    items = 0;        // set the number of items of queue to zero.
    head = 0;         // set the head of the queue to zero.
    tail = 0;         // set the tail of the queue to zero.
  }

  /// Resize the size of the queue.
  template<typename T> void Queue<T>::resize(const int s) {
    if (s <= 0)                               // defensive issue.
      return;
      //error("QUEUE: error due to undesirable size for queue size.");
    T* temp = (T*)malloc(sizeof(T) * s);      // allocate enough memory for the temporary array.
    if (temp == NULL)                         // if there is a memory allocation error.
      return
      //error("QUEUE: insufficient memory to initialize temporary queue.");
    for (uint16_t i = 0; i < items; i++)      // copy the items from the old queue to the new one.
      temp[i] = contents[(head + i) % size];
    free(contents);                           // deallocate the old array of the queue.
    contents = temp;                          // copy the pointer of the new queue.
    head = 0;                                 // set the head and tail of the new queue.
    tail = items;                             // set the head and tail of the new queue.
    size = s;                                 // set the new size of the queue.
  }

  /// Add an item to the queue.
  template<typename T> void Queue<T>::push(const T i) {
    if (isFull())                 // check if the queue is full.
      resize(size * 2);           // double size of array.
    contents[tail++] = i;         // store the item to the array.
    if (tail == size) tail = 0;   // wrap-around index.
    items++;                      // increase the items.
  }

  /// Remove an item from the queue.
  template<typename T> T Queue<T>::pop() {
    if (isEmpty()) error("QUEUE: can't pop item from queue: queue is empty.");// check if the queue is empty.
    T item = contents[head++];// fetch the item from the array
    items--;// decrease the items
    if (head == size) head = 0;  // wrap-around index
    if (!isEmpty() && (items <= size / 4)) resize(size / 2);  // shrink size of array if necessary
    return item;// return the item from the array
  }

  /// Get the front of the queue.
  template<typename T> T Queue<T>::peek() const {
    if (isEmpty())            // check if the queue is empty.
      error("QUEUE: can't get the front item of queue: queue is empty.");
    return contents[head];    // get the item from the array.
  }

  /// Check if the queue is empty.
  template<typename T> bool Queue<T>::isEmpty() const {
    return items == 0;
  }

  /// Check if the queue is full.
  template<typename T> bool Queue<T>::isFull() const {
    return items == size;
  }

  /// Get the number of items in the queue.
  template<typename T> int Queue<T>::count() const {
    return items;
  }

  /// Set the printer of the queue.
  /*template<typename T> void Queue<T>::setPrinter(Print& p) {
    printer = &p;
  }*/

  /// Exit report method in case of error.
  /*template<typename T> void Queue<T>::error(const char* m) const {
    if (printer) printer->println(m);
  }*/

#endif
