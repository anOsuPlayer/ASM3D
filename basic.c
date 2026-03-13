#include "basic.h"

Point make_point() {
    return (Point) malloc(sizeof(struct point_t));
}

void free_point(Point p) {
    free(p);
}

Line make_line() {
    return (Line) malloc(sizeof(struct line_t));
}

void free_line(Line l) {
    free(l);
}

Surface make_surface() {
    return (Surface) malloc(sizeof(struct surface_t));
}

void free_surface(Surface s) {
    free(s);
}