#pragma once

#define ROOT_NODES 100

typedef struct bolt_map_node_s bolt_map_node_t;

typedef struct bolt_map_node_s {
    long key;
    void *data;

    bolt_map_node_t *next;
} bolt_map_node_t;

typedef struct bolt_map_s {
    bolt_map_node_t *nodes[ROOT_NODES];
} bolt_map_t;
