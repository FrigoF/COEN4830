// mandelbrot.cu 
// 
//  Fred J. Frigo
//  28-Aug-2021
//
//  See section B19.4:
//  https://docs.nvidia.com/cuda/archive/9.1/pdf/CUDA_C_Programming_Guide.pdf`
//
//  See also;
//  http://selkie.macalester.edu/csinparallel/modules/CUDAArchitecture/build/html/1-Mandelbrot/Mandelbrot.html
//
//  To compile:  nvcc mandelbrot.cu -o mandelbrot
//

#include <stdio.h>

__device__ uint32_t mandel_double(double cr, double ci, int max_iter) {
    double zr = 0;
    double zi = 0;
    double zrsqr = 0;
    double zisqr = 0;

    uint32_t i;

    for (i = 0; i < max_iter; i++){
		zi = zr * zi;
		zi += zi;
		zi += ci;
		zr = zrsqr - zisqr + cr;
		zrsqr = zr * zr;
		zisqr = zi * zi;
		
    //the fewer iterations it takes to diverge, the farther from the set
		if (zrsqr + zisqr > 4.0) break;
    }
	
    return i;
}


__global__ void mandel_kernel(uint32_t *counts, double xmin, double ymin,
            double step, int max_iter, int dim, uint32_t *colors) {
    int pix_per_thread = dim * dim / (gridDim.x * blockDim.x);
    int tId = blockDim.x * blockIdx.x + threadIdx.x;
    int offset = pix_per_thread * tId;
    for (int i = offset; i < offset + pix_per_thread; i++){
        int x = i % dim;
        int y = i / dim;
        double cr = xmin + x * step;
        double ci = ymin + y * step;
        counts[y * dim + x]  = colors[mandel_double(cr, ci, max_iter)];
    }
    if (gridDim.x * blockDim.x * pix_per_thread < dim * dim
            && tId < (dim * dim) - (blockDim.x * gridDim.x)){
        int i = blockDim.x * gridDim.x * pix_per_thread + tId;
        int x = i % dim;
        int y = i / dim;
        double cr = xmin + x * step;
        double ci = ymin + y * step;
        counts[y * dim + x]  = colors[mandel_double(cr, ci, max_iter)];
    }
    
}

int main()
{ 
   
   mandel_kernel<<<n, m>>>(dev_counts, xmin , ymin, step, max_iter, dim, colors);
   cudaDeviceSynchronize();
   printf(“CUDA Mandelbrot\n”); 
   return 0;
}
