#ifndef FREESPACE_H
#define FREESPACE_H

struct freespace {
	int address;
	int size;

	freespace(int address, int size) {
		this->address = address;
		this->size = size;
	}
};

#endif
