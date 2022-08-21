# path-tracer

### Build with Ninja
```bash
cmake -G Ninja -B build
ninja -C./build
```

### Building on Windows 
- Using Ninja
```powershell
cmake -GNinja -Bbuild -DCMAKE_BUILD_TYPE=Release
ninja -C./build
```
- Using MSBUILD
```powershell
cmake -B build
msbuild build\PathTracer.sln -t:Build -p:Configuration=Release
```
## Docker Build & Run
- quick build: `docker build -t path_tracer_qk:latest -f Docker/quickbuild.Dockerfile .`
- src build: `docker build -t path_tracer:latest -f Docker/sourcebuild.Dockerfile .`
- run: `docker run  -e DISPLAY=host.docker.internal:0 --name pt_vm -it path_tracer:latest`

## X11 Forwarding
- Mac with XQuartz
    first run `xhost + 127.0.0.1`
    Then the Docker run command above.

## Setup Clang Tidy 
### On MacOS
```bash
ln -s "$(brew --prefix llvm)/bin/clang-tidy" "/usr/local/bin/clang-tidy"
ln -s "$(brew --prefix llvm)/bin/clang-apply-replacements" "/usr/local/bin/clang-apply-replacements"
ln -s "$(brew --prefix llvm)/bin/run-clang-tidy" "/usr/local/bin/run-clang-tidy"
```
### Run Clang Tidy
After running cmake, the build dir will have a `compile_commands.json` file. Thats all you need to run `run-clang-tidy.py`.
```bash
run-clang-tidy -p build/ -header-filter='.*' -fix -format
```

## Supported Platform(s)
- OS X
- Linux
- Windows

