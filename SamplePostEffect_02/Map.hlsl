Texture2D g_txDiffuse: register (t0);
Texture2D g_txShadow : register (t1);

SamplerState samLinear: register (s0);
SamplerState ShadowLinear: register (s1);

cbuffer cb0 : register(b0)
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView: packoffset(c4);
	matrix g_matProj: packoffset(c8);
	float4 g_MeshColor : packoffset(c12);
};
cbuffer cb1 : register(b1)
{
	float4 vDirectionLight : packoffset(c0);
	float4 vDiffuseLight : packoffset(c1);
	float4 vAmbientLight : packoffset(c2);
	float4 vSpecularLight : packoffset(c3);
	float4 vDiffuseColor : packoffset(c4);
	float4 vAmbientColor : packoffset(c5);
	float4 vSpecularColor : packoffset(c6);
};
struct VS_INPUT
{
	float3 p  : POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR;
	float2 t  : TEXCOORD;
};
struct VS_OUTPUT
{
	float4 p  : SV_POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR0;
	float2 t  : TEXCOORD0;
	float4 tShadow : TEXCOORD1;
};
// Vertex Shader
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(float4(vIn.p, 1.0f), g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);

	output.n = vIn.n;
	output.t = vIn.t;
	output.c = vIn.c;
	float fNear = 0.1f;
	float fFar = 300.0f;
	output.c.w = (output.p.w - fNear) / (fFar - fNear);
	return output;
}
VS_OUTPUT VS_NORMAL_MAP(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(float4(vIn.p, 1.0f), g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.n = vIn.n;
	output.t = vIn.t;
	output.c = vIn.c;
	float fNear = 0.1f;
	float fFar = 1000.0f;
	output.c.w = (output.p.w - fNear) / (fFar - fNear);
	return output;
}
// Pixel Shader
struct PBUFFER_OUTPUT
{
	float4 color0 : SV_TARGET0;
	float4 color1 : SV_TARGET1;
};
PBUFFER_OUTPUT PS(VS_OUTPUT vIn) : SV_Target
{
	PBUFFER_OUTPUT output;
	float4 vColor = g_txDiffuse.Sample(samLinear, vIn.t);

	output.color0 = vColor;
	float3 vNormal = vIn.n * 0.5f + 0.5f;
	output.color1 = float4(vNormal, vIn.c.w);
	return output;
}
PBUFFER_OUTPUT PS_NORMAL_MAP(VS_OUTPUT vIn) : SV_Target
{
	PBUFFER_OUTPUT output;
	float4 vColor = g_txDiffuse.Sample(samLinear, vIn.t);
	float4 vColor2 = g_txShadow.Sample(samLinear, vIn.t);
	vColor2 = normalize((vColor2 - 0.5f) * 2.0f);
	float3 vLight = normalize(float4(vDirectionLight.x, vDirectionLight.y, vDirectionLight.z, vDirectionLight.w));
	float fDot = dot(vColor2.xyz, vLight);
	float3 vLightColor = float3(1, 1, 1) * fDot;
	float4 vFinal = vColor * float4(vLightColor,1.0f);
	output.color0 = vFinal;
	float3 vNormal = vIn.n * 0.5f + 0.5f;
	output.color1 = float4(vNormal, vIn.c.w);
	return output;
}