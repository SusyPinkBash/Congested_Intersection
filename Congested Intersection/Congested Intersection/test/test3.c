#include "../busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int main(){
    struct simulation *s = si_new("test/tripset3.in");
    if(s == NULL)
    {
        printf("simulation loading error\n");
        assert(s != NULL);
        return 0;
    }

    // printf("%d\n", si_get_congestion(s, 0,500, 0,0)); //
    // printf("%d\n", si_get_congestion(s, 1,1000, 15,15)); //
    // printf("%d\n", si_get_congestion(s, 300,600, 20,21)); //
    // printf("%d\n", si_get_congestion(s, 250,500, 11,25)); //

    assert(si_get_congestion(s, 0,500, 0,0)== 106);
    assert(si_get_congestion(s, 1,1000, 15,15)== 98);
    assert(si_get_congestion(s, 300,600, 20,21)== 31);
    assert(si_get_congestion(s, 250,500, 11,25)== 16);
    si_delete(s);
}
