/*
This is an extension to the earlier assignment where you will support the
presence of multiple | (pipe)in the command line.
For example when the program is executed as ./a.out cmd1| cmd2 | cmd3 | .......|
cmdn, It creates n -1 pipes.cmd1 will write to write end of the first pipe cmd2
will read from the first pipe and write to write end of the 2nd pipe. In general
cmdi will write to the write end of ith pipe and cmd(i + 1) will write to the
write end of the(i + 1) st pipe and so on. Finally cmdn will print its output to
the standard output.
*/