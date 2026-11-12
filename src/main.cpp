#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(NexusMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) {
            return false;
        }

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) {
            log::warn("NEXUS: bottom-menu was not found; skipping menu button.");
            return true;
        }

        auto icon = CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png");
        if (!icon) {
            log::warn("NEXUS: could not load the menu button sprite.");
            return true;
        }

        auto button = CCMenuItemSpriteExtra::create(
            icon,
            this,
            menu_selector(NexusMenuLayer::onNexusButton)
        );

        if (!button) {
            log::warn("NEXUS: failed to create menu button.");
            return true;
        }

        button->setID("nexus-open-button"_spr);
        menu->addChild(button);
        menu->updateLayout();

        return true;
    }

    void onNexusButton(CCObject*) {
        FLAlertLayer::create(
            "NEXUS MOD MENU",
            "<cy>Welcome to NEXUS.</c>\n\n"
            "<cg>PLAYER</c>  •  Player-related utilities\n"
            "<cg>LEVEL</c>  •  Level information tools\n"
            "<cg>EDITOR</c>  •  Editor workflow tools\n"
            "<cg>VISUALS</c>  •  Visual customization\n"
            "<cg>MISC</c>  •  General utilities\n\n"
            "This is the initial installable foundation. "
            "Feature controls will be added and tested in separate steps.",
            "CLOSE"
        )->show();
    }
};
