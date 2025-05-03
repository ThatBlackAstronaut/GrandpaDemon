#ifndef LISTMANAGER_H
#define LISTMANAGER_H

#include <vector>
#include <string>
#include <sstream>
#include <cstddef>
#include <cstdlib>

using namespace geode::prelude;

class ListManager {
public:
    static std::vector<int> demonIDList;
    static bool firstTimeOpen;
    static int filterType;
    static bool isSupremeSearching;

    static void parseRequestString(std::string str) {
        size_t isFound = str.find("_id");

        while (isFound != std::string::npos) {
            str = str.substr(isFound + 5);
            size_t findBracket = str.find("}");

            int id = std::stoi(str.substr(0, findBracket));
            demonIDList.push_back(id);

            isFound = str.find("_id");
        }
    }

    static int getPositionOfID(int id) {
        for (unsigned int i = 0; i < demonIDList.size(); i++) {
            if (demonIDList[i] == id) return i;
        }
        return -1;
    }

    static CCSprite* getSpriteFromPosition(int pos, bool hasText) {
        if (pos <= 499 && pos > 249) {
            return CCSprite::createWithSpriteFrameName(
                hasText ? "GrD_demon0_text.png"_spr : "GrD_demon0.png"_spr);
        }
        if (pos <= 249 && pos > 149) {
            return CCSprite::createWithSpriteFrameName(
                hasText ? "GrD_demon1_text.png"_spr : "GrD_demon1.png"_spr);
        }
        if (pos <= 149 && pos > 74) {
            return CCSprite::createWithSpriteFrameName(
                hasText ? "GrD_demon2_text.png"_spr : "GrD_demon2.png"_spr);
        }
        if (pos <= 74 && pos > 24) {
            return CCSprite::createWithSpriteFrameName(
                hasText ? "GrD_demon3_text.png"_spr : "GrD_demon3.png"_spr);
        }
        if (pos <= 24 && pos > 0) {
            return CCSprite::createWithSpriteFrameName(
                hasText ? "GrD_demon4_text.png"_spr : "GrD_demon4.png"_spr);
        }
        if (pos == 0) {
            if (Mod::get()->getSettingValue<bool>("grandpa-demon-disable")) {
                return CCSprite::createWithSpriteFrameName(
                    hasText ? "GrD_demon4_text.png"_spr : "GrD_demon4.png"_spr);
            } else {
                return CCSprite::createWithSpriteFrameName(
                    hasText ? "GrD_demon5_text.png"_spr : "GrD_demon5.png"_spr);
            }
        }
        return nullptr;
    }

    static GJSearchObject* getSearchObject(int upper, int lower) {
        std::stringstream download;
        bool first = true;

        if (!(upper == 0 && lower == 0)) {
            for (int i = upper; i > lower; i--) {
                if (!first) {
                    download << ",";
                }
                download << std::to_string(demonIDList.at(i));
                first = false;
            }
        } else {
            download << std::to_string(demonIDList.at(0));
        }

        download << "&gameVersion=22";
        return GJSearchObject::create(SearchType::Type19, download.str());
    }
};

std::vector<int> ListManager::demonIDList;
bool ListManager::firstTimeOpen = true;
int ListManager::filterType = 0;
bool ListManager::isSupremeSearching = false;

#endif
