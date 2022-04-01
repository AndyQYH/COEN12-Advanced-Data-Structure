/*
run time1: O(nlog(n))
run time2: O(log(n))
run time3: O(n)
run time4: O(n)
*/


# include <stdio.h>
# include <math.h>

struct point {
    float x, y;
};

typedef struct point POINT;


struct point add(POINT p1, POINT p2)
{
    p1.x = p1.x + p2.x;
    p1.y = p1.y + p2.y;

    return p1;
}


float distance(POINT p1, POINT p2)
{
    float xdiff, ydiff;

    xdiff = p1.x - p2.x;
    ydiff = p1.y - p2.y;

    return sqrt(xdiff * xdiff + ydiff * ydiff);

}


int main(void)
{
    POINT a, b, c;

    a.x = 0;
    a.y = 0;

    b.x = 2;
    b.y = 2;

    c.x = 3;
    c.y = 2;

    printf("%f\n", distance(a, add(b, c)));
}
