#ifndef NUM_DIR_LIGHTS
    #define NUM_DIR_LIGHTS 1
#endif

#include "Light.hlsl"


cbuffer cbWorldInfo : register(b0)
{
    matrix gWorld;
    matrix gWorldInverseTranspose;
}

cbuffer cbColorPass : register(b1)
{
    matrix gViewProj;
    float3 gEyePos;
    float gPadding;
    
    int3 gLightCounts;
    float gPadding2;
    float4 gAmbientLight;
    Light gLights[MaxLights];
}

struct VS_IN
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

struct VS_OUT
{
    float4 position : SV_POSITION;
    float3 basicPos : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

VS_OUT VSMain(VS_IN input)
{
    VS_OUT output;

    float4 pos = mul(float4(input.position, 1.0f), gWorld);
    output.position = mul(pos, gViewProj);
    output.basicPos = pos.xyz;
    output.normal = mul(input.normal, (float3x3)gWorldInverseTranspose);
    output.normal = normalize(output.normal);
    output.color = input.color;
    
    return output;
}

float4 PSMain(VS_OUT input) : SV_TARGET
{
    //return input.color;
    
    float3 eye = normalize(gEyePos - input.basicPos);
    
    float4 ambientLight = gAmbientLight * input.color;
    
    float4 directLight = ComputeLight(gLights, gLightCounts, input.basicPos, input.normal, eye) * input.color;
    
    float4 result = ambientLight + directLight;
     
    return result;
}