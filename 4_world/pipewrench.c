modded class PipeWrench extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		//AddAction(ActionDismantlePart);
		AddAction(ActionRepairCarEngine);
		AddAction(ActionRepairCarChassis);
		AddAction(ActionRepairCarPart);
		AddAction(ActionMineRock);
	}
}