#ifndef PCB_H
#define PCB_H

struct PCB {
	int job_number;
	int priority;
	int job_size;
	int max_cpu_time;
	int arrival_time;
	int cpu_time_used;
	int memory_position;

	bool in_core;
	bool on_io_queue;
	bool is_doing_io;
	bool is_blocked;
};

#endif
