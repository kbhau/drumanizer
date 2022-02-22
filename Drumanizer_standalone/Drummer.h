#pragma once

#include "Limb.h"

class Drummer
{

public:
    double Get_offset(int key_number, int millisecond);
    double Play_note(int velocity, int millisecond);
    void Naturalise();

private:
    Limb dominant_hand;
    Limb off_hand;
    Limb dominant_leg;
    Limb off_leg;

    Limb* last_limb = nullptr;

private:
    Limb* Get_better_limb(Limb& dominant, Limb& off, int millisecond);
    Limb* Get_limb(int key_number, int millisecond);
};
