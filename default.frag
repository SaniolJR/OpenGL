#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D tex0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

uniform float ka;
uniform float kd;
uniform float ks;
uniform float shininess;

void main()
{
    vec3 ambient = ka * lightColor.rgb;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = kd * diff * lightColor.rgb;

    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = ks * spec * lightColor.rgb;

    vec3 texColor = texture(tex0, TexCoord).rgb;
    vec3 result = (ambient + diffuse + specular) * texColor;

    FragColor = vec4(result, 1.0);
}
