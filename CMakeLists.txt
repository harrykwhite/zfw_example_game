cmake_minimum_required(VERSION 3.30)

project(zfw_example_game)

find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(zeta_framework)

add_executable(zfw_example_game
	src/entry.c
	src/game.c
	src/game.h
	src/player.c
	src/player.h

	zeta_framework/vendor/glad/src/glad.c
)

target_include_directories(zfw_example_game PRIVATE
    zeta_framework/zfw/include
    zeta_framework/zfw_common/include
    zeta_framework/vendor/glad/include
)

target_link_libraries(zfw_example_game PRIVATE glfw zfw zfw_common)

add_dependencies(zfw_example_game zfw_asset_packer)
add_custom_command(TARGET zfw_example_game POST_BUILD
	COMMAND $<TARGET_FILE:zfw_asset_packer> ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:zfw_example_game>
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE_DIR:zfw_example_game>/assets.zfwdat ${CMAKE_CURRENT_BINARY_DIR}/assets.zfwdat
)

