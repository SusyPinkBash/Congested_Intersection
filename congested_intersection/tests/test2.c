#include "../busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int main(){
    struct simulation *s = si_new("tripset2.in");
    if(s == NULL)
        return 0;
    assert(si_get_congestion(s, 0,0, 0,0) == 0); // =0
    assert(si_get_congestion(s, 0,15, 0,0)==7); // =7
    assert(si_get_congestion(s, 10, 25, 3,1)==3); // =3
    assert(si_get_congestion(s, 1,49, 4,4)==0); // =0
    assert(si_get_congestion(s, 2, 40, 3,2)==6); // =6
    assert(si_get_congestion(s, 11, 45, 0,3)==4); // =4
    assert(si_get_congestion(s, 3, 49, 7,3)==-1); // =-1
    si_delete(s);
}

