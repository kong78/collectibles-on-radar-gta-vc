#include "Util.h"

// TODO Should I over-engineer this by searching for those coords directly from the SCM script in CTheScripts::ScriptSpace?
// GOD, NO! F*** THAT!!!

// Hardcoded values from ROBBING.SC (first 12 coords) and AMMU.SC (last 3 coords)
const CVector Util::DEFAULT_STORE_LOCATIONS[15] = {
    { -858.8f, -632.66f, 10.6f }, // Deli // HAVANA
    { -854.3f, 850.0f, 10.6f },   // Jewllers // DOWNTOW
    { -830.4f, 741.9f, 10.6f },   // Chemist // DOWNTOWN
    { -846.6f, -72.6f, 10.8f },   // Chemist // HAITI
    { 379.9f, 210.2f, 10.6f },    // Jewllers // VICEPOINT
    { 383.2f, 759.7f, 11.0f },    // Chemist // VICEPOINT
    { 450.0f, 782.5f, 12.2f },    // 7-11 // VICEPOINT
    { 352.7f, 1111.3f, 24.5f },   // Music store // MALL
    { 423.5f, 1039.4f, 18.1f },   // Gash // MALL
    { 468.7f, 1206.6f, 19.0f },   // Jewllers // MALL
    { -1167.1f, -615.8f, 11.0f }, // Cuban Cafe // HAVANA
    { -1192.2f, -323.7f, 11.1f }, // Laundrete // HAVANA
    { 202.4f, -471.1f, 10.1f },   // HARDWARE STORE OCEAN BEACH // WASHINGTON BEACH
//  { 366.1f, 1052.2f, 18.2f },   // NOTE It's an Ammu-Nation, cannot be robbed (and uses the same flag as the MALL one bellow)
    { 364.5f, 1074.3f, 18.0f },   // HARDWARE STORE SHOPPING MALL // MALL
    { -963.8f, -692.3f, 10.3f },  // HARDWARE STORE LITTLE HAVANA // HAVANA
};
// Hardcoded values from USJ.SC (all 36 coords) indexed from 1 to 36
const CVector Util::DEFAULT_USJ_LOCATIONS[36] = {
    { -1487.781f, -1044.546f, 18.707f - 3.f },  // OVER WESTERN BOARDING TUNNEL FROM EAST
    { -1352.695f, -755.212f, 28.673f - 4.f },   // JUMP ONTO TERMINAL ROOF FROM SURFER DUDE BILL BOARD
    { -1216.49f, -911.833f, 19.0f - 3.f },      // BOARDING STAIRS OVER ROAD ONTO BUILDING
    { -1252.139f, -1054.685f, 22.016f - 3.f },  // HUGE RAMP AT END OF RUNWAY ONTO ROAD
    { -1551.685f, -1075.674f, 19.121f - 2.5f }, // OVER WESTERN BOARDING TUNNEL FROM WEST
    { -1595.712f, -1272.881f, 19.068f - 2.5f }, // OVER RED RADAR BUILDING FROM BORADING STAIRS
    { -1553.337f, -1230.952f, 17.194f - 2.5f }, // OVER RED RADAR BUILDING FROM SIGN
    { -1340.022f, -998.257f, 19.115f - 3.f },   // OVER EASTERN BOARDING TUNNEL
    { 24.721f, 897.801f, 25.103f - 2.5f },      // FROM ROOF INTO PORN STUDIO
    { 317.2051f, -223.2012f, 42.3731f - 2.6f }, // OFF THE TOP OF THE BUILDING SITE
    { -674.345f, 1162.422f, 29.916f - 2.5f },   // INFRONT OF AMMU UP STAIRS OVER STREET INTO HOG TIED
    { -529.84f, 830.062f, 98.717f - 3.f },      // OUT OF HIGHRISE INTO HOLE IN OPPOSIT HIGHRISE
    { -839.022f, 1153.526f, 31.94f - 2.5f },    // G-SPOT OVER STREET FROM HOSPITAL
    { -312.447f, 1109.196f, 47.741f - 2.5f },   // ON TO THE ROOF WITH THE G-SPOTLIGHT
    { -1011.583f, -30.098f, 15.181f - 2.5f },   // WOODEN RAMP BEHIND SHITTY LITTLE BUILDINGS NEAR AUNTIE
    { -942.702f, -114.506f, 15.181f - 2.5f },   // OVER DRIED OUT CANAL/AQUADUCT
    { -900.789f, 260.804f, 15.915f - 2.5f },    // ONTO ROOF WITH HAITI HELI CHECKPOINT
    { -1041.895f, -569.323f, 21.855f - 2.5f },  // JUMP ACROSS THE STREET FROM THE ROOF - EAST FROM THE CUBANS PLACE
    { 208.993f, -963.672f, 19.967f - 2.5f },    // JUMP FROM THE MALL ACROSS ROAD AND ROOF OFF VENTS
    { 46.115f, -964.415f, 25.883f - 2.5f },     // MALL
    { 435.8542f, -334.3212f, 15.8977f - 3.0f }, // SOUTH DOWN ROAD FROM MALIBU OVER BRIDGE
    { 110.481f, -1230.6f, 35.67f - 2.5f },      // OUT OF THE MULTISTOREY CARPARK
    { 7.435f, -1245.895f, 17.752f - 3.5f },     // GAS STATION
    { 9.103f, -1326.505f, 20.361f - 2.5f },     // PINK ROOF SOUTH FROM GAS STATION
    { -321.028f, -1379.498f, 10.929f - 3.0f },  // COLONELS JETTY SOUTH
    { -321.028f, -1276.589f, 10.929f - 3.0f },  // COLONELS JETTY
    { 218.05f, -1152.0f, 12.84f - 2.5f },       // PALLETS OVER WIDE ALLEY BEHIND OCEAN DRIVE
    { 259.056f, -945.833f, 12.84f - 2.f },      // PALLETS OVER ROAD BEHIND OCEAN DRIVE
    { 444.5f, -118.4f, 16.0f - 3.f },           // MALIBU
    { 284.4732f, -494.1143f, 16.0f - 3.f },     // DIRT MOUND IN CARPARK OVER RIVER BY COPSHOP
    { 370.79f, -709.863f, 19.895f - 3.f },      // UP STAIRS IN ALLEY BEHIND OCEAN DRIVE
    { 461.589f, -522.23f, 18.931f - 3.f },      // STAIRS GOING WEST AT GUARDIAN ANGELS
    { 454.105f, -504.736f, 18.931f - 3.f },     // STAIRS GOING SOUTH AT GARDIAN ANGEL
    { 460.91f, -383.362f, 14.222f - 3.f },      // WOODEN RAMP AT END OF BUILDINGS SOUTH FROM MALIBU
    { 259.041f, -480.608f, 14.688f - 4.f },     // OVER RIVER NEXT TO COP SHOP
    { -346.818f, -290.741f, 12.926f - 3.f },    // IN GARDEN UP STAIRS
};

tStore Util::s_storeList[15];
tUsj Util::s_usjList[36];

void Util::initStoreList()
{
    // Initializing default values
    for (size_t i = 0; i < (sizeof (Util::s_storeList) / sizeof (tStore)); ++i)
    {
        Util::s_storeList[i].done = nullptr;
        if (i < (sizeof (Util::DEFAULT_STORE_LOCATIONS) / sizeof (CVector)))
            Util::s_storeList[i].location = Util::DEFAULT_STORE_LOCATIONS[i];
    }

    // NOTE Should I try to find the coords this way too? Nope!

    // Trying to search for the 'robbed_shop_1' variables in ScriptSpace (for the first 12 coords in ROBBING.SC)
    unsigned char patternStore1[] = { 0xA4, 0x03, 0x53, 0x48, 0x4F, 0x50, 0x53, 0x00 }; // "SCRIPT_NAME SHOPS\0"
    unsigned char* pPatternStore1 = Util::findAddressScriptSpace(patternStore1, sizeof (patternStore1));
    if (pPatternStore1)
    {
        // wildcards:                      {                                 ??    ??          ??    ??    ??    ?? }
        unsigned char patternStoreVars[] = { 0x51, 0x00, 0x04, 0x00, 0x02, 0xD0, 0x17, 0x01, 0xA0, 0x15, 0xFF, 0xFF }; // "return; $1524 = -60000"
        size_t start = (pPatternStore1 - &CTheScripts::ScriptSpace[0]) - 1;
        // offset = 84 so I skip to the robbed_shop_1 variable
        unsigned char* pPatternStoreVars = Util::findAddressScriptSpace(patternStoreVars, sizeof (patternStoreVars), 2 + 79 + 3, start, false);
        if (pPatternStoreVars)
        {
            for (size_t i = 0; i < 12; ++i)
            {
                size_t ssIdx = *((short*) (pPatternStoreVars + 7 * i)); // 6176, ..., 6220
                Util::s_storeList[i].done = (int*) &CTheScripts::ScriptSpace[ssIdx];
            }
        }
    }

    // Trying to search for the 'robbed_hardshop_1' variables in ScriptSpace (for the last 3 coords in AMMU.SC)
    unsigned char patternStore2[] = { 0xA4, 0x03, 0x41, 0x4D, 0x4D, 0x55, 0x00 }; // "SCRIPT_NAME AMMU\0"
    unsigned char* pPatternStore2 = Util::findAddressScriptSpace(patternStore2, sizeof (patternStore2));
    if (pPatternStore2)
    {
        // wildcards:                      {                                 ??    ??          ?? }
        unsigned char patternStoreVars[] = { 0x4E, 0x00, 0x04, 0x00, 0x02, 0x6C, 0x0D, 0x04, 0x00 }; // "terminate_this_script; $859 = 0"
        size_t start = (pPatternStore2 - &CTheScripts::ScriptSpace[0]) - 1;
        // offset = 212 so I skip to the robbed_shop_1 variable
        unsigned char* pPatternStoreVars = Util::findAddressScriptSpace(patternStoreVars, sizeof (patternStoreVars), 2 + 207 + 3, start, false);
        if (pPatternStoreVars)
        {
            for (size_t i = 0; i < 3; ++i)
            {
                size_t ssIdx = *((short*) (pPatternStoreVars + 7 * i)); // 3544, 3548, 3552
                Util::s_storeList[12 + i].done = (int*) &CTheScripts::ScriptSpace[ssIdx];
            }
        }
    }
}

void Util::initUsjList()
{
    // Initializing default values
    for (size_t i = 0; i < (sizeof (Util::s_usjList) / sizeof (tUsj)); ++i)
    {
        Util::s_usjList[i].done = nullptr;
        if (i < (sizeof (Util::DEFAULT_USJ_LOCATIONS) / sizeof (CVector)))
            Util::s_usjList[i].location = Util::DEFAULT_USJ_LOCATIONS[i];
    }

    // NOTE Should I try to find the coords this way too? Nope!

    // Trying to search for the 'flag_usj1_passed' variables in ScriptSpace
    unsigned char patternUsj[] = { 0xA4, 0x03, 0x55, 0x53, 0x4A, 0x00 }; // pattern: "SCRIPT_NAME USJ\0"
    unsigned char* pPatternUsj = Util::findAddressScriptSpace(patternUsj, sizeof (patternUsj));
    if (pPatternUsj)
    {
        // wildcards:                    {                                 ??    ??             }
        unsigned char patternUsjVars[] = { 0x4E, 0x00, 0x04, 0x00, 0x02, 0x6c, 0x0c, 0x04, 0x00 }; // "terminate_this_script; $795 = 0"
        size_t start = (pPatternUsj - &CTheScripts::ScriptSpace[0]) - 1;
        // offset = 5 so I skip to the flag_usj1_passed variable
        unsigned char* pPatternUsjVars = Util::findAddressScriptSpace(patternUsjVars, sizeof (patternUsjVars), 2 + 3, start, false);
        if (pPatternUsjVars)
        {
            for (size_t i = 0; i < (sizeof (Util::s_usjList) / sizeof (tUsj)); ++i)
            {
                size_t ssIdx = *((short*) (pPatternUsjVars + 7 * i)); // 3180, 3184, ..., 3320
                Util::s_usjList[i].done = (int*) &CTheScripts::ScriptSpace[ssIdx];
            }
        }
    }
}

unsigned char* Util::findAddressScriptSpace(const unsigned char* pattern, size_t patternSize, ptrdiff_t offset, size_t start, bool forward)
{
    if (patternSize <= 0 || patternSize > sizeof (CTheScripts::ScriptSpace))
        return nullptr;

    if (forward)
    {
        for (size_t i = start; i <= sizeof (CTheScripts::ScriptSpace) - patternSize; ++i)
        {
            ptrdiff_t offsetIndex = static_cast<ptrdiff_t>(i) + offset;
            if (std::memcmp(&CTheScripts::ScriptSpace[i], pattern, patternSize) == 0)
            {
                if (offsetIndex >= 0 && offsetIndex < static_cast<ptrdiff_t>(sizeof (CTheScripts::ScriptSpace)))
                {
                    return &CTheScripts::ScriptSpace[offsetIndex];
                }
                else
                {
                    return nullptr;
                }
            }
        }
    }
    else
    {
        if (start > sizeof (CTheScripts::ScriptSpace) - patternSize)
            start = sizeof (CTheScripts::ScriptSpace) - patternSize;

        for (int i = static_cast<int>(start); i >= 0; --i)
        {
            ptrdiff_t offsetIndex = static_cast<ptrdiff_t>(i) + offset;
            if (std::memcmp(&CTheScripts::ScriptSpace[i], pattern, patternSize) == 0)
            {
                if (offsetIndex >= 0 && offsetIndex < static_cast<ptrdiff_t>(sizeof (CTheScripts::ScriptSpace)))
                {
                    return &CTheScripts::ScriptSpace[offsetIndex];
                }
                else
                {
                    return nullptr;
                }
            }
        }
    }

    return nullptr;
}
