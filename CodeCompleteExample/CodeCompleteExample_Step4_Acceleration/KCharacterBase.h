#pragma once

#include <Windows.h>
#include <string>

class KCharacterBase
{
public:
    virtual void        OnFrameMove( float fElapsedTime_ );
    virtual void        OnFrameRender( HDC hdc_, float fElaspedTime_ );
    void                SetCharacterName( const std::string& strName_ );
    const std::string&  GetCharacterName() const;
    DWORD               GetCharacterId() const { (*(DWORD*)this); }

private:
    std::string         m_strCharacterName;
};//class KCharacterBase