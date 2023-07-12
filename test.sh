if [ "$1" = "v" ]; then
    ./build.sh && cd build && ctest --verbose && cd ..
else
    ./build.sh && cd build && ctest --output-on-failure && cd ..
fi
