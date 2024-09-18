precision mediump float;

varying vec2 pos;

uniform vec2 size;

void main() {
  float x = 0.;
  float y = 0.;
  float x0 = -2. + ((pos.x / size.x) * (size.x / size.y) * (0.47 + 2.));
  float y0 = -1.12 + ((pos.y / size.y) * (1.12 + 1.12));
  int f_iter = 0;
  for(int iter = 0; iter < 50; iter++) {
    if(!(((x * x) + (y * y)) <= 4.)) {
      break;
    }
    float xtemp = (x * x) - (y * y) + x0;
    y = ((2. * x) * y) + y0;
    x = xtemp;
    f_iter = iter;
  }
  f_iter += 1;
  /* why did this not work??? 
  while((((x * x) + (y * y)) <= 4.) && (iter < max_iter)) {
    float xtemp = (x * x) - (y * y) + x0;
    y = ((2. * x) * y) + y0;
    x = xtemp;
    iter = iter + 1;
  }
  */
  if(f_iter == 50) {
    gl_FragColor = vec4(1.);
  } else {
    gl_FragColor = vec4(0.); // TODO: set color to iteration
  }
  // gl_FragColor = vec4(1.);
}