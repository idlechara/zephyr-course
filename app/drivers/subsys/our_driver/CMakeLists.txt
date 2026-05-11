if(CONFIG_IDLECHARA_SENSOR)
    target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/idlechara_sensor.c)
endif()
zephyr_include_directories(include)