#include "KCharacterUtil.h"

bool KCharacterUtil::WriteCharacterData( KCharacterPtr spChar_, FILE* pFile_ )
{
    if( spChar_ == nullptr )
    {
        return false;
    }//if

    if( pFile_ == nullptr )
    {
        return false;
    }//if

    fwprintf( pFile_, L"Name = %s\r\n", spChar_->GetCharacterName().c_str() );
    fwprintf( pFile_, L"Hp = %i\r\n", spChar_->GetHp() );

    return true;
}//KCharacterUtil::WriteCharacterData()

KVector KCharacterUtil::UpdateVelocity( const KVector& v0, const KVector& a, float fTime )
{
    KVector v = v0 + a * fTime;
    return v;
}//KCharacterUtil::UpdateVelocity()

KVector KCharacterUtil::UpdatePosition( const KVector& s0, const KVector& v0, const KVector& a, float fTime )
{
    KVector s = s0 + v0 * fTime + a * fTime * fTime * 0.5f;
    return s;
}//KCharacterUtil::UpdatePosition()
