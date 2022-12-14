cmake_minimum_required(VERSION 3.11)

include(../cmake/raylib.cmake)
include(../cmake/nlohmann_json.cmake)

project(game VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cpp map.cpp map.h item_base.cpp item_base.h item_chest.cpp item_chest.h item_dagger.cpp item_dagger.h inventory_ui.cpp inventory_ui.h inventory_template.h item_potion.cpp item_potion.h item_apple.cpp item_apple.h item_crystal.cpp item_crystal.h item_ring.cpp item_ring.h character_base.cpp character_base.h character_player.cpp character_player.h item_armor.cpp item_armor.h character_robot.cpp character_robot.h)

# Add config.h.in file
configure_file(config.h.in config.h)
target_include_directories(${PROJECT_NAME} PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#  Link to Raylib
target_link_libraries(${PROJECT_NAME} raylib nlohmann_json::nlohmann_json -static)

# Copy assets to assets path
add_custom_target(copy_assets
        COMMAND ${CMAKE_COMMAND} -P "${CMAKE_CURRENT_LIST_DIR}/../cmake/copy-assets.cmake"
        )
add_dependencies(${PROJECT_NAME} copy_assets)

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif ()

# CPack instructions
# call e.g. cpack -G ZIP -C Debug to create a binary distribution
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "${PROJECT_NAME}_Bundle")
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/assets" DESTINATION "${PROJECT_NAME}_Bundle")