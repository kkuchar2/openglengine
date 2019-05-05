#version 330 core

uniform sampler2D tex;

in vec2 uv;

out vec4 FragColor;

vec2 cmpxcjg(in vec2 c) {
	return vec2(c.x, -c.y);
}

vec2 cmpxmul(in vec2 a, in vec2 b) {
	return vec2(a.x * b.x - a.y * b.y, a.y * b.x + a.x * b.y);
}

vec2 cmpxpow(in vec2 c, int p) {
    vec2 tmp = vec2(1.0,0.0) ;
    for (int i = 0; i < p; ++i) {
        c = cmpxmul(tmp, c);
    }
    return c;
}

vec2 cmpxdiv(in vec2 a, in vec2 b) {
    return cmpxmul(a, cmpxcjg(b));
}

float cmpxmag(in vec2 c) {
    return sqrt(c.x * c.x + c.y * c.y);
}

float madelbrot(in vec2 c, in int iterations) {

    float n = 0.0;

    vec2 z = vec2(0.0, 0.0);

    while (cmpxmag(z) <= 2.0 && n < iterations) {
        z = cmpxmul(z, z) + c;
        n += 1;
    }

    return n;
}

void main()
{
    // [(0, 0) -> (1, 1)] from bottom left
    vec2 normPos = uv;

    // [(-0.5, -0.5) -> (0.5, 0.5)] from bottom left
    normPos = normPos - vec2(0.5, 0.5);

    // [(-1, -1) -> (1, 1)] from bottom left
    normPos = normPos * 2.0;

    // [(-2, -1) -> (2, 1)] from bottom left
    normPos = vec2(normPos.x * 2.0 - 0.5, normPos.y * 1.2);

    // Complex number
    vec2 c = vec2(normPos.x, normPos.y);

    float a = madelbrot(c, 80) / 80;

    vec3 one = vec3(1.0, 1.0, 1.0);

    vec3 rgb = texture(tex, uv).rgb;

    FragColor = vec4(rgb * a, 0.5);
}