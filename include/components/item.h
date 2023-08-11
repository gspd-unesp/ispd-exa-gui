#pragma once

class Icon;

class Item {
    public: 
        virtual void showConfiguration() = 0;
        virtual Icon *getIcon() = 0;
};
