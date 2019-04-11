#pragma once

struct KeyInfo {
    std::vector<bool> pressedKeys;

    KeyInfo() {
        for (int i = 0; i < 349; i++) {
            pressedKeys.push_back(false);
        }
    }

    bool operator==(const KeyInfo & info) const {
        return false;
    }
};