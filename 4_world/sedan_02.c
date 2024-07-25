modded class Sedan_02
{
	void Sedan_02()
	{
		m_dmgContactCoef		= 0.0790;

		m_EngineStartOK			= "Sedan_02_engine_start_SoundSet";
		m_EngineStartBattery	= "Sedan_02_engine_failed_start_fuel_SoundSet";
		m_EngineStartPlug		= "Sedan_02_engine_failed_start_fuel_SoundSet";
		m_EngineStartFuel		= "Sedan_02_engine_failed_start_fuel_SoundSet";
		m_EngineStopFuel		= "Sedan_02_engine_stop_SoundSet";

		m_CarDoorOpenSound		= "offroad_door_open_SoundSet";
		m_CarDoorCloseSound		= "offroad_door_close_SoundSet";
		
		m_CarHornShortSoundName = "Sedan_02_Horn_Short_SoundSet";
		m_CarHornLongSoundName	= "Sedan_02_Horn_SoundSet";
		
		SetEnginePos("0 0.7 -1.7");
	}
}