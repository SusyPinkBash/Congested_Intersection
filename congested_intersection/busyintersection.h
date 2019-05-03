#ifndef BUSY_INTERSECTION_H_INCLUDED
#define BUSY_INTERSECTION_H_INCLUDED

struct simulation;

/* Constructor: returns the null pointer in case of failure.
* Reads the set of trips from the given file.
*/
struct simulation * si_new(char * filename);
/* Destructor: clear all memory allocated for the given simulation. */
void si_delete(struct simulation * s);
/* Returns the number of cars passed the square (x,y),
* starting from time "start", up to time "end".
*/
int si_get_congestion(struct simulation * s, unsigned long start, unsigned long end,
unsigned x, unsigned y);
#endif
