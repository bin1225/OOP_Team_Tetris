#include "Item.h"

Item::Item(const std::string& itemName, const std::string& desc)
    : name(itemName), description(desc) {
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}
