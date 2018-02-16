#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
    if (points->cols == points->lastcol) {
        grow_matrix(points, points->cols*2);
    }
    
    points->m[0][points->lastcol] = x;
    points->m[1][points->lastcol] = y;
    points->m[2][points->lastcol] = z;
    points->m[3][points->lastcol] = 1;
    points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
    add_point(points, x0, y0, z0);
    add_point(points, x1, y1, z1);
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {
    int j;

    for (j = 0; j < points->cols; j += 2) {
        draw_line(points->m[0][j], points->m[1][j], points->m[0][j+1], points->m[1][j+1], s, c);
    }
}

void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
    int A = y1 - y0;
    int B = -x1 + x0;

    int x, y;
    x = x0;
    y = y0;

    int d;

    if ((A >= 0 && -B >= 0) || (A <= 0 && -B <= 0)) {
        // octants I, II
        if (abs(B) >= abs(A)) {
            // octant I
            d = 2*A + B;

            while (x <= x1) {
                plot(s, c, x, y);

                if (d > 0) {
                    y++;
                    d += 2*B;
                }
                x++;
                d += 2*A;
            }
        } else {
            // octant II
            d = A + 2*B;

            while (y <= y1) {
                plot(s, c, x, y);

                if (d < 0) {
                    x++;
                    d += 2*A;
                }
                y++;
                d += 2*B;
            }
        }
    } else {
        if (abs(B) >= abs(A)) {
            // octant VIII
            d = 2*A - B;

            while (x <= x1) {
                plot(s, c, x, y);

                if (d < 0) {
                    y--;
                    d -= 2*B;
                }
                x++;
                d += 2*A;
            }
        } else {
            // octant VII
            d = A - 2*B;
            while (x <= x1) {
                plot(s, c, x, y);

                if (d > 0) {
                    x++;
                    d += 2*A;
                }
                y--;
                d -= 2*B;
            }
        }
    }
}
