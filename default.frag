#version 330 core

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D tex0;

uniform vec3 camPos;

uniform vec3 lightPositions[8];
uniform vec3 lightColors[8];

uniform vec3 mainLightColor;
uniform vec3 mainLightPos;

uniform float ka;
uniform float kd;
uniform float ks;
uniform float shininess;

void main()
{
    vec3 ambient = vec3(0.0);
    vec3 diffuse = vec3(0.0);
    vec3 specular = vec3(0.0);

    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(camPos - FragPos);

    float ledIntensity = 0.1;

    for (int i = 0; i < 8; ++i)
    {
        vec3 lightDir = normalize(lightPositions[i] - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

        ambient  += ka * lightColors[i] * ledIntensity;
        diffuse  += kd * diff * lightColors[i] * ledIntensity;
        specular += ks * spec * lightColors[i] * ledIntensity;
    }

    // g³ówne œwiat³o – mocniejsze
    vec3 mainDir = normalize(mainLightPos - FragPos);
    float mainDiff = max(dot(norm, mainDir), 0.0);
    vec3 mainReflect = reflect(-mainDir, norm);
    float mainSpec = pow(max(dot(viewDir, mainReflect), 0.0), shininess);

    ambient  += ka * mainLightColor;
    diffuse  += kd * mainDiff * mainLightColor;
    specular += ks * mainSpec * mainLightColor;

    vec4 texColor = texture(tex0, TexCoord);
    vec3 lighting = ambient + diffuse + specular;
    FragColor = vec4(lighting, 1.0) * texColor;
}
