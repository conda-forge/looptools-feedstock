#!/bin/bash
# Bash strict mode, c.f. http://redsymbol.net/articles/unofficial-bash-strict-mode/
set -euxo pipefail
IFS=$'\n\t'

./configure --help
# LOOPTOOLS_CONFIGURE_ARGS is set for each output in recipe.yaml, and is either
# empty or a single argument. If it is empty, pass no argument at all, as
# configure warns about an empty one.
./configure --prefix="${PREFIX}" ${LOOPTOOLS_CONFIGURE_ARGS:+"${LOOPTOOLS_CONFIGURE_ARGS}"}
# configure sets PARALLEL to use every core on the machine and
# LIBDIRSUFFIX to install to $PREFIX/lib64 on x86_64 and ppc64le
make install PARALLEL="-j${CPU_COUNT}" LIBDIRSUFFIX=
# The compilers fcc calls are run requirements, so are found under $PREFIX
# and not $BUILD_PREFIX at install time.
sed -i "s|${BUILD_PREFIX}|${PREFIX}|g" "${PREFIX}/bin/fcc"
# The compiler flags written to fcc include -fdebug-prefix-map for the work
# directory and the prefix of the build. Remove them so that no path of the
# build machine is left in fcc. They have no use for the compilations that fcc
# is used for.
sed -i -E 's| -fdebug-prefix-map=[^ }"]+||g' "${PREFIX}/bin/fcc"
