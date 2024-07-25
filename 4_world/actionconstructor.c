modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		// SingleUse Actions	
		actions.Insert(ActionRepairCarPartRusted);
		actions.Insert(ActionRepairCarPartWithEpoxy);
		actions.Insert(ActionRepairCarEngineWithEpoxy);
		actions.Insert(ActionRepairCarEngineWithWrench);
	}
}
