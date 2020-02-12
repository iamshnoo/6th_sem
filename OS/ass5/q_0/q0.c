/*
There is a fixed size buffer and there are two types of processes;  
producer process and consumer processes. The producer processes produce 
items and enters them into the buffer and the consumer processes remove 
the items from the buffer and consume them.

A producer should not produce items into the buffer when the consumer 
is consuming an item from the buffer and vice versa. 
So the buffer should only be accessed by the producer or consumer at a time. 
The producer processes should also stop producing items if the buffer is 
full and the consumer process stops consuming items if the buffer is empty. 
Write a program to achieve the above-mentioned synchronization using semaphore.

Your program should be well indented and documented.
*/