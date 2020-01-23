#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 fragPosition;
out vec3 normal;

uniform mat4 proj;
uniform mat4 view;
uniform mat4 world;

void main()
{
    mat4 modelview = view * world;
    fragPosition = vec3(modelview * vec4(aPos, 1.0));
    normal = mat3(transpose(inverse(modelview))) * aNormal;

    gl_Position = proj * modelview * vec4(aPos.x, aPos.y, aPos.z, 1.0);
};