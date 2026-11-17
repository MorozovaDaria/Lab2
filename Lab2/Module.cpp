#include <stdexcept>
#include <string>
#include <algorithm>
#include "Module.h"
#include "Station.h"
#include "Damage.h"
#include "ModuleEvent.h"
#include "Types.h"

int Module::nextId_ = 1;
Module::Module(std::string name, int effectiveness, int endurance, int energy, int capacity) : name_(name), effectiveness_(effectiveness), durability_(endurance), energyConsumption_(energy), capacity_(capacity), isBlocked_(false)
{
	ID_ = nextId_++;
	condition_ = "выключен";
	if (effectiveness > 100 || effectiveness < 0) {
		throw std::invalid_argument("Error");
	}
}
int Module::getID() const {
	return ID_;
}
std::string Module::getName() const {
	return name_;
}
int Module::getEffectiveness() const {
	return effectiveness_;
}
std::string Module::getCondition() const {
	return condition_;
}
Durability& Module::getDurability() {
	return durability_;
}
EnergyConsumption& Module::getEnergyConsumption() {
	return energyConsumption_;
}
Capacity& Module::getCapacity() {
	return capacity_;
}
void Module::activate() {
	condition_ = "включен";
}
void Module::deactivate() {
	condition_ = "выключен";
}
void Module::setState(const std::string& newState) {
	if (newState == "включен" || newState == "выключен" || newState == "авария" || newState == "ремонт") {
		condition_ = newState;
	}
	else {
		throw std::invalid_argument("Error");
	}
}
void Module::setEffectiveness(int newEff) {
	if (newEff > 100 || newEff < 0) {
		throw std::invalid_argument("Error");
	}
	effectiveness_ = newEff;
}
void Module::moveToIndex(Station& station, size_t currentIndex, size_t newIndex) {
	station.moveModule(currentIndex, newIndex);
}

//изменения 2 лаба
void Module::subscribe(IObserver* observer) {
	if (observer != nullptr) {
		observers_.push_back(observer);
	}
}
void Module::unsubscribe(IObserver* observer) {
	observers_.erase(
		std::remove(observers_.begin(), observers_.end(), observer),
		observers_.end()
	);
}
void Module::notify(const ModuleEvent& event) {
	for (IObserver* observer : observers_) {
		if (observer != nullptr) {
			observer->onModuleEvent(event);
		}
	}
}
Module& operator-(Module& module, const Damage& damage) {
	if (module.getIsBlocked()) {
		return module;
	}
	int amount = static_cast<int>(damage.getAmount());
	module.durability_.decrease(amount);

	module.notify(ModuleEvent(EventType::Damaged, module.getID(), amount, 0));

	if (module.durability_.getValue() <= 0) {
		module.notify(ModuleEvent(EventType::Destroyed, module.getID(), amount, 0));
	}
	return module;
}
Module& operator*(Module& module, double modifier) {
	if (module.getIsBlocked()) {
		return module;
	}
	int newEffectiveness = static_cast<int>(module.effectiveness_ * modifier);
	if (newEffectiveness > 100) newEffectiveness = 100;
	if (newEffectiveness < 0) newEffectiveness = 0;

	module.effectiveness_ = newEffectiveness;
	return module;
}