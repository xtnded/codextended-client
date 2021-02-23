#pragma once
#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <algorithm>
#include <functional>
#include "discord/discord_rpc.h"
#include "discord/discord_register.h"

void CL_DiscordInitialize();
void CL_DiscordFrame();
void CL_DiscordShutdown();