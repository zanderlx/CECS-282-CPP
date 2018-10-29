#include "MemoryManager.h"

#include <iomanip>
#include <iostream>
#include <stdlib.h>
using namespace std;

namespace MemoryManager
{

// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT

//

// This is the only static memory that you may use, no other global variables

// may be created, if you need to save data make it fit in MM_pool

//

// IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT IMPORTANT

	const int MM_POOL_SIZE = 65536;

	char MM_pool[MM_POOL_SIZE];

	// I have provided this tool for your use

	void memView(int start, int end)

	{

		const unsigned int SHIFT = 8;

		const unsigned int MASK = 1 << SHIFT - 1;

		unsigned int value; // used to facilitate bit shifting and masking

		cout << " Pool Unsignd Unsigned " << endl;

		cout << "Mem Add indx bits chr ASCII# short int " << endl;

		cout << "-------- ---- -------- --- ------ ------- ------------" << endl;

		for (int i = start; i <= end; i++)

		{

			cout << (long*)(MM_pool + i) << ':'; // the actual address in hexadecimal

			cout << '[' << setw(2) << i << ']'; // the index into MM_pool

			value = MM_pool[i];

			cout << " ";

			for (int j = 1; j <= SHIFT; j++) // the bit sequence for this byte (8 bits)

			{

				cout << ((value & MASK) ? '1' : '0');

				value <<= 1;

			}

			cout << " ";

			cout << '|' << *(char*)(MM_pool + i) << "| ("; // the ASCII character of the 8 bits (1 byte)

			cout << setw(4) << ((int)(*((unsigned char*)(MM_pool + i)))) << ")";// the ASCII number of the character

			cout << " (" << setw(5) << (*(unsigned short*)(MM_pool + i)) << ")";// the unsigned short value of 16 bits (2 bytes)

			cout << " (" << setw(10) << (*(unsigned int*)(MM_pool + i)) << ")"; // the unsigned int value of 32 bits (4 bytes)

			cout << endl;

		}

	}

	// Initialize set up any data needed to manage the memory pool
	void initializeMemoryManager(void)
	{
		// Free-Space location
		*(unsigned short*) & MM_pool[0] = 6;

		// First "Node" in the In-Use List (Allocated List)
		*(unsigned short*) & MM_pool[2] = 0;

		// First "Node" in the Used List (Deallocated List)
		*(unsigned short*) & MM_pool[4] = 0;
	}

	// Return a pointer inside the memory pool

	// If no chunk can accommodate aSize call onOutOfMemory()

	void* allocate(int aSize)

	{
		// Next free space location
		unsigned short nextFreeSpace = *(unsigned short*) & MM_pool[0];
		// First "Node" of in-use list
		unsigned short inUseHead = *(unsigned short*) & MM_pool[2];

		// There is no more free space to use
		if (aSize > (MM_POOL_SIZE - (nextFreeSpace + 6)))
			onOutOfMemory();
		else
		{
			// Next "Node" is previously allocated node
			*(unsigned short*) & MM_pool[nextFreeSpace + 2] = inUseHead;
			// Previous "Node" is nothing - Nothing is before the first node
			*(unsigned short*) & MM_pool[nextFreeSpace + 4] = 0;  
			// Update next node's information
			*(unsigned short*) & MM_pool[inUseHead + 4] = nextFreeSpace;

			// Update next free space and update head of in-used list
			*(unsigned short*) & MM_pool[0] += aSize + 6;
			*(unsigned short*) & MM_pool[2] = nextFreeSpace;
		}
	}

	// Free up a chunk previously allocated memory

	void deallocate(void* aPointer)

	{
		unsigned short next = *(unsigned short*)((char*)aPointer - 4);
		unsigned short previous = *(unsigned short*)((char*)aPointer - 2);
		unsigned short deall = *(unsigned short*) & MM_pool[4];

		unsigned short hod  = *(unsigned short*) & MM_pool[previous + 2];
		unsigned short inuse = *(unsigned short*) & MM_pool[2];
		

		
		if (next == 0 && previous == 0) {
			if (deall == 0) {
				*(unsigned short*)&MM_pool[4] = hod;
				
				if (hod == inuse) {
					*(unsigned short*)&MM_pool[2] = 0;
				}
			}
		}
		else {
			if (next == 0) {
				*(unsigned short*)&MM_pool[previous + 2] = 0;
				*(unsigned short*)&MM_pool[hod + 4] = 0;
				if (deall == 0) {
					*(unsigned short*)&MM_pool[4] = hod;
				}
				else {
					*(unsigned short*)&MM_pool[4] = hod;
					*(unsigned short*)&MM_pool[hod + 2] = deall;
					*(unsigned short*)&MM_pool[deall + 4] = *(unsigned short*)&MM_pool[4];
				}
			}
			// This checks if the current node is the first node (previous is 0)
			else if (previous == 0) {
				unsigned short newhead = *(unsigned short*)&MM_pool[hod + 2];
				// Makes the first node in the used list to the newly allocated memory
				*(unsigned short*) & MM_pool[2] = newhead;
				// 
				*(unsigned short*) & MM_pool[newhead + 4] = 0;

				if (deall == 0) {
					*(unsigned short*)&MM_pool[4] = hod;
				}
				else {
					*(unsigned short*)&MM_pool[4] = hod;
					*(unsigned short*)&MM_pool[hod + 2] = deall;
					*(unsigned short*)&MM_pool[deall + 4] = *(unsigned short*)&MM_pool[4];
				}
			}
			else {
				*(unsigned short*)&MM_pool[previous + 2] = next;
				*(unsigned short*)&MM_pool[next + 4] = previous;
				*(unsigned short*)&MM_pool[hod + 2] = 0;
				*(unsigned short*)&MM_pool[hod + 4] = 0;
				if (deall == 0) {
					*(unsigned short*)&MM_pool[4] = hod;
				}
				else {
					*(unsigned short*)&MM_pool[4] = hod;
					*(unsigned short*)&MM_pool[hod + 2] = deall;
					*(unsigned short*)&MM_pool[deall + 4] = *(unsigned short*)&MM_pool[4];
				}
			}
		}
	}

	// Scan the memory pool and return the total free space remaining in bytes
	int freeMemory(void)
	{
		// Max size of memory subtracted by the next free memory
		return 65536 - (*(unsigned short*) & MM_pool[0]);
	}

	// Scan the memory pool and return the total deallocated memory in bytes
	int usedMemory(void)
	{
		// Start at the head of used (deallocated) list
		unsigned short usedHead = *(unsigned short*) & MM_pool[4];
		// If there is nothing in used list, return 0
		if (usedHead == 0)
			return 0;
		// Else there is something already in the used list
		else
		{
			unsigned short amount = 0;
			// Keep iterating through the used memory list
			while(usedHead != 0)
			{
				amount = *(unsigned short*) & MM_pool[usedHead] + amount + 6;
				usedHead = *(unsigned short*) & MM_pool[usedHead + 2];
			}
			return amount;
		}
	}

	// Scan the memory pool and return the total in use memory
	int inUseMemory(void)
	{
		// Start at the head of the in-use list
		unsigned short inUseHead = *(unsigned short*) & MM_pool[2];

		// If there is nothing in the in-use list, return 0
		if (inUseHead == 0)
			return 0;
		// Else there is something in the in-use list
		else
		{
			unsigned short amount = 0;
			while ( inUseHead != 0 )
			{
				amount = *(unsigned short*) & MM_pool[inUseHead] + amount + 6;
				inUseHead = *(unsigned short*) & MM_pool[inUseHead + 2];
			}
			return amount;
		}
	}

	// Return the size (in bytes) associated with this memory address
	int size(void * aPointer)
	{

		// Returns the size of a specific pointer based on first location of the node
		return *(unsigned short*)( (char*) aPointer - 6); 
	}

	// This is called when no more memory is available to allocate
	void onOutOfMemory(void)
	{
		std::cerr << "/nMemory pool out of memory" << std::endl;

		cin.get( );

		exit(1);
	}
}