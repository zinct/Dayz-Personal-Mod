modded class ActionRepairCarChassisWithBlowtorch : ActionRepairCarChassis
{
	void ActionRepairCarChassisWithBlowtorch()
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
		m_ConditionItem		= new CCINone();
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
		CarScript car 		= CarScript.Cast(targetObject);
		EntityAI carEntity 	= EntityAI.Cast(targetObject);
		
		if (!car || !player)
			return false;
		
		if (car.EngineIsOn())
			return false;

		if (GetGame().IsMultiplayer() && GetGame().IsServer())
			return true;
			

		if (m_LastValidType != target.Type() || m_LastValidComponentIndex != target.GetComponentIndex() || m_CurrentDamageZone == "")
		{
			string damageZone = "";
			array<string> selections = new array<string>();
			targetObject.GetActionComponentNameList(target.GetComponentIndex(), selections, LOD.NAME_FIRE);

			foreach (string selection : selections)
			{
				//NOTE: relevant fire geometry and view geometry selection names MUST match in order to get a valid damage zone
				if (carEntity && !DamageSystem.GetDamageZoneFromComponentName(carEntity, selection, damageZone))
				{
					if (damageZone == "BackWood" || damageZone == "BackTarp" || damageZone == "Engine" || damageZone == "Front" || damageZone == "Roof" || damageZone == "Back" || damageZone == "Doors" || damageZone == "Fender_1_1" || damageZone == "Fender_1_2" || damageZone == "Fender_2_1" || damageZone == "Fender_2_2" || damageZone == "FuelTank" || damageZone == "Reflector_1_1" || damageZone == "Reflector_1_2" || damageZone == "Reflector_2_1" || damageZone == "Reflector_2_2")
						return false;

					if (damageZone == "Chassis" || damageZone == "")
					{
						int zoneHP = car.GetHealthLevel(damageZone);
						if (zoneHP > GameConstants.STATE_WORN /*&& zoneHP < GameConstants.STATE_RUINED*/)
						{
							m_CurrentDamageZone = damageZone;
							m_LastValidComponentIndex = target.GetComponentIndex();
						
							return true;
						}
					}
				}
			}
		}
		
		return false;
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		Object tgObject = action_data.m_Target.GetObject();
		
		string damageZone = RepairCarPartActionData.Cast(action_data).m_DamageZone;
		if (!GetGame().IsMultiplayer())
			damageZone = m_CurrentDamageZone;

		if (tgObject /*&& damageZone != ""*/)
		{
			CarScript car = CarScript.Cast(tgObject);
			if (car)
			{
				int newDmgLevel = Math.Clamp(car.GetHealthLevel(damageZone) - 1, GameConstants.STATE_WORN, GameConstants.STATE_RUINED);
				float zoneMax 		= car.GetMaxHealth(damageZone, "");
				float randomValue 	= Math.RandomFloatInclusive(zoneMax * 0.05, zoneMax * 0.15);
				
				switch (newDmgLevel)
				{
					case GameConstants.STATE_BADLY_DAMAGED:
						car.SetHealth(damageZone, "", (zoneMax * GameConstants.DAMAGE_RUINED_VALUE) + randomValue);
					break;
					case GameConstants.STATE_DAMAGED:
						car.SetHealth(damageZone, "", (zoneMax * GameConstants.DAMAGE_BADLY_DAMAGED_VALUE) + randomValue);
					break;
					case GameConstants.STATE_WORN:
						car.SetHealth(damageZone, "", (zoneMax * GameConstants.DAMAGE_DAMAGED_VALUE) + randomValue);
					break;
				}

				if (action_data.m_MainItem.HasQuantity())
				{
					if (action_data.m_MainItem.GetQuantity() > 1)
					{
						int qnt = action_data.m_MainItem.GetQuantity();
						Fabric usedTarp = Fabric.Cast(action_data.m_MainItem);
						WoodenPlank usedPlank = WoodenPlank.Cast(action_data.m_MainItem);
						if (usedTarp || usedPlank)
						{
							qnt -= 1;
						}
						else
						{
							qnt -= action_data.m_MainItem.GetQuantityMax() * 0.25;
						}

						action_data.m_MainItem.SetQuantity(qnt);
					}
					else
					{
						action_data.m_MainItem.Delete();
					}
				}
			}
		}
	}
};
