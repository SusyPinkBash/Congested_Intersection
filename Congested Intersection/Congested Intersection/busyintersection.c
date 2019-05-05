//
//  busyintersection.c
//  Congested Intersection
//
//  Created by Susanna Ardigo' on 02.05.19.
//  Copyright © 2019 Susanna Ardigo'. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "busyintersection.h"


// ########## STRUCTS ##########
typedef struct {
    unsigned long row;
    unsigned long col;
} position;

struct car {
    unsigned long carID;
    position * position;
    struct car * next_car;
};

struct trip {
    unsigned long carID;
    struct car * car;
    unsigned long time_start;
    position * starting_position;
    position * ending_position;
    unsigned long distance;
    struct trip * next_trip;
};

struct simulation {
    unsigned long colums;
    unsigned long rows;
    unsigned long n_cars;
    unsigned long n_trips;
    struct car * first_car;
    struct trip * first_trip;
};

// ##### HELPER STRUCTS #####

typedef struct {
    int n;
    int len;
} ints_tuple;



// ########## HELPER FUNCTIONS ##########

/* Copies chars from a file to a char * buffer given an end char to stop at */
char * file_to_buffer(FILE * file, char * buffer, char end, int buff_len) {
    int c;
    int i=0;
    while ((c=fgetc(file)) != end && c != EOF) {
        if (i >= buff_len) {
            buff_len += 10;
            buffer = realloc(buffer, buff_len*sizeof(char));
        }
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    return buffer;
}

/* gives the number id of the next photo */
ints_tuple get_next_number(const char * line) {
    int buffer_len = 15;
    char * buffer = malloc(buffer_len*sizeof(char));
    int i=0;
    
    
    while (line[i] != ' ' && line[i] != '\0') {
//        printf("%c @ %d\n", line[i], line[i]);
        if (i >= buffer_len) {
            buffer_len += 10;
            buffer = realloc(buffer, buffer_len*sizeof(char));
        }
        buffer[i] = line[i];
        ++i;
    }
    buffer[i] = '\0';
    int n = atoi(buffer);
    free(buffer);
    ints_tuple temp = {n, ++i};
    return temp;
}

/* subtracts two unsigned longs  */
unsigned long subtractions(unsigned long x, unsigned long y) {
    if (x >= y) {
        return x - y;
    }
    return y - x;
}

int overlaps(struct trip * trip, unsigned long start, unsigned long end) {
    
}


// ##### GETTER FUNCTIONS #####

/* calculates the distance of two points on the map */
unsigned long get_distance(position * start, position * end) {
    return subtractions(start->row, end->row) + subtractions(start->col, end->col);
}


// ##### SETTER FUNCTIONS #####
/* sets all the numbers in the simulation struct  */
void set_simulation_ints(struct simulation * this, FILE * file) {
    /* Read first line with data about the simulation*/
    char * line = malloc(15*sizeof(char));
    line = file_to_buffer(file, line, '\n', 15);
    
    ints_tuple temp = get_next_number(line);
    int offset = temp.len;
    this->colums = temp.n;
    
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    this->rows = temp.n;
    
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    this->n_cars = temp.n;
    
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    this->n_trips = temp.n;
    
    free(line);
}

/* set positions equal to another given position */
void set_position_from_position(position * this, position * other) {
    this->row = other->row;
    this->col = other->col;
}


// ########## CREATE STRUCTS FUNCTIONS ##########

/* Constructor: returns the null pointer in case of failure.
 * Creates a position object.
 */
position * position_new(unsigned long row, unsigned long column) {
    position * this = malloc(sizeof(position));
    this->row = row;
    this->col = column;
    return this;
}

position * position_copy(position * other) {
    position * this = malloc(sizeof(position));
    this->row = other->row;
    this->col = other->col;
    return this;
}

/* Constructor: returns the null pointer in case of failure.
 * Creates a car object.
 */
struct car * car_new(int carID) {
    struct car * this = malloc(sizeof(struct car));
    
    this->carID = (unsigned long) carID;
    this->position = position_new(0, 0);
    this->next_car = NULL;
    
    return this;
}


/* Constructor: returns the null pointer in case of failure.
 * Creates a trip object.
 */
struct trip * trip_new(FILE * file, struct car * cars[]) {
    struct trip * this = malloc(sizeof(struct trip));
    
    char * line = malloc(15*sizeof(char));
    line = file_to_buffer(file, line, '\n', 15);
    
    ints_tuple temp = get_next_number(line);
    int offset = temp.len;
    this->carID = temp.n;
    this->car = cars[temp.n];
    
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    this->time_start = temp.n;
    
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    unsigned long r = temp.n;
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    unsigned long c = temp.n;
    this->ending_position = position_new(r, c);
    
    free(line);
    this->next_trip = NULL;
    this ->starting_position = position_copy(this->car->position);
    this->distance = get_distance(this->car->position, this->ending_position);
    set_position_from_position(this->car->position, this->ending_position);
    
    
    return this;
}


/* Constructor: returns the null pointer in case of failure.
 * Reads the set of trips from the given file.
 */
struct simulation * si_new(char * filename) {
//    printf("%s\n", filename);
    FILE * file = fopen(filename, "r");
    struct simulation * this = malloc(sizeof(struct simulation));
    if (!file) {
        perror("Error trying to create the simulation");
        return NULL;
    }
    
    set_simulation_ints(this, file);
    unsigned long n_cars = this->n_cars;
    unsigned long n_trips = this->n_trips;
    
    struct car * cars[n_cars];
    
    // cars linked list
    struct car * prev = car_new(0);
    struct car * current = prev;
    this->first_car = current;
    cars[0] = prev;
    
    for (int i=1; i < n_cars; ++i) {
        current = car_new(i);
        cars[i] = current;
        prev->next_car = current;
        prev = current;
    }
    
    // trips linked list
    struct trip * old = trip_new(file, cars);
    struct trip * new = old;
    this->first_trip = old;
    
    for (int i=1; i < n_trips; ++i) {
        new = trip_new(file, cars);
        old->next_trip = new;
        old = new;
    }
    return this;
}


// ########## DESTRUCT STRUCTS FUNCTIONS ##########

/* Destructor: clear all memory allocated for the given position. */
void position_delete(position * this) {
    if (this) {
        free(this);
    }
}

/* Destructor: clear all memory allocated for the given car. */
void car_delete(struct car * this) {
    if (this) {
        position_delete(this->position);
        if (this->next_car) {
            car_delete(this->next_car);
            this->next_car = NULL;
        }
        free(this);
    }
}

/* Destructor: clear all memory allocated for the given trip. */
void trip_delete(struct trip * this) {
    
    if (this) {
        position_delete(this->starting_position);
        position_delete(this->ending_position);
        this->car = NULL;
        if (this->next_trip) {
            trip_delete(this->next_trip);
            this->next_trip = NULL;
        }
        free(this);
    }
    
}


/* Destructor: clear all memory allocated for the given simulation. */
void si_delete(struct simulation * s) {
    
    if (s) {
        if (s->first_trip) {
            trip_delete(s->first_trip);
            s->first_trip = NULL;
        }
        if (s->first_car) {
            car_delete(s->first_car);
            s->first_car = NULL;
        }
        free(s);
    }
}

// ########## CALCULATE CONGESTION ##########

/* Returns the number of cars passed the square (x,y),
 * starting from time "start", up to time "end".
 */
int si_get_congestion(struct simulation * s, unsigned long start, unsigned long end,
                      unsigned x, unsigned y) {
    
    struct trip * current = s->first_trip;
    while (current) {
        
        
        current = current->next_trip;
    }
    return 0;
}
