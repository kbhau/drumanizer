#include <random>

#include "Limb.h"



std::default_random_engine rng(666);
std::normal_distribution<double> nrm(0.0, 1.0);
std::uniform_real_distribution<double> unr{};



double Limb::Get_offset_at_ms(int millisecond)
{
    auto temp_balance = 0.0;
    auto temp_stamina = 0.0;

    Get_projected_vars(millisecond, temp_balance, temp_stamina);

    auto out_offset = std::max(std::min(nrm(rng), 1.0), -1.0);
    out_offset *= timing_base
        + timing_balance_factor * (1.0 - balance)
        + timing_stamina_factor * (1.0 - stamina);
    out_offset *= timing_scale;

    return out_offset;
}

double Limb::Get_power_level_at_ms(int millisecond)
{
    auto temp_balance = 0.0;
    auto temp_stamina = 0.0;

    Get_projected_vars(millisecond, temp_balance, temp_stamina);

    return temp_balance * 0.9 + temp_stamina * 0.1;
}

/**
* Changes internal state and returns the velocity of the note.
*/
int Limb::Play_note(int millisecond, int velocity)
{
    Get_projected_vars(millisecond, balance, stamina);
    
    auto out_velocity = nrm(rng);
    out_velocity *= velocity_base
        + velocity_balance_factor * (1.0 - balance)
        + velocity_stamina_factor * (1.0 - stamina);
    out_velocity *= velocity_scale;
    out_velocity += velocity;
    if (out_velocity >= 127.0) {
        out_velocity = 127.0 - unr(rng) * 6.0;
    }

    if (balance < 0.35) {
        out_velocity *= balance / 0.35;
    }
    if (stamina < 0.35) {
        out_velocity *= stamina / 0.35;
    }

    balance -= balance_cost_base
        + balance_cost_velocity_mult * out_velocity / 127.0;
    stamina -= stamina_cost_base
        + stamina_cost_velocity_mult * out_velocity / 127.0;

    last_millisecond_played = millisecond;

    if (out_velocity < 0.0) {
        out_velocity = 1.0 + unr(rng) * 7.0;
    }

    return out_velocity;
}

void Limb::Get_projected_vars(int millisecond, double& balance, double& stamina)
{
    auto dt = static_cast<double>(millisecond - last_millisecond_played) / 1000.0;
    balance += balance_recovery_per_second * dt;
    if (balance > 1.0) {
        balance = 1.0;
    }
    stamina += stamina_recovery_per_second * dt;
    if (stamina > 1.0) {
        stamina = 1.0;
    }
}
