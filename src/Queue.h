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
      Queue();								      // init the queue (constructor)
      ~Queue();							        // clear the queue (destructor)
      void	push(const T i);				// push an item to the queue.
      T 		pop();									// pop an item from the queue.
      T 		peek() const;						// get an item from the queue.
      bool 	isEmpty() const;				// check if the queue is empty.
      int 	count() const;					// get the number of items in the queue. 
      bool 	isFull() const;				  // check if the queue is full.
      void 	setPrinter(Print& p);	  // set the printer of the queue.

    private:
      void 	resize(const int s);					// resize the size of the queue.
      void 	error(const char * m) const;	// exit report method in case of error.
      static const int initialSize = 2;	  // the initial size of the queue.
      Print* 	printer; 									  // the printer of the queue.
      T*  	contents;    									// the array of the queue.
      int 	size;        									// the size of the queue.
      int 	items;       									// the number of items of the queue.
      int 	head;        									// the head of the queue.
      int 	tail;        									// the tail of the queue.
  };
  
#endif
