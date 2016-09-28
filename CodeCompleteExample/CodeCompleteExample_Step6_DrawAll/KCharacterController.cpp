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
    //::ZeroMemory( &m_pos, sizeof( m_pos ) );
}//KCharacterController::Finalize()

/*virtual*/
void KCharacterController::OnFrameMove( float fElapsedTime_ )
{
    if( KCharacterPtr spCharacter = m_wpCharacter.lock() )
    {
        //m_pos = spCharacter->GetPos();
        //m_dwHp = spCharacter->GetHp();

        float fAccelerationFactor = fElapsedTime_ * 100.f;
        KVector acceleration = spCharacter->GetAcceleration();
        bool bDirModified = false;
        if( ::GetAsyncKeyState( VK_LEFT ) ) {
            acceleration = acceleration + KVector( -fAccelerationFactor, 0, 0 );
            bDirModified = true;
        }//if
        if( ::GetAsyncKeyState( VK_RIGHT ) ) {
            acceleration = acceleration + KVector( fAccelerationFactor, 0, 0 );
            bDirModified = true;
        }//if
        if( ::GetAsyncKeyState( VK_UP ) ) {
            acceleration = acceleration + KVector( 0, -fAccelerationFactor, 0 );
            bDirModified = true;
        }//if
        if( ::GetAsyncKeyState( VK_DOWN ) ) {
            acceleration = acceleration + KVector( 0, fAccelerationFactor, 0 );
            bDirModified = true;
        }//if

        if( bDirModified == true )
        {
            // set modified new dir.
            spCharacter->SetAcceleration( acceleration );
        } else {
            spCharacter->SetAcceleration( KVector(0,0,0) );
        }//if.. else..

    }//if
}//KCharacterController::OnFrameMove()

/*virtual*/
void KCharacterController::OnFrameRender( HDC hdc_, float fElaspedTime_ )
{
    if( KCharacterPtr spCharacter = m_wpCharacter.lock() )
    {
        //{{ step6: commented out
        //const int iWidth = 100;
        //const int iHeight = 100;
        //const int iLeft = m_pos.x - iWidth / 2;
        //const int iTop = m_pos.y - iHeight / 2;
        //const int iCenterX = iLeft + iWidth / 2;
        //const int iCenterY = iTop + iHeight / 2;

        //WCHAR wszText[1024] = L"";
        //wsprintf( wszText, L"HP : %i", m_dwHp );
        //const int iLen = wcslen( wszText );
        //::Ellipse( hdc_, iLeft, iTop, iLeft + iWidth, iTop + iHeight );
        //::TextOut( hdc_, iCenterX, iCenterY, wszText, iLen );
        //}} step6
    }//if
}//KCharacterController::OnFrameRender()
