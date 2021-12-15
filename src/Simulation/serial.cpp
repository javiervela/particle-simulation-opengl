/*
JAVIER VELA
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "common.h"
#include "serial.h"

//
// create bin
//
int bin_create(bin_t **bins, int n)
{
    double size = sqrt(density * n);
    int n_col = (size / cutoff) + 1;
    /* DEBUG */ // printf("Number of bins: %d (%d x %d)\n", n_col * n_col, n_col, n_col);
    *bins = (bin_t *)malloc(n_col * n_col * sizeof(bin_t));
    /* DEBUG */ // printf("inside create\n");
    /* DEBUG */ // printf("%d\n", *bins);
    return n_col;
}

//
// initialize empty bins
//
void bin_init(bin_t *bins, int n_col)
{
    int n = n_col * n_col;
    for (int i = 0; i < n; i++)
    {
        /* DEBUG */ // printf(";%d", i);
        bins[i].size = 0;
        /* DEBUG */ // printf(";%d;", i);
        bins[i].particles_bin = (particle_t **)malloc(bin_size * sizeof(particle_t *));
    }
}

//
// assign particles to bins
//
void bin_assign(particle_t *particles, int n_particles, bin_t *bins, int n_col)
{
    for (int i = 0; i < n_particles; i++)
    {
        int bin_x = particles[i].x / cutoff;
        int bin_y = particles[i].y / cutoff;

        /* DEBUG */ // printf("BEFORE: For particle x=%f y=%f asssigned to bin x=%d y=%d\n", particles[i].x, particles[i].y, bin_x, bin_y);

        if (bins[bin_x + bin_y * n_col].size >= bin_size)
        {
            fprintf(stderr, "bin_assign failed because it was full!");
            exit(-1);
        }
        bins[bin_x + bin_y * n_col].particles_bin[bins[bin_x + bin_y * n_col].size] = &particles[i];
        bins[bin_x + bin_y * n_col].size++;

        /* DEBUG */ // printf("For particle x=%f y=%f asssigned to bin x=%d y=%d with size=%d\n", particles[i].x, particles[i].y, bin_x, bin_y, bins[bin_x + bin_y * n_col].size);
    }
}

//
// clear bin
//
void bin_clear(bin_t *bins, int n_col)
{
    for (int i = 0; i < n_col * n_col; i++)
    {
        bins[i].size = 0;
    }
}

//
// delete bin
//
void bin_delete(bin_t *bins, int n_col)
{
    for (int i = 0; i < n_col * n_col; i++)
    {
        free(bins[i].particles_bin);
    }
    free(bins);
}

//
// move all particles in bin
//
void move_bin(int i, int j, bin_t *bins, int bin_n_col)
{
    bin_t bin = bins[i * bin_n_col + j];
    // for every particle in bin
    for (int k = 0; k < bin.size; k++)
    {
        move(*bin.particles_bin[k]);
    }
}

//
// compute force with particles in neighbor bin
//
void compute_force_neighbor(bin_t &bin, int bin_k, bin_t &bin_neighbor /* , double &dmin, double &davg, int &navg */)
{
    for (int l = 0; l < bin_neighbor.size; l++)
        apply_force(*bin.particles_bin[bin_k], *bin_neighbor.particles_bin[l]);
}

//
// compute force with all neighbor bins
//
void compute_force_bin(int i, int j, bin_t *bins, int bin_n_col)
{
    bin_t bin = bins[i * bin_n_col + j];
    // for every particle in bin
    for (int k = 0; k < bin.size; k++)
    {
        bin.particles_bin[k]->ax = bin.particles_bin[k]->ay = 0;
        for (int l = 0; l < bin.size; l++)
        {
            // compute forces within itself
            apply_force(*bin.particles_bin[k], *bin.particles_bin[l]);
        }
        if (i != 0 && j != 0)
        {
            // compute forces with top left neighbor
            compute_force_neighbor(bin, k, bins[(i - 1) * bin_n_col + (j - 1)]);
        }
        if (i != 0)
        {
            // compute forces with top neighbor
            compute_force_neighbor(bin, k, bins[(i - 1) * bin_n_col + (j)]);
        }
        if (i != 0 && j != bin_n_col - 1)
        {
            // compute forces with top right neighbor
            compute_force_neighbor(bin, k, bins[(i - 1) * bin_n_col + (j + 1)]);
        }
        if (j != bin_n_col - 1)
        {
            // compute forces with right neighbor
            compute_force_neighbor(bin, k, bins[(i)*bin_n_col + (j + 1)]);
        }
        if (i != bin_n_col - 1 && j != bin_n_col - 1)
        {
            // compute forces with bottom right neighbor
            compute_force_neighbor(bin, k, bins[(i + 1) * bin_n_col + (j + 1)]);
        }
        if (i != bin_n_col - 1)
        {
            // compute forces with bottom neighbor
            compute_force_neighbor(bin, k, bins[(i + 1) * bin_n_col + (j)]);
        }
        if (i != bin_n_col - 1 && j != 0)
        {
            // compute forces with bottom left neighbor
            compute_force_neighbor(bin, k, bins[(i + 1) * bin_n_col + (j - 1)]);
        }
        if (j != 0)
        {
            // compute forces with left neighbor
            compute_force_neighbor(bin, k, bins[(i)*bin_n_col + (j - 1)]);
        }
    }
}

bin_t *bins;
int bin_n_col;

//
// create and init particles to bins
//
void init(int n)
{
    bin_n_col = bin_create(&bins, n);
    bin_init(bins, bin_n_col);
}

//
// delete bins
//

void destroy()
{
    bin_delete(bins, bin_n_col);
}

//
//  simulate 1 step
//
void simulateStep(particle_t *particles, int n)
{
    //
    // assign particles to bins
    //
    bin_assign(particles, n, bins, bin_n_col);

    //
    //  compute forces
    //
    for (int i = 0; i < bin_n_col; i++)
    {
        for (int j = 0; j < bin_n_col; j++)
        {
            compute_force_bin(i, j, bins, bin_n_col);
        }
    }

    //
    //  move particles
    //
    for (int i = 0; i < bin_n_col; i++)
    {
        for (int j = 0; j < bin_n_col; j++)
        {
            move_bin(i, j, bins, bin_n_col);
        }
    }

    //
    // empty bins
    //
    bin_clear(bins, bin_n_col);
}
