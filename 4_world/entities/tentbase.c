modded class TentBase
{
	override void OnItemLocationChanged(EntityAI old_owner, EntityAI new_owner)
	{
		if(CanBeManipulated())
		{
			super.OnItemLocationChanged(old_owner, new_owner);
		}
	}

	override bool CanDisplayCargo()
	{
		if(m_State == PACKED)
		{
			return false;
		}

		return super.CanDisplayCargo();
	}

	override bool CanPutInCargo(EntityAI parent)
	{
		if(m_State == PACKED)
		{
			return false;
		}

		return super.CanPutInCargo(parent);
	}

    void Pack(bool update_navmesh, bool init = false)
	{
		HideAllAnimationsAndProxyPhysics();
		
		m_State = PACKED;
		m_IsEntrance = PACKED;
		m_IsWindow = PACKED;
		m_IsToggle = PACKED;
		
		Refresh();

        // GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
        // GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		
		if (update_navmesh) 
		{
			RegenerateNavmesh();	
		}
						
		DestroyClutterCutter();
		
		SetSynchDirty();
		
		if ((!GetGame().IsDedicatedServer()) && !init)
		{
			GetOnViewIndexChanged().Invoke();
		}
	}

    void Pitch(bool update_navmesh, bool init = false)
	{
		HideAllAnimationsAndProxyPhysics();
		
		m_State = PITCHED;
		m_IsEntrance = PITCHED;
		m_IsWindow = PITCHED;
		m_IsToggle = PITCHED;
		
		Refresh();
		
		GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		
		if (update_navmesh) 
		{
			RegenerateNavmesh();
		}

		SetSynchDirty();
		
		if ((!GetGame().IsDedicatedServer()) && !init)
		{
			GetOnViewIndexChanged().Invoke();
		}
	}

    bool CanBePacked()
	{
		if (GetState() == PITCHED && this.GetInventory().AttachmentCount() == 0)
		{
            return true;
		}
		
		return false;
	}
}