#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;
in vec4 FragPosLightSpace;

uniform sampler2D diffuseTexture;
uniform sampler2D shadowMap;

uniform vec3 viewPos;

struct Light {
    vec3 position;
    vec3 color;
    vec3 direction;
    float intensity;
};

uniform Light light;

float ShadowCalculation (vec4 FragPosLightSpace, vec3 norm, vec3 lightDir)
{
    // Perform perspective divide
    vec3 projCoords = FragPosLightSpace.xyz / FragPosLightSpace.w;

    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;

    // Keep shadows at 0.0 when outside the light's far plane
    if(projCoords.z > 1.0)
        return 0.0;

    float currentDepth = projCoords.z;
    float bias = max(0.005 * (1.0 - dot(norm, lightDir)), 0.0005);

    // PCF 
    float shadow = 0.0;
    
    // Get the size of a single texel in the shadow map
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

    // Loop through a 3x3 grid around the target pixel
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += (currentDepth - bias > pcfDepth) ? 1.0 : 0.0;        
        }    
    }

    // Average the result across all 9 samples
    shadow /= 9.0;

    return shadow;
}

void main()
{
    vec3 objectColor = texture(diffuseTexture, TexCoord).rgb;

    // Ambient
    float ambientStrength = 0.15;
    vec3 ambient = ambientStrength * light.color;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // Specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    
    float spec = pow(max(dot(norm, halfwayDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;

    float shadow = ShadowCalculation(FragPosLightSpace, norm, lightDir);

    vec3 lighting = ambient + (1.0 - shadow) * (diffuse + specular);
    vec3 finalColor = lighting * objectColor;

    FragColor = vec4(finalColor, 1.0);
}