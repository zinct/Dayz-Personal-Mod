class CfgPatches
{
    class IndraPersonalMod
    {
        requiredAddons[]=
        {
                "DZ_Data",
                "DZ_Scripts",
                "DZ_Gear_Camping",
                "DZ_Characters_Backpacks"
        };
    };
};

class CfgMods
{
        class IndraPersonalMod
        {
                type="mod";
                name = "Disable Sprint Metabolism";
                credits = "Indra Mahesa";
                author = "Indra Mahesa";
                dependencies[]={"Game", "Mission", "World"}; 
                class defs
                {
                        class gameScriptModule
                        {
                                value="";
                                files[]={"IndraPersonalMod/3_game"};
                        };
                        class missionScriptModule
                        {
                                value="";
                                files[]={"IndraPersonalMod/5_mission"};
                        };
                        class worldScriptModule
                        {
                                value="";
                                files[]={"IndraPersonalMod/4_world"};
                        };
                };
        };
};

class CfgVehicles
{
	class TentBase;
	class LargeTent : TentBase
	{
		inventorySlot[] +=
		{
			"Back"
		};
		itemInfo[] +=
		{
			"Clothing",
			"Back"
		};
                attachments[]=
                {
                        "CamoNet",
			"Lights"
                };
	};

	// Define large tent backpack object
	class Clothing;
	class LargeTentBackpack : Clothing
	{
		scope = 2;
		displayName = "Large Tent Backpack";
		descriptionShort = "This is just simple backpack for a packing up Large Tent";
		model = "\dz\gear\camping\large_tent_backpack.p3d";
		inventorySlot[] +=
		{
			"Back"
		};
		itemInfo[] +=
		{
			"Clothing",
			"Back"
		};
		rotationFlags = 16;
		itemSize[] = { 10,4 };
		itemsCargoSize[] = { 10,40 };
		weight = 90000;
		varWetMax = 0.49000001;
		heatIsolation = 0.69999999;
		visibilityModifier = 0.80000001;
		soundAttType = "Military";
		randomQuantity = 4;
		class ClothingTypes
		{
			male = "dz\gear\camping\large_tent_backpack.p3d";
			female = "dz\gear\camping\large_tent_backpack.p3d";
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints = 2000;
					transferToAttachmentsCoef = 0.5;
					healthLevels[] =
					{

						{
							1,

							{
								"DZ\gear\camping\data\bagpack.rvmat"
							}
						},

						{
							0.69999999,

							{
								"DZ\gear\camping\data\bagpack.rvmat"
							}
						},

						{
							0.5,

							{
								"DZ\gear\camping\data\bagpack_damage.rvmat"
							}
						},

						{
							0.30000001,

							{
								"DZ\gear\camping\data\bagpack_damage.rvmat"
							}
						},

						{
							0,

							{
								"DZ\gear\camping\data\bagpack_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet = "pickUpBackPack_Metal_Light_SoundSet";
					id = 796;
				};
				class pickUpItem
				{
					soundSet = "pickUpBackPack_Metal_SoundSet";
					id = 797;
				};
				class drop
				{
					soundset = "taloonbag_drop_SoundSet";
					id = 898;
				};
			};
		};
	};
};