#include "busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int main(){
    struct simulation *s = si_new("tripset1.in");
    
    if(s == NULL)
    {
        fprintf(stderr, "simulation loading error\n");
        assert(s != NULL);
        return 0;
    }
//    si_get_congestion(simulation, start, end, x, y);
    
    //             si_get_congestion(s, s,e, x,y));
//    printf("%d\n", si_get_congestion(s, 0,0, 0,0)); // =1 CORRECT
//    printf("%d\n", si_get_congestion(s, 0,5, 0,0)); // =2 CORRECT
    printf("%d\n", si_get_congestion(s, 1,3, 0,1)); // =1
//    printf("%d\n", si_get_congestion(s, 0,6, 0,1)); // =3
//    printf("%d\n", si_get_congestion(s, 0,5, 3,0)); // =0
//    printf("%d\n", si_get_congestion(s, 11,20, 3,0)); // =1
//    assert(si_get_congestion(s, 0,0, 0,0) ==1);
//    assert(si_get_congestion(s, 0,5, 0,0) ==2);
//    assert(si_get_congestion(s, 1,3, 0,1) ==1);
//    assert(si_get_congestion(s, 0,6, 0,1) ==3);
//    assert(si_get_congestion(s, 0,5, 3,0) ==0);
//    assert(si_get_congestion(s, 11,20, 3,0) ==1);
    si_delete(s);
}
