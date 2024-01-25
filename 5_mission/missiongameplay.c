
modded class MissionGameplay {
    override void AddActiveInputRestriction(int restrictor)
	{
		//unique behaviour outside regular excludes
		if (restrictor > -1)
		{
			switch (restrictor)
			{
				case EInputRestrictors.INVENTORY:
				{
					// GetUApi().GetInputByID(UAWalkRunForced).ForceEnable(true); // force walk on!
					PlayerBase player = PlayerBase.Cast( GetGame().GetPlayer() );
					if ( player )
					{
						ItemBase item = player.GetItemInHands();
						if (item && item.IsWeapon())
							player.RequestResetADSSync();
					}
					break;
				}
				case EInputRestrictors.MAP:
				{
					GetUApi().GetInputByID(UAWalkRunForced).ForceEnable(true); // force walk on!
					break;
				}
			}
			
			if (!m_ActiveInputRestrictions)
			{
				m_ActiveInputRestrictions = new array<int>;
			}
			if (m_ActiveInputRestrictions.Find(restrictor) == -1)
			{
				m_ActiveInputRestrictions.Insert(restrictor);
			}
		}
	}
}