#pragma once

#include <CRGBA.h>

class Settings
{
public:
    static const std::string MAIN;
    static const std::string COLORS;
    static const std::string EXTRA;

    // Default values

    static const unsigned int KEY_CODE_ON_OFF;
    static const CRGBA COLOR_STORE;
    static const CRGBA COLOR_HIDDEN_PACKAGE;
    static const CRGBA COLOR_RAMPAGE;
    static const CRGBA COLOR_USJ;
    static const CRGBA COLOR_DEFAULT;

    // [MAIN]

    static unsigned int s_keyCodeOnOff;
    static bool s_drawStores;
    static bool s_drawHiddenPackages;
    static bool s_drawRampages;
    static bool s_drawUSJs;
    static bool s_drawNearest;

    // [COLORS]

    static CRGBA s_colorStore;
    static CRGBA s_colorHiddenPackage;
    static CRGBA s_colorRampage;
    static CRGBA s_colorUSJ;

    // [EXTRA]

    static bool s_drawBribes;
    static bool s_drawArmours;
    static bool s_drawWeapons;
    static bool s_drawHealths;
    static CRGBA s_colorBribe;
    static CRGBA s_colorArmour;
    static CRGBA s_colorWeapon;
    static CRGBA s_colorHealth;
    static bool s_enabledOnStartup;
    static bool s_drawDroppedWeapons;

public:
    static void read();
    static unsigned int toRGBA(const std::string& str, unsigned int defaultValue);
};
