cbuffer cb0
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
};

struct VS_INPUT
{
	float4 p : POSITION;
	float4 c : COLOR;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
};

VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(vIn.p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.c = vIn.c;
	return output;
}

float4 PS(VS_OUTPUT vIn) : SV_Target
{
	return vIn.c;
}

float4 RED(VS_OUTPUT vIn) : SV_Target
{
	return float4(1.0f,0.0f,0.0f,1.0f);
}

float4 GREEN(VS_OUTPUT vIn) : SV_Target
{
	return float4(0.0f,1.0f,0.0f,1.0f);
}

float4 BLUE(VS_OUTPUT vIn) : SV_Target
{
	return float4(0.0f,0.0f,1.0f,1.0f);
}
