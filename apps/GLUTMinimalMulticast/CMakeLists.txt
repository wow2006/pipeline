# Copyright NVIDIA Corporation 2016
# TO THE MAXIMUM EXTENT PERMITTED BY APPLICABLE LAW, THIS SOFTWARE IS PROVIDED
# *AS IS* AND NVIDIA AND ITS SUPPLIERS DISCLAIM ALL WARRANTIES, EITHER EXPRESS
# OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT SHALL NVIDIA OR ITS SUPPLIERS
# BE LIABLE FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES
# WHATSOEVER (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
# BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY LOSS)
# ARISING OUT OF THE USE OF OR INABILITY TO USE THIS SOFTWARE, EVEN IF NVIDIA HAS
# BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES

cmake_minimum_required(VERSION 2.6)

project( GLUTMinimalMulticast )

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLUT)

if (GLUT_FOUND)
  find_package( Boost COMPONENTS program_options REQUIRED )

  set( SOURCES
    src/main.cpp
  )

  set ( HEADERS
  )

  include_directories( "."
                       "inc"
                       ${Boost_INCLUDE_DIRS}
                       ${GLEW_INCLUDE_DIRS}
                       ${GLUT_INCLUDE_DIR}
                     )

  add_definitions( ${GLEW_DEFINITIONS} )

  add_executable( GLUTMinimalMulticast
    ${SOURCES}
    ${HEADERS}
  )

  target_link_libraries( GLUTMinimalMulticast
    ${GLUT_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    ${GLEW_LIBRARY}
    ${Boost_LIBRARIES}
    DPSgCore
    DPSgGL
    DPSgRdrRiXGL
    DPSgIO
    DPSgUIManipulator
    DPSgGenerator
    DPSgUIGLUT
  )

  CopyGLEW( GLUTMinimalMulticast "${DP_BINARY_PATH}" )
  CopyGLUT( GLUTMinimalMulticast "${DP_BINARY_PATH}" )

  set_target_properties( GLUTMinimalMulticast PROPERTIES FOLDER "Apps")
else()
  message("GLUT not found, disabling GLUTMinimalMulticast.")
endif()

