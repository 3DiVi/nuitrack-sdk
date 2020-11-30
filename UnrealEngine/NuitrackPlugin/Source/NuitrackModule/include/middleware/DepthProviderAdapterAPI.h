#ifndef DEPTHPROVIDERADAPTERAPI_H_
#define DEPTHPROVIDERADAPTERAPI_H_

#include <stdint.h>

/**
 * Output mode for depth map
 */
typedef struct
{
	// PFS
	int fps;

	// X resolution
	int xres;

	// Y resolution
	int yres;

	// Horizontal field of view
	float hfov;
} DepthOutputMode;

extern "C"
{

/**
 * Callback for depth map
 */
typedef void (*depth_callback)(uint32_t frame_id, uint64_t timestamp, const uint16_t* depth_buffer);

/**
 * Initialize library
 */
bool init();

/**
 * Get depth map output mode
 */
DepthOutputMode get_depth_output_mode();

/**
 * Set depth map callback
 */
void set_depth_callback(depth_callback callback);

/**
 * Start generating depth map, call depth map callback
 */
void start_depth();

/**
 * Stop generating
 */
void stop_depth();

/**
 * Release library
 */
void release();

}

#endif /* DEPTHPROVIDERADAPTERAPI_H_ */
