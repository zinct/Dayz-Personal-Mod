class CfgPatches
{
    class IndraPersonalMod
    {
        requiredAddons[]=
        {
                "DZ_Data",
                "DZ_Scripts",
                "DZ_Vehicles_Wheeled",
                "DZ_Vehicles_Parts",
                "DZ_Sounds_Effects",
				"DZ_Gear_Consumables"
        };
    };
};

class CfgMods
{
        class IndraPersonalMod
        {
                type="mod";
                name = "Indra personal Mod";
                credits = "Indra Mahesa";
                author = "Indra Mahesa";
                dependencies[]={"Game", "World", "Mission"}; 
                class defs
                {
                        class gameScriptModule
                        {
                                value="";
                                files[]={"IndraPersonalMod/3_game"};
                        };
                        class worldScriptModule
                        {
                                value="";
                                files[]={"IndraPersonalMod/4_world"};
                        };
                        class missionScriptModule
                        {
                                value="";
                                files[]={"IndraPersonalMod/5_mission"};
                        };
                };
        };
};

class CfgVehicles 
{
        class CarScript;
        class SimulationModule;
        class Sedan_02: CarScript
	{
		class SimulationModule: SimulationModule
		{
			class Engine {
				rpmIdle = 900;
				rpmMin = 1000;
				rpmClutch = 1400;
				rpmRedline = 7000;
			};
		};
	};

	class Inventory_Base;
	class WoodenLog: Inventory_Base
	{
		// weight=100;
		itemBehaviour=2;
	};
};

class CfgSoundSets {
	class FMusic_Menu_SoundSet {
		soundShaders[] = {"FMusic_Menu_SoundShader"};
		volumeFactor = 1;
		frequencyFactor = 1;
		spatial = 0;
	};
};

class CfgSoundShaders
{
	class FMusic_Menu_SoundShader {
		samples[] = {{"IndraPersonalMod\sounds\custom_background_music.ogg", 1}};
		volume = 0.5;
	};

        class baseVehiclesSedan_02_SoundShader;
        class baseEngineSedan_02_SoundShader;
        class Sedan_02_engine_start_SoundShader: baseVehiclesSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\engine_start.ogg",
				1
			}
		};
		volume=0.69999999;
	};
        class Sedan_02_engine_stop_SoundShader: baseVehiclesSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_stop.ogg",
				1
			}
		};
		volume=0.69999999;
	};
        class Sedan_02_engine_failed_start_fuel_SoundShader: baseVehiclesSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\engine_failed_start_fuel.ogg",
				1
			}
		};
		volume=1;
	};

	class Sedan_02_Engine_Ext_Rpm0_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_rpm0.ogg",
				1
			}
		};
		frequency="0.85 * ((900 + ((rpm - 900)/(6500/5600))) max 900) / 850";
		volume="0.4 * 1 * engineOn * 0.4 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((850+1200)/2) + 2.5*50),(((850+1200)/2) - 50)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Ext_Rpm1_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_rpm1.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 1200";
		volume="0.4 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 0.6 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((850+1200)/2) - 2.5*50),(((850+1200)/2) + 50)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1200+1700)/2) + 2.5*150),(((1200+1700)/2) - 150)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Offload_Ext_Rpm1_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_offload_rpm1.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 1200";
		volume="0.4 * 1 * (thrust factor[0.6,0.2]) * 0.8 * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 0.6 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((850+1200)/2) - 2.5*50),(((850+1200)/2) + 50)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1200+1700)/2) + 2.5*150),(((1200+1700)/2) - 150)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Ext_Rpm2_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_rpm2.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 1700";
		volume="0.4 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 0.85 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1200+1700)/2) - 2.5*150),(((1200+1700)/2) + 150)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1700+2300)/2) + 2.5*150),(((1700+2300)/2) - 150)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Offload_Ext_Rpm2_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_offload_rpm2.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 1700";
		volume="0.4 * 1 * (thrust factor[0.6,0.2]) * 0.8 * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 0.85 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1200+1700)/2) - 2.5*150),(((1200+1700)/2) + 150)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1700+2300)/2) + 2.5*150),(((1700+2300)/2) - 150)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Ext_Rpm3_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_rpm3.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 2300";
		volume="0.4 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1700+2300)/2) - 2.5*150),(((1700+2300)/2) + 150)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((2300+3250)/2) + 2.5*200),(((2300+3250)/2) - 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Offload_Ext_Rpm3_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_offload_rpm3.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 2300";
		volume="0.4 * 1 * (thrust factor[0.6,0.2]) * 0.8 * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((1700+2300)/2) - 2.5*150),(((1700+2300)/2) + 150)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((2300+3250)/2) + 2.5*200),(((2300+3250)/2) - 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Ext_Rpm4_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_rpm4.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 3250";
		volume="0.4 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((2300+3250)/2) - 2.5*200),(((2300+3250)/2) + 200)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((3250+4400)/2) + 2.5*200),(((3250+4400)/2) - 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Offload_Ext_Rpm4_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_offload_rpm4.ogg",
				1
			}
		};
		frequency="0.85 * (900 + ((rpm - 900)/(6500/5600))) / 3250";
		volume="0.4 * 1 * (thrust factor[0.6,0.2]) * 0.8 * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((2300+3250)/2) - 2.5*200),(((2300+3250)/2) + 200)]) * ((900 + ((rpm - 900)/(6500/5600))) factor [(((3250+4400)/2) + 2.5*200),(((3250+4400)/2) - 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Ext_Rpm5_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_rpm5.ogg",
				1
			}
		};
		frequency="(0.85 * (900 + ((rpm - 900)/(6500/5600))) / 4400) min (6500/5600)";
		volume="0.4 * 1 * (thrust factor[0.1,0.45]) * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((3250+4400)/2) - 2.5*200),(((3250+4400)/2) + 200)]) * ((1 - 0.25*doors) max campos)";
	};
	class Sedan_02_Engine_Offload_Ext_Rpm5_SoundShader: baseEngineSedan_02_SoundShader
	{
		samples[]=
		{
			
			{
				"IndraPersonalMod\sounds\vaz_classic_engine_ext_offload_rpm4.ogg",
				1
			}
		};
		frequency="(0.85 * (900 + ((rpm - 900)/(6500/5600))) / 4400) min (6500/5600)";
		volume="0.4 * 1 * (thrust factor[0.6,0.2]) * 0.8 * (0.7 + 0.3 * (speed factor [10,60])) * engineOn * 1 * ((900 + ((rpm - 900)/(6500/5600))) factor [(((3250+4400)/2) - 2.5*200),(((3250+4400)/2) + 200)]) * ((1 - 0.25*doors) max campos)";
	};
};