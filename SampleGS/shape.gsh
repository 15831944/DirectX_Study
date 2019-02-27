struct G_OUT
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
[maxvertexcount(4)]
void GS(in point V_OUT vIn[1], inout TriangleStream<G_OUT> vOut)
{
	// Strip���� �����Ѵ�.
	const float3 g_positions[4] =
	{
		float3(-1.0,  1.0, 0.0),
		float3(1.0,  1.0, 0.0),
		float3(-1.0, -1.0, 0.0),
		float3(1.0, -1.0, 0.0),
	};
	float4 g_color[4] =
	{
		float4(1.0f, 0.0f, 0.2f, 1.0f),
		float4(0.0f,1.0f, 0.0f, 1.0f),
		float4(0.0f, 0.0f, 1.0f,1.0f),
		float4(1.0f, 1.0f,1.0f,  1.0f),
	};
	const float2 g_texcoords[4] =
	{
		float2(0.0, 0.0),
		float2(1.0, 0.0),
		float2(0.0, 1.0),
		float2(1.0, 1.0),
	};

	G_OUT vVertex;
	for (int i = 0; i < 4; i++)
	{
		vVertex.p = float4(vIn[0].p.xyz + g_positions[i].xyz * time, 1.0f);
		vVertex.c = g_color[i];
		vVertex.t = g_texcoords[i];
		vOut.Append(vVertex);
	}
	vOut.RestartStrip();
}