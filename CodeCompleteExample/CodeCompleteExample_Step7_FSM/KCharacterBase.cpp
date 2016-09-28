#include "KCharacterBase.h"

/*virtual*/ void KCharacterBase::OnFrameMove( float fElapsedTime_ )
{
}//KCharacterBase::OnFrameMove()

/*virtual*/ void KCharacterBase::OnFrameRender( HDC hdc_, float fElaspedTime_ )
{
}//KCharacterBase::OnFrameRender()

void KCharacterBase::SetCharacterName( const std::string& strName_ )
{
    m_strCharacterName = strName_;
}//KCharacterBase::SetCharacterName()

const std::string& KCharacterBase::GetCharacterName() const
{
    return m_strCharacterName;
}//KCharacterBase::GetCharacterName()
