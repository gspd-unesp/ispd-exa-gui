#pragma once


class ItemConfiguration;
class Icon;
class Cloner;

class Component {
    public: 
        virtual ~Component() = default;
        virtual void showConfiguration() = 0;
        virtual Icon *getIcon() = 0;
        virtual ItemConfiguration *getConf() = 0;
        virtual Cloner *cloner() = 0;
};
