

//Make it so we don't need to include any other C files in our build.
#define CNFG_IMPLEMENTATION

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rawdraw_sf.h"

float xOffset = -2.0;
float yOffset = -1.12;
float xZoom = 0.0;
float yZoom = 0.0;
float zoom = 1.0; // Unused for now
bool render = true;

void HandleKey(int keycode, int bDown) {
	switch(keycode) {
		case 87: {
			if(bDown) {
				xZoom += (-2.47 / 10);
				yZoom += (-2.47 / 10);
				render = true;
			}
			break;
		}
		case 83: {
			if(bDown) {
				xZoom -= (-2.47 / 10);
				yZoom -= (-2.47 / 10);
				render = true;
			}
			break;
		}
		case 161: {
			if(bDown) {
				xOffset -= 0.1;
				render = true;
			}
			break;
		}
		case 162: {
			if(bDown) {
				yOffset -= 0.1;
				render = true;
			}
			break;
		}
		case 163: {
			if(bDown) {
				xOffset += 0.1;
				render = true;
			}
			break;
		}
		case 164: {
			if(bDown) {
				yOffset += 0.1;
				render = true;
			}
			break;
		}
		default: {
			printf("Key: %d, bDown(?): %d\n", keycode, bDown);
		}
	}
}
void HandleButton(int x, int y, int button, int bDown) { }
void HandleMotion(int x, int y, int mask) { }
int HandleDestroy() { return 0; }
int main()
{
	uint32_t* palette = calloc(0xffffff, sizeof(uint32_t));
	for(uint32_t i = 1; i < 0xffffff; i++) {
		palette[i] = (((palette[i - 1] >> 8) + 1) << 8) | 0x000000ff;
	}
	CNFGSetup("mandelbrot set", 1024, 768);
	while(CNFGHandleInput())
	{
		short w, h;
		CNFGClearFrame();
		CNFGGetDimensions(&w, &h);
		
		if(render) {
			for(int px = 0; px < w; px++) {
			    for(int py = 0; py < h; py++) {
				    float x0 = xOffset + (((float)px) / ((float)w)) * (((float)w) / ((float)h)) *  (0.47 - (-2.0));
				    float y0 = yOffset + (((float)py) / ((float)h)) * (1.12 - (-1.12));
    				float x = 0.0;
	    			float y = 0.0;
    				int iter = 0;
	    			int max_iter = 1000;
		    		while((((x*x) + (y*y)) <= 4) && (iter < max_iter)) {
			    		float xtemp = (x*x) - (y*y) + x0;
				    	y = ((2.0 * x) * y) + y0;
    					x = xtemp;
	    				iter++;
		    		}

			    	if(iter == max_iter) {
				    	CNFGColor(0x00000000);
					    CNFGTackPixel(px, py);
				    } else {
					    CNFGColor(palette[iter]);
					    CNFGTackPixel(px, py);
				    }
			    }
		    }

		    CNFGSwapBuffers();
			render = false;
		}
	}
	free(palette);
}