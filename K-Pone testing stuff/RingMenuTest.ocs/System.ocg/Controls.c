
static g_player_cursor_pos_ingame; // array of [x,y] pos arrays; indexed by player. last cursor pos as sent by CON_CursorPos
static g_player_gui_cursor_pos; // array of [x,y] pos arrays; indexed by player. current cursor pos as sent by CON_GUICursor

global func PlayerControl(int player, int control, control_extra, int x, int y, int strength, bool repeated, int release)
{	
	if (control == CON_GUICursor)
	{
		// Update player's GUI cursor positions
		if (!g_player_gui_cursor_pos)
			g_player_gui_cursor_pos = [];
		g_player_gui_cursor_pos[player] = [x,y];
		
		return true;
	}

	if (control == CON_AimingCursor)
	{
		if (!g_player_cursor_pos_ingame)
			g_player_cursor_pos_ingame = [];
		g_player_cursor_pos_ingame[player] = [x, y];
		
		return true;
	}

	if (control == CON_RingMenu && !release)
	{
		var crew = GetCursor(player);
		RingMenu->OpenRingMenu(crew);
		
		return true;
	}
	
	if (control == CON_RingMenu && release)
	{
		var crew = GetCursor(player);
		RingMenu->CloseRingMenu(crew);
		
		return true;
	}
	
	
	return _inherited(player, control, control_extra, x, y, strength, repeated, release);
}

global func GetPlayerGUICursorPos(int plr)
{
	if (!g_player_gui_cursor_pos[plr]) return nil;
	return g_player_gui_cursor_pos[plr];
}

global func GetPlayerCursorPos(int plr, bool ingame)
{
	if (!ingame) return inherited(plr, ...);
	if (!g_player_cursor_pos_ingame) return nil;
	return g_player_cursor_pos_ingame[plr];
}