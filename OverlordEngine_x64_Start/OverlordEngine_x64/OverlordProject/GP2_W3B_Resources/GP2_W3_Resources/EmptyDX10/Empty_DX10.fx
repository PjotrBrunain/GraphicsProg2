//DX10 - FLAT SHADER
//Digital Arts & Entertainment


//GLOBAL VARIABLES
//****************
float4x4 gMatrixWorldViewProj : WORLDVIEWPROJECTION;
float4 gColorDiffuse : COLOR = float4(1.0, 1.0, 1.0, 1.0);


//STATES
//******
RasterizerState gRS_NoCulling { CullMode = NONE; };


//MAIN VERTEX SHADER
//******************
float4 MainVS(float3 pos : POSITION) : POSITION{
	return mul(float4(pos.xyz, 1.0), gMatrixWorldViewProj);
}


//MAIN PIXEL SHADER
//*****************
float4 MainPS() : COLOR {
	return gColorDiffuse;
}


//TECHNIQUES
//**********
technique10 DefaultTechnique {
	pass p0 {
		SetRasterizerState(gRS_NoCulling);	
		SetVertexShader(CompileShader(vs_4_0, MainVS()));
		SetPixelShader(CompileShader(ps_4_0, MainPS()));
	}
}