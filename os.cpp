#include<iostream>
#include<list>
#include<queue>
#include<map>

#include "freespace.h"
#include "PCB.h"

// Typedefs for easier use
typedef map<int, PCB> JobTable; // Index is JobNo. and value is PCB.
typedef list<freespace> FreeSpaceTable; // List of freespace nodes.
typedef queue<PCB *> IOQueue; // Queue of pointers to PCBs
typedef list<PCB *> DrumList; // List of pointers to PCBs in drum.


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

// Static variables
static JobTable job_table;
static FreeSpaceTable free_space_table;
static IOQueue io_queue;
static DrumList drum_list;
static int time; // Stores the current time. Taken from interrupts.

// Global Variables
bool job_using_cpu;
int using_drum;
int job_in_cpu; // -1 if no job, otherwise JobNo.
int job_in_io; // -1 if no job, otherwise JobNo.
int job_in_drum;

// Function headers
int find_mem_loc(int job_size);
void alloc_mem(int start_address, int job_size);
void dealloc_mem(int start_address, int job_size);
void insert_in_drum(int job_to_insert);
void try_to_swap_in();

// Finds job with highest priority in the job table and returns the job number. Ignores the job of specified number
int find_job(int ignore_job);

// Schedules jobs
bool scheduler(int &a, int p[], bool svc_block);

// I/O setup
void send_io(int &a, int p[]);
// Main Program
void startup() {
	ontrace();

	free_space_table.push_back(FreeSpace(0,100));
	time = 0;
	job_using_cpu = false;
	job_in_cpu = -1;
	job_in_io = -1;
	job_in_drum = 0;
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
