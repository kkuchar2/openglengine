#pragma once

struct MouseButtonInfo {
    int button;
    int action;
    int mods;

    MouseButtonInfo() {
        button = -1;
        action = -1;
        mods = -1;
    }

    bool operator==(const MouseButtonInfo & info) const {
        return button == info.button && action == info.action && mods == info.mods;
    }
};