#pragma once

#include <Rose/Property/BooleanProperty.h>

class Settings {

    public:

        std::shared_ptr<BooleanProperty> showNormalsProperty;

        static Settings & Instance()
        {
            static Settings instance;
            return instance;
        }

        Settings() {
            showNormalsProperty = std::make_shared<BooleanProperty>(false);
        };

        bool getShowNormals() { return showNormalsProperty->getValue(); }

    public:

        void operator=(Settings const&)  = delete;
};
