#include "KCharacter.h"
#include "KCharacterUtil.h"

//{{ step6
extern RECT                 g_clientRect;
//}} step6

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

    //{{ step6
    KVector velocity = GetVelocity();
    KVector acceleration = GetAcceleration();
    velocity = KCharacterUtil::UpdateVelocity( velocity, acceleration, fElapsedTime_ );

    bool bDirModified = false;
    const int cdwWidth = g_clientRect.right - g_clientRect.left + 1;
    const int cdwHeight = g_clientRect.bottom - g_clientRect.top + 1;

    if( m_pos.x < 0 || m_pos.x > cdwWidth ) {
        velocity.x = -velocity.x; // toggle x-dir
        bDirModified = true;
    }//if
    if( m_pos.y < 0 || m_pos.y > cdwHeight ) {
        velocity.y = -velocity.y; // toggle y-dir
        bDirModified = true;
    }//if

    if( bDirModified == true ) {
        // set modified new dir.
    }//if

    SetVelocity( velocity );

    // update character position.
    m_pos = KCharacterUtil::UpdatePosition( m_pos, velocity, acceleration, fElapsedTime_ );
    SetPos( m_pos );
    //}} step6
}//KCharacter::OnFrameMove()

/*virtual*/
void KCharacter::OnFrameRender( HDC hdc_, float fElaspedTime_ )
{
    WCHAR wszText[] = L"KCharacter::OnFrameRender";
    const int iManager = GetCharacterManagerIndex();
    ::TextOut( hdc_, 1, 1 + iManager * 16, wszText, _countof( wszText ) - 1 );

    //{{ step6
    const int iWidth = 100;
    const int iHeight = 100;
    const int iLeft = m_pos.x - iWidth / 2;
    const int iTop = m_pos.y - iHeight / 2;
    const int iCenterX = iLeft + iWidth / 2;
    const int iCenterY = iTop + iHeight / 2;

    //WCHAR wszText[ 1024 ] = L"";
    wsprintf( wszText, L"HP : %i", m_dwHp );
    const int iLen = wcslen( wszText );
    ::Ellipse( hdc_, iLeft, iTop, iLeft + iWidth, iTop + iHeight );
    ::TextOut( hdc_, iCenterX, iCenterY, wszText, iLen );
    //}} step6
}//KCharacter::OnFrameRender()
