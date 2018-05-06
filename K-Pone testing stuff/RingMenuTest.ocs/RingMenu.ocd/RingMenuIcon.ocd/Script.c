
local caption = "I like trains";

local showtextfx = new Effect
{
	Timer = func()
	{
		Target->CustomMessage(Target.caption, Target, Target->GetOwner());
	}
};

func Initialize()
{
	CreateEffect(showtextfx,1,1);
}