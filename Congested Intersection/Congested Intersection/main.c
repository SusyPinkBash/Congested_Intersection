#include "busyintersection.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>


int main(){
    struct simulation *s = si_new("../../../../../../../../Desktop/test/tripset1.in");
    if(s == NULL)
    {
        fprintf(stderr, "simulation loading error\n");
        assert(s != NULL);
        return 0;
    }
    
     assert(si_get_congestion(s, 0,0, 0,0) ==1);
     assert(si_get_congestion(s, 0,5, 0,0) ==2);
     assert(si_get_congestion(s, 1,3, 0,1) ==1);
     assert(si_get_congestion(s, 0,6, 0,1) ==3);
     assert(si_get_congestion(s, 0,5, 3,0) ==0);
     assert(si_get_congestion(s, 11,20, 3,0) ==1);
    si_delete(s);
    
    
    s = si_new("../../../../../../../../Desktop/test/tripset2.in");
    if(s == NULL)
    {
        fprintf(stderr, "simulation loading error\n");
        assert(s != NULL);
        return 0;
    }

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
    
    
    s = si_new("../../../../../../../../Desktop/test/tripset3.in");
    if(s == NULL)
    {
        printf("simulation loading error\n");
        assert(s != NULL);
        return 0;
    }
    assert(si_get_congestion(s, 0,500, 0,0)== 106);
    assert(si_get_congestion(s, 1,1000, 15,15)== 98);
    assert(si_get_congestion(s, 300,600, 20,21)== 31);
    assert(si_get_congestion(s, 250,500, 11,25)== 16);
    si_delete(s);
    
    
    s = si_new("../../../../../../../../Desktop/test/tripset4.in");
    if(s == NULL)
    {
        printf("simulation loading error\n");
        assert(s != NULL);
        return 0;
    }
    
    assert(si_get_congestion(s, 0,4, 0,0)== 3);
    assert(si_get_congestion(s, 1,5, 1,1)== 3);
    assert(si_get_congestion(s, 0,15, 0,2)== 0);
    assert(si_get_congestion(s, 0,15, 2,0)== 0);
    assert(si_get_congestion(s, 3,9, 2,1)== 4);
    assert(si_get_congestion(s, 3,9, 2,1)== 4);
    si_delete(s);
    
}

