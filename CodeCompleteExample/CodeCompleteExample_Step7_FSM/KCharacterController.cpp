#include "KCharacterController.h"
#include "KCharacterUtil.h"
//{{ step7
#include "KCharacterManager.h"
//}} step7

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

        //{{ step7
        extern KCharacterManager g_characterManager;
        const int numCharacter = g_characterManager.GetNumCharacter();

        for( int iCharacter0 = 0; iCharacter0 < numCharacter; ++iCharacter0 ) {
            KCharacterPtr spChar0 = g_characterManager.GetCharacter( iCharacter0 );
            spChar0->ResetCollisionTarget();
            for( int iCharacter1 = 0; iCharacter1 < numCharacter; ++iCharacter1 ) {
                KCharacterPtr spChar1 = g_characterManager.GetCharacter( iCharacter1 );

                if( spChar0 != spChar1 ) {
                    KVector v0 = spChar0->GetPos();
                    KVector v1 = spChar1->GetPos();
                    v0 = v0 - v1;
                    const float fDistance = v0.Length();
                    const float fCollDistance = spChar0->GetDiameter() / 2.f + spChar1->GetDiameter() / 2.f;
                    if( fDistance < fCollDistance ) {
                        spChar0->AddCollisionTarget( spChar1 );
                    }//if
                }//if
            }//for
        }//for
        //}} step7

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
