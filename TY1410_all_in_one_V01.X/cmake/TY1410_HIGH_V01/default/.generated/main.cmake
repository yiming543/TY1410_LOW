include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(TY1410_HIGH_V01_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(TY1410_HIGH_V01_default_default_XC8_FILE_TYPE_assemble)
add_library(TY1410_HIGH_V01_default_default_XC8_assemble OBJECT ${TY1410_HIGH_V01_default_default_XC8_FILE_TYPE_assemble})
    TY1410_HIGH_V01_default_default_XC8_assemble_rule(TY1410_HIGH_V01_default_default_XC8_assemble)
    list(APPEND TY1410_HIGH_V01_default_library_list "$<TARGET_OBJECTS:TY1410_HIGH_V01_default_default_XC8_assemble>")

endif()

# Handle files with suffix S, for group default-XC8
if(TY1410_HIGH_V01_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(TY1410_HIGH_V01_default_default_XC8_assemblePreprocess OBJECT ${TY1410_HIGH_V01_default_default_XC8_FILE_TYPE_assemblePreprocess})
    TY1410_HIGH_V01_default_default_XC8_assemblePreprocess_rule(TY1410_HIGH_V01_default_default_XC8_assemblePreprocess)
    list(APPEND TY1410_HIGH_V01_default_library_list "$<TARGET_OBJECTS:TY1410_HIGH_V01_default_default_XC8_assemblePreprocess>")

endif()

# Handle files with suffix [cC], for group default-XC8
if(TY1410_HIGH_V01_default_default_XC8_FILE_TYPE_compile)
add_library(TY1410_HIGH_V01_default_default_XC8_compile OBJECT ${TY1410_HIGH_V01_default_default_XC8_FILE_TYPE_compile})
    TY1410_HIGH_V01_default_default_XC8_compile_rule(TY1410_HIGH_V01_default_default_XC8_compile)
    list(APPEND TY1410_HIGH_V01_default_library_list "$<TARGET_OBJECTS:TY1410_HIGH_V01_default_default_XC8_compile>")

endif()


# Main target for this project
add_executable(TY1410_HIGH_V01_default_image_bcQ4iH1k ${TY1410_HIGH_V01_default_library_list})

set_target_properties(TY1410_HIGH_V01_default_image_bcQ4iH1k PROPERTIES
    OUTPUT_NAME "default"
    SUFFIX ".elf"
    ADDITIONAL_CLEAN_FILES "${output_extensions}"
    RUNTIME_OUTPUT_DIRECTORY "${TY1410_HIGH_V01_default_output_dir}")
target_link_libraries(TY1410_HIGH_V01_default_image_bcQ4iH1k PRIVATE ${TY1410_HIGH_V01_default_default_XC8_FILE_TYPE_link})

# Add the link options from the rule file.
TY1410_HIGH_V01_default_link_rule( TY1410_HIGH_V01_default_image_bcQ4iH1k)


