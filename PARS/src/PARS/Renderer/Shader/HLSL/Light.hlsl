#define MaxLights           16
#define MaxMaterial         8

struct Light
{
    float3 lightColor;
    float falloffStart;
    float3 direction;
    float falloffEnd;
    float3 position;
    float spotPower;
};

struct Material
{
    float4 DiffuseAlbedo;
    float3 FresnelR0;
    float Shininess;
};

float CalcAttenuation(float dist, float falloffStart, float falloffEnd)
{
    return saturate((falloffEnd - dist) / (falloffEnd - falloffStart));
}

float3 Fresnel(float3 R0, float3 normal, float3 lightVec)
{
    float cosAngle = saturate(dot(normal, lightVec));
    
    float F0 = 1.0f - cosAngle;
    float3 RF = R0 + (1.0f - R0) * pow(F0, 5);
    
    return RF;    
}

float3 BlinnPhong(float3 lightColor, float3 lightVec, float3 normal, float3 eye, Material mat)
{
    float3 halfVec = normalize(eye + lightVec);
    
    float m = mat.Shininess * 256.0f;
    float roughnessFactor = (m + 8.0f) * pow(max(dot(halfVec, normal), 0.0f), m) / 8.0f;
    float3 fresnelFactor = Fresnel(mat.FresnelR0, halfVec, lightVec);
    
    float3 specAlbedo = fresnelFactor * roughnessFactor;
    specAlbedo /= (specAlbedo + 1.0f);
    
    return (mat.DiffuseAlbedo.rgb + specAlbedo) * lightColor;
}

float3 ComputeDirectionalLight(Light light, Material mat, float3 normal, float3 eye)
{
    float3 lightVec = -light.direction;
    
    float ndotl = max(dot(lightVec, normal), 0.0f);
    float3 lightColor = light.lightColor * ndotl;
    
    return BlinnPhong(lightColor, lightVec, normal, eye, mat);
}

float3 ComputePointLight(Light light, Material mat, float3 pos, float3 normal, float3 eye)
{
    float3 lightVec = light.position - pos;
    
    float dist = length(lightVec);
    
    if(dist > light.falloffEnd)
        return 0.0f;
    
    lightVec /= dist;
    
    float ndotl = max(dot(lightVec, normal), 0.0f);
    float3 lightColor = light.lightColor * ndotl;
    
    float attenuation = CalcAttenuation(dist, light.falloffStart, light.falloffEnd);
    lightColor *= attenuation;
    
    return BlinnPhong(lightColor, lightVec, normal, eye, mat);
}

float3 ComputeSpotLight(Light light, Material mat, float3 pos, float3 normal, float eye)
{
    float3 lightVec = light.position - pos;
    
    float dist = length(lightVec);
    
    if(dist > light.falloffEnd)
        return 0.0f;
    
    lightVec /= dist;
    
    float ndotl = max(dot(lightVec, normal), 0.0f);
    float3 lightColor = light.lightColor * ndotl;
    
    float attenuation = CalcAttenuation(dist, light.falloffStart, light.falloffEnd);
    lightColor *= attenuation;
    
    float spotFactor = pow(max(dot(-lightVec, light.direction), 0.0f), light.spotPower);
    lightColor *= spotFactor;
    
    return BlinnPhong(lightColor, lightVec, normal, eye, mat);
}

float4 ComputeLight(Light lights[MaxLights], Material mat, int3 lightCounts, float3 pos, float3 normal, float3 eye)
{
    float3 result = 0.0f;
  
    for(int i = 0; i < lightCounts.x; ++i)
    {
        result += ComputeDirectionalLight(lights[i], mat, normal, eye);
    }
    
    return float4(result, 0.0f);
}