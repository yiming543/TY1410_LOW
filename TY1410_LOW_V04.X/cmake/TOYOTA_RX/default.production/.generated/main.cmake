# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(TOYOTA_RX_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(TOYOTA_RX_default_default_XC8_FILE_TYPE_assemble)
add_library(TOYOTA_RX_default_default_XC8_assemble OBJECT ${TOYOTA_RX_default_default_XC8_FILE_TYPE_assemble})
    TOYOTA_RX_default_default_XC8_assemble_rule(TOYOTA_RX_default_default_XC8_assemble)
    list(APPEND TOYOTA_RX_default_library_list "$<TARGET_OBJECTS:TOYOTA_RX_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(TOYOTA_RX_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(TOYOTA_RX_default_default_XC8_assemblePreprocess OBJECT ${TOYOTA_RX_default_default_XC8_FILE_TYPE_assemblePreprocess})
    TOYOTA_RX_default_default_XC8_assemblePreprocess_rule(TOYOTA_RX_default_default_XC8_assemblePreprocess)
    list(APPEND TOYOTA_RX_default_library_list "$<TARGET_OBJECTS:TOYOTA_RX_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(TOYOTA_RX_default_default_XC8_FILE_TYPE_compile)
add_library(TOYOTA_RX_default_default_XC8_compile OBJECT ${TOYOTA_RX_default_default_XC8_FILE_TYPE_compile})
    TOYOTA_RX_default_default_XC8_compile_rule(TOYOTA_RX_default_default_XC8_compile)
    list(APPEND TOYOTA_RX_default_library_list "$<TARGET_OBJECTS:TOYOTA_RX_default_default_XC8_compile>")
endif()


add_executable(${TOYOTA_RX_default_image_name} ${TOYOTA_RX_default_library_list})
set_target_properties(${TOYOTA_RX_default_image_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${TOYOTA_RX_default_output_dir})

target_link_libraries(${TOYOTA_RX_default_image_name} PRIVATE ${TOYOTA_RX_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
TOYOTA_RX_default_link_rule(${TOYOTA_RX_default_image_name})




