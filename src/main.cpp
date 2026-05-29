/*
 * File: main.cpp
 * Author: 1therealcloud
 * Last Update: 2026-05-29
 * Description: SHA-256 string hashing plugin for SA-MP.
 */
#include "amx/amx.h"
#include "plugincommon.h"

#include "picosha2.h"

#include "build-number.h"

#include <string>
#include <vector>
#include <cstring>

typedef void (*logprintf_t)(char* format, ...);
logprintf_t logprintf;
extern void *pAMXFunctions;

cell AMX_NATIVE_CALL Crypto_SHA256(AMX* amx, cell* params)
{
    if (params[0] < 3) return 0;

    char* input = nullptr;
    amx_StrParam(amx, params[1], input);
    if (!input) return 0;

    size_t input_len = std::strlen(input);
    std::string hash = picosha2::hash256_hex_string(input, input + input_len);

    cell* dest_addr = nullptr;
    if (amx_GetAddr(amx, params[2], &dest_addr) != AMX_ERR_NONE) return 0;

    size_t max_len = static_cast<size_t>(params[3]);
    if (max_len == 0) return 0;

    size_t copy_len = (hash.length() < max_len - 1) ? hash.length() : max_len - 1;
    for (size_t i = 0; i < copy_len; ++i) {
        dest_addr[i] = static_cast<cell>(static_cast<unsigned char>(hash[i]));
    }
    dest_addr[copy_len] = 0;

    return 1;
}

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData) {
    pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
    logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];
    logprintf("[SHA256] Plugin loaded successfully. Build number: %d", calculate_build_number());
    return true;
}

AMX_NATIVE_INFO PluginNatives[] = {
    {"Crypto_SHA256", Crypto_SHA256},
    {0, 0}
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx) {
    return amx_Register(amx, PluginNatives, -1);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx) {
    return AMX_ERR_NONE;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    logprintf("[SHA256] Plugin unloaded.");
}
