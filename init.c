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

    if ( ( month < 11 ) || ( month >= 12 ) )
    {
    	year = 2011;
        month = 11;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
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
			m_EventManagerServer.RegisterEvent( Aurora, 0.2 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.05 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.2 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.6 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.25 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.05 );
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