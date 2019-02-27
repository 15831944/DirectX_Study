//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D g_txDiffuse: register (t0);
SamplerState samLinear: register (s0);
cbuffer cb0
{
	float4x4	g_matWorld		: packoffset(c0);
	float4x4	g_matView		: packoffset(c4);
	float4x4	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};
//--------------------------------------------------------------------------------------
struct VS_INPUT
{
	float3 p : POSITION;
	float4 c : COLOR;
	float2 t : TEXCOORD;
	row_major float4x4 mTransform : mTransform;
	row_major float1x4 pc		: POSCOLOR;
	uint InstanceId : SV_InstanceID;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
	uint   i : INDEX;
};

//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(float4(vIn.p, 1.0f), vIn.mTransform);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.t = vIn.t;
	output.c = vIn.pc;
	output.i = vIn.InstanceId;
	return output;
}

//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(VS_OUTPUT vIn) : SV_Target
{
	return g_txDiffuse.Sample(samLinear, vIn.t);// *vIn.c;
}
