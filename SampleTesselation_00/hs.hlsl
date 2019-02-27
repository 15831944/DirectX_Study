#define MAX_POINTS 3
cbuffer cb0
{
	matrix g_matWorld : packoffset(c0);
	matrix g_matView: packoffset(c4);
	matrix g_matProj: packoffset(c8);
	float4 g_MeshColor : packoffset(c12);
};
struct VS_OUTPUT
{
	float4 p  : SV_POSITION;
	float3 n  : NORMAL;
	float4 c  : COLOR0;
	float2 t  : TEXCOORD0;
};
struct HS_OUTPUT
{
	float3 p : POSITION;
	float3 n : NORMAL;
	float4 c : COLOR;
	float2 t : TEXCOORD;
};

[domain("tri")]
[partitioning("integer")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("PatchConstantFunction")]
[maxtessfactor(64.0f)]
HS_OUTPUT HS(InputPatch< VS_OUTPUT, MAX_POINTS> patch,
	uint pointId : SV_OutputControlPointID,
	uint patchId : SV_PrimitiveID)
{
	HS_OUTPUT output;
	output.p = patch[pointId].p;
	output.n = patch[pointId].n;
	output.c = patch[pointId].c;
	output.t = patch[pointId].t;
	return output;
}
void PatchConstantFunction()
{

}