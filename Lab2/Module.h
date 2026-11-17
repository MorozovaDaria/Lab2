#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include "Durability.h"
#include "EnergyConsumption.h"
#include "Capacity.h"
#include "IObservable.h"
#include "ModuleEvent.h"
#include "Types.h"

class Station;
class Damage;

class Module : public IObservable {
protected:
	int ID_;
	std::string name_;
	int effectiveness_;
	std::string condition_;
	Durability durability_;
	EnergyConsumption energyConsumption_;
	Capacity capacity_;
	static int nextId_;

	bool isBlocked_;
public:
	Module(std::string name, int effectiveness, int endurance, int energy, int capacity);
	virtual ~Module() override = default;
	virtual Module* clone() const = 0;
	virtual std::string getType() const = 0;
	int getID() const;
	std::string getName() const;
	int getEffectiveness() const;
	std::string getCondition() const;
	Durability& getDurability();
	EnergyConsumption& getEnergyConsumption();
	Capacity& getCapacity();
	void activate();
	void deactivate();
	void setState(const std::string& newState);
	void setEffectiveness(int newEff);
	void moveToIndex(Station& station, size_t currentIndex, size_t newIndex);

	//изменения 2 лаба
	bool getIsBlocked() const { 
		return isBlocked_; 
	}
	void setBlocked(bool state) { 
		isBlocked_ = state; 
	}
	void subscribe(IObserver* observer) override;
	void unsubscribe(IObserver* observer) override;
	void notify(const ModuleEvent& event) override;
	friend Module& operator-(Module& module, const Damage& damage);
	friend Module& operator*(Module& module, double modifier);
};