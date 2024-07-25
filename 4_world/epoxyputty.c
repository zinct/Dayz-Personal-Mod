modded class EpoxyPutty: Inventory_Base 
{
	override void SetActions()
	{
		super.SetActions();
		RemoveAction(ActionRepairCarChassis);	

		//AddAction(ActionGlueTarget);
		//AddAction(ActionGlueSelf);
		AddAction(ActionRepairCarPartRusted);
		AddAction(ActionRepairCarPartWithEpoxy);
		AddAction(ActionRepairCarEngineWithEpoxy);
	}
};
