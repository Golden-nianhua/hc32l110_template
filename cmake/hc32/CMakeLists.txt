cmake_minimum_required(VERSION 3.22)
# Enable CMake support for ASM and C languages
enable_language(C ASM)
# symbols (macros)
set(HC_Defines_Syms 
	USE_DDL_DRIVER
	HC32L110x6
    $<$<CONFIG:Debug>:DEBUG>
)

# include paths
set(HC_Include_Dirs
    ${CMAKE_SOURCE_DIR}/Core/Inc
    ${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/inc
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/HC/HC32L110/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Core/Include
)

# application sources
set(HC_Application_Src
    ${CMAKE_SOURCE_DIR}/Core/Src/main.c
    ${CMAKE_SOURCE_DIR}/startup_hc32l110.s
)

# DDL Drivers
set(HC32_Drivers_Src
    ${CMAKE_SOURCE_DIR}/Core/Src/system_hc32l110.c
    ${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/adc.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/adt.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/bt.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/clk.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/crc.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/ddl.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/flash.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/gpio.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/i2c.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/interrupts_hc32l110.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/lpm.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/lpt.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/lpuart.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/lvd.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/pca.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/reset.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/rtc.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/spi.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/trim.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/uart.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/vc.c
	${CMAKE_SOURCE_DIR}/Drivers/HC32L110_DDL_Driver/src/wdt.c
)

# Drivers Midllewares



# Link directories setup
set(HC_LINK_DIRS

)
# Project static libraries
set(HC_LINK_LIBS 
    HC32_Drivers
    
)
# Interface library for includes and symbols
add_library(hc32 INTERFACE)
target_include_directories(hc32 INTERFACE ${HC_Include_Dirs})
target_compile_definitions(hc32 INTERFACE ${HC_Defines_Syms})

# Create HC32_Drivers static library
add_library(HC32_Drivers OBJECT)
target_sources(HC32_Drivers PRIVATE ${HC32_Drivers_Src})
target_link_libraries(HC32_Drivers PUBLIC hc32)


# Add application sources to the project
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${HC_Application_Src})

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE ${HC_LINK_DIRS})

# Add libraries to the project
target_link_libraries(${CMAKE_PROJECT_NAME} ${HC_LINK_LIBS})

# Add the map file to the list of files to be removed with 'clean' target
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES ${CMAKE_PROJECT_NAME}.map)

# Validate thatcode is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()
