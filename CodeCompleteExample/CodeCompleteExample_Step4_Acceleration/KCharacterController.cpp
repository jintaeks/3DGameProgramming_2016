#include "KCharacterController.h"
#include "KCharacterUtil.h"

extern RECT                 g_clientRect;

void KCharacterController::SetCharacter( KCharacterWeakPtr spChar_ )
{
    m_wpCharacter = spChar_;
}//KCharacterController::SetCharacter()

KCharacterWeakPtr KCharacterController::GetCharacter() const
{
    return m_wpCharacter;
}//KCharacterController::GetCharacter()

void KCharacterController::Finalize() {
    m_wpCharacter.reset();
    ::ZeroMemory( &m_pos, sizeof( m_pos ) );
}//KCharacterController::Finalize()

/*virtual*/
void KCharacterController::OnFrameMove( float fElapsedTime_ )
{
    if( KCharacterPtr spCharacter = m_wpCharacter.lock() )
    {
        m_pos = spCharacter->GetPos();
        m_dwHp = spCharacter->GetHp();

        KVector velocity = spCharacter->GetVelocity();
        //{{ step4
        KVector acceleration = spCharacter->GetAcceleration();
        velocity = KCharacterUtil::UpdateVelocity( velocity, acceleration, fElapsedTime_ );
        //}} step4

        const int cdwWidth = g_clientRect.right - g_clientRect.left + 1;
        const int cdwHeight = g_clientRect.bottom - g_clientRect.top + 1;
        bool bDirModified = false;
        if( m_pos.x < 0 || m_pos.x > cdwWidth )
        {
            velocity.x = -velocity.x; // toggle x-dir
            bDirModified = true;
        }//if
        if( m_pos.y < 0 || m_pos.y > cdwHeight )
        {
            velocity.y = -velocity.y; // toggle y-dir
            bDirModified = true;
        }//if

        if( bDirModified == true )
        {
            // set modified new dir.
            spCharacter->SetVelocity( velocity );
        }//if

        // update character position.
        //{{ step4
        //m_pos = m_pos + velocity;
        m_pos = KCharacterUtil::UpdatePosition( m_pos, velocity, acceleration, fElapsedTime_ );
        //}} step4
        spCharacter->SetPos( m_pos );
    }//if
}//KCharacterController::OnFrameMove()

/*virtual*/
void KCharacterController::OnFrameRender( HDC hdc_, float fElaspedTime_ )
{
    if( KCharacterPtr spCharacter = m_wpCharacter.lock() )
    {
        const int iWidth = 100;
        const int iHeight = 100;
        const int iLeft = m_pos.x - iWidth / 2;
        const int iTop = m_pos.y - iHeight / 2;
        const int iCenterX = iLeft + iWidth / 2;
        const int iCenterY = iTop + iHeight / 2;

        WCHAR wszText[1024] = L"";
        wsprintf( wszText, L"HP : %i", m_dwHp );
        const int iLen = wcslen( wszText );
        ::Ellipse( hdc_, iLeft, iTop, iLeft + iWidth, iTop + iHeight );
        ::TextOut( hdc_, iCenterX, iCenterY, wszText, iLen );
    }//if
}//KCharacterController::OnFrameRender()
