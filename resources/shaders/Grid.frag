#version 400

in vec2 f_uv;
in vec3 f_translation;
in float f_time;

out vec4 FragColor;

uniform vec2 resolution;
uniform sampler2D tex;


void main()
{
     float divisions = 100.0;

     float distance = sqrt(pow(f_uv.x - 0.5, 2) + pow(f_uv.y - 0.5, 2));

     float thickness = 0.01;

     float delta = 0.05 / 2.0;

     float x = fract(f_uv.x / (1.0 / divisions));
     float y = fract(f_uv.y / (1.0 / divisions));



     float xdelta = fwidth(x) * 2.5;
     float ydelta = fwidth(y) * 2.5;

     x = smoothstep(x - xdelta, x + xdelta, thickness);
     y = smoothstep(y - ydelta, y + ydelta, thickness);

     float c = clamp(x + y, 0.1, 1.0);

     float sigmaX = 0.15;
     float sigmaY = 0.15;

     float amplitude = 0.7;

     float x_coeff = pow(f_uv.x - 0.5, 2.0) / (2.0 * pow(sigmaX, 2.0));
     float y_coeff = pow(f_uv.y - 0.5, 2.0) / (2.0 * pow(sigmaY, 2.0));
     float gauss = amplitude * exp(-(x_coeff + y_coeff));

     gl_FragColor = vec4(c, c, c, gauss);
}