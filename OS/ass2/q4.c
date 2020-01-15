// Child Processes execute different Programs with switches

/**************************************************************
 * In the previous assignment we have developed a C program which
 * when executed as "./a.out executable1 executable2 ... executableN"
 * creates N child processes where the 1st child process 1st executes
 * the 1st executable file (given by executable1).
 * 2nd executes the 2nd executable file (given by executable2) and so on.
 * Please note that in this assignment no scope was there to pass
 * command line arguments to the executables. Extend the  assignment
 * so that this can be done now. That is the program now can be called
 * as "./a.out ls -l ps -ef" such that 1st child process executes the
 * command "ls -" and the second one executes "ps -ef".!
 ****************************************************************/