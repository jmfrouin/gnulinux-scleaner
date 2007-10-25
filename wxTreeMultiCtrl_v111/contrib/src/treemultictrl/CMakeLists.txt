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

# Add files to library treemultictrl

IF(WIN32)
ELSE(WIN32)
  ADD_DEFINITIONS( -DLINUX=1 `wx-config --cxxflags`)
ENDIF(WIN32)

IF(USE_CHECKBOXVIEW)
  ADD_DEFINITIONS( -DCHECKBOXVIEW=1 )
ELSE(USE_CHECKBOXVIEW)
  ADD_DEFINITIONS( -DCHECKBOXVIEW=0)
ENDIF(USE_CHECKBOXVIEW)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WXWIDGETS_CXX_FLAGS}")

INCLUDE_DIRECTORIES(${TREEMULTICTRL_INCLUDE_PATH}
                    ${WXWIDGETS_INCLUDE_DIR}
                    ${TREEMULTICTRL_SOURCE_DIR} )

SET(SRCS TreeMultiItemBase.cpp 
         TreeMultiItemNode.cpp
         TreeMultiItemWindow.cpp
         TreeMultiItemRoot.cpp
         wxTreeMultiCtrl.cpp
         wxTreeMultiEvent.cpp )

ADD_LIBRARY(treemultictrl ${SRCS} wxTreeMultiCtrl.h TreeMultiItemBase.h TreeMultiItemNode.h TreeMultiItemRoot.h wxTreeMultiEvent.h)

IF(LINUX)
	TARGET_LINK_LIBRARIES(treemultictrl `wx-config --libs`)
ENDIF(LINUX)
