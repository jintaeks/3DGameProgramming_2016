
#pragma once

#include "KCharacter.h"
#include <memory>

class KCharacterController;
typedef std::shared_ptr<KCharacterController>     KCharacterControllerPtr;

class KCharacterController
{
public:
                        KCharacterController()
                            : m_wpCharacter()
                            , m_dwHp( 0 )
                        {
                            ::ZeroMemory( &m_pos, sizeof( m_pos ) );
                        }//KCharacterController()
    void                SetCharacter( KCharacterWeakPtr spChar_ );
    KCharacterWeakPtr   GetCharacter() const;
    void                Finalize();
    virtual void        OnFrameMove( float fElapsedTime_ );
    virtual void        OnFrameRender( HDC hdc_, float fElaspedTime_ );

private:
    KCharacterWeakPtr   m_wpCharacter;
    KVector             m_pos;
    DWORD               m_dwHp;
};//class KCharacterController
