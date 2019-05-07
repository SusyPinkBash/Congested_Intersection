#include "../busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int main(){
    struct simulation *s = si_new("test/tripset4.in");
    if(s == NULL)
    {
        printf("simulation loading error\n");
        assert(s != NULL);
        return 0;
    }

    // printf("%d\n", si_get_congestion(s, 0,4, 0,0)); //
    // printf("%d\n", si_get_congestion(s, 1,5, 1,1)); //
    // printf("%d\n", si_get_congestion(s, 0,15, 0,2)); //
    // printf("%d\n", si_get_congestion(s, 0,15, 2,0)); //
    // printf("%d\n", si_get_congestion(s, 3,9, 2,1)); //
    // printf("%d\n", si_get_congestion(s, 5,13, 3,1)); //

    assert(si_get_congestion(s, 0,4, 0,0)== 3);
    assert(si_get_congestion(s, 1,5, 1,1)== 3);
    assert(si_get_congestion(s, 0,15, 0,2)== 0);
    assert(si_get_congestion(s, 0,15, 2,0)== 0);
    assert(si_get_congestion(s, 3,9, 2,1)== 4);
    assert(si_get_congestion(s, 3,9, 2,1)== 4);
    si_delete(s);
}
