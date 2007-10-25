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

SET(SAMPLE_SRCS MultiCtrlTest.cpp)

IF(WIN32)
    SET(SAMPLE_SRCS ${SAMPLE_SRCS} MultiCtrlTest.rc)
ELSE(WIN32)
  ADD_DEFINITIONS( -DLINUX=1 `wx-config --cxxflags`)
ENDIF(WIN32)


IF(USE_CHECKBOXVIEW)
  ADD_DEFINITIONS( -DCHECKBOXVIEW=1 )
ELSE(USE_CHECKBOXVIEW)
  ADD_DEFINITIONS( -DCHECKBOXVIEW=0)
ENDIF(USE_CHECKBOXVIEW)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}${WXWIDGETS_CXX_FLAGS}")

INCLUDE_DIRECTORIES(${TREEMULTICTRL_INCLUDE_PATH}
                    ${WXWIDGETS_INCLUDE_DIR}
		    ${TREEMULTICTRL_SOURCE_DIR}/contrib/samples)

LINK_DIRECTORIES( ${TREEMULTICTRL_BINARY_DIR}/contrib/lib ${WXWIDGETS_LINK_DIRECTORIES} ${LINK_DIRECTORIES})

ADD_EXECUTABLE(tmctest WIN32 ${SAMPLE_SRCS})

IF(WIN32)
	TARGET_LINK_LIBRARIES(tmctest treemultictrl ${WXWIDGETS_LIBRARIES})
ELSE(WIN32)
	TARGET_LINK_LIBRARIES(tmctest treemultictrl `wx-config --libs`)
ENDIF(WIN32)

