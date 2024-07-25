modded class RecipeBase
{
	//spawns results in the world
	void SpawnItems(ItemBase ingredients[], PlayerBase player, array<ItemBase> spawned_objects/*out*/)
	{
		//vector item_position = player.GetPosition() + ( player.GetDirection() * 1 );
		//Debug.Log("SpawnItems called","recipes");
		spawned_objects.Clear();//just to make sure
		EntityAI object = NULL;
		
		for(int i = 0; i < m_NumberOfResults; i++)
		{
			string item_to_spawn = m_ItemsToCreate[i];
			
			if( m_ResultInheritsColor[i] != -1 )
			{
				ItemBase item = ingredients[m_ResultInheritsColor[i]];
				//string class_name = item.GetType();
				string color = item.ConfigGetString("color");
				string new_class_name = m_ItemsToCreate[i] + color;
				item_to_spawn = new_class_name;
			}
			
			if( m_ResultToInventory[i] == -1 || player.IsInVehicle() ) 
			{
				Debug.Log("  = "+m_ResultToInventory[i].ToString(),"recipes");
				
				InventoryLocation inv_loc = new InventoryLocation;
				if (player.GetInventory().FindFirstFreeLocationForNewEntity(item_to_spawn, FindInventoryLocationType.ANY, inv_loc))
				{
					object = player.GetInventory().CreateInInventory(item_to_spawn);
				}
			}
			else if (m_ResultToInventory[i] >= 0)
			{
				/*
				object = player.SpawnEntityOnGroundOnCursorDir(item_to_spawn, 0.5);

				ItemBase item_swap_with = ingredients[m_ResultToInventory[i]];
				player.SwapEntities(true, item_swap_with, EntityAI.Cast(object));
				*/
			}
			else if ( m_ResultToInventory[i] == -2 )
			{
				object = player.GetInventory().CreateEntityInCargo(item_to_spawn);
			}
			if( !object )
			{
				//spawning in inventory failed, spawning on the ground instead.....
				object = player.SpawnEntityOnGroundOnCursorDir(item_to_spawn, m_ResultSpawnDistance[i]);
				if( !object)
				{
					Error("failed to spawn entity "+item_to_spawn+" , make sure the classname exists and item can be spawned");
				}
			}
			spawned_objects.Insert(ItemBase.Cast(object));
			//Debug.Log("spawning item "+item_to_spawn,"recipes");
			object = null;
		}

	}
};