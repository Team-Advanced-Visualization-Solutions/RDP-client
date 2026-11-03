# RDP-client: Modern X11 RDP Client
# RDP-client X11 CLI cmake
#
# Copyright 2012 Marc-Andre Moreau <marcandre.moreau@gmail.com>
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(SRCS xfreerdp.c)

addtargetwithresourcefile(${MODULE_NAME} TRUE "${PROJECT_VERSION}" SRCS)
set_target_properties(${MODULE_NAME} PROPERTIES OUTPUT_NAME "rdp-client")
set_target_properties(${MODULE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")
set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "Client/X11")

list(APPEND LIBS rdp-client-x11)

target_link_libraries(${MODULE_NAME} PRIVATE ${LIBS})

if(NOT MSVC)
  target_compile_options(${MODULE_NAME} PRIVATE -Wno-deprecated-declarations)
endif()

installwithrpath(
  TARGETS
  ${MODULE_NAME}
  RUNTIME
  DESTINATION
  ${CMAKE_INSTALL_BINDIR}
  COMPONENT
  client
)
install_freerdp_desktop("${MODULE_NAME}")

set_property(TARGET ${MODULE_NAME} PROPERTY FOLDER "Client/X11")
