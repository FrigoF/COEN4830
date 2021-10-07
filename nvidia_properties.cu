// nvidia_properties.cu 
// 
//  Fred J. Frigo
//  07-Oct-2021
//
//
//  See CUDA by Example, J Sanders & E Kandrot, p 33
//
//  To compile:  nvcc nvidia_properties.cu -o nvidia_props
//

#include <stdio.h>
#include <unistd.h>
#include <err.h>
#include <stdint.h>

// you must first call the cudaGetDeviceProperties() function, then pass 
// the devProp structure returned to this function:
int getSPcores(cudaDeviceProp devProp)
{  
    int cores = 0;
    int mp = devProp.multiProcessorCount;
    switch (devProp.major){
     case 2: // Fermi
      if (devProp.minor == 1) cores = mp * 48;
      else cores = mp * 32;
      break;
     case 3: // Kepler
      cores = mp * 192;
      break;
     case 5: // Maxwell
      cores = mp * 128;
      break;
     case 6: // Pascal
      if ((devProp.minor == 1) || (devProp.minor == 2)) cores = mp * 128;
      else if (devProp.minor == 0) cores = mp * 64;
      else printf("Unknown device type\n");
      break;
     case 7: // Volta and Turing
      if ((devProp.minor == 0) || (devProp.minor == 5)) cores = mp * 64;
      else printf("Unknown device type\n");
      break;
     case 8: // Ampere
      if (devProp.minor == 0) cores = mp * 64;
      else if (devProp.minor == 6) cores = mp * 128;
      else printf("Unknown device type\n");
      break;
     default:
      printf("Unknown device type\n"); 
      break;
      }
    return cores;
}

int main( void ) 
{
    cudaDeviceProp prop;
    int count;

    cudaGetDeviceCount( &count );

    for (int i=0; i< count; i++) {
        cudaGetDeviceProperties( &prop, i );
        printf( " --- General Information for device %d ---\n", i );
        printf( "Name: %s\n", prop.name );
        printf( "Total cores = %d\n", getSPcores(prop));
        printf( "Compute capability: %d.%d\n", prop.major, prop.minor );
        printf( "Clock rate: %d\n", prop.clockRate );
        printf( "Device copy overlap: " );
        if (prop.deviceOverlap)
            printf( "Enabled\n" );
        else
            printf( "Disabled\n" );
        printf( "Kernel execition timeout : " );
        if (prop.kernelExecTimeoutEnabled)
            printf( "Enabled\n" );
        else
            printf( "Disabled\n" );
        printf( " --- Memory Information for device %d ---\n", i );
        printf( "Total global mem: %ld\n", prop.totalGlobalMem );
        printf( "Total constant Mem: %ld\n", prop.totalConstMem );
        printf( "Max mem pitch: %ld\n", prop.memPitch );
        printf( "Texture Alignment: %ld\n", prop.textureAlignment );
        printf( " --- MP Information for device %d ---\n", i );
        printf( "Multiprocessor count: %d\n", prop.multiProcessorCount );
        printf( "Shared mem per mp: %ld\n", prop.sharedMemPerBlock );
        printf( "Registers per mp: %d\n", prop.regsPerBlock );
        printf( "Threads in warp: %d\n", prop.warpSize );
        printf( "Max threads per block: %d\n", prop.maxThreadsPerBlock );
        printf( "Max thread dimensions: (%d, %d, %d)\n",
            prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2] );
        printf( "Max grid dimensions: (%d, %d, %d)\n",
            prop.maxGridSize[0], prop.maxGridSize[1],prop.maxGridSize[2] );
        printf( "\n" );
    }
    return(0);
}
