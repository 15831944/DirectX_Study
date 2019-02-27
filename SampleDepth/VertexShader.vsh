struct VS_INPUT
{
	float3 p : POSITION;
	float2 t : TEXCOORD;
	float4 c : COLOR;
};
struct VS_OUTPUT
{
	float4 p : SV_POSITION;			
	float2 t : TEXCOORD0;		
	float4 c : COLOR0;		 
};
VS_OUTPUT VS(VS_INPUT vIn)
{
	VS_OUTPUT vOut = (VS_OUTPUT)0;
	vOut.p.x = vIn.p.x;
	vOut.p.y = vIn.p.y;
	vOut.p.z = vIn.p.z;
	vOut.p.w = 1.0f;
	vOut.t = vIn.t;
	vOut.c = vIn.c;

	return vOut;
}