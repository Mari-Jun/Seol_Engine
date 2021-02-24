cbuffer cbWorldInfo : register(b0)
{
    matrix gWorld;
}

cbuffer cbCameraInfo : register(b1)
{
    matrix gViewProj;
}

struct VS_IN
{
	float3 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_OUT VSMain(VS_IN input)
{
	VS_OUT output;

    output.position = mul(mul(float4(input.position, 1.0f), gWorld), gViewProj);
	output.color = input.color;

	return output;
}

float4 PSMain(VS_OUT input) : SV_TARGET
{
	return input.color;
}