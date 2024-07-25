class ARepairPliers extends RecipeBase {

	override void Init() {
		m_Name = "#STR_RepairPliers";
		m_IsInstaRecipe = false; // should this recipe be performed instantly without animation
		m_AnimationLength = 1; // animation length in relative time units
		m_Specialty = -0.01; // value > 0 for roughness, value < 0 for precision

		//----------------------------------------------------------------------------------------------------------------------

		// ingredient 1
		InsertIngredient(0, "Pliers"); // you can insert multiple ingredients this way
		m_MinDamageIngredient[0] = 2; // -1 = disable check, 4 = RUINED, 3 = BADLY_DAMAGED, 2 = DAMAGED, 1 = WORN, 0 = PRISTINE
		m_MaxDamageIngredient[0] = 3; // -1 = disable check, 4 = RUINED, 3 = BADLY_DAMAGED, 2 = DAMAGED, 1 = WORN, 0 = PRISTINE
		m_MinQuantityIngredient[0] = -1; // -1 = disable check
		m_MaxQuantityIngredient[0] = -1; // -1 = disable check
		m_IngredientAddHealth[0] = 20; // 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0; // 0 = do nothing
		m_IngredientDestroy[0] = false; // true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false; // set 'true' to allow modification of the values by softskills on this ingredient

		// ingredient 2
		InsertIngredient(1, "Whetstone"); // you can insert multiple ingredients this way
		m_MinDamageIngredient[1] = -1; // -1 = disable check, 4 = RUINED, 3 = BADLY_DAMAGED, 2 = DAMAGED, 1 = WORN, 0 = PRISTINE
		m_MaxDamageIngredient[1] = 3; // -1 = disable check, 4 = RUINED, 3 = BADLY_DAMAGED, 2 = DAMAGED, 1 = WORN, 0 = PRISTINE
		m_MinQuantityIngredient[1] = 5; // -1 = disable check
		m_MaxQuantityIngredient[1] = -1; // -1 = disable check
		m_IngredientAddHealth[1] = 0; // 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = -5; // 0 = do nothing
		m_IngredientDestroy[1] = false; // true = destroy, false = do nothing
		m_IngredientUseSoftSkills[1] = true; // set 'true' to allow modification of the values by softskills on this ingredient
		
		//----------------------------------------------------------------------------------------------------------------------
		
		// results

		//----------------------------------------------------------------------------------------------------------------------
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player) { // final check for recipe's validity
		return true;
	}
};

