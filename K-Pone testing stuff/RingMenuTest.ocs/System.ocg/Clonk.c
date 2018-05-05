
#appendto Clonk


func Initialize(...)
{
	SetPlayerControlEnabled(GetOwner(), CON_Aim, true);
	SetPlayerControlEnabled(GetOwner(), CON_GUICursor, true);
	return _inherited(...);
}

