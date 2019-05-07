//#include "busyintersection.h"
//#include<stdio.h>
//#include<stdlib.h>
//#include<assert.h>
//
//
//int main(){
//    struct simulation *s = si_new("test/tripset1.in");
//    if(s == NULL)
//    {
//        fprintf(stderr, "simulation loading error\n");
//        assert(s != NULL);
//        return 0;
//    }
//    
//     assert(si_get_congestion(s, 0,0, 0,0) ==1);
//     assert(si_get_congestion(s, 0,5, 0,0) ==2);
//     assert(si_get_congestion(s, 1,3, 0,1) ==1);
//     assert(si_get_congestion(s, 0,6, 0,1) ==3);
//     assert(si_get_congestion(s, 0,5, 3,0) ==0);
//     assert(si_get_congestion(s, 11,20, 3,0) ==1);
//    si_delete(s);
//    
//    
//    s = si_new("test/tripset2.in");
//    if(s == NULL)
//    {
//        fprintf(stderr, "simulation loading error\n");
//        assert(s != NULL);
//        return 0;
//    }
//
//    printf("\n%d == 3 \n", si_get_congestion(s, 0,0, 0,0));
//    printf("%d == 8 \n", si_get_congestion(s, 0,15, 6,1));
//    printf("%d == 18 \n", si_get_congestion(s, 10, 35, 3,1));
//    printf("%d == 15 \n", si_get_congestion(s, 42,60, 4,4));
//    printf("%d == 45 \n", si_get_congestion(s, 0, 100, 3,8));
//    printf("%d == 0 \n", si_get_congestion(s, 70, 70, 0,3));
//    printf("%d == 2 \n", si_get_congestion(s, 55, 78, 5,10));
//    printf("%d == -1 \n", si_get_congestion(s, 55, 78, 7,3));
////    assert(si_get_congestion(s, 0,0, 0,0) == 3); // =3
////    assert(si_get_congestion(s, 0,15, 6,1)==8); // =8
////    assert(si_get_congestion(s, 10, 35, 3,1)==18); // =18
////    assert(si_get_congestion(s, 42,60, 4,4)==15); // =15
////    assert(si_get_congestion(s, 0, 100, 3,8)==45); // =45
////    assert(si_get_congestion(s, 70, 70, 0,3)==0); // =0
////    assert(si_get_congestion(s, 55, 78, 5,10)==2); // =2
////    assert(si_get_congestion(s, 55, 78, 7,3)==-1); // =-1
//    si_delete(s);
//    
//    
//    s = si_new("test/tripset3.in");
//    if(s == NULL)
//    {
//        printf("simulation loading error\n");
//        assert(s != NULL);
//        return 0;
//    }
//    assert(si_get_congestion(s, 0,500, 0,0)== 101);
//    assert(si_get_congestion(s, 1,1000, 15,15)== 658);
//    assert(si_get_congestion(s, 300,600, 20,21)== 157);
//    assert(si_get_congestion(s, 250,500, 11,25)== 96);
//    si_delete(s);
//    
//}

