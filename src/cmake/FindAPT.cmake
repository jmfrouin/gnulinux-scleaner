# Find the libapt-pkg includes
#

SET(APT_PKG_INCLUDE_FOUND "NO")

FIND_PATH(APT_PKG_INCLUDE_DIR pkgcache.h /usr/include/apt-pkg/)

IF(APT_PKG_INCLUDE_DIR)
    SET(APT_INCLUDE_DIR ${APT_PKG_INCLUDE_DIR})
    SET(APT_PKG_INCLUDE_FOUND "YES")
ENDIF(APT_PKG_INCLUDE_DIR)

IF (APT_PKG_INCLUDE_FOUND)
  MESSAGE(STATUS "Found apt-pkg header")
ELSE (APT_PKG_INCLUDE_FOUND)
  MESSAGE(FATAL_ERROR "Could not find apt-pkg header, please install it : apt-get install libapt-pkg-dev")
ENDIF (APT_PKG_INCLUDE_FOUND)
