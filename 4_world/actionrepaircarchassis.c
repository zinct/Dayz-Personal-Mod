modded class ActionRepairCarChassis: ActionContinuousBase
{
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;
		
		CarScript car = CarScript.Cast(target.GetObject());
		if (!car || !player)
		{
			return false;
		}
		
		if (GetGame().IsMultiplayer() && GetGame().IsServer())
		{
			return true;
		}
		
		if (m_LastValidType != target.Type() || m_LastValidComponentIndex != target.GetComponentIndex() || m_CurrentDamageZone == "")
		{
			string damageZone = "";
			array<string> selections = new array<string>();
			car.GetActionComponentNameList(target.GetComponentIndex(), selections);
			
			foreach (string selection : selections)
			{
				//NOTE: relevant fire geometry and view geometry selection names MUST match in order to get a valid damage zone
				if (car && DamageSystem.GetDamageZoneFromComponentName(car, selection, damageZone))
				{
					if (damageZone == "Engine")
						return false;

					int zoneHP = car.GetHealthLevel(damageZone);
					if (zoneHP > GameConstants.STATE_WORN && zoneHP < GameConstants.STATE_RUINED)
					{
						m_CurrentDamageZone = damageZone;
						m_LastValidComponentIndex = target.GetComponentIndex();
					
						//Determine if using a "Special" item for repairing
						WoodenPlank plank = WoodenPlank.Cast(item);
						Fabric tarp = Fabric.Cast(item);
						
						//Prevent planks and tarp from repairing non related areas
						if ((tarp || plank) && (damageZone != "BackWood" && damageZone != "BackTarp"))
							return false;

						return true;
					}
				}
			}
		}
		
		return false;
	}
};