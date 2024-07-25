modded class ActionRepairCarPartWithBlowtorch : ActionRepairCarPart 
{
	void ActionRepairCarPartWithBlowtorch()
	{
		m_CallbackClass 	= ActionRepairCarChassisWithBlowtorchCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_FLAME_REPAIR;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody 			= true;
		m_LockTargetOnUse	= false;
		m_Text 				= "#repair";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem 	= new CCINone();
		m_ConditionTarget 	= new CCTCursorBT(UAMaxDistances.REPAIR);
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		Blowtorch bt = Blowtorch.Cast(item);
		if (!bt.HasEnoughEnergyForRepair(UATimeSpent.BASEBUILDING_REPAIR_MEDIUM))
			return false;

		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;
		
		Object targetObject = target.GetObject();
		Object targetParent = target.GetParent();
		CarDoor carDoor = CarDoor.Cast(targetObject);
		
		if (!carDoor || !player)
			return false;	
		
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
			return true;
			
		if (carDoor)
		{
			//Check if item is attached to car -> If so, block repair if door is closed
			if (targetParent != null)
			{
				InventoryLocation loc = new InventoryLocation();
				bool isPresent = carDoor.GetInventory().GetCurrentInventoryLocation(loc);
				
				if (!isPresent || loc.GetSlot() == -1)
					return false;
				
				string slotName = InventorySlots.GetSlotName(loc.GetSlot());
				if (slotName && CarScript.Cast(targetParent).GetCarDoorsState(slotName) != CarDoorState.DOORS_OPEN)
					return false;
			}
			
			//Check health level of door
			int zoneHP = carDoor.GetHealthLevel("");
			return zoneHP > GameConstants.STATE_WORN /*&& zoneHP < GameConstants.STATE_RUINED*/);
		}
		
		return false;
	}
}
