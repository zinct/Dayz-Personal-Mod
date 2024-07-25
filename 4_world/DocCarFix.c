modded class PlayerBase extends ManBase
{
	bool CanBeRestrained()
	{
		if (/*IsInVehicle() ||*/ IsRaised() || IsSwimming() || IsClimbing() || IsClimbingLadder() || IsRestrained() || !GetWeaponManager() || GetWeaponManager().IsRunning() || !GetActionManager() || GetActionManager().GetRunningAction() != null || IsMapOpen())
		{
			return false;
		}
		if (GetThrowing() && GetThrowing().IsThrowingModeEnabled())
		{
			return false;
		}
		return true;
	}

	override bool CanReceiveItemIntoHands(EntityAI item_to_hands)
	{
		if (IsInVehicle() && !CarDoor.Cast(item_to_hands))
			return true;
		
		if (!CanPickupHeavyItem(item_to_hands))
			return false;
		
		return super.CanReceiveItemIntoHands(item_to_hands);
	}

	override bool CanReleaseCargo (EntityAI cargo)
	{
		if ( IsInVehicle() )
		{
			return true;
		}
		return super.CanReleaseCargo(cargo);
	}

	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if ( IsInVehicle() )
		{
			EntityAI root = item.GetHierarchyRoot();
			if ( !root.IsTransport() && !root.IsPlayer() )
				return false;
		}
		
		return super.CanReceiveItemIntoCargo(item);
	}

	override bool CanSwapItemInCargo (EntityAI child_entity, EntityAI new_entity)
	{
		if ( IsInVehicle() )
		{
			return true;
		}
		return super.CanSwapItemInCargo(child_entity, new_entity);
	}

	override bool CanDropEntity (notnull EntityAI item)
	{
		if (IsInVehicle())
		{
			return true;
		}
		
		if (GetInventory().HasInventoryReservation(item, null))
		{
			return false;
		}
		
		if (IsRestrained())
		{
			if (GetHumanInventory().GetEntityInHands() == item)
				return false;
		}
		
		return true; 
	}
	
	override bool CanBeTargetedByAI(EntityAI ai)
	{
		#ifdef DIAG_DEVELOPER
		if (!m_CanBeTargetedDebug)
		{
			return false;
		}
		#endif
		
		return super.CanBeTargetedByAI(ai) && !IsUnconscious() /*&& !IsInVehicle()*/;
	}

	void TryHideItemInHands(bool hide, bool force = false)
	{
		if (!hide && ((!IsSwimming() && !IsClimbingLadder() /*&& !IsInVehicle()*/ && !AnimCommandCheck(HumanMoveCommandID.CommandSwim | HumanMoveCommandID.CommandLadder /*| HumanMoveCommandID.CommandVehicle*/)) || force))
		{
			GetItemAccessor().HideItemInHands(false);
		}
		else
		{
			GetItemAccessor().HideItemInHands(true);
		}
	}
	
	override void OnCommandVehicleStart()
	{
		m_AnimCommandStarting = HumanMoveCommandID.CommandVehicle;
		
		if ( GetInventory() )
			GetInventory().LockInventory(LOCK_FROM_SCRIPT);
		
		CloseInventoryMenu();
		
		ItemBase itemInHand = GetItemInHands();
		EntityAI itemOnHead = FindAttachmentBySlotName("Headgear");

		if (itemInHand && itemInHand.GetCompEM())
			itemInHand.GetCompEM().SwitchOff();

		TryHideItemInHands(false, true);//true);

		if (itemOnHead && itemOnHead.GetCompEM())
			itemOnHead.GetCompEM().SwitchOff();
		
		HumanCommandVehicle hcv = GetCommand_Vehicle();
		if (hcv && hcv.GetVehicleSeat() == DayZPlayerConstants.VEHICLESEAT_DRIVER)
			OnVehicleSeatDriverEnter();
		
		//GetGame().GetMission().AddActiveInputExcludes({"vehicledriving"});
		if ( GetInventory().IsInventoryLocked() )
			GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
	}
	
	override void OnCommandVehicleFinish()
	{
		//if ( GetInventory().IsInventoryLocked() )
		//	GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
		
		TryHideItemInHands(false, true);
		
		if (m_IsVehicleSeatDriver)
			OnVehicleSeatDriverLeft();
		
		//GetGame().GetMission().RemoveActiveInputExcludes({"vehicledriving"});
	}	

	override bool IsPlayerInStance(int pStanceMask)		// STANCEMASK_ERECT | STANCEMASK_CROUCH 
	{
		if ( IsInVehicle() || GetCommand_Vehicle() )
			return true;

		return super.IsPlayerInStance(pStanceMask);
	}

	override EntityAI SpawnEntityOnGroundOnCursorDir(string object_name, float distance)
	{
		vector position = GetPosition() + (GetDirection() * distance);
		HumanCommandVehicle hcv = GetCommand_Vehicle();
		if (hcv)
		{
			vector ori = GetOrientation() + Vector(90,0,0);
			if (hcv.GetVehicleSeat() == DayZPlayerConstants.VEHICLESEAT_DRIVER || hcv.GetVehicleSeat() == DayZPlayerConstants.VEHICLESEAT_PASSENGER_L)
			{
				ori = GetOrientation() - Vector(90,0,0);
			}

			position = GetWorldPosition() + (ori.AnglesToVector() * 1.2);
		}

		return SpawnEntityOnGroundPos(object_name, position);
	}
/*
	override bool PhysicalPredictiveDropItem(EntityAI entity, bool heavy_item_only = true)
	{
		vector dir;
		ItemBase item = ItemBase.Cast(entity);
		
		HumanCommandVehicle hcv = GetCommand_Vehicle();
		Transport trans = hcv.GetTransport();
		if (IsInVehicle())
		{
			dir = trans.GetOrientation() + Vector(90,0,0);
			if (hcv.GetVehicleSeat() == DayZPlayerConstants.VEHICLESEAT_DRIVER || hcv.GetVehicleSeat() == DayZPlayerConstants.VEHICLESEAT_PASSENGER_L)
			{
				dir = trans.GetOrientation() - Vector(90,0,0);
			}

			//if (GetHierarchyRootPlayer());
			//	return GetHumanInventory().ThrowEntity(item,dir,80);

			//return GetInventory().DropEntity(InventoryMode.SERVER, trans, item);
			//return DropItem(item); //PredictiveDropEntity(item);

			vector pos = GetWorldPosition() + (dir.AnglesToVector() * 2.0);

			vector impulse = 5 * dir;

			vector dropExtents = "0.5 0.0 0.5";

			item.GetInventory().DropEntityInBounds(InventoryMode.SERVER, item.GetHierarchyParent(), item, dropExtents, 0, 0, 0);

	
			//MiscGameplayFunctions.ThrowEntityFromInventory(entity, pos, direction, impulse, ThrowEntityFlags.NONE);
			//DropItem(item);
			//ThrowItem(item);
			//dBodyApplyImpulse(item, impulse);
			return true;
		}
		else if (GetItemInHands() == item) //from hands
		{
			//HOTFIX
			return PredictiveDropEntity(item);

			if (entity.ConfigGetString("physLayer") != "item_large" && heavy_item_only)
			{
				return PredictiveDropEntity(item);
			}
			else
			{
				dir = GetOrientation();
				//item.m_ItemBeingDropped = true;
				return GetHumanInventory().ThrowEntity(item,dir,0);
			}
		}
		else //from anywhere else
		{
			ActionManagerClient mngr_client;
			if (CastTo(mngr_client,m_ActionManager))
			{
				ActionTarget atrg = new ActionTarget(null, null, -1, vector.Zero, -1);
				if (mngr_client.GetAction(ActionDropItemSimple).Can(this,atrg,item))
				{
					//Param1<bool> p1 = new Param1<bool>(false);
					//p1.param1 = heavy_item_only;
//					mngr_client.PerformActionStart(mngr_client.GetAction(ActionDropItemSimple),atrg,item/*,p1  //);
					return true;
				}
				return false;
			}
			else
				return true;
		}
	}
*/
	override bool PredictiveDropEntity (notnull EntityAI item)
	{
		bool can_detach;
		HumanCommandVehicle hcv = GetCommand_Vehicle();
		if (CanRedirectToWeaponManager(item,can_detach))
		{
			if (can_detach)
			{
				vector m4[4];
				Math3D.MatrixIdentity4(m4);
				
				//! We don't care if a valid transform couldn't be found, we just want to preferably use it instead of placing on the player
				GameInventory.PrepareDropEntityPos(this, item, m4, false, GameConstants.INVENTORY_ENTITY_DROP_OVERLAP_DEPTH);
				InventoryLocation il = new InventoryLocation;
				il.SetGround(item, m4);
				return GetWeaponManager().DetachMagazine(il);
			}
			return false;
		}
/*		else if (hcv)
		{
			vector pos = GetPosition();
			//vector ori = GetOrientation();
			//vector rotation_matrix[3];
			//float direction[4];

			vector ori = GetOrientation() + Vector(90,0,0);
			if (hcv.GetVehicleSeat() == DayZPlayerConstants.VEHICLESEAT_DRIVER || hcv.GetVehicleSeat() == DayZPlayerConstants.VEHICLESEAT_PASSENGER_L)
			{
				ori = GetOrientation() - Vector(90,0,0);
			}

			vector dir = ori.AnglesToVector();
			pos = GetWorldPosition() + (ori.AnglesToVector() );//* 0.1);
			
			//Math3D.YawPitchRollMatrix( ori, rotation_matrix );
			//Math3D.MatrixToQuat( rotation_matrix, direction );

			ThrowEntityFromVehicle(item, pos, ori);
			GetGame().ClearJunctureEx(this, item);
			return true;
		}*/
		return super.PredictiveDropEntity(item);		
	}

	void ThrowEntityFromVehicle(notnull EntityAI entity, vector pos, vector ori)
	{	
		EntityAI entity_for_placing = entity;
		vector rotation_matrix[3];
		float dir[4];
		InventoryLocation src = new InventoryLocation;
		InventoryLocation dst = new InventoryLocation;
		
		Math3D.YawPitchRollMatrix(ori, rotation_matrix);
		Math3D.MatrixToQuat(rotation_matrix, dir);
		
		if (entity_for_placing.GetInventory().GetCurrentInventoryLocation(src))
		{
			dst.SetGroundEx(entity_for_placing, pos, dir);
			
			if (GetGame().IsMultiplayer())
				ServerTakeToDst(src, dst);
			else // singleplayer
				MoveEntityToFinalPositionSinglePlayer(src, dst);		
		}
	}

	void MoveEntityToFinalPositionSinglePlayer(InventoryLocation src, InventoryLocation dst)
	{
		GetInventory().TakeToDst(InventoryMode.LOCAL, src, dst);
	}
};	

modded class AttachmentsOutOfReach
{
	override static bool IsAttachmentReachable(EntityAI e, string att_slot_name = "", int slot_id = -1, float range = 1.5)
	{
		if( !e.IgnoreOutOfReachCondition() )
		{
			PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
			if( player.IsInVehicle() && !CarDoor.Cast(e))
			{
				EntityAI root = e.GetHierarchyRoot();
				//if ( root.IsTransport() || root.IsPlayer() )
					return true;
				
				//return false;
			}
			else
			{
				
				vector pos_att;
				if ( slot_id != -1 )
				{
					att_slot_name = InventorySlots.GetSlotName(slot_id);
				}
				if( att_slot_name != "" )
				{
					if( e.MemoryPointExists(att_slot_name) )
					{
						vector mem_point = e.GetMemoryPointPos(att_slot_name);
						pos_att = e.ModelToWorld(mem_point);
					}
					else
					{
						pos_att = e.ModelToWorld(GetAttachmentPosition(e, InventorySlots.GetSlotIdFromString( att_slot_name ) ));
					}
					
				}
				
				vector pos_player = player.GetPosition();
				
				float height_diff = Math.AbsFloat( pos_player[1] - pos_att[1] );
				if( height_diff < range )
				{
					pos_player[1] = 0;
					pos_att[1] = 0;
					if ( vector.Distance(pos_player, pos_att) <= range )
					{
						return true;
					}
					return false;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return true;
		}
	}
};

modded class InventoryActionHandler  //allow longer distances in car before losing action
{
	void OnUpdate()
	{
		
		if( !m_isActive ) return;
		
		if( m_player.IsRaised() || m_player.GetCommand_Melee() )
		{
			DeactiveAction();
			return;			
		}
		
		if( GetGame().IsInventoryOpen() )
		{
			DeactiveAction();
			return;				
		}

		if (m_useItemInHands)
		{
			ItemBase handItem = m_player.GetItemInHands();
		
			if( handItem != m_mainItem )
			{
				DeactiveAction();
				return;
			}
		}

		if (m_player.IsInVehicle())
		{
			if( Math.AbsFloat( vector.Distance(m_actionStartPos, m_player.GetPosition())) > 100.0 )
			{
				DeactiveAction();
				return;
			}
		}
		else if( Math.AbsFloat( vector.Distance(m_actionStartPos, m_player.GetPosition())) > MIN_DISTANCE_TO_INTERRUPT )
		{
			DeactiveAction();
			return;
		}
		
		
	}	
};

modded class Hatchback_02 extends CarScript
{
	override bool CanDisplayCargo()
	{
		//if ( !super.CanDisplayCargo() )
		//	return false;

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );	
		if ( GetCarDoorsState("Hatchback_02_Trunk") == CarDoorState.DOORS_CLOSED && !player.IsInVehicle() && !player.GetCommand_Vehicle() )
			return false;
		
		return true;
	}
};

modded class OffroadHatchback extends CarScript
{
	override bool CanDisplayCargo()
	{
		//if ( !super.CanDisplayCargo() )
		//	return false;

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );	
		if ( GetCarDoorsState("NivaTrunk") == CarDoorState.DOORS_CLOSED && !player.IsInVehicle() && !player.GetCommand_Vehicle() )
			return false;
		
		return true;
	}
};

modded class Offroad_02 extends CarScript
{
	override bool CanDisplayCargo()
	{
		//if ( !super.CanDisplayCargo() )
		//	return false;

		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );	
		if ( GetCarDoorsState("Offroad_02_Trunk") == CarDoorState.DOORS_CLOSED && !player.IsInVehicle() && !player.GetCommand_Vehicle() )
			return false;
		
		return true;
	}
};

modded class CarScript 
{
	override bool IsInventoryVisible()
	{
		return true; //( GetGame().GetPlayer() && ( !GetGame().GetPlayer().GetCommand_Vehicle() || GetGame().GetPlayer().GetCommand_Vehicle().GetTransport() == this ) );
	}

/*
	override bool CanObstruct()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		return player.IsInVehicle();
	}
*/
	override float GetMomentum()// lessen vehicle damage for lower velocity crash
	{
		float momentum = GetVelocity(this).Length() * dBodyGetMass(this);
		float speed = GetVelocity(this).Length() * 3.6;

		if (speed < 10) {momentum = momentum*0.10}
		else if (speed < 20) {momentum = momentum*0.25}
		else if (speed < 30) {momentum = momentum*0.50}
		else if (speed < 50) {momentum = momentum*0.75}
		
		return momentum;
	}
};

modded class CarDoor extends InventoryItemSuper
{
	override bool CanObstruct()
	{
		PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
		return player.IsInVehicle();
	}
};

