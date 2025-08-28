#pragma once

#include <string>
#include <unordered_map>
#include <algorithm>
#include <iostream>

enum class GUICommand {
    App_Quit,
    Sim_TogglePause,
    File_NewSimulation,
    File_LoadSimulation,
    File_SaveSimulation,
    View_ShowMenu,
    None
};
