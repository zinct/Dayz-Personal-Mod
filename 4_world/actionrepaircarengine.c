modded class ActionRepairCarEngine: ActionContinuousBase
{
	void ActionRepairCarEngine()
	{
		m_CallbackClass = ActionRepairTentPartCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		//m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_ASSEMBLE;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_CRAFTING;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = false;
		m_LockTargetOnUse = false;
		m_Text = "#repair";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
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
			targetObject.GetActionComponentNameList(target.GetComponentIndex(), selections, LOD.NAME_VIEW);

			foreach (string selection : selections)
			{
				//NOTE: relevant fire geometry and view geometry selection names MUST match in order to get a valid damage zone
				if (carEntity && DamageSystem.GetDamageZoneFromComponentName(carEntity, selection, damageZone))
				{
					if (damageZone == "Engine")
					{
						int zoneHP = car.GetHealthLevel(damageZone);
						if (zoneHP > GameConstants.STATE_WORN && zoneHP < GameConstants.STATE_RUINED)
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

		if (tgObject && damageZone != "")
		{
			CarScript car = CarScript.Cast(tgObject);
			if (car)
			{
				int newDmgLevel = Math.Clamp(car.GetHealthLevel(damageZone) - 1, GameConstants.STATE_PRISTINE, GameConstants.STATE_RUINED);
				float zoneMax = car.GetMaxHealth(damageZone, "");
				float randomValue = Math.RandomFloatInclusive(zoneMax * 0.05, zoneMax * 0.15);
				
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

					case GameConstants.STATE_PRISTINE:
						car.SetHealth(damageZone, "", (zoneMax * GameConstants.DAMAGE_WORN_VALUE) + randomValue);
						break;
					
					default:
						break;
				}

				MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, UADamageApplied.BUILD);

				if ( action_data.m_MainItem.HasQuantity() )
				{
					if ( action_data.m_MainItem.GetQuantity() > 1 )
					{
						int qnt = action_data.m_MainItem.GetQuantity();
						qnt -= action_data.m_MainItem.GetQuantityMax() * 0.25;
						action_data.m_MainItem.SetQuantity( qnt );
					}
					else
						action_data.m_MainItem.Delete();
				}
			}
		}
	}
};