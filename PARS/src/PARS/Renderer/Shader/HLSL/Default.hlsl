#ifndef NUM_DIR_LIGHTS
    #define NUM_DIR_LIGHTS 1
#endif

#include "Light.hlsl"

struct InstanceData
{
    matrix world;
    matrix worldInverseTranspose;
};

struct MaterialInstanceData
{
    uint index;
};

struct MaterialData
{
    float4 diffuseAlbedo;
    float3 fresnelR0;
    float roughness;
    
    int diffuseMapIndex;
    uint padding0;
    uint padding1;
    uint padding2;
};

StructuredBuffer<InstanceData> gInstanceDatas : register(t0, space0);
StructuredBuffer<MaterialInstanceData> gMaterialInstanceDatas : register(t1, space0);
StructuredBuffer<MaterialData> gMaterials : register(t2, space0);

Texture2D gDiffuseMap[] : register(t3);

SamplerState gSamplerState : register(s0);

//cbuffer cbWorldInfo : register(b0)
//{
//    matrix gWorld;
//    matrix gWorldInverseTranspose;
//}

cbuffer cbCurMatIndex : register(b0, space0)
{
    uint gMatIndex;
};

cbuffer cbDefaultPass : register(b1, space0)
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
    return input.color;
    
    //float3 eye = normalize(gEyePos - input.basicPos);
    
    //float4 ambientLight = gAmbientLight * input.color;
    
    //float4 directLight = ComputeLight(gLights, gLightCounts, input.basicPos, input.normal, eye) * input.color;
    
    //float4 result = ambientLight + directLight;
     
    //return result;
}


struct VS_MATERIAL_IN
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD;
};

struct VS_MATERIAL_OUT
{
    float4 position : SV_POSITION;
    float3 basicPos : POSITION;
    float3 normal : NORMAL;
    float2 texcoord : TEXCOORD;
    nointerpolation uint matIndex : MATINDEX;
};

VS_MATERIAL_OUT VSMaterialMain(VS_MATERIAL_IN input, uint instanceID : SV_InstanceID)
{    
    VS_MATERIAL_OUT output;
    
    InstanceData instData = gInstanceDatas[instanceID];
    
    float4 pos = mul(float4(input.position, 1.0f), instData.world);
    output.position = mul(pos, gViewProj);
    output.basicPos = pos.xyz;
        
    //노멀을 언리얼, Max에서 scale변환을 하지 않는 행렬을 곱해주는 것 같다..
    //일단은 역전치행렬 곱해주고..
    output.normal = mul(input.normal, (float3x3)instData.worldInverseTranspose);
    //output.normal = input.normal;
    output.texcoord = input.texcoord;
    
    output.matIndex = gMaterialInstanceDatas[instanceID].index;
    
    return output;
}

float4 PSMaterialMain(VS_MATERIAL_OUT input) : SV_TARGET
{
    //return float4(input.texcoord, 0.0f, 0.0f);
    //return gMaterials[input.matIndex].DiffuseAlbedo;
    
    MaterialData matData = gMaterials[input.matIndex];
    float4 diffuseAlbedo = matData.diffuseAlbedo;
    float3 fresnelR0 = matData.fresnelR0;
    float shininess = 1.0f - matData.roughness;
    
    if(matData.diffuseMapIndex >= 0)
    {
        diffuseAlbedo *= gDiffuseMap[matData.diffuseMapIndex].Sample(gSamplerState, input.texcoord);
    }
    
    input.normal = normalize(input.normal);
    
    //return float4(abs(input.normal), 1.0f);
    
    float3 eye = normalize(gEyePos - input.basicPos);
    
    float4 ambientLight = gAmbientLight * diffuseAlbedo;
    
    Material mat = { diffuseAlbedo, fresnelR0, shininess };
    
    float4 directLight = ComputeLight(gLights, mat, gLightCounts, input.basicPos, input.normal, eye);
    
    float4 result = ambientLight + directLight;
    
    result.a = diffuseAlbedo.a;
     
    return result;
}