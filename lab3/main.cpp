#include "SeaBattle.h"
#include <boost/program_options.hpp>

using namespace boost::program_options;

StrategyType GetStratType(const std::string &str);
ViewType GetViewType(const std::string &str);
bool IsStrategy(const std::string &str);

int main(int argc, char *argv[]) {
    options_description desc("Options");
    desc.add_options()
            ("help,h", "Show help")
            ("count,c", value<int>()->default_value(1), "Number of rounds")
            ("firstplaym", value<std::string>()->default_value("random"), "First player shoot mode")
            ("firstplacem", value<std::string>()->default_value("random"), "First player place mode")
            ("secondplaym", value<std::string>()->default_value("random"), "Second player shoot mode")
            ("secondplacem", value<std::string>()->default_value("random"), "Second player place mode")
            ("view,v", value<std::string>()->default_value("console"), "View mode");
    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }
    int count = vm["count"].as<int>();
    std::string firstPlaceStrategy = vm["firstplacem"].as<std::string>();
    std::string firstPlayStrategy = vm["firstplaym"].as<std::string>();
    std::string secondPlaceStrategy = vm["secondplacem"].as<std::string>();
    std::string secondPlayStrategy = vm["secondplaym"].as<std::string>();
    std::string viewMode = vm["view"].as<std::string>();
    if (!IsStrategy(firstPlaceStrategy) || !IsStrategy(firstPlayStrategy) ||
    !IsStrategy(secondPlaceStrategy) || !IsStrategy(secondPlayStrategy) ||
    (viewMode != "graphic" && viewMode != "console")) {
        std::cout << desc << std::endl;
        return 0;
    }
    for (int i = 0; i < count; ++i) {
        SeaBattle game(GetStratType(firstPlaceStrategy), GetStratType(firstPlayStrategy),
                       GetStratType(secondPlaceStrategy), GetStratType(secondPlayStrategy),
                       GetViewType(viewMode));
        try {
            game.StartGame();
        }
        catch (StrategyLogicException &e) {
            std::cerr << "strategy error" << std::endl;
            return 0xFF;
        }
    }
    return 0;
}

ViewType GetViewType(const std::string &str) {
    if (str == "graphic") {
        return ViewType::graphic;
    }
    return ViewType::console;
}

bool IsStrategy(const std::string &str) {
    return (str == "random" || str == "optimal" || str == "manual");
}

StrategyType GetStratType(const std::string &str) {
    if (str == "optimal") {
        return StrategyType::optimal;
    }
    if (str == "manual") {
        return StrategyType::manual;
    }
    return StrategyType::random;
}
