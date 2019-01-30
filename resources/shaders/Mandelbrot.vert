#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform vec3 translation;
uniform vec3 rotation;
uniform vec3 scale;

layout (location = 0) in vec3 vCoord;
layout (location = 1) in vec2 uvCoord;

out vec2 f_uv;
out vec3 f_translation;
out vec3 f_rotation;
out vec3 f_scale;
out float f_time;

mat4 rotMat(vec3 axis, float angle)
{
    axis = normalize(axis);

    float s = sin(angle);
    float c = cos(angle);
    float oc = 1.0 - c;

    return mat4(oc * axis.x * axis.x + c,           oc * axis.x * axis.y - axis.z * s,  oc * axis.z * axis.x + axis.y * s,  0.0,
                oc * axis.x * axis.y + axis.z * s,  oc * axis.y * axis.y + c,           oc * axis.y * axis.z - axis.x * s,  0.0,
                oc * axis.z * axis.x - axis.y * s,  oc * axis.y * axis.z + axis.x * s,  oc * axis.z * axis.z + c,           0.0,
                0.0,                                0.0,                                0.0,                                1.0);
}

mat4 rotMat(vec3 rotation_vec) {
    mat4 rotMatX = rotMat(vec3(1.0, 0.0, 0.0), rotation.x);
    mat4 rotMatY = rotMat(vec3(0.0, 1.0, 0.0), rotation.y);
    mat4 rotMatZ = rotMat(vec3(0.0, 0.0, 1.0), rotation.z);
    return rotMatX * rotMatY * rotMatZ;
}

mat4 scaleMatrix(vec3 scale)
{
    return mat4(scale.x, 0.0,     0.0,     0.0,
                0.0,     scale.y, 0.0,     0.0,
                0.0,     0.0,     scale.z, 0.0,
                0.0,     0.0,     0.0,     1.0);
}

void main()
{
    gl_Position = projection * view * model * (scaleMatrix(scale) * rotMat(rotation)) * vec4(vCoord, 1.0) + vec4(translation, 0.0);

    f_uv = uvCoord;
    f_translation = translation;
    f_rotation = rotation;
    f_scale = scale;
    f_time = time;
}