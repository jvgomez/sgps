SGPS_ADD_EXECUTABLE("AUTO" "ALL_FILES_RECURSE")

# If you need to link some other external library:
TARGET_LINK_LIBRARIES(${EXE_NAME} boost_filesystem boost_system m)

