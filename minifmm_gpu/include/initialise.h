#pragma once

#include "params.h"

void initialise(int argc, char** argv, t_fmm_params* params);
void init_data(t_fmm_params* params);
void init_with_known_data(t_fmm_params* params, double *weights, double *points, long num_points, int num_terms, int ncrit, float theta);
void precompute(t_fmm_params* params);
