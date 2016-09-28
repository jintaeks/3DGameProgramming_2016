#include "KCharacter.h"

void KCharacter::SetCharacterManagerIndex( int iIndex_ )
{
    m_iCharacterManagerIndex = iIndex_;
}//KCharacter::SetCharacterManagerIndex()

int KCharacter::GetCharacterManagerIndex() const
{
    return m_iCharacterManagerIndex;
}//KCharacter::GetCharacterManagerIndex()

/*virtual*/
void KCharacter::OnFrameMove( float fElapsedTime_ )
{
    if( rand() % 100 == 0 )
    {
		const DWORD dwHp = GetHp();
		SetHp( dwHp + 1 );
    }//if
}//KCharacter::OnFrameMove()

/*virtual*/
void KCharacter::OnFrameRender( HDC hdc_, float fElaspedTime_ )
{
    WCHAR wszText[] = L"KCharacter::OnFrameRender";
    const int iManager = GetCharacterManagerIndex();
    ::TextOut( hdc_, 1, 1 + iManager * 16, wszText, _countof( wszText ) - 1 );
}//KCharacter::OnFrameRender()
