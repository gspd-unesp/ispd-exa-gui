#pragma once

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

typedef struct node {
    unsigned long size;
    char * color;
    char * name;
    struct node * next;
    struct node * prev;
    struct node * insertnext;
    int num;
    double x;
    double y;
    double radius;
} node_t;

void usage(char *progname);
static void hsv2rgb(double h, double s, double v, unsigned int * r, unsigned int * b, unsigned int * g);
static void printSVG(node_t * first, node_t * a_, node_t * bb_topright, node_t * bb_bottomleft, int debug, FILE *output_file);
static node_t * alloc_node(unsigned long size_, int num_);
static void bound(node_t * n, node_t * topright, node_t * bottomleft);
static double distance(node_t * a);
static void place(node_t * a, node_t * b, node_t * c);
static int intersects(node_t * a, node_t * b);
static void insert(node_t * a, node_t * b);
static void splice(node_t * a, node_t * b);
static node_t * placeCircles(node_t * firstnode, node_t * bb_topright, node_t * bb_bottomleft, int debug);

