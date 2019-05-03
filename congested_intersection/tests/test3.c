#include "../busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int main(){
    struct simulation *s = si_new("tripset3.in");
    if(s == NULL)
        return 0;
    assert(si_get_congestion(s, 0,1000, 0,0)== 23); // =23
    assert(si_get_congestion(s, 10000,20999, 5,6)== 117); // =117
    assert(si_get_congestion(s, 5000,9000, 3,10)== 21); // =21
    assert(si_get_congestion(s, 2222,6666, 2,8)== 48); // =48
    si_delete(s);
}
