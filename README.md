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

## Supported Platform(s)
- OS X
- Linux
- Windows

