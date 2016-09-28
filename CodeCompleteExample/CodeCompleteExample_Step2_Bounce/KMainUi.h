#ifndef _KMAIN_UI_H
#define _KMAIN_UI_H

#include <Windows.h>
#include "KCharacter.h"

class KMainUi
{
    struct KCharacterRenderData
    {
        DWORD           m_dwHp;
    };//struct KCharacterRenderData

public:
                        KMainUi();
    void                SetCharacter( KCharacterWeakPtr spChar_ );
    void                Finalize();
    void                OnFrameMove( float fElapsedTime_ );
    void                OnFrameRender( HDC hdc_, float fElaspedTime_ );

    bool                WriteUiData( FILE* pFile_ );

private:
    KCharacterWeakPtr   m_wpCharacter;
    KCharacterRenderData
                        m_characterRenderData;
};//class KMainUi
#endif // _KMAIN_UI_H
