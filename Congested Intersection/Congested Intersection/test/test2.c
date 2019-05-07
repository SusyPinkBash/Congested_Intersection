#include "../busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int main(){
    struct simulation *s = si_new("test/tripset2.in");
    if(s == NULL)
    {
        fprintf(stderr, "simulation loading error\n");
        assert(s != NULL);
        return 0;
    }
    // printf("%d\n", si_get_congestion(s, 0,0, 0,0));
    // printf("%d\n", si_get_congestion(s, 0,15, 6,1));
    // printf("%d\n", si_get_congestion(s, 10, 35, 3,1));
    // printf("%d\n", si_get_congestion(s, 0, 100, 3,1));
    // printf("%d\n", si_get_congestion(s, 42,60, 4,4));
    // printf("%d\n", si_get_congestion(s, 0, 100, 3,8));
    // printf("%d\n", si_get_congestion(s, 70, 70, 0,3));
    // printf("%d\n", si_get_congestion(s, 55, 78, 4,5));
    // printf("%d\n", si_get_congestion(s, 35, 78, 5,3));

    assert(si_get_congestion(s, 0,0, 0,0) == 1); //
    assert(si_get_congestion(s, 0,15, 6,1)==0); //
    assert(si_get_congestion(s, 10, 35, 3,1)==3); //
    assert(si_get_congestion(s, 0, 100, 3,1)==14); //
    assert(si_get_congestion(s, 42,60, 4,4)==1); //
    assert(si_get_congestion(s, 0, 100, 3,8)==-1); //
    assert(si_get_congestion(s, 70, 70, 0,3)==0); //
    assert(si_get_congestion(s, 55, 78, 4,5)==2); //
    assert(si_get_congestion(s, 35, 78, 5,3)==8); //
    si_delete(s);
}

