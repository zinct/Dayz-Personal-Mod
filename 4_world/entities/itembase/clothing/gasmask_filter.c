modded class GasMask_Filter : ItemBase
{	
	override float GetFilterDamageRatio() 
	{
		return 0.05; //Health lost per quantity consumed
	}
}