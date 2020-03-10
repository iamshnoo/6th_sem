/*****************************************************************
 * The idea is to create a number of processes and associate with each process a 'mailbox'
 * where a single message for each process can be stored.
 * You will use semaphores to ensure that there is at most one message in each mailbox.
 * The number of processes should be controlled by the first command line parameter ('numproc').
 * In your programm, limit the maximum number of processes to 100 (define a constant NUMPROC
 * with that value and check the input parameter so that it does not exceed this value).
 * In the parent process, use the fork() system call to create 'numproc' number of child processes.
 * Associated with each process is a mailbox, containing a message that is defined by
 * the following C structure:
 *   struct msg {
 *       int from;       // sender index
 *       int type;       // 0=request, 1=response, -1=termination
 *       int val;        // beginning of range
 *   };
 *
 * Create an array of mailboxes (of length NUMPROC) to store at most one message for each mailbox.
 * These mailboxes are shared (created using shmget() system call) and accessable by all the process.
 * Use semaphores to control access to each mailbox.
 * Further, write two procedures, sendmsg and recvmsg, with the following interfaces:
 * sendmsg(int to, struct msg *pmsg);
 * recvmsg(int from, struct msg *pmsg);
 *
 * The index of a process is its number so the index of the parent process is zero,
 * the first child process is one, and so on. The sendmsg call should block if somebody is currently
 * writing into a mailbox and recvmsg should block if a mailbox is empty.
 * Your program will use two command line arguments as follows
 * ./mailbox numproc numvals
 * to determine how it works. The first argument is the number of child processes to be created
 * and the second argument is the maximum number of integers for which factorial to be calculated.
 * The parent process distributes the work load to all the child process in the form of a number
 * to calculate the factorial. Whenever a process sends back a result, the parent process prints it
 * (the number, its factorial. and the child process that computed the factorial) out.
 * If factorial of more numbers are remaining to be calculated, the parent sends the next number
 * to this newly free process. This continues until the parent has finished the numbers
 * when It (parent process) sends a termination message to the child process.
 * The parent then cleans up all the resources and then exits.
 * To simulate processors of different speed, each child should delay the response for a number of
 * seconds corresponding to its identifier (1 second for process 1, 2 seconds for process 2, etc.).
 * If the message type received is -1, the child exits immediately.
 *
 * Please ensure that your program(s) are well-documented and properly indented.
 *****************************************************************/



/*
 * I could not do this question.
 */