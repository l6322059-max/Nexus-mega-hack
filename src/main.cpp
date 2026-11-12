#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class NexusPopup : public geode::Popup {
protected:
    int m_category = 0;
    bool m_states[5][3] = {};

    static constexpr const char* CATEGORIES[5] = {
        "PLAYER", "LEVEL", "EDITOR", "VISUALS", "MISC"
    };

    static constexpr const char* FEATURES[5][3] = {
        {"Practice tools", "Show hitboxes (UI)", "Player info"},
        {"Level info", "Object counter", "Attempt counter"},
        {"Editor helpers", "Grid overlay (UI)", "Object info"},
        {"Dark interface", "Compact labels", "Menu animations"},
        {"Performance info", "Notifications", "Reset menu"}
    };

    void rebuildContent() {
        auto content = m_mainLayer->getChildByID("nexus-content"_spr);
        if (content) content->removeFromParent();

        auto panel = CCNode::create();
        panel->setID("nexus-content"_spr);
        m_mainLayer->addChild(panel);

        auto heading = CCLabelBMFont::create(CATEGORIES[m_category], "goldFont.fnt");
        heading->setScale(0.55f);
        heading->setPosition({180.f, 150.f});
        panel->addChild(heading);

        auto hint = CCLabelBMFont::create("Tap a row to switch its menu state", "chatFont.fnt");
        hint->setScale(0.42f);
        hint->setPosition({180.f, 128.f});
        panel->addChild(hint);

        for (int i = 0; i < 3; ++i) {
            auto title = CCLabelBMFont::create(FEATURES[m_category][i], "bigFont.fnt");
            title->setAnchorPoint({0.f, 0.5f});
            title->setScale(0.43f);
            title->setPosition({55.f, 99.f - i * 34.f});
            panel->addChild(title);

            auto stateText = m_states[m_category][i] ? "ON" : "OFF";
            auto button = CCMenuItemExt::createSpriteExtra(
                ButtonSprite::create(stateText, "goldFont.fnt", "GJ_button_04.png", 0.65f),
                [this, i](CCMenuItemSpriteExtra*) {
                    m_states[m_category][i] = !m_states[m_category][i];
                    this->rebuildContent();
                }
            );
            auto menu = CCMenu::create();
            menu->addChild(button);
            menu->setPosition({292.f, 99.f - i * 34.f});
            panel->addChild(menu);
        }

        auto note = CCLabelBMFont::create("NEXUS  •  UI PREVIEW BUILD", "chatFont.fnt");
        note->setScale(0.38f);
        note->setPosition({180.f, 12.f});
        panel->addChild(note);
    }

    bool init() {
        if (!geode::Popup::init(360.f, 220.f))
            return false;

        this->setTitle("NEXUS MOD MENU");
        auto subtitle = CCLabelBMFont::create("MODULAR CONTROL CENTER", "chatFont.fnt");
        subtitle->setScale(0.45f);
        subtitle->setPosition({180.f, 184.f});
        m_mainLayer->addChild(subtitle);

        const char* names[5] = {"PLAYER", "LEVEL", "EDITOR", "VISUALS", "MISC"};
        for (int i = 0; i < 5; ++i) {
            auto tab = CCMenuItemExt::createSpriteExtra(
                ButtonSprite::create(names[i], "goldFont.fnt", "GJ_button_05.png", 0.55f),
                [this, i](CCMenuItemSpriteExtra*) {
                    m_category = i;
                    this->rebuildContent();
                }
            );
            auto menu = CCMenu::create();
            menu->addChild(tab);
            menu->setPosition({48.f + i * 66.f, 164.f});
            m_mainLayer->addChild(menu);
        }

        rebuildContent();
        return true;
    }

public:
    static NexusPopup* create() {
        auto ret = new NexusPopup();
        if (ret->init()) {
            ret->autorelease();
            return ret;
        }
        delete ret;
        return nullptr;
    }
};

class $modify(NexusMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init())
            return false;

        auto menu = this->getChildByID("bottom-menu");
        if (!menu) {
            log::warn("NEXUS: bottom-menu was not found.");
            return true;
        }

        auto icon = CCSprite::createWithSpriteFrameName("GJ_likeBtn_001.png");
        if (!icon) {
            log::warn("NEXUS: menu icon could not be loaded.");
            return true;
        }

        auto button = CCMenuItemSpriteExtra::create(
            icon, this, menu_selector(NexusMenuLayer::onNexusButton)
        );
        if (!button)
            return true;

        button->setID("nexus-open-button"_spr);
        menu->addChild(button);
        menu->updateLayout();
        return true;
    }

    void onNexusButton(CCObject*) {
        auto popup = NexusPopup::create();
        if (popup)
            popup->show();
        else
            FLAlertLayer::create("NEXUS", "Could not open the menu.", "OK")->show();
    }
};
