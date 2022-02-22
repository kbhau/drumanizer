#include "Drummer.h"

double Drummer::Get_offset(int key_number, int millisecond)
{
    last_limb = Get_limb(key_number, millisecond);
    return last_limb->Get_offset_at_ms(millisecond);
}

double Drummer::Play_note(int velocity, int millisecond)
{
    return last_limb->Play_note(millisecond, velocity);
}

void Drummer::Naturalise()
{
    auto l = &dominant_hand;
    l->balance_recovery_per_second = 8.75;
    l->balance_cost_velocity_mult = 0.23;
    l->stamina_recovery_per_second = 0.68;
    l->stamina_cost_velocity_mult = 0.052;
    l->timing_scale = 0.165;
    l->velocity_scale = 0.75;

    l = &off_hand;
    l->balance_recovery_per_second = 7.75;
    l->balance_cost_velocity_mult = 0.285;
    l->stamina_recovery_per_second = 0.615;
    l->stamina_cost_velocity_mult = 0.058;
    l->timing_scale = 0.19;
    l->timing_balance_factor = 18.25;
    l->velocity_scale = 0.83;
    l->velocity_balance_factor = 42.0;

    l = &dominant_leg;
    l->balance_recovery_per_second = 7.5;
    l->balance_cost_velocity_mult = 0.255;
    l->stamina_recovery_per_second = 0.71;
    l->stamina_cost_velocity_mult = 0.048;
    l->timing_scale = 0.18;
    l->velocity_scale = 0.8;

    l = &off_leg;
    l->balance_recovery_per_second = 6.85;
    l->balance_cost_velocity_mult = 0.27;
    l->stamina_recovery_per_second = 0.695;
    l->stamina_cost_velocity_mult = 0.0495;
    l->timing_scale = 0.195;
    l->timing_balance_factor = 18.75;
    l->velocity_scale = 0.835;
}

Limb* Drummer::Get_better_limb(Limb& dominant, Limb& off, int millisecond)
{
    auto power_dominant = dominant.Get_power_level_at_ms(millisecond);
    auto power_off = off.Get_power_level_at_ms(millisecond);

    if (power_off > power_dominant + 0.04) {
        return &off;
    }

    return &dominant;
}

Limb* Drummer::Get_limb(int key_number, int millisecond)
{
    if (key_number <= 36) {
        return Get_better_limb(dominant_leg, off_leg, millisecond);
    } else {
        return Get_better_limb(dominant_hand, off_hand, millisecond);
    }
}



/*
83	CHOKE ALL CYMBALS
65	HI-HAT PEDAL
63	(Hi-Hat closed)
62	HI-HAT CLOSED
61	HI-HAT HALF OPEN
60	HI-HAT OPEN
58	CRASH RIGHT CHOKED
57	CRASH RIGHT
55	SPLASH
53	RIDE BELL
52	CHINA
51	RIDE
50	(Tom Hi)
49	CRASH LEFT
48	TOM HI
47	(Tom Mid)
46	HI-HAT OPEN
45	TOM MID
44	HI-HAT HALF OPEN
43	(Tom Low)
42	HI-HAT CLOSED
41	TOM LOW
40	(Snare)
39	(Snare)
38	SNARE
37	SIDE-STICK
36	KICK
35	(Kick)
*/