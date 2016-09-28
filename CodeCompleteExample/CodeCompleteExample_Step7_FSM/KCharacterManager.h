#pragma once

#include <vector>
#include "KCharacter.h"


class KCharacterManager
{
public:
    int                 CreateCharacter();
    bool                DestroyCharacter();
    void                Finalize();
    int                 GetNumCharacter() const;
    bool                FindCharacter( int& iOutCharIndex_, const std::string& strName_ );
    bool                IsValidCharacterIndex( int iIndex_ ) const;
    KCharacterPtr       GetCharacter( int iIndex_ );
    void                OnFrameMove( float fElapsedTime_ );
    void                OnFrameRender( HDC hdc_, float fElaspedTime_ );

private:
    std::vector<KCharacterPtr>
                        m_vecCharacters;
};//class KCharacterManager
