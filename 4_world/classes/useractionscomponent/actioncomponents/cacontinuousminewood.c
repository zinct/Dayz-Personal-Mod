// modded class CAContinuousMineWood : CAContinuousBase
// {
//     override void Setup( ActionData action_data )
// 	{
// 		m_TimeElpased = 0;
// 		if ( !m_SpentUnits )
// 		{ 
// 			m_SpentUnits = new Param1<float>(0);
// 		}
// 		else
// 		{	
// 			m_SpentUnits.param1 = 0;
// 		}
// 		m_MaterialAndQuantityMap = new map<string,int>;
// 		m_DataLoaded = GetMiningData(action_data);
		
// 		if (m_CycleTimeOverride > -1.0)
// 		{
// 			m_TimeBetweenMaterialDrops = m_CycleTimeOverride;
// 			if (!action_data.m_MainItem) //hand action
// 				m_TimeBetweenMaterialDrops = m_TimeBetweenMaterialDrops * 3;
// 		}
// 		m_AdjustedTimeBetweenMaterialDrops = action_data.m_Player.GetSoftSkillsManager().SubtractSpecialtyBonus( m_TimeBetweenMaterialDrops, m_Action.GetSpecialtyWeight(), true );		
// 		m_TimeToComplete = 0;
//         m_AdjustedTimeBetweenMaterialDrops = 0;
//         m_TimeBetweenMaterialDrops = 0; 
// 	}
// }