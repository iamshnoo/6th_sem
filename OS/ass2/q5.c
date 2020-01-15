// Synchronizing termination of processes

/*****************************************************************
 * In the previous assignment you have written a C program which when executed
 * as "./a.out executable1 executable2 ... executableN" creates N additional
 * child processes where the 1st child process 1st executes the 1st executable
 * file (given by executable1). 2nd executes the 2nd executable file (given by
 * executable2) and so on. In this assignment modify the program so that the
 * parent process waits for completion of its N child processes. The parent
 * process reports whether a  child process executing a particular  executable
 * terminated normally or abnormally. Try to include as much detailed reporting
 * as possible.
 *****************************************************************/