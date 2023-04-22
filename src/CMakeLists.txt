add_subdirectory(lib)

add_executable(simplexsolver main.c)
target_link_libraries(simplexsolver fraction bigm matrix simplex visualcell tableux input stages)

include(GenerateG1A)
include(GenerateG3A)
include(Fxconv)

find_package(Gint 2.9 REQUIRED)

# Shared assets, fx-9860G-only assets and fx-CG-50-only assets
set(ASSETS
  # ...
)
set(ASSETS_fx
  ../assets-fx/example.png
  # ...
)
set(ASSETS_cg
  # ...
)

fxconv_declare_assets(${ASSETS} ${ASSETS_fx} ${ASSETS_cg} WITH_METADATA)

target_compile_options(simplexsolver PRIVATE -Wall -Wextra -Os)
target_link_libraries(simplexsolver Gint::Gint)


if("${FXSDK_PLATFORM_LONG}" STREQUAL fx9860G)
  generate_g1a(TARGET simplexsolver OUTPUT "../SimplexSolver.g1a"
    NAME "SimplexSolver" ICON ../assets-fx/icon.png)
elseif("${FXSDK_PLATFORM_LONG}" STREQUAL fxCG50)
  generate_g3a(TARGET simplexsolver OUTPUT "../SimplexSolver.g3a"
    NAME "SimplexSolver" ICONS ../assets-cg/icon-uns.png ../assets-cg/icon-sel.png)
endif()