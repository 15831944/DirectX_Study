Texture2D g_txDiffuse: register (t0);
SamplerState samLinear: register (s0);

cbuffer cb0
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView: packoffset(c4);
	matrix g_matProj: packoffset(c8);
	float4 g_MeshColor : packoffset(c12);
};
cbuffer cb1
{
	float4 vDirectionLight : packoffset(c0);
	float4 vDiffuseLight : packoffset(c1);
	float4 vAmbientLight : packoffset(c2);
	float4 vSpecularLight : packoffset(c3);
	float4 vDiffuseColor : packoffset(c4);
	float4 vAmbientColor : packoffset(c5);
	float4 vSpecularColor : packoffset(c6);
};
struct VS_PC_INPUT
{
	float3 p  : POSITION;
	float4 c  : COLOR;
};
struct VS_PC_OUTPUT
{
	float4 p	: SV_POSITION;
	float4 c	: COLOR0;
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
};
// Vertex Shader
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	output.p = mul(float4(vIn.p, 1.0f), g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);

	//float3 vLight = normalize(float3(0.7f, 0.7f, 0.0f));
	float3 vLight = normalize(vDirectionLight);
	float fDot = dot(vIn.n, vLight);
	float4 vVertexColor;
	vVertexColor.r = fDot;
	vVertexColor.g = fDot;
	vVertexColor.b = fDot;
	vVertexColor.a = 1.0f;
	output.c = vVertexColor;

	//output.c = g_MeshColor;
	//output.c = vIn.c;
	output.n = vIn.n;
	output.t = vIn.t;
	return output;
}
VS_PC_OUTPUT VSLine(VS_PC_INPUT vIn)
{
	VS_PC_OUTPUT output = (VS_PC_OUTPUT)0;
	output.p = mul(float4(vIn.p, 1.0f), g_matWorld);
	output.p = mul(output.p, g_matView);
	output.p = mul(output.p, g_matProj);
	output.c = vIn.c;
	return output;
}
// Pixel Shader
float4 PS(VS_OUTPUT vIn) : SV_Target
{
	float4 vColor = g_txDiffuse.Sample(samLinear, vIn.t);
	//vColor.a = vIn.a;
	return vIn.c;
	return vColor;// *vIn.c;
	//return vIn.c * (1.0f - vColor.a) + vColor * vColor.a;
	//return vIn.c * (1.0f - vIn.c.a) + vColor * vIn.c.a;
	//return vIn.c * (vColor * vIn.c.a);
}
float4 PS_Diffuse(VS_OUTPUT vIn) : SV_Target
{
	float vColor = g_txDiffuse.Sample(samLinear, vIn.t);
	float4 vFinalColor = vColor * Diffuse(vIn.n) * vIn.c;
	vColor.a = 1.0f;
	return vFinalColor;
}
float4 Diffuse(float3 vNormal) : SV_Target
{
	float fIntensity = max(0, dot(vNormal, normalize(-vDirectionLight)));
	float4 Diffuse = vAmbientLight * vAmbientColor +
	(vDiffuseLight * vDiffuseColor * fIntensity);
	return Diffuse;
}
float4 PSColor(VS_OUTPUT vIn) : SV_Target
{
	return  vIn.c;
}
float4 PSLine(VS_PC_OUTPUT vIn) : SV_Target
{
	return  vIn.c;
}