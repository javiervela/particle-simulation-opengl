#ifndef SERIAL_H
#define SERIAL_H

#include "common.h"

//
//  tuned constants
//
#define density 0.0005
#define cutoff 0.01
#define bin_size 5

//
// type bin
//
typedef struct
{
    // number of particles in bin
    unsigned int size;
    // array of pointers to the particles contained
    particle_t **particles_bin;
} bin_t;

int bin_create(bin_t **bins);
void bin_init(bin_t *bins, int n_col);
void bin_assign(particle_t *particles, int n_particles, bin_t *bins, int n_col);
void bin_clear(bin_t *bins, int n_col);
void bin_delete(bin_t *bins, int n_col);
void init(int n);
void destroy(int bin_n_col);
void simulateStep(particle_t *particles, int n);

#endif