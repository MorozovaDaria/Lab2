#include <iostream>
#include <memory>
#include <ctime>
#include "CommandCenter.h"
#include "StandardModuleFactory.h"
#include "AdvancedModuleFactory.h"
#include "EarthOrbit.h"
#include "DeepSpace.h"
#include "AsteroidField.h"
#include "EnvironmentProxy.h"
#include "SolarStorm.h"
#include "MeteorShower.h"
#include "CargoContainer.h"
#include "SpaceAnomaly.h"
#include "ResourcePackage.h"

int main() {
    setlocale(LC_ALL, "RU");
    srand(static_cast<unsigned>(time(nullptr)));

    std::cout << "Сценарий 1: Создание командного центра и добавление модулей\n";
    CommandCenter center(6, 1000.0, 400.0, 100);
    StandardModuleFactory standardFactory;
    AdvancedModuleFactory advancedFactory;

    center.addModule(std::unique_ptr<Module>(standardFactory.createApartmentModule("CrewCabin-1", 85, 100, 12, 6)));
    center.addModule(std::unique_ptr<Module>(standardFactory.createEnergyModule("Solar-1", 90, 90, 40, 15)));
    center.addModule(std::unique_ptr<Module>(advancedFactory.createResearchModule("PhysicsLab-1", 95, 80, 25, 8)));
    center.addModule(std::unique_ptr<Module>(advancedFactory.createApartmentModule("Medical-1", 80, 95, 15, 5)));

    std::cout << "Модулей на станции: " << center.size() << std::endl;
    std::cout << "Энергия: " << center.getEnergy() << " | Кислород: " << center.getOxygen()
        << " | Безопасность: " << center.getSafetyLevel() << std::endl;

    std::cout << "\nСценарий 2: Установка окружения EarthOrbit + Proxy\n";
    auto earth = std::make_shared<EarthOrbit>();
    auto proxy = std::make_shared<EnvironmentProxy>(earth);
    center.setEnvironment(proxy);
    std::cout << "Текущее окружение: " << center.getEnvironment()->getName() << std::endl;
    center.applyCurrentEnvironment();

    std::cout << "\nСценарий 3: Смена окружения на DeepSpace\n";
    auto deepSpace = std::make_shared<DeepSpace>();
    auto deepProxy = std::make_shared<EnvironmentProxy>(deepSpace);
    center.setEnvironment(deepProxy);
    std::cout << "Новое окружение: " << center.getEnvironment()->getName() << std::endl;
    center.applyCurrentEnvironment();

    std::cout << "\nСценарий 4: Солнечная буря (SolarStorm)\n";
    SolarStorm storm;
    Module* target = center.findModuleById(1);
    if (target) {
        std::cout << "До удара прочность: " << target->getDurability().getValue() << std::endl;
        storm.interact(center, *target);
        std::cout << "После удара прочность: " << target->getDurability().getValue() << std::endl;
    }

    std::cout << "\nСценарий 5: Метеоритный поток (MeteorShower)\n";
    MeteorShower shower;
    Module* target2 = center.findModuleById(2);
    if (target2) {
        std::cout << "До удара прочность: " << target2->getDurability().getValue() << std::endl;
        shower.interact(center, *target2);
        std::cout << "После удара прочность: " << target2->getDurability().getValue() << std::endl;
    }

    std::cout << "\nСценарий 6: Грузовой контейнер (CargoContainer)\n";
    std::cout << "До: Энергия = " << center.getEnergy() << ", Кислород = " << center.getOxygen()
        << ", Безопасность = " << center.getSafetyLevel() << std::endl;
    CargoContainer cargo;
    Module* any = center.findModuleById(3);
    if (any) {
        cargo.interact(center, *any);
    }
    std::cout << "После: Энергия = " << center.getEnergy() << ", Кислород = " << center.getOxygen()
        << ", Безопасность = " << center.getSafetyLevel() << std::endl;

    std::cout << "\nСценарий 7: Космическая аномалия (SpaceAnomaly)\n";
    SpaceAnomaly anomaly;
    Module* target3 = center.findModuleById(3);
    if (target3) {
        std::cout << "Эффективность до: " << target3->getEffectiveness() << std::endl;
        anomaly.interact(center, *target3);
        std::cout << "Эффективность после: " << target3->getEffectiveness() << std::endl;
        std::cout << "Заблокирован: " << (target3->getIsBlocked() ? "да" : "нет") << std::endl;
    }

    std::cout << "\nСценарий 8: Астероидное поле\n";
    auto asteroid = std::make_shared<AsteroidField>();
    auto asteroidProxy = std::make_shared<EnvironmentProxy>(asteroid);
    center.setEnvironment(asteroidProxy);
    std::cout << "Окружение: " << center.getEnvironment()->getName() << std::endl;
    center.applyCurrentEnvironment();

    std::cout << "\nФинальное состояние\n";
    std::cout << "Модулей осталось: " << center.size() << std::endl;
    std::cout << "Энергия: " << center.getEnergy() << std::endl;
    std::cout << "Кислород: " << center.getOxygen() << std::endl;
    std::cout << "Уровень безопасности: " << center.getSafetyLevel() << std::endl;

    return 0;
}