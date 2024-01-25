class ReplaceZenTentLambda : ReplaceItemWithNewLambdaBase
{
	void ReplaceZenTentLambda(EntityAI old_item, string new_item_type)
	{
		m_OldItem = old_item;
		m_NewItemType = new_item_type;
	}

	override void CopyOldPropertiesToNew(notnull EntityAI old_item, EntityAI new_item)
	{
		for(int j = old_item.GetInventory().AttachmentCount() - 1; j >= 0 ; j--)
		{
			EntityAI oldAttachment = old_item.GetInventory().GetAttachmentFromIndex(j);

			EntityAI newAttachment = EntityAI.Cast(new_item.GetInventory().CreateAttachment(oldAttachment.GetType()));
			MiscGameplayFunctions.TransferItemProperties(oldAttachment, newAttachment);
		}

		CargoBase cargo = old_item.GetInventory().GetCargo();

		if(cargo)
		{
			for(int i = cargo.GetItemCount() - 1; i >= 0 ; i--)
			{
				InventoryLocation loc = new_item.m_OldLocation;
				new_item.GetInventory().TakeEntityToInventory(InventoryMode.SERVER, FindInventoryLocationType.CARGO | FindInventoryLocationType.ATTACHMENT, cargo.GetItem(i));
			}
		}

		MiscGameplayFunctions.TransferItemProperties(old_item, new_item);
	}
};