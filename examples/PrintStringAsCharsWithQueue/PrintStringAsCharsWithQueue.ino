/*
 *  Manage a string by using a generic, dynamic queue data structure.
 *
 *  Copyright (C) 2020  Quantum Studio Technologies Inc. (alex.mytko@gmail.com)
 */


#include <Queue.h>                            // include queue library header

// declare a string message
const String msg = "You're use Queue for printing string as array of chars.";

Queue<char> queue;                            // create a queue of characters

// startup point entry (runs once)
void setup() {
  Serial.begin(115200);                       // start serial communication
  
  for (uint8_t i = 0; i < msg.length(); i++)  // enqueue all the message's characters to the queue
    queue.push(msg.charAt(i));
    
  while (!queue.isEmpty())                    // dequeue all the message's characters from the queue
    Serial.print(queue.pop());

  Serial.println();                           // print end of line character
}

// loop the main sketch
void loop() { }
