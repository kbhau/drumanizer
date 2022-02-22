#pragma once

class Limb
{
public:
    double balance = 1.0;
    double balance_recovery_per_second = 8.0;
    double balance_cost_base = 0.2;
    double balance_cost_velocity_mult = 0.25;
    double stamina = 1.0;
    double stamina_recovery_per_second = 0.65;
    double stamina_cost_base = 0.035;
    double stamina_cost_velocity_mult = 0.055;
    double timing_base = 10.0;
    double timing_balance_factor = 16.5;
    double timing_stamina_factor = 9.0;
    double timing_scale = 0.18;
    double velocity_base = 10.0;
    double velocity_balance_factor = 30.0;
    double velocity_stamina_factor = 25.0;
    double velocity_scale = 0.8;

public:
    double Get_offset_at_ms(int millisecond);
    double Get_power_level_at_ms(int millisecond);
    int Play_note(int millisecond, int velocity);

private:
    int last_millisecond_played = 0;

private:
    void Get_projected_vars(int millisecond, double& balance, double& stamina);
};
