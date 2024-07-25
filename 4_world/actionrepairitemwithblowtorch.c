modded class ActionRepairItemWithBlowtorch : ActionContinuousBase 
{
	void ActionRepairItemWithBlowtorch()
	{
		m_CallbackClass 	= ActionRepairItemWithBlowtorchCB;
		m_SpecialtyWeight 	= UASoftSkillsWeight.PRECISE_LOW;

		m_CommandUID 		= DayZPlayerConstants.CMD_ACTIONFB_FLAME_REPAIR;
		m_StanceMask 		= DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_FullBody 			= true;
		m_LockTargetOnUse	= false;
		m_Text 				= "#repair";
	}
	
	override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
	{
		CarScript car = CarScript.Cast(target.GetObject());
		if (car || !player)
			return false;

		PluginRepairing moduleRepairing;
		Class.CastTo(moduleRepairing, GetPlugin(PluginRepairing));
		Blowtorch bt = Blowtorch.Cast(item);

		return bt.HasEnoughEnergyForRepair(UATimeSpent.BASEBUILDING_REPAIR_MEDIUM) && moduleRepairing && moduleRepairing.CanRepair(item, target.GetObject());
	}
}
