add_library(
    module
    OBJECT
    main.cpp
)

set(ALL_OBJECT_FILES
  ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:module>
  PARENT_SCOPE)