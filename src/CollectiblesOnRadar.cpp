#include "plugin.h"
#include "common.h"
#include "CHud.h" // CHud::SetHelpMessage
#include "CMenuManager.h" // FrontEndMenuManager.m_bDrawRadarOrMap
#include "CPickups.h"
#include "CRadar.h"
#include "CTimer.h" // CTimer::m_snTimeInMilliseconds
#include "ePickupType.h"

#include "Util.h"
#include "Settings.h"

enum eBlipMode // should be in CRadar.h
{
    BLIP_MODE_TRIANGULAR_UP = 0, // RADAR_TRACE_LOW
    BLIP_MODE_TRIANGULAR_DOWN,   // RADAR_TRACE_HIGH
    BLIP_MODE_SQUARE,            // RADAR_TRACE_NORMAL
};

class CollectiblesOnRadar { // VC
private:
    static bool s_modEnabled;
    static int s_keyPressTime;

public:
    CollectiblesOnRadar()
    {
        //AllocConsole();
        //FILE* f = new FILE;
        //freopen_s(&f, "CONOUT$", "w", stdout);

        plugin::Events::initRwEvent += []()
        {
            Settings::read();
        };

        plugin::Events::initGameEvent += []()
        {
            Util::initStoreList();
            Util::initUsjList();
        };

        //plugin::Events::shutdownRwEvent += []()
        //{
        //};

        plugin::Events::gameProcessEvent += []()
        {
            if (plugin::KeyPressed(Settings::s_keyCodeOnOff) && CTimer::m_snTimeInMillisecondsPauseMode - s_keyPressTime > 200)
            {
                s_modEnabled = !s_modEnabled;
                CHud::SetHelpMessage(s_modEnabled ? "Collectibles on radar ON" : "Collectibles on radar OFF", true, false);
                s_keyPressTime = CTimer::m_snTimeInMillisecondsPauseMode;

                if (s_modEnabled)
                {
                    Settings::read();
                }
            }
        };

        plugin::Events::drawBlipsEvent += []()
        {
            CPlayerPed* playa = FindPlayerPed();
            if (s_modEnabled && playa)
            {
                const bool ignoreRange = FrontEndMenuManager.m_bDrawRadarOrMap; // FrontEndMenuManager.m_bMenuActive
                const CVector& playaPos = FindPlayerCentreOfWorld_NoSniperShift();
                drawStores(playaPos, ignoreRange);
                drawPickups(playaPos, ignoreRange); // hidden packages, rampages
                drawUSJs(playaPos, ignoreRange);
            }
        };
    }

private:
    static void drawStores(const CVector& playaPos, bool ignoreRange)
    {
        if (!Settings::s_drawStores)
        {
            return;
        }

        static CVector2D radarSpace, screenSpace;

        bool drawStore = true;
        float nearestStore = 9999999.f;
        int indexStore = -1;

        for (unsigned int i = 0; i < (sizeof (Util::s_storeList) / sizeof (tStore)); ++i)
        {
            const bool enabled = (Util::s_storeList[i].done && !(*Util::s_storeList[i].done));
            
            if (enabled)
            {
                const CVector& storePos = Util::s_storeList[i].location;

                const float distance = DistanceBetweenPoints(CVector2D(playaPos.x, playaPos.y), CVector2D(storePos.x, storePos.y));
                if (distance < CRadar::m_radarRange || ignoreRange)
                {
                    CRadar::TransformRealWorldPointToRadarSpace(radarSpace, CVector2D(storePos.x, storePos.y));
                    //CRadar::LimitRadarPoint(radarSpace); // inside range already // returns distance
                    CRadar::TransformRadarPointToScreenSpace(screenSpace, radarSpace);

                    unsigned char mode = BLIP_MODE_TRIANGULAR_UP;
                    if (storePos.z - playaPos.z <= 2.0f)
                    {
                        if (storePos.z - playaPos.z < -4.0f) mode = BLIP_MODE_TRIANGULAR_DOWN;
                        else mode = BLIP_MODE_SQUARE;
                    }

                    drawStore = false;

                    CRadar::ShowRadarTraceWithHeight(screenSpace.x, screenSpace.y, 1,
                        Settings::s_colorStore.r, Settings::s_colorStore.g, Settings::s_colorStore.b, Settings::s_colorStore.a, mode);
                }
                else
                {
                    if (Settings::s_drawNearest)
                    {
                        if (drawStore && distance < nearestStore)
                        {
                            nearestStore = distance;
                            indexStore = i;
                        }
                    }
                }
            }
        }

        if (!Settings::s_drawNearest || ignoreRange)
        {
            return;
        }

        if (drawStore && indexStore >= 0)
        {
            const CVector& storePos = Util::s_storeList[indexStore].location;

            CRadar::TransformRealWorldPointToRadarSpace(radarSpace, CVector2D(storePos.x, storePos.y));
            CRadar::LimitRadarPoint(radarSpace);
            CRadar::TransformRadarPointToScreenSpace(screenSpace, radarSpace);

            unsigned char mode = BLIP_MODE_TRIANGULAR_UP;
            if (storePos.z - playaPos.z <= 2.0f)
            {
                if (storePos.z - playaPos.z < -4.0f) mode = BLIP_MODE_TRIANGULAR_DOWN;
                else mode = BLIP_MODE_SQUARE;
            }

            CRadar::ShowRadarTraceWithHeight(screenSpace.x, screenSpace.y, 1,
                Settings::s_colorStore.r, Settings::s_colorStore.g, Settings::s_colorStore.b, Settings::s_colorStore.a, mode);
        }
    }

    static void drawPickups(const CVector& playaPos, bool ignoreRange)
    {
        static CVector2D radarSpace, screenSpace;

        bool drawPackage = true; // draw the nearest pickup outside range
        bool drawRampage = true;

        float nearestPackage = 9999999.f; // nearest pickup distance
        float nearestRampage = 9999999.f;

        int indexPackage = -1; // index of the nearest pickup
        int indexRampage = -1;

        for (unsigned int i = 0; i < (sizeof (CPickups::aPickUps) / sizeof (CPickup)); i++) 
        {
            const short model = CPickups::aPickUps[i].nModelId;
            const unsigned char type = CPickups::aPickUps[i].bPickupType;
            const bool disabled = CPickups::aPickUps[i].bRemoved;

            if (!disabled
                && ((Settings::s_drawHiddenPackages && model == 410)
                    || (Settings::s_drawRampages && model == 383)
                    || (Settings::s_drawBribes && model == 375)
                    || (Settings::s_drawArmours && model == 368)
                    || (Settings::s_drawWeapons && model >= 258 && model <= 294) // TODO Find out the type of map weapons (not the ones dropped)
                    || (Settings::s_drawHealths && model == 366)))
            {
                const CVector& pickupPos = CPickups::aPickUps[i].vecPos;

                const float distance = DistanceBetweenPoints(CVector2D(playaPos.x, playaPos.y), CVector2D(pickupPos.x, pickupPos.y));
                if (distance < CRadar::m_radarRange || ignoreRange)
                {
                    CRadar::TransformRealWorldPointToRadarSpace(radarSpace, CVector2D(pickupPos.x, pickupPos.y));
                    //CRadar::LimitRadarPoint(radarSpace); // inside range already // returns distance
                    CRadar::TransformRadarPointToScreenSpace(screenSpace, radarSpace);

                    unsigned char mode = BLIP_MODE_TRIANGULAR_UP;
                    if (pickupPos.z - playaPos.z <= 2.0f)
                    {
                        if (pickupPos.z - playaPos.z < -4.0f) mode = BLIP_MODE_TRIANGULAR_DOWN;
                        else mode = BLIP_MODE_SQUARE;
                    }

                    CRGBA color;
                    switch (model)
                    {
                    case 410:
                        color = Settings::s_colorHiddenPackage;
                        drawPackage = false;
                        break;
                    case 383:
                        color = Settings::s_colorRampage;
                        drawRampage = false;
                        break;
                    case 375:
                        color = Settings::s_colorBribe;
                        break;
                    case 368:
                        color = Settings::s_colorArmour;
                        break;
                    case 366:
                        color = Settings::s_colorHealth;
                        break;
                    default:
                        color = Settings::s_colorWeapon;
                    }

                    CRadar::ShowRadarTraceWithHeight(screenSpace.x, screenSpace.y, 1, color.r, color.g, color.b, color.a, mode);
                }
                else
                {
                    if (Settings::s_drawNearest)
                    {
                        switch (model)
                        {
                        case 410: // hidden package
                            if (drawPackage && distance < nearestPackage)
                            {
                                nearestPackage = distance;
                                indexPackage = i;
                            }
                            break;
                        case 383: // rampage
                            if (drawRampage && distance < nearestRampage)
                            {
                                nearestRampage = distance;
                                indexRampage = i;
                            }
                            break;
                        }
                    }
                }
            }
        }

        if (!Settings::s_drawNearest || ignoreRange)
        {
            return;
        }

        if (drawPackage && indexPackage >= 0)
        {
            const CVector& pickupPos = CPickups::aPickUps[indexPackage].vecPos;

            CRadar::TransformRealWorldPointToRadarSpace(radarSpace, CVector2D(pickupPos.x, pickupPos.y));
            CRadar::LimitRadarPoint(radarSpace);
            CRadar::TransformRadarPointToScreenSpace(screenSpace, radarSpace);

            unsigned char mode = BLIP_MODE_TRIANGULAR_UP;
            if (pickupPos.z - playaPos.z <= 2.0f)
            {
                if (pickupPos.z - playaPos.z < -4.0f) mode = BLIP_MODE_TRIANGULAR_DOWN;
                else mode = BLIP_MODE_SQUARE;
            }

            CRadar::ShowRadarTraceWithHeight(screenSpace.x, screenSpace.y, 1,
                Settings::s_colorHiddenPackage.r, Settings::s_colorHiddenPackage.g, Settings::s_colorHiddenPackage.b, Settings::s_colorHiddenPackage.a, mode);
        }

        if (drawRampage && indexRampage >= 0)
        {
            const CVector& pickupPos = CPickups::aPickUps[indexRampage].vecPos;

            CRadar::TransformRealWorldPointToRadarSpace(radarSpace, CVector2D(pickupPos.x, pickupPos.y));
            CRadar::LimitRadarPoint(radarSpace);
            CRadar::TransformRadarPointToScreenSpace(screenSpace, radarSpace);

            unsigned char mode = BLIP_MODE_TRIANGULAR_UP;
            if (pickupPos.z - playaPos.z <= 2.0f)
            {
                if (pickupPos.z - playaPos.z < -4.0f) mode = BLIP_MODE_TRIANGULAR_DOWN;
                else mode = BLIP_MODE_SQUARE;
            }

            CRadar::ShowRadarTraceWithHeight(screenSpace.x, screenSpace.y, 1,
                Settings::s_colorRampage.r, Settings::s_colorRampage.g, Settings::s_colorRampage.b, Settings::s_colorRampage.a, mode);
        }
    }

    static void drawUSJs(const CVector& playaPos, bool ignoreRange)
    {
        if (!Settings::s_drawUSJs)
        {
            return;
        }

        static CVector2D radarSpace, screenSpace;

        bool drawUsj = true;
        float nearestUsj = 9999999.f;
        int indexUsj = -1;

        for (unsigned int i = 0; i < (sizeof (Util::s_usjList) / sizeof (tUsj)); ++i)
        {
            const bool enabled = (Util::s_usjList[i].done && !(*Util::s_usjList[i].done));

            if (enabled)
            {
                const CVector& usjPos = Util::s_usjList[i].location;

                const float distance = DistanceBetweenPoints(CVector2D(playaPos.x, playaPos.y), CVector2D(usjPos.x, usjPos.y));
                if (distance < CRadar::m_radarRange || ignoreRange)
                {
                    CRadar::TransformRealWorldPointToRadarSpace(radarSpace, CVector2D(usjPos.x, usjPos.y));
                    //CRadar::LimitRadarPoint(radarSpace); // inside range already // returns distance
                    CRadar::TransformRadarPointToScreenSpace(screenSpace, radarSpace);

                    unsigned char mode = BLIP_MODE_TRIANGULAR_UP;
                    if (usjPos.z - playaPos.z <= 2.0f)
                    {
                        if (usjPos.z - playaPos.z < -4.0f) mode = BLIP_MODE_TRIANGULAR_DOWN;
                        else mode = BLIP_MODE_SQUARE;
                    }

                    drawUsj = false;

                    CRadar::ShowRadarTraceWithHeight(screenSpace.x, screenSpace.y, 1,
                        Settings::s_colorUSJ.r, Settings::s_colorUSJ.g, Settings::s_colorUSJ.b, Settings::s_colorUSJ.a, mode);
                }
                else
                {
                    if (Settings::s_drawNearest)
                    {
                        if (drawUsj && distance < nearestUsj)
                        {
                            nearestUsj = distance;
                            indexUsj = i;
                        }
                    }
                }
            }
        }

        if (!Settings::s_drawNearest || ignoreRange)
        {
            return;
        }

        if (drawUsj && indexUsj >= 0)
        {
            const CVector& usjPos = Util::s_usjList[indexUsj].location;

            CRadar::TransformRealWorldPointToRadarSpace(radarSpace, CVector2D(usjPos.x, usjPos.y));
            CRadar::LimitRadarPoint(radarSpace);
            CRadar::TransformRadarPointToScreenSpace(screenSpace, radarSpace);

            unsigned char mode = BLIP_MODE_TRIANGULAR_UP;
            if (usjPos.z - playaPos.z <= 2.0f)
            {
                if (usjPos.z - playaPos.z < -4.0f) mode = BLIP_MODE_TRIANGULAR_DOWN;
                else mode = BLIP_MODE_SQUARE;
            }

            CRadar::ShowRadarTraceWithHeight(screenSpace.x, screenSpace.y, 1,
                Settings::s_colorUSJ.r, Settings::s_colorUSJ.g, Settings::s_colorUSJ.b, Settings::s_colorUSJ.a, mode);
        }
    }
} collectiblesOnRadarPlugin;

bool CollectiblesOnRadar::s_modEnabled = true;
int CollectiblesOnRadar::s_keyPressTime = 0;
