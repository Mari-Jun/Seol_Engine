#ifndef NUM_DIR_LIGHTS
    #define NUM_DIR_LIGHTS 1
#endif

#include "Light.hlsl"

struct InstanceData
{
    matrix world;
    matrix worldInverseTranspose;
    uint4 convertIndice[MaxMaterial];
};

StructuredBuffer<InstanceData> gInstanceDatas : register(t0, space0);
StructuredBuffer<Material> gMaterials : register(t1, space0);

cbuffer cbWorldInfo : register(b0)
{
    matrix gWorld;
    matrix gWorldInverseTranspose;
}

cbuffer cbConvertMatIndex : register(b1)
{
    int4 gConvertIndice[MaxMaterial];
}

cbuffer cbConvertMatIndex : register(b1, space1)
{
    uint gConvertIndex;
}

cbuffer cbColorPass : register(b2)
{
    matrix gViewProj;
    float3 gEyePos;
    float gPadding;
    
    int3 gLightCounts;
    float gPadding2;
    float4 gAmbientLight;
    Light gLights[MaxLights];
}

struct VS_DIFFUSE_IN
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

struct VS_DIFFUSE_OUT
{
    float4 position : SV_POSITION;
    float3 basicPos : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

VS_DIFFUSE_OUT VSDiffuseMain(VS_DIFFUSE_IN input, uint instanceID : SV_InstanceID)
{
    VS_DIFFUSE_OUT output;
    
    InstanceData instData = gInstanceDatas[instanceID];

    float4 pos = mul(float4(input.position, 1.0f), instData.world);
    output.position = mul(pos, gViewProj);
    output.basicPos = pos.xyz;
    output.normal = mul(input.normal, (float3x3)instData.worldInverseTranspose);
    output.normal = normalize(output.normal);
    output.color = input.color;
    
    return output;
}

float4 PSDiffuseMain(VS_DIFFUSE_OUT input) : SV_TARGET
{
    //return input.color;
    
    float3 eye = normalize(gEyePos - input.basicPos);
    
    float4 ambientLight = gAmbientLight * input.color;
    
    float4 directLight = ComputeLight(gLights, gLightCounts, input.basicPos, input.normal, eye) * input.color;
    
    float4 result = ambientLight + directLight;
     
    return result;
}


struct VS_MATERIAL_IN
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    int index : MATINDEX;
};

struct VS_MATERIAL_OUT
{
    float4 position : SV_POSITION;
    float3 basicPos : POSITION;
    float3 normal : NORMAL;
    float4 color : COLOR;
};

VS_MATERIAL_OUT VSMaterialMain(VS_MATERIAL_IN input, uint instanceID : SV_InstanceID)
{
    VS_MATERIAL_OUT output;
    
    InstanceData instData = gInstanceDatas[instanceID];
    
    float4 pos = mul(float4(input.position, 1.0f), instData.world);
    output.position = mul(pos, gViewProj);
    output.basicPos = pos.xyz;
    output.normal = mul(input.normal, (float3x3) instData.worldInverseTranspose);
    output.normal = normalize(output.normal);
    output.color = gMaterials[instData.convertIndice[0][0]].DiffuseAlbedo;
    
    return output;
}

float4 PSMaterialMain(VS_MATERIAL_OUT input) : SV_TARGET
{
    return input.color;
    
    //float3 eye = normalize(gEyePos - input.basicPos);
    
    //float4 ambientLight = gAmbientLight * input.color;
    
    //float4 directLight = ComputeLight(gLights, gLightCounts, input.basicPos, input.normal, eye) * input.color;
    
    //float4 result = ambientLight + directLight;
     
    //return result;
}