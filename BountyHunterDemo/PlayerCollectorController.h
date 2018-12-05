///-------------------------------------------------------------------------------------------------
/// File:	PlayerCollectorController.h.
///
/// Summary:	Declares the player collector controller class.
///-------------------------------------------------------------------------------------------------

#ifndef __PLAYER_COLLECTOR_CONTROLLER_H__
#define __PLAYER_COLLECTOR_CONTROLLER_H__

#include "PlayerController.h"
#include "Collector.h"

class PlayerCollectorController : public PlayerController<Collector>
{
public:

	PlayerCollectorController(const GameObjectId collectorId, const PlayerId playerId);
	virtual ~PlayerCollectorController();

	// Inherited via PlayerController
	virtual void Update(const PlayerAction* action) override;

}; // class PlayerCollectorController

#endif // __PLAYER_COLLECTOR_CONTROLLER_H__
