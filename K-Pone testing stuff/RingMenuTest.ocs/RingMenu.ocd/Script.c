/*

	RingMenu
	
	@author: K-Pone

*/

local Visibility = VIS_Owner;

local fxRingMenu = new Effect
{	
	Name = "RingMenu",
	posx = nil, // These will be set when the RingMenu is created. Needed to determine the position of the cursor.
	posy = nil,
	selection = 0, // 1 at top, counting clockwise to 8, 0 is center
	ringmenu_obj = nil, // The object that displays the ring
	icons = [nil, nil, nil, nil, nil, nil, nil, nil, nil], // icons to display

	UpdateSelection = func()
	{
		var cursorpos = GetPlayerGUICursorPos(Target->GetOwner());
		
		if (Distance(posx, posy, cursorpos[0], cursorpos[1]) < 40)
		{
			selection = 0;
		}
		else
		{
			var ang = Angle(posx, posy, cursorpos[0], cursorpos[1]);
			
			if (ang >= 338 || ang < 23)
				selection = 1;
			if (ang >= 23 && ang < 68)
				selection = 2;
			if (ang >= 68 && ang < 113)
				selection = 3;
			if (ang >= 113 && ang < 158)
				selection = 4;
			if (ang >= 158 && ang < 203)
				selection = 5;
			if (ang >= 203 && ang < 248)
				selection = 6;
			if (ang >= 248 && ang < 293)
				selection = 7;
			if (ang >= 293 && ang < 338)
				selection = 8;
		}
		
		var gfxnames = ["C", "N", "NE", "E", "SE", "S", "SW", "W", "NW"];
		
		ringmenu_obj->SetGraphics(gfxnames[selection]);
	},
	
	Start = func()
	{
		// Create the RingMenu
		ringmenu_obj = CreateObject(RingMenu);
		ringmenu_obj->SetOwner(Target->GetOwner());
		var cursorpos = GetPlayerCursorPos(Target->GetOwner(), false);
		posx = cursorpos[0];
		posy = cursorpos[1];
		ringmenu_obj->SetPosition(posx, posy);
		
		icons[0] = CreateObject(RingMenuIcon);
		icons[0]->SetPosition(posx, posy);
		icons[0]->SetGraphics(nil, Icon_Exit);
		
		for (var i = 1; i < 9; i++)
		{
			var icon_distance = 100; // Distance of outer icons to center
			
			icons[i] = CreateObject(RingMenuIcon);
			icons[i]->SetPosition(posx + Sin((i-1) * 45, icon_distance), posy - Cos((i-1) * 45, icon_distance));
			icons[i].Plane = ringmenu_obj.Plane + 1;
		}
		
		
		
	},
	
	Stop = func()
	{
		// Execute command on RingMenu
		UpdateSelection();
		ringmenu_obj->MenuItemSelected(selection, Target);
		
		// Remove RingMenu
		for (var obj in icons)
		{
			if (obj) obj->RemoveObject();
		}
		ringmenu_obj->RemoveObject();
	},
	
	Timer = func()
	{
		// Update RingMenu Graphics
		UpdateSelection();
	}
};


func Initialize()
{
	
}

func OpenRingMenu(clonk)
{
	clonk->CreateEffect(fxRingMenu,1,1);
}

func CloseRingMenu(clonk)
{
	clonk->RemoveEffect("RingMenu", clonk);
}

/* Ring Menu Actions */
func MenuItemSelected(int index, clonk)
{
	// index is 0 for center. Counting up, starting on Top/North at 1.
	var sounds = ["UI::Ding","UI::Ding","UI::Ding","UI::Ding","UI::Ding","UI::Ding","UI::Ding","UI::Ding","UI::Ding"];
	
	clonk->Sound(sounds[index]);
	Log("Ringmenü Auswahl: %d", index);
	
}