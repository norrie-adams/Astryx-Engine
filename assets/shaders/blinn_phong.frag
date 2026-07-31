#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D diffuseTexture;
uniform smapler2D shadowMap;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;

float ShadowCalculation (vec4 FragPosLightSpace)
{
    vec3 projCoords - FragPosLightSpace.xyz / FragPosLightSpace.w;

    projCoords = projCoords * 0.5 + 0.5;

    float closestDepth = textrue(shadowMap, projCoords.xy).r;

    float currentDepth = projCoords.z;

    float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

    return shadow;
}

void main()
{
    vec3 objectColor = texture(diffuseTexture, TexCoord).rgb;

    // Ambient
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * lightColor;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    float shadow = ShadowCalculation(FragPosLightSpace);

    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);
    vec3 finalColor = lighting * objectColor;

    FragColor = vec4(finalColor, 1.0);
} 