class RepairCarPartRustedActionReciveData : ActionReciveData
{
	string m_DamageZoneRecived;
}

class RepairCarPartRustedActionData : ActionData
{
	string m_DamageZone;
}

class ActionRepairCarPartRustedCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		m_ActionData.m_ActionComponent = new CAContinuousTime( UATimeSpent.BASEBUILDING_REPAIR_SLOW );
	}
};

class ActionRepairCarPartRusted: ActionContinuousBase
{
	typename m_LastValidType;
	string m_CurrentDamageZone = "";
	int m_LastValidComponentIndex = -1;
	const float MAX_ACTION_DIST = 3;
	
	void ActionRepairCarPartRusted()
	{
		m_CallbackClass = ActionRepairTentPartCB;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_LOW;
		
		//m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_ASSEMBLE;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody = true;
		m_LockTargetOnUse = false;
		m_Text = "Repair Rust";
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINonRuined; //To change?
		m_ConditionTarget = new CCTCursor(UAMaxDistances.SMALL); //CCTNonRuined( UAMaxDistances.BASEBUILDING ); ??
	}
	
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		//Action not allowed if player has broken legs
		if (player.GetBrokenLegs() == eBrokenLegs.BROKEN_LEGS)
			return false;
		
		Object targetObject = target.GetObject();
		Object targetParent = target.GetParent();
		CarDoor carDoor = CarDoor.Cast( targetObject );
		//EntityAI carPartEntity = EntityAI.Cast( targetObject );
		
		if ( !carDoor || !player )
			return false;	

		if ( !carDoor.GetType().Contains("Rust") )
			return false;	
		
		if ( GetGame().IsMultiplayer() && GetGame().IsServer() )
			return true;
			
		if ( carDoor )
		{
			//Check if item is attached to car -> If so, block repair if door is closed
			if (targetParent != null)
			{
				InventoryLocation loc = new InventoryLocation();
				bool isPresent = carDoor.GetInventory().GetCurrentInventoryLocation( loc );
				
				if ( !isPresent || loc.GetSlot() == -1 )
					return false;
				
				string slotName = InventorySlots.GetSlotName( loc.GetSlot() );
				if ( slotName && CarScript.Cast( targetParent ).GetCarDoorsState( slotName ) != CarDoorState.DOORS_OPEN )
					return false;
			}
			
			//Check health level of door
			int zoneHP = carDoor.GetHealthLevel( "" );
			if ( zoneHP < GameConstants.STATE_RUINED )
				return true;
			
			return false;
		}
		
		return false;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		Object carPart = action_data.m_Target.GetObject();
		ItemBase usedItem = action_data.m_MainItem;
		string m_CarPart = carPart.GetType();
		string newCarPart = GetNewCarPart( m_CarPart );
		
		if (newCarPart != "")
		{
			ReplaceDoorLambda lambda = new ReplaceDoorLambda(carPart, newCarPart);
			MiscGameplayFunctions.TurnItemIntoItemEx(action_data.m_Player, lambda);

			if ( usedItem.HasQuantity() )
			{
				if ( usedItem.GetQuantity() > 0.51 )
				{
					int qnt = usedItem.GetQuantity();
					qnt -= usedItem.GetQuantityMax() * 0.5;
					usedItem.SetQuantity( qnt );
				}
				else
					usedItem.Delete();
			}
		}
	};
	
	string GetNewCarPart ( string m_CarPart )
	{
		//int lenght = m_CarPart.Length();
		//int end = lenght - 4;
		string newCarPart;// = m_CarPart.Substring( 0, end );

		switch (m_CarPart)
		{
			case "HatchbackDoors_Driver_GreenRust":
				newCarPart = "HatchbackDoors_Driver";
			break;

			case "HatchbackDoors_CoDriver_GreenRust":
				newCarPart = "HatchbackDoors_CoDriver";
			break;
			
			case "HatchbackHood_GreenRust":
				newCarPart = "HatchbackHood";
			break;

			case "HatchbackTrunk_GreenRust":
				newCarPart = "HatchbackTrunk";
			break;
				
			case "HatchbackDoors_Driver_BlueRust":
				newCarPart = "HatchbackDoors_Driver_Blue";
			break;

			case "HatchbackDoors_CoDriver_BlueRust":
				newCarPart = "HatchbackDoors_CoDriver_Blue";
			break;
			
			case "HatchbackHood_BlueRust":
				newCarPart = "HatchbackHood_Blue";
			break;

			case "HatchbackTrunk_BlueRust":
				newCarPart = "HatchbackTrunk_Blue";
			break;
				
			case "HatchbackDoors_Driver_WhiteRust":
				newCarPart = "HatchbackDoors_Driver_White";
			break;

			case "HatchbackDoors_CoDriver_WhiteRust":
				newCarPart = "HatchbackDoors_CoDriver_White";
			break;
			
			case "HatchbackHood_WhiteRust":
				newCarPart = "HatchbackHood_White";
			break;

			case "HatchbackTrunk_WhiteRust":
				newCarPart = "HatchbackTrunk_White";
			break;

			case "CivSedanDoors_Driver_WhiteRust":
				newCarPart = "CivSedanDoors_Driver";
			break;

			case "CivSedanDoors_CoDriver_WhiteRust":
				newCarPart = "CivSedanDoors_CoDriver";
			break;

			case "CivSedanDoors_BackLeft_WhiteRust":
				newCarPart = "CivSedanDoors_BackLeft";
			break;

			case "CivSedanDoors_BackRight_WhiteRust":
				newCarPart = "CivSedanDoors_BackRight";
			break;

			case "CivSedanHood_WhiteRust":
				newCarPart = "CivSedanHood";
			break;

			case "CivSedanTrunk_WhiteRust":
				newCarPart = "CivSedanTrunk";				
			break;

			case "CivSedanDoors_Driver_WineRust":
				newCarPart = "CivSedanDoors_Driver_Wine";
			break;

			case "CivSedanDoors_CoDriver_WineRust":
				newCarPart = "CivSedanDoors_CoDriver_Wine";
			break;

			case "CivSedanDoors_BackLeft_WineRust":
				newCarPart = "CivSedanDoors_BackLeft_Wine";
			break;

			case "CivSedanDoors_BackRight_WineRust":
				newCarPart = "CivSedanDoors_BackRight_Wine";
			break;

			case "CivSedanHood_WineRust":
				newCarPart = "CivSedanHood_Wine";
			break;

			case "CivSedanTrunk_WineRust":
				newCarPart = "CivSedanTrunk_Wine";				
			break;

			case "CivSedanDoors_Driver_BlackRust":
				newCarPart = "CivSedanDoors_Driver_Black";
			break;

			case "CivSedanDoors_CoDriver_BlackRust":
				newCarPart = "CivSedanDoors_CoDriver_Black";
			break;

			case "CivSedanDoors_BackLeft_BlackRust":
				newCarPart = "CivSedanDoors_BackLeft_Black";
			break;

			case "CivSedanDoors_BackRight_BlackRust":
				newCarPart = "CivSedanDoors_BackRight_Black";
			break;

			case "CivSedanHood_BlackRust":
				newCarPart = "CivSedanHood_Black";
			break;

			case "CivSedanTrunk_BlackRust":
				newCarPart = "CivSedanTrunk_Black";				
			break;

			case "Hatchback_02_Door_1_1_RedRust":
				newCarPart = "Hatchback_02_Door_1_1";
			break;

			case "Hatchback_02_Door_2_1_RedRust":
				newCarPart = "Hatchback_02_Door_2_1";
			break;

			case "Hatchback_02_Door_1_2_RedRust":
				newCarPart = "Hatchback_02_Door_1_2";
			break;

			case "Hatchback_02_Door_2_2_RedRust":
				newCarPart = "Hatchback_02_Door_2_2";
			break;

			case "Hatchback_02_Hood_RedRust":
				newCarPart = "Hatchback_02_Hood";
			break;

			case "Hatchback_02_Trunk_RedRust":
				newCarPart = "Hatchback_02_Trunk";				
			break;

			case "Hatchback_02_Door_1_1_BlackRust":
				newCarPart = "Hatchback_02_Door_1_1_Black";
			break;

			case "Hatchback_02_Door_2_1_BlackRust":
				newCarPart = "Hatchback_02_Door_2_1_Black";
			break;

			case "Hatchback_02_Door_1_2_BlackRust":
				newCarPart = "Hatchback_02_Door_1_2_Black";
			break;

			case "Hatchback_02_Door_2_2_BlackRust":
				newCarPart = "Hatchback_02_Door_2_2_Black";
			break;

			case "Hatchback_02_Hood_BlackRust":
				newCarPart = "Hatchback_02_Hood_Black";
			break;

			case "Hatchback_02_Trunk_BlackRust":
				newCarPart = "Hatchback_02_Trunk_Black";				
			break;

			case "Hatchback_02_Door_1_1_BlueRust":
				newCarPart = "Hatchback_02_Door_1_1_Blue";
			break;

			case "Hatchback_02_Door_2_1_BlueRust":
				newCarPart = "Hatchback_02_Door_2_1_Blue";
			break;

			case "Hatchback_02_Door_1_2_BlueRust":
				newCarPart = "Hatchback_02_Door_1_2_Blue";
			break;

			case "Hatchback_02_Door_2_2_BlueRust":
				newCarPart = "Hatchback_02_Door_2_2_Blue";
			break;

			case "Hatchback_02_Hood_BlueRust":
				newCarPart = "Hatchback_02_Hood_Blue";
			break;

			case "Hatchback_02_Trunk_BlueRust":
				newCarPart = "Hatchback_02_Trunk_Blue";				
			break;

			case "Sedan_02_Door_1_1_YellowRust":
				newCarPart = "Sedan_02_Door_1_1";
			break;

			case "Sedan_02_Door_2_1_YellowRust":
				newCarPart = "Sedan_02_Door_2_1";
			break;

			case "Sedan_02_Door_1_2_YellowRust":
				newCarPart = "Sedan_02_Door_1_2";
			break;

			case "Sedan_02_Door_2_2_YellowRust":
				newCarPart = "Sedan_02_Door_2_2";
			break;

			case "Sedan_02_Hood_YellowRust":
				newCarPart = "Sedan_02_Hood";
			break;

			case "Sedan_02_Trunk_YellowRust":
				newCarPart = "Sedan_02_Trunk";			
			break;

			case "Sedan_02_Door_1_1_RedRust":
				newCarPart = "Sedan_02_Door_1_1_Red";
			break;
			
			case "Sedan_02_Door_2_1_RedRust":
				newCarPart = "Sedan_02_Door_2_1_Red";
			break;

			case "Sedan_02_Door_1_2_RedRust":
				newCarPart = "Sedan_02_Door_1_2_Red";
			break;

			case "Sedan_02_Door_2_2_RedRust":
				newCarPart = "Sedan_02_Door_2_2_Red";
			break;

			case "Sedan_02_Hood_RedRust":
				newCarPart = "Sedan_02_Hood_Red";
			break;
			
			case "Sedan_02_Trunk_RedRust":
				newCarPart = "Sedan_02_Trunk_Red";
			break;

			case "Sedan_02_Door_1_1_GreyRust":
				newCarPart = "Sedan_02_Door_1_1_Grey";
			break;
			
			case "Sedan_02_Door_2_1_GreyRust":
				newCarPart = "Sedan_02_Door_2_1_Grey";
			break;

			case "Sedan_02_Door_1_2_GreyRust":
				newCarPart = "Sedan_02_Door_1_2_Grey";
			break;

			case "Sedan_02_Door_2_2_GreyRust":
				newCarPart = "Sedan_02_Door_2_2_Grey";
			break;

			case "Sedan_02_Hood_GreyRust":
				newCarPart = "Sedan_02_Hood_Grey";
			break;
			
			case "Sedan_02_Trunk_GreyRust":
				newCarPart = "Sedan_02_Trunk_Grey";
			break;

			case "Truck_01_Door_1_1_GreenRust":
				newCarPart = "Truck_01_Door_1_1";
			break;

			case "Truck_01_Door_2_1_GreenRust":
				newCarPart = "Truck_01_Door_2_1";
			break;

			case "Truck_01_Hood_GreenRust":
				newCarPart = "Truck_01_Hood";
			break;

			case "Truck_01_Door_1_1_BlueRust":
				newCarPart = "Truck_01_Door_1_1_Blue";
			break;

			case "Truck_01_Door_2_1_BlueRust":
				newCarPart = "Truck_01_Door_2_1_Blue";
			break;

			case "Truck_01_Hood_BlueRust":
				newCarPart = "Truck_01_Hood_Blue";
			break;

			case "Truck_01_Door_1_1_OrangeRust":
				newCarPart = "Truck_01_Door_1_1_Orange";
			break;

			case "Truck_01_Door_2_1_OrangeRust":
				newCarPart = "Truck_01_Door_2_1_Orange";
			break;

			case "Truck_01_Hood_OrangeRust":
				newCarPart = "Truck_01_Hood_Orange";
			break;

			case "Offroad_02_Door_1_1_Rust":
				newCarPart = "Offroad_02_Door_1_1";
			break;

			case "Offroad_02_Door_1_2_Rust":
				newCarPart = "Offroad_02_Door_1_2";
			break;

			case "Offroad_02_Door_2_1_Rust":
				newCarPart = "Offroad_02_Door_2_1";
			break;

			case "Offroad_02_Door_2_2_Rust":
				newCarPart = "Offroad_02_Door_2_2";
			break;
			
			case "Offroad_02_Trunk_Rust":
				newCarPart = "Offroad_02_Trunk";
			break;
		}

		return newCarPart;
	};

	override ActionData CreateActionData()
	{
		RepairCarPartRustedActionData action_data = new RepairCarPartRustedActionData;
		return action_data;
	}
	
	override void WriteToContext(ParamsWriteContext ctx, ActionData action_data)
	{
		super.WriteToContext( ctx, action_data );
		RepairCarPartRustedActionData repair_action_data;

		if( HasTarget() && Class.CastTo( repair_action_data,action_data ) )
		{
			repair_action_data.m_DamageZone = m_CurrentDamageZone;
			ctx.Write(repair_action_data.m_DamageZone);
		}
	}
	
	override bool ReadFromContext(ParamsReadContext ctx, out ActionReciveData action_recive_data )
	{
		if( !action_recive_data )
			action_recive_data = new RepairCarPartRustedActionReciveData;

		super.ReadFromContext( ctx, action_recive_data );
		RepairCarPartRustedActionReciveData recive_data_repair = RepairCarPartRustedActionReciveData.Cast( action_recive_data );

		if( HasTarget() )
		{
			string zone;
			if ( !ctx.Read( zone ) )
				return false;

			recive_data_repair.m_DamageZoneRecived = zone;
		}

		return true;
	}
	
	override void HandleReciveData( ActionReciveData action_recive_data, ActionData action_data )
	{
		super.HandleReciveData( action_recive_data, action_data );

		RepairCarPartRustedActionReciveData recive_data_repair = RepairCarPartRustedActionReciveData.Cast( action_recive_data );
		RepairCarPartRustedActionData.Cast( action_data ).m_DamageZone = recive_data_repair.m_DamageZoneRecived;
	}
};

class ReplaceDoorLambda : ReplaceItemWithNewLambdaBase
{
	override void CopyOldPropertiesToNew(notnull EntityAI old_item, EntityAI new_item)
	{
		super.CopyOldPropertiesToNew(old_item, new_item);

		MiscGameplayFunctions.TransferItemProperties(old_item, new_item);		
	}
}