#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#include "physics2d.h"

void passed()
{
    printf("\n*********** All test passed ***********\n\n");
}

double roundp(double var, int percision)
{ 
    // 37.66666 * 100 =3766.66 
    // 3766.66 + .5 =3767.16    for rounding off value 
    // then type cast to int so value is 3767 
    // then divided by 100 so the value converted into 37.67 
    int multi = pow(10, percision);
    double value = (int)(var * multi + 0.5); 
    return (double) value / multi; 
}

void test_map()
{
    typedef struct {
        double value;
        double start1;
        double end1;
        double start2;
        double end2;
        double result;
        bool expected;
    } test;

    test tests[] =  {
        {45, 0, 100, 0, 1000, 450.00, true},
        {45, 1, 100, 0, 1000, 450.00, false},
        {145, 100, 200, 200, 300, 245.00, true},
        {145, 100, 200, 1000, 2000, 1450.00, true},
        {50, 0, 100, 500, 1000, 750.00, true},  
    };

    for (int i=0; i<5; i++) {
        test t = tests[i];
        double got = map(t.value, t.start1, t.end1, t.start2, t.end2);
        assert((roundp(got, 2) == t.result) == t.expected);
    }
}


int main()
{

    test_map();

    passed();

    return 0;
}
