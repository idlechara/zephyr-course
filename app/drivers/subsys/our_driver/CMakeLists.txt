if(CONFIG_OUR_DRIVER)
    target_sources(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/our_driver.c)
endif()
zephyr_include_directories(include)