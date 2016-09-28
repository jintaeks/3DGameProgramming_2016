
#pragma once

#include "KCharacterBase.h"
#include <memory>
#include "KVector.h"

class KCharacter;
typedef std::shared_ptr<KCharacter>     KCharacterPtr;
typedef std::weak_ptr<KCharacter>       KCharacterWeakPtr;

class KCharacter : public KCharacterBase
{
public:
    //{{ step7
    enum ECharacterState {
        ESTATE_IDLE,
        ESTATE_WATCH,
        ESTATE_COLLISION,
    };//enum ECharacterState
    //}} step7
                        KCharacter()
                            : m_dwHp( 0 )
                            , m_dwCharacterDataStamp( 0 )
                            , m_eCharacterState( ESTATE_IDLE )
                            , m_fDiameter( 100.f )
                        {
                            m_pos = KVector( 0, 0, 0 );
                            m_velocity = KVector( 100, 100, 0 );
                        }
    void                SetCharacterManagerIndex( int iIndex_ );
    int                 GetCharacterManagerIndex() const;
    virtual void        OnFrameMove( float fElapsedTime_ ) override;
    virtual void        OnFrameRender( HDC hdc_, float fElaspedTime_ ) override;

    DWORD               GetHp() const { return m_dwHp; }
    void                SetHp( DWORD dwNewHp_ )
                        {
                            m_dwHp = dwNewHp_;
                            m_dwCharacterDataStamp += 1;
                        }//SetHp()
    DWORD               GetCharacterDataStamp() const { return m_dwCharacterDataStamp; }

    KVector             GetPos() const { return m_pos; }
    void                SetPos( const KVector& pnt_ ) { m_pos = pnt_; }
    KVector             GetVelocity() const { return m_velocity; }
    void                SetVelocity( const KVector& dir_ ) { m_velocity = dir_; }

    //{{ step4
    KVector             GetAcceleration() const { return m_acceleration; }
    void                SetAcceleration( const KVector& accel ) { m_acceleration = accel; }
    //}} step4
    //{{ step7
    float               GetDiameter() const { return m_fDiameter; }
    void                ResetCollisionTarget();
    void                AddCollisionTarget( KCharacterWeakPtr spTarget_ );
    //}} step7
    //{{ step7
private:
    void                _OnFrameMove_ESTATE_IDLE( float fElapsedTime_ );
    void                _OnFrameMove_ESTATE_WATCH( float fElapsedTime_ );
    void                _OnFrameMove_ESTATE_COLLISION( float fElapsedTime_ );
    //}} step7

private:
    int                 m_iCharacterManagerIndex;
    DWORD               m_dwHp;
    DWORD               m_dwCharacterDataStamp;

    KVector             m_pos;
    KVector             m_velocity;
    //{{ step4
    KVector             m_acceleration;
    //}} step4
    //{{ step7
    float               m_fDiameter;
    ECharacterState     m_eCharacterState;
    int                 m_iCollCounter;
    //}} step7
};//class KCharacter : public KCharacterBase
