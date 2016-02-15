# Install script for directory: /home/crazyhorse/test/ShadowSocks/Json/rapidjson

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "pkgconfig")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/pkgconfig/RapidJSON.pc")
FILE(INSTALL DESTINATION "/usr/local/lib/pkgconfig" TYPE FILE FILES "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/RapidJSON.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "pkgconfig")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "doc")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/doc/RapidJSON/readme.md")
FILE(INSTALL DESTINATION "/usr/local/share/doc/RapidJSON" TYPE FILE FILES "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/readme.md")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "doc")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/rapidjson")
FILE(INSTALL DESTINATION "/usr/local/include" TYPE DIRECTORY FILES "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/include/rapidjson")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/share/doc/RapidJSON/examples/")
FILE(INSTALL DESTINATION "/usr/local/share/doc/RapidJSON/examples" TYPE DIRECTORY FILES "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/example/" REGEX "/CMakeFiles$" EXCLUDE REGEX "/Makefile$" EXCLUDE REGEX "/cmake\\_install\\.cmake$" EXCLUDE)
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "examples")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")
  list(APPEND CPACK_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/cmake/RapidJSON/RapidJSONConfig.cmake;/usr/local/lib/cmake/RapidJSON/RapidJSONConfigVersion.cmake")
FILE(INSTALL DESTINATION "/usr/local/lib/cmake/RapidJSON" TYPE FILE FILES
    "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/RapidJSONConfig.cmake"
    "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/RapidJSONConfigVersion.cmake"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "dev")

IF(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  INCLUDE("/home/crazyhorse/test/ShadowSocks/Json/rapidjson/doc/cmake_install.cmake")
  INCLUDE("/home/crazyhorse/test/ShadowSocks/Json/rapidjson/example/cmake_install.cmake")
  INCLUDE("/home/crazyhorse/test/ShadowSocks/Json/rapidjson/test/cmake_install.cmake")

ENDIF(NOT CMAKE_INSTALL_LOCAL_ONLY)

IF(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
ELSE(CMAKE_INSTALL_COMPONENT)
  SET(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
ENDIF(CMAKE_INSTALL_COMPONENT)

FILE(WRITE "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/${CMAKE_INSTALL_MANIFEST}" "")
FOREACH(file ${CMAKE_INSTALL_MANIFEST_FILES})
  FILE(APPEND "/home/crazyhorse/test/ShadowSocks/Json/rapidjson/${CMAKE_INSTALL_MANIFEST}" "${file}\n")
ENDFOREACH(file)
