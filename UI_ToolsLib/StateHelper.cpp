#include "JState.h"
void JState::SetRSState(ID3D11DeviceContext* pContext, ID3D11RasterizerState* pState)
{
	pContext->RSSetState(pState);
}
void JState::SetDSState(ID3D11DeviceContext* pContext, ID3D11DepthStencilState* pState)
{
	pContext->OMSetDepthStencilState(pState, 0x00);
}
void JState::SetSamplerState(ID3D11DeviceContext* pContext, ID3D11SamplerState* pState)
{
	pContext->PSSetSamplers(0, 1, &pState);
}
void JState::SetAlphaBlendState(ID3D11DeviceContext* pContext, ID3D11BlendState* pState)
{
	pContext->OMSetBlendState(pState, 0, -1);
}
