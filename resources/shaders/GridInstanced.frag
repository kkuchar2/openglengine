#version 400


uniform vec2 resolution;
uniform sampler2D tex;

in vec2 uv;

out vec4 FragColor;

void main()
{
     float divisions = 200.0;

     float distance = sqrt(pow(uv.x - 0.5, 2) + pow(uv.y - 0.5, 2));

     float thickness = 0.01;

     float delta = 0.05 / 2.0;

     float x = fract(uv.x / (1.0 / divisions));
     float y = fract(uv.y / (1.0 / divisions));

     float xdelta = fwidth(x) * 2.5;
     float ydelta = fwidth(y) * 2.5;

     x = smoothstep(x - xdelta, x + xdelta, thickness);
     y = smoothstep(y - ydelta, y + ydelta, thickness);

     float c = clamp(x + y, 0.1, 1.0);

     float sigmaX = 0.05;
     float sigmaY = 0.05;

     float amplitude = 0.5;

     float x_coeff = pow(uv.x - 0.5, 2.0) / (2.0 * pow(sigmaX, 2.0));
     float y_coeff = pow(uv.y - 0.5, 2.0) / (2.0 * pow(sigmaY, 2.0));
     float gauss = amplitude * exp(-(x_coeff + y_coeff));

     FragColor = vec4(c, c, c, gauss);
}