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
