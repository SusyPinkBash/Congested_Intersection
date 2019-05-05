#include "busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int main(){
    struct simulation *s = si_new("tripset2.in");

    if(s == NULL)
    {
        fprintf(stderr, "simulation loading error\n");
        assert(s != NULL);
        return 0;
    }
//                                  (s, s,e, x,y)
    printf("%d\n", si_get_congestion(s, 0,0, 0,0));
    printf("%d\n", si_get_congestion(s, 0,15, 6,1));
    printf("%d\n", si_get_congestion(s, 10, 35, 3,1));
    printf("%d\n", si_get_congestion(s, 42,60, 4,4));
    printf("%d\n", si_get_congestion(s, 0, 100, 3,8));
    printf("%d\n", si_get_congestion(s, 70, 70, 0,3));
    printf("%d\n", si_get_congestion(s, 55, 78, 5,10));
    printf("%d\n", si_get_congestion(s, 55, 78, 7,3));
    
//    assert(si_get_congestion(s, 0,0, 0,0) == 3); // =3
//    assert(si_get_congestion(s, 0,15, 6,1)==8); // =8
//    assert(si_get_congestion(s, 10, 35, 3,1)==18); // =18
//    assert(si_get_congestion(s, 42,60, 4,4)==15); // =15
//    assert(si_get_congestion(s, 0, 100, 3,8)==45); // =45
//    assert(si_get_congestion(s, 70, 70, 0,3)==0); // =0
//    assert(si_get_congestion(s, 55, 78, 5,10)==2); // =2
//    assert(si_get_congestion(s, 55, 78, 7,3)==-1); // =-1
    si_delete(s);
}
