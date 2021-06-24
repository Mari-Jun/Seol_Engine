#define MaxLights 16

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
    
};

//float3 BlinnPhong(float3 lightColor, float3 lightVec, float3 normal, float3 eye)
//{
//    float3 halfVec = normalize(eye + lightVec);
    
    
//}

float3 ComputeDirectionalLight(Light light, float3 normal, float3 eye)
{
    float3 lightVec = -light.direction;
    
    float ndotl = max(dot(lightVec, normal), 0.0f);
    float3 lightColor = light.lightColor * ndotl;
    
    return lightColor;
}

float4 ComputeLight(Light lights[MaxLights], float3 pos, float3 normal, float3 eye)
{
    float3 result = 0.0f;
  
#if (NUM_DIR_LIGHTS > 0)
    for(int i = 0; i < NUM_DIR_LIGHTS; ++i)
    {
        result += ComputeDirectionalLight(lights[i], normal, eye);
    }
#endif

    return float4(result, 0.0f);
}