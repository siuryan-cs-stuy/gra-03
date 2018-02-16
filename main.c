#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {

  screen s;
  color c;
  struct matrix *edges;
  struct matrix *edges_test;
  struct matrix *edges_drawing;
  struct matrix *identity;

  printf("Creating Edge Matrix 1:\n");
  edges = new_matrix(4, 4);
  print_matrix(edges);

  printf("Adding edges to Edge Matrix 1:\n");
  add_edge(edges, 1, 2, 3, 5, 2, 3);
  add_edge(edges, 3, 0, 2, 2, 2, 2);
  print_matrix(edges);

  printf("Edge Matrix 2:\n");
  edges_test = new_matrix(4, 2);
  add_edge(edges_test, 9, 2, 4, 6, 6, 6);
  print_matrix(edges_test);

  printf("Identity Matrix:\n");
  identity = new_matrix(4, 4);
  ident(identity);
  print_matrix(identity);

  printf("Multiplying edge matricies:\n");
  matrix_mult(edges, edges_test);
  print_matrix(edges_test);

  printf("Creating drawing...\n");
  edges_drawing = new_matrix(4, 2);

  // draw!!!
  c.green = MAX_COLOR;
  add_edge(edges_drawing, 0, 0, 0, 500, 500, 0);
  c.green = MAX_COLOR;
  add_edge(edges_drawing, 0, 500, 0, 500, 0, 0);

  draw_lines(edges_drawing, s, c);
  display(s);

  free_matrix( edges );
  free_matrix( edges_test );
  free_matrix( identity );
}
