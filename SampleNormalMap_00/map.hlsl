//--------------------------------------------------------------------------------------
// Constant Buffer Variables
//--------------------------------------------------------------------------------------
Texture2D	g_txDiffuse : register (t0);
Texture2D	g_txNormalMap	: register (t1);
SamplerState g_samLinear: register (s0);

cbuffer cb0 : register(b0)
{
	matrix	g_matWorld		: packoffset(c0);
	matrix	g_matView		: packoffset(c4);
	matrix	g_matProj		: packoffset(c8);
	float4  g_MeshColor     : packoffset(c12);
};

//-----------------------------------------------------------------------------
//��� ����
//-----------------------------------------------------------------------------
cbuffer cbObjectChangesEveryFrame: register(b1)
{
	// Global
	matrix				g_matNormal;
	float3				cb_vLightVector;
	float3				cb_vEyePos;
	float3				cb_vEyeDir;
};

cbuffer cbObjectNeverChanges: register(b2)
{
	// Global
	float4				cb_AmbientLightColor: packoffset(c0);
	float4				cb_DiffuseLightColor: packoffset(c1);
	float3				cb_SpecularLightColor: packoffset(c2);
	float				cb_SpecularPower : packoffset(c2.w);
};

struct PNCT2_VS_INPUT
{
	float4 p		: POSITION;
	float3 n		: NORMAL;
	float4 c		: COLOR0;
	float2 t		: TEXCOORD0;
	//float3 Tan		: TANGENT;
};

struct PCT4_PS_INPUT
{
	float4 p			: SV_POSITION;
	float4 c			: COLOR0;
	float3 n : NORMAL;
	float2 t			: TEXCOORD0;
	float3 vEye			: TEXCOORD1;
	float3 vHalf		: TEXCOORD2;
	float3 vLightDir	: TEXCOORD3;
};


//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
PCT4_PS_INPUT VS(PNCT2_VS_INPUT input)
{
	PCT4_PS_INPUT output = (PCT4_PS_INPUT)0;
	float4 vWorldPos = mul(input.p, g_matWorld);
	float4 vViewPos = mul(vWorldPos, g_matView);
	output.p = mul(vViewPos, g_matProj);

	output.t = input.t*50.0f;

	output.c = input.c;
	output.n = input.n;
	//float3 vNormal = normalize(mul(input.n, (float3x3)g_matNormal));
	//output.vEye = normalize(cb_vEyeDir);
	//output.c = saturate(dot(input.n, -cb_vLightVector));

	//float3 T = normalize(mul(input.Tan, (float3x3)g_matNormal));
	//float3 B = normalize(cross(vNormal, T));

	//float3x3 tanMat = { T.x, B.x, vNormal.x,
	//	T.y, B.y, vNormal.y,
	//	T.z, B.z, vNormal.z };
	//float3 vLightDir = cb_vLightVector.xyz;// normalize(cb_vLightVector.xyz - vWorldPos);
	//output.vHalf = normalize(mul(normalize(vLightDir + output.vEye), tanMat));
	//output.vLightDir = normalize(mul(-vLightDir, tanMat));
	//output.vEye = normalize(mul(output.vEye, tanMat));
	return output;
}

//f2fConnector distanceFragment(v2fConnector v2f,
//	uniform sampler2D colorTex,
//	uniform sampler2D normalTex,
//	uniform sampler3D distanceTex,
//	uniform float3 normalizationFactor)
//{
//
//	f2fConnector f2f;
//	// Normalize the offset vector in texture space.
//	// The normalization factor ensures we are normalized with respect
//	// to a distance which is defined in terms of pixels.
//	float3 offset = normalize(v2f.tanEyeVec);
//	offset *= normalizationFactor;
//	float3 texCoord = v2f.texCoord;
//	// March a ray
//	for (int i = 0; i < NUM_ITERATIONS; i++) 
//	{
//		float distance = f1tex3D(distanceTex, texCoord);
//		texCoord += distance * offset;
//	}
//	// Compute derivatives of unperturbed texcoords.
//	// This is because the offset texcoords will have discontinuities
//	// which lead to incorrect filtering.
//	float2 dx = ddx(v2f.texCoord.xy);
//	float2 dy = ddy(v2f.texCoord.xy);
//	// Do bump-mapped lighting in tangent space.
//	// 'normalTex' stores tangent-space normals remapped
//	// into the range [0, 1].
//	float3 tanNormal = 2 * f3tex2D(normalTex, texCoord.xy, dx, dy) - 1;
//	float3 tanLightVec = normalize(v2f.tanLightVec);
//	float diffuse = dot(tanNormal, tanLightVec);
//	// Multiply diffuse lighting by texture color
//	f2f.COL.rgb = diffuse * f3tex2D(colorTex, texCoord.xy, dx, dy);
//	f2f.COL.a = 1;
//	return f2f;
//}
//--------------------------------------------------------------------------------------
// Pixel Shader
//--------------------------------------------------------------------------------------
float4 PS(PCT4_PS_INPUT input) : SV_Target
{
	// �⺻ �ؽ��� �÷� 
	/*	float4 normal		=	g_txNormalMap.Sample( g_samLinear, input.t );
	float1 x			=	input.t.x+normal.x*0.1f*cb_vLightVector.z;
	float1 y			=	input.t.y+normal.y*0.1f*cb_vLightVector.x;
	float2 uv			=	float2(input.t.y, y);
	*/
	float4 DiffuseColor = g_txDiffuse.Sample(g_samLinear, input.t);

	// ��ǻ�� ���� 
	float4 normal = g_txNormalMap.Sample(g_samLinear, input.t);
	normal = normalize((normal - 0.5f) * 2.0f);
	float  fDot = saturate(dot(normal.xyz, input.vLightDir));
	float3 LightColor = cb_DiffuseLightColor.rgb * fDot;

	// ����ŧ�� ���� 		
	float3 R = reflect(-input.vLightDir, normal.xyz);
	float3 SpecColor = cb_SpecularLightColor.rgb * pow(saturate(dot(R, input.vEye)), cb_SpecularPower);
	//float3 SpecColor	=	cb_SpecularLightColor.rgb * pow( saturate(dot( input.vHalf, normal.xyz )), cb_SpecularPower );

	// ��ü �÷� ����  	
	float4 vFinalColor = DiffuseColor * float4(LightColor + SpecColor + cb_AmbientLightColor, 1.0f);
	//float4 vFinalColor = DiffuseColor;
	return normal;// *input.c;
}
float4 DEFAULT_PS(PCT4_PS_INPUT input) : SV_Target
{
	return g_txDiffuse.Sample(g_samLinear, input.t);
}