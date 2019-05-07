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
    unsigned column;
    unsigned row;
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
    unsigned columns;
    unsigned rows;
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


// ########## FUNCTIONS DECARATIONS ##########
position * position_new(unsigned row, unsigned column);
void position_delete(position * this);


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

int check_corner(position * start, position * end, unsigned long x, unsigned long y) {
    if (y == start->column) {
        unsigned x0, x1;
        if (start->row <= end->row) {
            x0 = start->row;
            x1 = end->row;
        }
        else {
            x0 = end->row;
            x1 = start->row;
        }
        return (x >= x0 && x <= x1);
    }
    if (x == end->row) {
        unsigned y0, y1;
        if (start->column <= end->column) {
            y0 = start->column;
            y1 = end->column;
        }
        else {
            y0 = end->column;
            y1 = start->column;
        }
//        if (y >= y0 && y <= y1)
//            return 1;
        return (y >= y0 && y <= y1);
    }
    return 0;
}

int check_time(unsigned long time, unsigned long start, unsigned long end) {
    return (time >= start && time <= end);
}


// ##### GETTER FUNCTIONS #####

/* calculates the distance of two points on the map */
unsigned long get_distance(position * start, position * end) {
    return subtractions(start->column, end->column) + subtractions(start->row, end->row);
}

unsigned long get_time_at_corner(unsigned long time_start, position * starting_position, unsigned c, unsigned r) {
    position * position_to_check = position_new(r, c);
    unsigned long distance = get_distance(starting_position, position_to_check);
    position_delete(position_to_check);
    return time_start + distance;
    
}


// ##### SETTER FUNCTIONS #####
/* sets all the numbers in the simulation struct  */
void set_simulation_ints(struct simulation * this, FILE * file) {
    /* Read first line with data about the simulation*/
    char * line = malloc(15*sizeof(char));
    line = file_to_buffer(file, line, '\n', 15);
    
    ints_tuple temp = get_next_number(line);
    int offset = temp.len;
    this->columns = temp.n;
    
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
    this->column = other->column;
    this->row = other->row;
}


// ########## CREATE STRUCTS FUNCTIONS ##########

/* Constructor: returns the null pointer in case of failure.
 * Creates a position object.
 */
position * position_new(unsigned column, unsigned row) {
    position * this = malloc(sizeof(position));
    this->column = column;
    this->row = row;
    return this;
}

position * position_copy(position * other) {
    position * this = malloc(sizeof(position));
    this->column = other->column;
    this->row = other->row;
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
struct trip * trip_new(FILE * file, struct car * cars[], unsigned long n_cars) {
    struct trip * this = malloc(sizeof(struct trip));
    
    char * line = malloc(15*sizeof(char));
    line = file_to_buffer(file, line, '\n', 15);
//    printf("%s\n", line);
    
    ints_tuple temp = get_next_number(line);
    int offset = temp.len;
    this->carID = temp.n;
    if (this->carID > n_cars)
        return NULL;
    this->car = cars[temp.n];
    
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    if (temp.len > 1000000000) {
        perror("The starting time is over 10^9\n");
        return NULL;
    }
    this->time_start = temp.n;
    
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    unsigned r = temp.n;
    temp = get_next_number(&line[offset]);
    offset += temp.len;
    unsigned c = temp.n;
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
    
    if ((this->columns > 100000) || (this->rows > 100000) || (n_cars > 1000) || (n_trips > 100000)) {
        perror("Error: the numbers given are higher than the limitation defined by the program\n");
        si_delete(this);
        return NULL;
    }
    
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
    struct trip * old = trip_new(file, cars, n_cars);
    if (old == NULL || old->ending_position->column >= this->rows || old->ending_position->column >= this->rows){
//        printf("columns: %u & rows %u\n", this->columns, this->rows);
//        if (old == NULL) {
//            printf("NULL\n");
//        }
//        if (old->ending_position->column >= this->columns) {
//            printf("ending col = %u\n", old->ending_position->column);
//        }
//        if (old->ending_position->row >= this->rows) {
//            printf("ending col = %u\n", old->ending_position->row);
//
//        }
        return NULL;
    }
    struct trip * new = old;
    this->first_trip = old;
    
    for (int i=1; i < n_trips; ++i) {
        new = trip_new(file, cars, n_cars);
        if (new == NULL || new->ending_position->column >= this->rows || new->ending_position->row >= this->columns){
//            printf("columns: %u & rows %u\n", this->columns, this->rows);
//            if (new == NULL) {
//                printf("NULL\n");
//            }
//            if (new->ending_position->column >= this->columns) {
//                printf("ending col = %u\n", new->ending_position->column);
//            }
//            if (new->ending_position->row >= this->rows) {
//                printf("ending col = %u\n", new->ending_position->row);
//
//            }
            return NULL;
        }
//        if (new == NULL || new->ending_position->column >= this->rows || new->ending_position->row >= this->colums){
//            if (new == NULL)
//                perror("\tTRIP new null\n");
//            if (new->ending_position->column > this->colums) {
//                printf("%lu %lu %u %u\n", new->carID, new->time_start, new->ending_position->column, new->ending_position->row);
//                perror("\tTRIP new col\n");
//                printf("%u > %u\n", new->ending_position->column, this->colums);
//            }
//            if (new->ending_position->row > this->rows)
//                perror("\tTRIP new row\n");
//            si_delete(this);
//            return NULL;
//        }
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
    if (!(x<s->rows && y<s->columns))
        return -1;
    
    struct trip * current = s->first_trip;
    int counter = 0;
//    printf("CORNER: x=%u, y=%u\n", y, x);
//    printf("TIME: [%lu, %lu]\n", start, end);
    while (current) {
//        printf("\nCurrent is: %lu @Time %lu + %lu\n", current->carID, current->time_start, current->distance);
//        printf("\tPosition x=%lu, y=%lu", current->starting_position->x, current->starting_position->y);
//        printf("\t --> x=%lu, y=%lu\n", current->ending_position->x, current->ending_position->y);
        if (check_corner(current->starting_position, current->ending_position, y, x)) {
            unsigned long time = get_time_at_corner(current->time_start , current->starting_position, y, x);
//            printf("\t --> Corner: yes @ Time %lu\n", time);
            if (check_time(time, start, end)) {
//                printf("\t --> Time: yes\n");
                ++counter;
            }
        }
        current = current->next_trip;
    }
    return counter;
}
