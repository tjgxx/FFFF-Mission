void main()
{
	/*
	  [Namalsk] CE init (offline)
	*/
	CreateHive();
	GetHive().InitOffline();

	/*
	  [Namalsk] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	   currently recommended time-frame is:
		11/1 -> 11/30
		keep in mind that gameplay features are tied to the mission date (stored in the storage) and that it SHOULD remain this period!
	   while using:
		day accelerated 6 times (serverTimeAcceleration=6), resulting in an average 78 min of day-time (RL)
		night accelerated 24 times (serverNightTimeAcceleration=4), resulting in an average of 26 min of night-time (RL)
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );
	
	if ( month < 12 )
    {
    	year = 2023;
        month = 8;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
	/*
	WINTER NAMALSK
    if ( ( month < 11 ) || ( month >= 12 ) )
    {
    	year = 2011;
        month = 11;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
	*/
	Get_ab_WillowispManager().CreateRandomWillowispController("Sebjan Mine Woods", "4802.379883 88.361198 8559.879883", 500, 40, Math.RandomIntInclusive(1, 3));
	
	array<string> willowispPositions = {
		"4507.180176 87.886299 8202.490234",
		"4504.870117 87.929703 8228.429688",
		"4231.950195 78.514603 8081.220215",
		"4236.709961 78.568398 8123.149902",
		"4311.850098 79.753601 8049.379883",
		"8557.900391 14.999963 10382.881836",
		"8885.138672 13.474287 10267.426758",
		"8743.138672 15.762648 10018.023438",
		"5194.238770 23.422983 10823.314453"
	};
	Get_ab_WillowispManager().CreateRandomWillowispController("woods north west", "5546.490234 52.934620 11010.299805", 500, 200, 15);
	Get_ab_WillowispManager().CreateRandomWillowispController("Sebjan woods north", "4835.031250 86.271873 8596.339844", 500, 200, 10);
	Get_ab_DesignatorManager().CreateRandomDesignatorController("Veresnik Fields", "5933.004883 39.196339 8925.993164", 500, 100, 30);
	Get_ab_DesignatorManager().CreateRandomDesignatorController("Wods", "4726.369629 93.141541 8496.296875", 500, 200, 20);
	Get_ab_DesignatorManager().CreateRandomDesignatorController("Forrest lubjansk", "4513.329102 53.664604 9405.777344", 250, 200, 20);
	Get_ab_WillowispManager().CreateRandomWillowispController("Sebjan woods north", "5698.758301 87.719589 7815.573730", 500, 200, 20);
	Get_ab_DesignatorManager().CreateRandomDesignatorController("Veresnik Fields", "5698.758301 87.719589 7815.573730", 500, 100, 20);
	};

class CustomMission: MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.25 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.15 );
			// m_EventManagerServer.RegisterEvent( Blizzard, 0.05 );
			// m_EventManagerServer.RegisterEvent( ExtremeCold, 0.2 );
			// m_EventManagerServer.RegisterEvent( Snowfall, 0.9 );
			// m_EventManagerServer.RegisterEvent( HeavyFog, 0.05 );
		}
	}

	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat( 0.50, 0.85 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
		
		TStringArray gloves = {"WoolGloves_White",  "WoolGloves_Tan",  "WoolGloves_Green",  "WoolGloves_Black", "WoolGlovesFingerless_Black", "WoolGlovesFingerless_Green", "WoolGlovesFingerless_Tan", "WoolGlovesFingerless_White", "Fingerless_Gloves_Wool", "Fingerless_Gloves_Wool_Grey", "Fingerless_Gloves_Wool_Black"};
		TStringArray hat = {"Ushanka_Green", "Ushanka_Blue", "Ushanka_Black", "ZmijovkaCap_Green", "ZmijovkaCap_Brown", "ZmijovkaCap_Black", "BeanieHat_Black", "BeanieHat_Green", "BeanieHat_Brown", "BoonieHat_Black", "BoonieHat_Dubok", "BoonieHat_NavyBlue", "PetushokHat_Green", "PetushokHat_Yellow", "RadarCap_Black", "RadarCap_Blue", "RadarCap_Green", "WinterCoif_Green"};
		TStringArray mask = {"Balaclava3Holes_Beige", "Balaclava3Holes_Black", "Balaclava3Holes_Green", "Shemagh_Facemask_Brown", "Shemagh_Facemask_Green", "Shemagh_Facemask_Black", "Shemagh_Facemask_White"};
		player.GetInventory().CreateInInventory(gloves.GetRandomElement());
		player.GetInventory().CreateInInventory(hat.GetRandomElement());

		int throwDice = Math.RandomInt( 0, 10 );

		if (throwDice < 3)
		{
			player.GetInventory().CreateInInventory(mask.GetRandomElement());
		}
		
		// top
		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "TraderPlus_Money_DIM_Gold" );
			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				itemBs.SetQuantity( 100 );
			}
			itemEnt = itemClothing.GetInventory().CreateInInventory( "TraderPlus_Money_DIM_Gold" );

			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				itemBs.SetQuantity( 100 );
			}
			itemEnt = itemClothing.GetInventory().CreateInInventory( "TraderPlus_Money_DIM_Gold" );

			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				itemBs.SetQuantity( 100 );
			}
			itemEnt = itemClothing.GetInventory().CreateInInventory( "TraderPlus_Money_DIM_Gold" );

			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				itemBs.SetQuantity( 50 );
			}
		}

		// pants
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
		}

		// shoes
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
		}

		// bump fresh spawn water and energy values (to compensate for the frozen food and harder-to-get wells)
		player.GetStatWater().Set( 900 );
		player.GetStatEnergy().Set( 1100 );
	}
};
  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
};