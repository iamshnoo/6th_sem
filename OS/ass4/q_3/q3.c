/*
This assignment is exactly similar to the previous assignment titled "Inter-Process Communication - 
An assignment on shared memory involving arbitrary number of processes." 

Let there be a process P0  and  n number other processes  P1, P2, ..., Pn, 
These processes are independently created by independent execution of one or 
more executable files. As shown in the following figure, 
all these processes  "share" integer variables n and  pid, and a character variable c (which works as a flag).

P1 creates n, pid, and c; and initializes c to 'n'. 
Subsequently, P1 regularly  "wakes up" (from "sleep") after a random amount of 
time (not more than 2 seconds) checks the value of c and if c is 'y'  
then prints the value of n (along with the corresponding pid) and makes c to be 'n' again. 

On the other hand, every Pi, 1≤ i ≤n,   
regularly  "wakes up" (from "sleep") after a random amount of time (not more than 2 seconds) 
checks the value of c and if c is 'n' then assigns some random value to n, 
along with its process id to pid, prints that value along with its own process id, and makes c to be 'y'.

If the program execution is terminated by the user (by pressing  Ctrl-C), 
both P1 and P2 should terminate and the allocated shared memory should be released.
*/