Texture2D				g_txDiffuse: register (t0);
Texture2D				g_txBlendA	: register(t1);
Texture2D				g_txBlendB	: register(t2);
SamplerState			g_samLinear: register (s0);
cbuffer cb0
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView: packoffset(c4);
	matrix g_matProj: packoffset(c8);
	float4 g_MeshColor : packoffset(c12);
};
struct VS_PC_OUTPUT
{
	float4 p	: SV_POSITION;
	float4 c	: COLOR0;
};
struct VS_OUTPUT
{
	float4 p  : SV_POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR0;
	float2 t  : TEXCOORD0;
};

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 txColor0 = g_txDiffuse.Sample(g_samLinear, input.t);
	float4 txColor1 = g_txBlendA.Sample(g_samLinear, input.t);
	float4 txColor2 = g_txBlendB.Sample(g_samLinear, input.t);
	//return vIn.c * (1.0f - vIn.c.a) + txColor0 * vIn.c.a;

	float4 AnimColor = lerp(txColor1, txColor2, g_MeshColor.a);
	float4 FinalColor = (input.c*AnimColor.a + AnimColor * (1.0f - AnimColor.a));// * input.c;	
	FinalColor = (txColor0*(1.0f - FinalColor.a) + FinalColor * AnimColor.a);// * input.c;	
	return FinalColor;
}
float4 PSColor(VS_OUTPUT vIn) : SV_Target
{
	return  vIn.c;
}
float4 PSLine(VS_PC_OUTPUT vIn) : SV_Target
{
	return  vIn.c;
}