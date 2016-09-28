#include "KCharacterManager.h"

int KCharacterManager::CreateCharacter()
{
    KCharacterPtr spCharacter;
    spCharacter.reset( new KCharacter() );
    m_vecCharacters.push_back( spCharacter );

    const int iCharIndex = m_vecCharacters.size() - 1;
    spCharacter->SetCharacterManagerIndex( iCharIndex );
    return iCharIndex;
}//KCharacterManager::CreateCharacter()

bool KCharacterManager::DestroyCharacter()
{
    if( m_vecCharacters.empty() == true )
    {
        return false;
    }//if

    m_vecCharacters.pop_back();
    return true;
}//KCharacterManager::DestroyCharacter()

void KCharacterManager::Finalize() {
    std::vector<KCharacterPtr> vecEmptyCharacters;
    m_vecCharacters.swap( vecEmptyCharacters );
}//KCharacterManager::Finalize()

int KCharacterManager::GetNumCharacter() const
{
    const int iNumCharacter = static_cast<int>( m_vecCharacters.size() );
    return iNumCharacter;
}//KCharacterManager::GetNumCharacter()

bool KCharacterManager::FindCharacter( int& iOutCharIndex_, const std::string& strName_ )
{
    const int iNumCharacter = static_cast<int>( m_vecCharacters.size() );
    for( int iCharIndex = 0; iCharIndex < iNumCharacter; ++iCharIndex )
    {
        KCharacterPtr& spChar = m_vecCharacters[ iCharIndex ];
        if( _stricmp( strName_.c_str(), spChar->GetCharacterName().c_str() ) == 0 )
        {
            iOutCharIndex_ = iCharIndex;
            return true;
        }//if
    }//for

    iOutCharIndex_ = -1;
    return false;
}//KCharacterManager::FindCharacter()

bool KCharacterManager::IsValidCharacterIndex( int iIndex_ ) const
{
    const int iNumCharacter = static_cast<int>( m_vecCharacters.size() );
    return iIndex_ >= 0 && iIndex_ < iNumCharacter;
}//KCharacterManager::IsValidCharacterIndex()

KCharacterPtr KCharacterManager::GetCharacter( int iIndex_ )
{
    if( IsValidCharacterIndex( iIndex_ ) == false )
    {
        return KCharacterPtr();
    }//if

    return m_vecCharacters[ iIndex_ ];
}//KCharacterManager::GetCharacter()

void KCharacterManager::OnFrameMove( float fElapsedTime_ )
{
    const int iNumCharacter = static_cast<int>( m_vecCharacters.size() );
    for( int iCharIndex = 0; iCharIndex < iNumCharacter; ++iCharIndex )
    {
        KCharacterPtr& spChar = m_vecCharacters[ iCharIndex ];
        spChar->OnFrameMove( fElapsedTime_ );
    }//for
}//KCharacterManager::OnFrameMove()

void KCharacterManager::OnFrameRender( HDC hdc_, float fElapsedTime_ )
{
    const int iNumCharacter = static_cast<int>( m_vecCharacters.size() );
    for( int iCharIndex = 0; iCharIndex < iNumCharacter; ++iCharIndex )
    {
        KCharacterPtr& spChar = m_vecCharacters[ iCharIndex ];
        spChar->OnFrameRender( hdc_, fElapsedTime_ );
    }//for
}//KCharacterManager::OnFrameRender()
