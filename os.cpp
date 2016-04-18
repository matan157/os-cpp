#include<iostream>
#include<list>

// SOS Functions
// Channel commands
// siodrum arguments
//      1. Job Number
//      2. Job Size
//      3. Starting Core Address
//      4. 
//          a. 1 => move from core to drum
//          b. 0 => move from drum to core
void siodisk(int jobnum);
void siodrum(int jobnum, int jobsize, int coreaddress, int direction);
void ontrace(); // Print trace
void offtrace(); // Don't print trace
// Main Program
void startup() {
}
// Interrupt handlers
void Crint(int& a, int p[]) {
    // Arrival of a new job on the drum.
    // At call: p[1]    =   Job Number
    //          p[2]    =   Priority
    //          p[3]    =   Job Size, K bytes
    //          p[4]    =   Max CPU time allowed for job
    //          p[5]    =   Current time
}

void Dskint(int& a, int p[]) {
    // Disk interrupt
    // At call: p[5]    =   Current Time
}

void Drmint(int& a, int p[]) {
    // Drum interrupt
    // At call: p[5]    =   Current Time
}

void Tro(int& a, int p[]) {
    // Timer Run Out
    // At call: p[5]    =   Current Time
}

void Svc(int &a, int p[]) {
    // Supervisor call from user program.
    // At call: p[5]    = Current time
    //      a = 5   >   Job has terminated
    //      a = 6   >   Job requests disk i/o
    //      a = 7   >   Job wants to be blocked until
    //                  all its pending i/o requests are
    //                  completed.
}

// TODO: 
//      scheduler();
//      swapper();
//      Stuff like that

// Running a Job:
//  Before leaving each interrupt handler
//  you must call the dispatcher to send
//  info about which job to run.
//  The dispatched should set the a and p arguments as follows:
//      a = 1   CPU is idle, p is ignored
//      a = 2   CPU is in user mode,
//          p[0], p[1], and p[5] are ignored
//          p[2] = base address of job to run
//          p[3] = size of job to be run (in K)
//          p[4] = time quantum
