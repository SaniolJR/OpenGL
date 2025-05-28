#version 330 core
uniform vec3 ledColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ledColor, 1.0);
}
