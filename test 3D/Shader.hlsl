// setShaderResourceView~ 할때 첫번째 인자가 레지스터의 슬롯이고,
// 변수명으로 그 슬롯에 해당하는 텍스쳐 픽셀 값을 받아와 조합해 사용할 수 있다.(Max 8, 샘플러도 마찬가지)

Texture2D g_txDiffuse :  register (t0);
//Texture2D g_txDiffuse2 :  register (t1);
SamplerState samLinear : register (s0);

// 상수 버퍼 : 버퍼 0번
cbuffer cbMatrix: register(b0)
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};


struct VS_INPUT
{
	float3 p : POSITION;
	float4 c : COLOR0;				// 0번 레지스터로 출력
	float2 t : TEXCOORD0;
};

struct VS_INPUT_PNCT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

struct VS_OUTPUT_PCT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};


VS_OUTPUT VS_PNCT(VS_INPUT_PNCT input)
{
	VS_OUTPUT_PCT output = (VS_OUTPUT_PCT)0;
	output.p = mul(float4(input.p, 1.0f), g_matWorld);
	//output.p = mul(output.p, g_matView);
	//output.p = mul(output.p, g_matProj);
	output.c = input.c;
	output.t = input.t;
	return output;
}

// 하위호환용
VS_OUTPUT VShader(VS_INPUT input)
{
	VS_OUTPUT_PCT output = (VS_OUTPUT_PCT)0;
	output.p = mul(float4(input.p, 1.0f), g_matWorld);
	//output.p = mul(output.p, g_matView);
	//output.p = mul(output.p, g_matProj);
	output.c = input.c;
	output.t = input.t;
	return output;
}

float4 PShader(VS_OUTPUT_PCT input) : SV_TARGET
{
	return g_txDiffuse.Sample(samLinear, input.t) * input.c;
}




float4 PPureColor(VS_OUTPUT_PCT input) : SV_TARGET
{
	return input.c;
}

float4 PButtonOver(VS_OUTPUT_PCT input) : SV_TARGET
{
	return g_txDiffuse.Sample(samLinear, input.t) * (input.c * 1.25f);
}

float4 PButtonClick(VS_OUTPUT_PCT input) : SV_TARGET
{
	return g_txDiffuse.Sample(samLinear, input.t) * (input.c * 0.75f);
}

float4 PHalfAlpha(VS_OUTPUT_PCT input) : SV_TARGET
{
	return g_txDiffuse.Sample(samLinear, input.t) * input.c * 0.55;
}

float4 PRedColor(VS_OUTPUT_PCT input) : SV_TARGET
{
	return g_txDiffuse.Sample(samLinear, input.t) + float4(1.0f, -0.6f, -0.6f, 0.0f);
}