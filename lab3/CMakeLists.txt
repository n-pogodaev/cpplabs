cmake_minimum_required(VERSION 3.15)
project(SeaBattle)

set(CMAKE_CXX_STANDARD 11)

add_executable(SeaBattle Strategy.h ManualStrategy.cpp ManualStrategy.h OptimalStrategy.cpp OptimalStrategy.h RandomStrategy.cpp RandomStrategy.h ConsoleView.cpp ConsoleView.h GameView.h GraphicView.cpp GraphicView.h Gamer.cpp Gamer.h SeaBattle.cpp SeaBattle.h main.cpp Field.h Field.cpp)

find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(SeaBattle ${Boost_LIBRARIES})
