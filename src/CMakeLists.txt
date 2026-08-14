
set(${PROJECT_NAME}_HEADERS
	dice.h
)

set(${PROJECT_NAME}_YAHT_HEADERS
  yaht/constants.h
  yaht/player.h
  yaht/scoresheet.h
)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_YAHT_HEADERS} dice.cpp yaht/player.cpp yaht/scoresheet.cpp)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

string(REPLACE "_" "/" INSTALL_DIRECTORY ${PROJECT_NAME})

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${INSTALL_DIRECTORY}")

install(FILES ${${PROJECT_NAME}_YAHT_HEADERS} DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${INSTALL_DIRECTORY}/yaht")

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib ARCHIVE DESTINATION lib)

