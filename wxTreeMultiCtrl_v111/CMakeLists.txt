##---------------------------------------------------------------------------
## $RCSfile$
## $Source$
## $Revision$
## $Date$
##---------------------------------------------------------------------------
## Author:      Jorgen Bodde
## Copyright:   (c) Jorgen Bodde
## License:     wxWidgets License
##---------------------------------------------------------------------------

##---------------------------------------------------
## Please set your wxWidgets configuration here
##--------------------------------------------------- 

SET(WXW_USE_DEBUG ON)
SET(WXW_USE_UNICODE OFF)
SET(WXW_USE_SHARED OFF)
SET(WXW_USE_UNIV OFF)
SET(WXW_USE_MONO OFF)
SET(WXW_FILE_VERSION "26")
SET(WXW_VERSION "2.6")

PROJECT( TREEMULTICTRL )

INCLUDE (${TREEMULTICTRL_SOURCE_DIR}/bin/FindwxW.cmake)
INCLUDE (${CMAKE_ROOT}/Modules/FindDoxygen.cmake OPTIONAL)

# Options for building the stuff
IF(DOXYGEN)
  OPTION( MAKE_DOXYGEN "Generate doxygen documentation" ON )
ENDIF(DOXYGEN)

OPTION( USE_CHECKBOXVIEW "Enable checkbox view functionality" OFF)

ADD_DEFINITIONS( ${WXWIDGETS_DEFINITIONS} )
SET(TREEMULTICTRL_INCLUDE_PATH ${TREEMULTICTRL_SOURCE_DIR}/contrib/include)

# If option Doxygen, create config script
CONFIGURE_FILE(${TREEMULTICTRL_SOURCE_DIR}/doc/Doxyfile.in
               ${TREEMULTICTRL_BINARY_DIR}/docs/Doxyfile
               @ONLY IMMEDIATE)

IF(MAKE_DOXYGEN AND DOXYGEN) 
	ADD_CUSTOM_TARGET(api-docs ALL ${DOXYGEN}
				       ${TREEMULTICTRL_BINARY_DIR}/docs/Doxyfile DEPENDS
				       ${TREEMULTICTRL_SOURCE_DIR}/doc/Doxyfile.in )  
ENDIF(MAKE_DOXYGEN AND DOXYGEN)

SUBDIRS(contrib)
