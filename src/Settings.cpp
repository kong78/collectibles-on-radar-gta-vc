#include "Settings.h"

#include "IniReader.h"

const std::string Settings::MAIN("MAIN");
const std::string Settings::COLORS("COLORS");
const std::string Settings::EXTRA("EXTRA");

// Default values

const unsigned int Settings::KEY_CODE_ON_OFF = VK_F12; // default ON/OFF key
const CRGBA Settings::COLOR_STORE(134, 96, 96);
const CRGBA Settings::COLOR_HIDDEN_PACKAGE(1, 154, 6);
const CRGBA Settings::COLOR_RAMPAGE(255, 153, 204);
const CRGBA Settings::COLOR_USJ(109, 94, 255);
const CRGBA Settings::COLOR_DEFAULT(255, 255, 255);

// [MAIN]

unsigned int Settings::s_keyCodeOnOff = Settings::KEY_CODE_ON_OFF;
bool Settings::s_drawStores = true;
bool Settings::s_drawHiddenPackages = true;
bool Settings::s_drawRampages = true;
bool Settings::s_drawUSJs = true;
bool Settings::s_drawNearest = true;

// [COLORS]

CRGBA Settings::s_colorStore(Settings::COLOR_STORE);
CRGBA Settings::s_colorHiddenPackage(Settings::COLOR_HIDDEN_PACKAGE);
CRGBA Settings::s_colorRampage(Settings::COLOR_RAMPAGE);
CRGBA Settings::s_colorUSJ(Settings::COLOR_USJ);

// [EXTRA]

bool Settings::s_drawBribes = false;
bool Settings::s_drawArmours = false;
bool Settings::s_drawWeapons = false;
bool Settings::s_drawHealths = false;
CRGBA Settings::s_colorBribe(Settings::COLOR_DEFAULT);
CRGBA Settings::s_colorArmour(Settings::COLOR_DEFAULT);
CRGBA Settings::s_colorWeapon(Settings::COLOR_DEFAULT);
CRGBA Settings::s_colorHealth(Settings::COLOR_DEFAULT);

void Settings::read()
{
    CIniReader iniReader("");

    // [MAIN]

    s_keyCodeOnOff = static_cast<unsigned int>(iniReader.ReadInteger(MAIN, "on_off_key", static_cast<int>(KEY_CODE_ON_OFF)));

    s_drawStores = iniReader.ReadBoolean(MAIN, "show_stores", true);
    s_drawHiddenPackages = iniReader.ReadBoolean(MAIN, "show_packages", true);
    s_drawRampages = iniReader.ReadBoolean(MAIN, "show_rampages", true);
    s_drawUSJs = iniReader.ReadBoolean(MAIN, "show_usjs", true);

    s_drawNearest = iniReader.ReadBoolean(MAIN, "show_nearest", true);

    // [COLORS]

    s_colorStore.Set(toRGBA(iniReader.ReadString(COLORS, "color_store", ""), COLOR_STORE.ToInt()));
    s_colorHiddenPackage.Set(toRGBA(iniReader.ReadString(COLORS, "color_package", ""), COLOR_HIDDEN_PACKAGE.ToInt()));
    s_colorRampage.Set(toRGBA(iniReader.ReadString(COLORS, "color_rampage", ""), COLOR_RAMPAGE.ToInt()));
    s_colorUSJ.Set(toRGBA(iniReader.ReadString(COLORS, "color_usj", ""), COLOR_USJ.ToInt()));

    // [EXTRA]

    s_drawBribes = iniReader.ReadBoolean(EXTRA, "show_bribes", false);
    s_drawArmours = iniReader.ReadBoolean(EXTRA, "show_armours", false);
    s_drawWeapons = iniReader.ReadBoolean(EXTRA, "show_weapons", false);
    s_drawHealths = iniReader.ReadBoolean(EXTRA, "show_healths", false);

    s_colorBribe.Set(toRGBA(iniReader.ReadString(EXTRA, "color_bribe", ""), COLOR_DEFAULT.ToInt()));
    s_colorArmour.Set(toRGBA(iniReader.ReadString(EXTRA, "color_armour", ""), COLOR_DEFAULT.ToInt()));
    s_colorWeapon.Set(toRGBA(iniReader.ReadString(EXTRA, "color_weapon", ""), COLOR_DEFAULT.ToInt()));
    s_colorHealth.Set(toRGBA(iniReader.ReadString(EXTRA, "color_health", ""), COLOR_DEFAULT.ToInt()));
}

unsigned int Settings::toRGBA(const std::string& str, unsigned int defaultValue)
{
    //static const std::regex patternRGBA("^#[A-Fa-f0-9]{6,8}$");

    // if (std::regex_match(str, patternRGBA))
    try
    {
        char color[9] = "ffffffff";
        str.copy(color, str.size() - 1, 1);
        return static_cast<unsigned int>(std::stoul(color, nullptr, 16));
    }
    catch (...)
    {}

    return defaultValue;
}
