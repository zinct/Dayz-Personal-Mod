class ActionRepairCarEngineWithWrenchCB : ActionRepairCarEngineCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime(UATimeSpent.BASEBUILDING_REPAIR_MEDIUM);
	}
}

class ActionRepairCarEngineWithWrench: ActionRepairCarEngine
{
	void ActionRepairCarEngineWithWrench()
	{
		m_CallbackClass 	= ActionRepairCarEngineWithEpoxyCB;
		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONMOD_CRAFTING;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody 			= false;
		m_LockTargetOnUse	= false;
		m_Text 				= "#repair";
	}
	
	override void CreateConditionComponents()  
	{
		m_ConditionItem 	= new CCINonRuined();
		m_ConditionTarget 	= new CCTCursor(UAMaxDistances.REPAIR);
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
						if (zoneHP > GameConstants.STATE_PRISTINE && zoneHP < GameConstants.STATE_RUINED)
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
};
