#include <stdio.h>
#include <stdlib.h>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include "rng.h"
#include "params.h"
#include "parse_args.h"
#include "traversal.h"
#include "type.h"
#include "kernels.h"
#include "timer.h"
#include "verify.h"
#include "initialise.h"
#include "finalise.h"
#include "util.h"
namespace py = pybind11;
const static size_t DEFAULT_NUM_POINTS      = 100000;
const static size_t DEFAULT_NCRIT           = 200;
const static int DEFAULT_NUM_TERMS          = 10;
const static TYPE DEFAULT_THETA             = 0.5;
const static size_t DEFAULT_NUM_SAMPLES     = 100;
void init_defaults(t_fmm_params* params)
{
    params->num_points     = DEFAULT_NUM_POINTS;
    params->ncrit          = DEFAULT_NCRIT;
    params->num_terms      = DEFAULT_NUM_TERMS;
    params->theta          = DEFAULT_THETA;
    params->num_samples    = DEFAULT_NUM_SAMPLES;
}
double * minifmm(double *weights, double *points, long num_points, int num_terms, int ncri, float theta)
{
    struct t_fmm_params params = t_fmm_params();
    init_defaults(&params);
    init_with_known_data(&params, weights, points, num_points, num_terms, ncri, theta);
    print_args(&params);
    printf("starting computation\n");
    printf(SEPERATOR);
    perform_fmm(&params);
    printf(SEPERATOR);
    double *ptrOut =(double *) malloc(sizeof(double)*num_points);
    for(int l = 0 ; l < num_points ; l++)
    {
        ptrOut[l] = params.pot[l];
    }
    finalise(&params);
    return ptrOut;
}

py::array_t<double, py::array::c_style | py::array::forcecast> minifmm_pybind(py::size_t num_points,
 py::array_t<double, py::array::c_style | py::array::forcecast> locations,
 py::array_t<double, py::array::c_style | py::array::forcecast> weights)
{
    py::buffer_info loc = locations.request();
    double *points = (double *) loc.ptr;
    py::buffer_info wt_buffer = weights.request();
    double *wt = (double *) wt_buffer.ptr;
    // Output Array
    py::array_t<double, py::array::c_style | py::array::forcecast> output({num_points});
    py::buffer_info out = output.request();
    double *ptrOut = (double *) out.ptr;

    //double *pot = minifmm(wt, points, num_points, 7, 200, 0.5);

    struct t_fmm_params params = t_fmm_params();
    init_defaults(&params);
    init_with_known_data(&params, wt, points, num_points, 7, 200, 0.5);
    printf("starting computation\n");
    printf(SEPERATOR);
    perform_fmm(&params);
    printf(SEPERATOR);
    for(int l = 0 ; l < num_points ; l++)
        ptrOut[l] = params.pot[l];
    return output;
}

PYBIND11_MODULE(minifmm, m)
{
    m.doc() = "Calculate the Repulsive Force gradient with MiniFMM on GPU"; // optional
    m.def("minifmm_pybind", &minifmm_pybind, py::return_value_policy::move);
}