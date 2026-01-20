#ifndef __MANDEL_OFFLOAD_H
#define __MANDEL_OFFLOAD_H

void mandel_gpu_loop(int width, int height, int *image, int max_iter);
void mandel_gpu_parallel(int width, int height, int *image, int max_iter);

#endif
