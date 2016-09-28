#include "KMainUi.h"

extern HWND             g_hwndMain;
extern RECT             g_clientRect;

KMainUi::KMainUi()
    : m_dwCharacterDataStamp( 0L )
{
}//KMainUi::KMainUi()

void KMainUi::SetCharacter( KCharacterWeakPtr spChar_ )
{
    m_wpCharacter = spChar_;
}//KMainUi::SetCharacter()

void KMainUi::Finalize() {
    m_wpCharacter.reset();
    m_dwCharacterDataStamp = 0L;
}//KMainUi::Finalize()

void KMainUi::OnFrameMove( float fElapsedTime_ )
{
    if( KCharacterPtr spCharacter = m_wpCharacter.lock() )
    {
        const DWORD dwCurStamp = spCharacter->GetCharacterDataStamp();
        if( dwCurStamp != m_dwCharacterDataStamp )
        {
            m_dwCharacterDataStamp = dwCurStamp;
            m_characterRenderData.m_dwHp = spCharacter->GetHp();
            InvalidateRect( g_hwndMain, NULL, TRUE );
        }//if
    }//if
}//KMainUi::OnFrameMove()

void KMainUi::OnFrameRender( HDC hdc_, float fElaspedTime_ )
{
    const int iWidth = 200;
    const int iHeight = 100;
    const int iLeft = g_clientRect.right - iWidth;
    const int iTop = 0;//g_clientRect.bottom - iHeight;
    ::Ellipse( hdc_, iLeft, iTop, iLeft + iWidth, iTop + iHeight );
    WCHAR wszText[1024] = L"";
    wsprintf( wszText, L"Hp : %i", m_characterRenderData.m_dwHp );
    const int iLen = wcslen( wszText );
    ::TextOut( hdc_, iLeft + iWidth / 2, iTop + iHeight / 2, wszText, iLen );
}//KMainUi::OnFrameRender()

bool KMainUi::WriteUiData( FILE* pFile_ )
{
    KCharacterPtr spCharacter = m_wpCharacter.lock();
    if( spCharacter == nullptr )
    {
        return false;
    }//if

    fwprintf( pFile_, L"Ui : Current Char = %s\r\n", spCharacter->GetCharacterName().c_str() );

    return true;
}//KMainUi::WriteUiData()
