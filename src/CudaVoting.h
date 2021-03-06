/*
 * =====================================================================================
 *
 *       Filename:  CudaVoting.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2012 04:48:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ming Liu (), ming.liu@mavt.ethz.ch
 *        Company:  ETHZ
 *
 * =====================================================================================
 */

#ifndef CUDAVOTING_H
#define CUDAVOTING_H

#include <vector_types.h>
namespace cudavoting{


    class CudaVoting{
        public:
   
        // executes sparse voting using initial ball tensors (distance measures)
        static void sparseBallVoting(float3 * h_fieldarray,
                    const float3 * h_points,
                    const float sigma, const int numPoints, int2 * h_log);
    
        // executes dense voting using initial ball tensors (distance measures)
        static void denseStickVoting(float3 * h_fieldarray,
                    const float3 * h_points, const float4 * h_sparsestick,
                    const float sigma, const int numPoints, int2 * h_log);
        // executes dense voting using initial ball tensors (distance measures)
        static void denseGridStickVoting(float3 * h_fieldarray, float3 * h_grids,
                    const float3 * h_points, const float4 * h_sparsestick,
                    const float sigma, const unsigned int numGrids, const int numPoints, int2 * h_log);

        // real dense voting by creating grid over points
        static void realDenseGridStickVoting(float3 * h_fieldarray,
                    const float3 * h_points, const float4 * h_sparsestick, 
                    const size_t maxGridSize, const int hw_size,
                    const float sigma, const float cell_size, const int numPoints, 
                    const unsigned int grid_dimx,
                    const unsigned int grid_dimy,
                    const unsigned int grid_dimz,
                    const float min_x,
                    const float min_y,
                    const float min_z,
                    int2 * hh_log);

        // tensor split by eigen decomposition of 33 matrix
        static void tensorSplit(
                    float3 * h_fieldarray, 
                    float * stick,
                    float * plate,
                    float * ball,
                    const int numPoints
                    );
        static void tensorSplitWithField(
                    float3 * h_fieldarray, 
                    float * stick,
                    float * plate,
                    float * ball,
                    float3 * h_stick_field,
                    float3 * h_plate_field,
                    const int numPoints
                    );
        static void unifiedDenseGridStickVoting(
                    const float3 * h_points, 
                    const size_t maxGridSize, const int hw_size,
                    const float sigma, const float cell_size, const int numPoints, 
                    const unsigned int grid_dimx,
                    const unsigned int grid_dimy,
                    const unsigned int grid_dimz,
                    const float min_x,
                    const float min_y,
                    const float min_z,
                    float * stick_saliency_grid,
                    float * plate_saliency_grid,
                    float * ball_saliency_grid,
                    float3 * grid_normals,
                    int2 * hh_log
                    );
//        static void unifiedDenseGridPlateVoting(
//                    const float3 * h_points, 
//                    const size_t maxGridSize, const int hw_size,
//                    const float sigma, const float cell_size, const int numPoints, 
//                    const unsigned int grid_dimx,
//                    const unsigned int grid_dimy,
//                    const unsigned int grid_dimz,
//                    const float min_x,
//                    const float min_y,
//                    const float min_z,
//                    float * stick_saliency_grid,
//                    float * plate_saliency_grid,
//                    float * ball_saliency_grid,
//                    int2 * hh_log
//                    );
    };


}






#endif
