
#pragma once

#include "KCharacter.h"

namespace KCharacterUtil
{
    bool                WriteCharacterData( KCharacterPtr spChar_, FILE* pFile_ );
    //{{ step4
    KVector             UpdateVelocity( const KVector& v0, const KVector& a, float fTime );
    KVector             UpdatePosition( const KVector& s0, const KVector& v0, const KVector& a, float fTime );
    //}} step4
}//namespace KCharacterUtil
