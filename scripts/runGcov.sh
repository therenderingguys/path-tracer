#!/bin/bash
export CODECOV_TOKEN="b2f59a77-9525-466d-b04b-c809a3f501ac"
find src test \( -name \*.h -o -name \*.cpp \) -exec gcov -style=file -i build/{} \;
bash <(curl -s https://codecov.io/bash)