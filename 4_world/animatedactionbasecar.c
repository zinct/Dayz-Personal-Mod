modded class AnimatedActionBase : ActionBase
{	
	protected int	m_CommandUIDVehicle;	//tells which command should be used for callback

	override int GetActionCommand( PlayerBase player )
	{
		if ( player.IsInVehicle() || player.GetCommand_Vehicle() )
		{
			if ( HasAltVehicleAnm() )
				return m_CommandUIDVehicle;
			else if ( m_CommandUID == DayZPlayerConstants.CMD_ACTIONFB_CRAFTING )
				return DayZPlayerConstants.CMD_ACTIONMOD_CRAFTING;
			else
				return m_CommandUID;
		}  //amn work in vehicle: CMD_ACTIONMOD_ITEM_TUNE, CMD_ACTIONMOD_SHAVE, CMD_ACTIONMOD_CRAFTING, CMD_ACTIONMOD_RESTRAINEDSTRUGGLE
		else if ( HasProneException() )
		{
			if ( player.IsPlayerInStance(DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT))
				return m_CommandUID;
			else
				return m_CommandUIDProne;
		}
		return m_CommandUID;
	}

	// if it is set to true if action have special alternate animation for in vehicle
	bool HasAltVehicleAnm()
	{
		return false;
	}
};

modded class ActionWorldCraft: ActionContinuousBase
{
	void ActionWorldCraft()
	{
		m_CallbackClass = ActionWorldCraftCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_CRAFTING;
		m_CommandUIDVehicle = DayZPlayerConstants.CMD_ACTIONMOD_CRAFTING;
		m_FullBody = false;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}
	
	override bool CanBeUsedInVehicle()
	{
		return true;
	}

	override bool HasAltVehicleAnm()
	{
		return true;
	}
	
	override void Start( ActionData action_data ) //Setup on start of action
	{
		super.Start(action_data);
		if ( action_data.m_Player ) action_data.m_Player.TryHideItemInHands(false);
	}
};