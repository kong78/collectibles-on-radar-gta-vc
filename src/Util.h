#pragma once

#include "CVector.h"
#include "CTheScripts.h"

struct tStore
{
    int* done {};
    CVector location {};
};

struct tUsj
{
    int* done {};
    CVector location {};
};

class Util
{
public:
    static const CVector DEFAULT_STORE_LOCATIONS[15];
    static const CVector DEFAULT_USJ_LOCATIONS[36];

    static tStore s_storeList[15];
    static tUsj s_usjList[36];

public:
    static void initStoreList();
    static void initUsjList();

    static unsigned char* findAddressScriptSpace(const unsigned char*, size_t, ptrdiff_t = 0, size_t = 0, bool = true);

    //template<typename T = unsigned char>
    //static T* getVariableScriptSpace(size_t index)
    //{
    //    return reinterpret_cast<T*>(&CTheScripts::ScriptSpace[index]);
    //}
};
