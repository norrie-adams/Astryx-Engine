#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 fragPosLightSpace;

struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;
    float intensity;
};

uniform Light light;

uniform vec3 light.position;
uniform vec3 viewPos;
uniform vec3 light.color;
uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

float shadowCalculation(vec4 fragPosLightSpace, vec3 normal, vec3 lightDir)
{
    // Convert Clip Space -> NDC 
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

    // Convert to UV range
    projCoords = projCoords * 0.5 + 0.5;

    // Get depth of current fragment
    float currentDepth = projCoords.z;

    // Makes fragments beyond shadow map plane not be shadowed to prevent weird shadows
    if(projCoords.z > 1.0)
        return 0.0;

    // Shadow bias to prevent shadow acne (small offset)
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);

    // Sample closet depth value from shadow map
    float closetDepth = texture(shadowMap, projCoords.xy).r;

    // Check if current fragment is in shadow
    float shadow = currentDepth - bias > closetDepth ? 1.0 : 0.0;

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
    vec3 lightDir = normalize(light.position - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;

    // Shadows
    float shadow = shadowCalculation(fragPosLightSpace, norm, lightDir);

    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);

    vec3 finalColor = lighting * objectColor;

    FragColor = vec4(finalColor, 1.0);
} 