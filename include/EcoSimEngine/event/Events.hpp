#pragma once
#include <string>

namespace Event {

    enum class GUICommand {
        App_Quit,
        Sim_TogglePause,
        File_NewSimulation,
        File_LoadSimulation,
        File_SaveSimulation,
        View_ShowMenu,
        None
    };

    struct SceneRequestEvent {
        std::string key;
        explicit SceneRequestEvent(std::string k) : key(std::move(k)) {}
    };

} // namespace Event