cmake_minimum_required(VERSION 3.15)
project(game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Look for SFML
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

# Source files
set(SOURCES
    AnimatedObject.cpp
    Arrow.cpp
    Bonus.cpp
    Enemy.cpp
    GraphicalObject.cpp
    main.cpp
    Platform.cpp
    Player.cpp
)

# Header files
set(HEADERS
    AnimatedObject.h
    Arrow.h
    Bonus.h
    Enemy.h
    GraphicalObject.h
    Platform.h
    Player.h
)

# Create executable
add_executable(game ${SOURCES} ${HEADERS})

# Link SFML libraries
target_link_libraries(game
    sfml-graphics
    sfml-window
    sfml-system
    sfml-audio
)

# Help organize files in Visual Studio
source_group("Header Files" FILES ${HEADERS})
source_group("Source Files" FILES ${SOURCES})