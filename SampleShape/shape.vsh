cbuffer cb0
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
};

struct VS_PC_INPUT
{
	float3 p : POSITION;
	float4 c : COLOR;
};
struct VS_PC_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
};
struct VS_INPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(vIn.p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.c = vIn.c;
	output.n = vIn.n;
	output.t = vIn.t;
	return output;
}
VS_PC_OUTPUT VSLine(VS_PC_INPUT vIn)
{
	VS_PC_OUTPUT output = (VS_PC_OUTPUT)0;
	output.p = mul(vIn.p, g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.c = vIn.c;
	return output;
}
