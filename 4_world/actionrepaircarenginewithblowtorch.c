modded class ActionRepairCarEngineWithBlowtorch: ActionRepairCarEngine
{
	void ActionRepairCarEngineWithBlowtorch()
	{
		m_CallbackClass 	= ActionRepairCarEngineWithBlowtorchCB;
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
					if (damageZone == "BackWood" || damageZone == "BackTarp")
						return false;

					if (damageZone == "Engine" || damageZone == "Front" || damageZone == "Roof" || damageZone == "Back" || damageZone == "Doors" || damageZone == "Fender_1_1" || damageZone == "Fender_1_2" || damageZone == "Fender_2_1" || damageZone == "Fender_2_2" || damageZone == "FuelTank" || damageZone == "Reflector_1_1" || damageZone == "Reflector_1_2" || damageZone == "Reflector_2_1" || damageZone == "Reflector_2_2")
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

	override void OnStartAnimationLoopServer(ActionData action_data)
	{
		super.OnStartAnimationLoopServer(action_data);

		action_data.m_MainItem.GetCompEM().SwitchOn();
	}
	
	override void OnFinishProgressServer(ActionData action_data)
	{
		super.OnFinishProgressServer(action_data);
		
		action_data.m_MainItem.GetCompEM().SwitchOff();
	}
	
	override void OnEndServer(ActionData action_data)
	{
		super.OnEndServer(action_data);
		
		action_data.m_MainItem.GetCompEM().SwitchOff();
	}
};

class CCTCursorBT : CCTBase
{
	protected float m_MaximalActionDistanceSq;
	
	//approximate head heights
	const float HEIGHT_ERECT = 1.6;
	const float HEIGHT_CROUCH = 1.05;
	const float HEIGHT_PRONE = 0.66;
	
	void CCTCursorBT( float maximal_target_distance = UAMaxDistances.DEFAULT )
	{
		m_MaximalActionDistanceSq = maximal_target_distance * maximal_target_distance;
	}
	
	override bool Can( PlayerBase player, ActionTarget target )
	{
		if( !target )
			return false;
		
		Object targetObject = target.GetObject();
		if ( !targetObject )
			targetObject = target.GetParent();
		
		if ( !player || !targetObject ) //|| targetObject.IsDamageDestroyed() )
			return false;

		vector playerHeadPos;
		MiscGameplayFunctions.GetHeadBonePos(player, playerHeadPos);
		
		float distanceRoot = vector.DistanceSq(target.GetCursorHitPos(), player.GetPosition());
		float distanceHead = vector.DistanceSq(target.GetCursorHitPos(), playerHeadPos);
		
		return ( distanceRoot <= m_MaximalActionDistanceSq || distanceHead <= m_MaximalActionDistanceSq );
	}
};