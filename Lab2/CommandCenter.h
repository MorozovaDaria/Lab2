#pragma once
#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Module.h"
#include "IObserver.h"
#include "Environment.h"
#include "ResourcePackage.h"
#include "ModuleEvent.h"

class CommandCenter : public IObserver {
private:
    std::vector<std::unique_ptr<Module>> modules_;
    double energy_;
    double oxygen_;
    int safetyLevel_;
    size_t maxModules_;
    std::shared_ptr<Environment> currentEnvironment_;

public:
    CommandCenter(size_t maxModules, double energy = 1000.0, double oxygen = 500.0, int safetyLevel = 100);
    ~CommandCenter() = default;

    bool addModule(std::unique_ptr<Module> module);
    void removeModuleById(int id);
    Module* findModuleById(int id);
    size_t size() const;
    size_t maxSize() const;

    double getEnergy() const;
    double getOxygen() const;
    int getSafetyLevel() const;
    void setEnvironment(std::shared_ptr<Environment> env);
    std::shared_ptr<Environment> getEnvironment() const;

    void applyCurrentEnvironment();
    void onModuleEvent(const ModuleEvent& event) override;

    friend CommandCenter& operator+(CommandCenter& center, const ResourcePackage& package);
};