find src/ \( -name \*.h -o -name \*.cpp \) -exec clang-format -style=file -i {} \;
find test/ \( -name \*.h -o -name \*.cpp \) -exec clang-format -style=file -i {} \;