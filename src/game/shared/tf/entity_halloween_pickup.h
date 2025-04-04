//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: CTF Halloween Pickup.
//
//=============================================================================//
#ifndef ENTITY_HALLOWEEN_PICKUP_H
#define ENTITY_HALLOWEEN_PICKUP_H

#ifdef _WIN32
#pragma once
#endif

#ifdef GAME_DLL
#include "tf_powerup.h"
#include "tf_gamerules.h"
#include "tf_player.h"
#endif

#include "ehandle.h"

#define TF_HALLOWEEN_PICKUP_MODEL	"models/items/target_duck.mdl"
#define TF_DUCK_PICKUP_MODEL	"models/workshop/player/items/pyro/eotl_ducky/eotl_bonus_duck.mdl"
#define TF_GIFT_MODEL			"models/props_halloween/gargoyle_ghost.mdl"; //"models/props_halloween/halloween_gift.mdl";
#define TF_HALLOWEEN_PICKUP_DEFAULT_SOUND	"AmmoPack.Touch"
							 
#define BONUS_DUCK_GLOW "superrare_beams1"
#define BONUS_DUCK_TRAIL_RED "duck_collect_trail_red"
#define BONUS_DUCK_TRAIL_BLUE "duck_collect_trail_blue"
#define BONUS_DUCK_TRAIL_SPECIAL_RED "duck_collect_trail_special_red"
#define BONUS_DUCK_TRAIL_SPECIAL_BLUE "duck_collect_trail_special_blue"
#define BONUS_DUCK_CREATED_SOUND "Duck.Quack"
											  
#ifdef CLIENT_DLL
#define CBonusDuckPickup C_BonusDuckPickup
#define CHalloweenPickup C_HalloweenPickup
#define CHalloweenGiftPickup C_HalloweenGiftPickup

#include "c_tf_player.h"
#endif

//=============================================================================
//
// CTF Halloween Pickup class.
//

class CHalloweenPickup
#ifdef GAME_DLL
	: public CTFPowerup
#else
	: public C_BaseAnimating
#endif
{
public:
#ifdef GAME_DLL
	DECLARE_CLASS( CHalloweenPickup, CTFPowerup );
#else
	DECLARE_CLASS( CHalloweenPickup, C_BaseAnimating );
#endif

	DECLARE_NETWORKCLASS();

	CHalloweenPickup();
	~CHalloweenPickup();

	virtual void	Precache( void ) OVERRIDE;

#ifdef GAME_DLL
	virtual int		UpdateTransmitState() OVERRIDE;
	virtual int		ShouldTransmit( const CCheckTransmitInfo *pInfo ) OVERRIDE;
	virtual bool	ValidTouch( CBasePlayer *pPlayer ) OVERRIDE;
	virtual bool	MyTouch( CBasePlayer *pPlayer ) OVERRIDE;
	virtual CBaseEntity* Respawn( void );

	virtual const char *GetDefaultPowerupModel( void ) OVERRIDE
	{ 
		return TF_HALLOWEEN_PICKUP_MODEL;
	}

	virtual float	GetRespawnDelay( void ) OVERRIDE;

	virtual bool	ItemCanBeTouchedByPlayer( CBasePlayer *pPlayer );
#endif // GAME_DLL

private:
	string_t		m_iszSound;
	string_t		m_iszParticle;

#ifdef GAME_DLL
	COutputEvent	m_OnRedPickup;
	COutputEvent	m_OnBluePickup;
#endif

	DECLARE_DATADESC();
};

class CBonusDuckPickup : public CHalloweenPickup
{
public:
	DECLARE_CLASS( CBonusDuckPickup, CHalloweenPickup );

	DECLARE_NETWORKCLASS();

	CBonusDuckPickup();
	~CBonusDuckPickup();

	virtual void	Precache( void ) OVERRIDE;
#ifdef GAME_DLL
	virtual const char *GetDefaultPowerupModel( void ) OVERRIDE
	{
		return TF_DUCK_PICKUP_MODEL;
	}

	virtual float	GetLifeTime() { if ( m_flLifeTime == 0) { m_flLifeTime = RandomFloat( 17.0f, 20.0f ); } return m_flLifeTime; }

	virtual bool	ValidTouch( CBasePlayer *pPlayer ) OVERRIDE;
	void			Spawn( void );
	virtual bool	MyTouch( CBasePlayer *pPlayer ) OVERRIDE;

	void			DropSingleInstance( Vector &vecLaunchVel, CBaseCombatCharacter *pThrower, float flThrowerTouchDelay, float flResetTime = 0.1f );
	void			NotifyFadeOut( void );

	void			UpdateCollisionBounds();

	// Make this a base class in powerup
	void	BlinkThink();

	void	SetCreatorId( int value ) { m_iCreatorId = value; }
	int		GetCreatorId( void ) { return m_iCreatorId; }

	void	SetAssisterId( int value ) { m_iAssisterId = value; }
	int		GetAssisterId( void ) { return m_iAssisterId; }

	void	SetVictimId( int value ) { m_iVictimId = value; }
	int		GetVictimId( void ) { return m_iVictimId; }

	void	SetSpecial( void ){ m_bSpecial = true; }
	void	SetDuckFlag( int iFlag ) { m_iFlags |= iFlag; }
#else
	virtual void	OnDataChanged( DataUpdateType_t updateType ) OVERRIDE;
#endif // GAME_DLL

private:
	string_t		m_iszSound;
	string_t		m_iszParticle;

#ifdef GAME_DLL
	float m_flLifeTime;
	float m_flKillTime;
	int m_nBlinkCount;
	int m_iCreatorId;
	int m_iAssisterId;
	int m_iVictimId;
	int m_iFlags;
#else	
	CNewParticleEffect	*pGlowEffect;
#endif

	CNetworkVar( bool, m_bSpecial );

	DECLARE_DATADESC();
};



//*************************************************************************************************


#endif // ENTITY_HALLOWEEN_PICKUP_H


