# XexUtils

XexUtils is a library to make Xbox 360 applications and/or libraries.

## Features

| Header file                      | Description                                                                                  | Examples                                  |
| -------------------------------- | -------------------------------------------------------------------------------------------- | ----------------------------------------- |
| [Assert](./src/Assert.h)         | Trigger a breakpoint with an assertion message in debug builds.                              | [Assert.md](./examples/Assert.md)         |
| [Dashlaunch](./src/Dashlaunch.h) | Get/set Dashlaunch options and access its global data.                                       | [Dashlaunch.md](./examples/Dashlaunch.md) |
| [Detour](./src/Detour.h)         | Detour/hook a function.                                                                      | [Detour.md](./examples/Detour.md)         |
| [Expected](./src/Expected.h)     | Partial clone of `std::expected` from C++23.                                                 | [Expected.md](./examples/Expected.md)     |
| [Filesystem](./src/Filesystem.h) | Functions to access storage devices and a class to represent a file path.                    | [Filesystem.md](./examples/Filesystem.md) |
| [Formatter](./src/Formatter.h)   | Convert from narrow to wide strings and generate strings from `printf` formats.              | [Formatter.md](./examples/Formatter.md)   |
| [General](./src/General.h)       | General purpose helpers that don't really fit in any namespace.                              | [General.md](./examples/General.md)       |
| [Http](./src/Http.h)             | Basic HTTP client with HTTPS support.                                                        | [Http.md](./examples/Http.md)             |
| [Hypervisor](./src/Hypervisor.h) | Read and write to hypervisor memory.                                                         | [Hypervisor.md](./examples/Hypervisor.md) |
| [Input](./src/Input.h)           | Detect single button presses and repeats more easily than using XInput directly.             | [Input.md](./examples/Input.md)           |
| [Kernel](./src/Kernel.h)         | Declarations of functions exported by `xboxkrnl.exe` and their associated structs and enums. |                                           |
| [Log](./src/Log.h)               | Very barebones logger.                                                                       | [Log.md](./examples/Log.md)               |
| [Math](./src/Math.h)             | Utility math functions and classes to manipulate vectors.                                    | [Math.md](./examples/Math.md)             |
| [Memory](./src/Memory.h)         | Read and write arbitrary data from and to arbritrary locations with safeguards.              | [Memory.md](./examples/Memory.md)         |
| [Optional](./src/Optional.h)     | Partial clone of `std::optional` from C++17.                                                 | [Optional.md](./examples/Optional.md)     |
| [SMC](./src/SMC.h)               | Interact with the power LED.                                                                 | [SMC.md](./examples/SMC.md)               |
| [Socket](./src/Socket.h)         | Open TCP connections with TLS support.                                                       | [Socket.md](./examples/Socket.md)         |
| [Url](./src/Url.h)               | Basic URL parser.                                                                            | [Url.md](./examples/Url.md)               |
| [ValueOrPtr](./src/ValueOrPtr.h) | Container class to manipulate a value or a pointer seemlessly.                               | [ValueOrPtr.md](./examples/ValueOrPtr.md) |
| [Xam](./src/Xam.h)               | Functions to nteract with the system UI and declarations of functions exported by `xam.xex`. | [Xam.md](./examples/Xam.md)               |

## Installation

### With pre-compiled binaries

- Download the latest binaries and header files from the [releases](https://github.com/ClementDreptin/XexUtils/releases).
- From Visual Studio, right click on your project, go to `Properties` and then:
    - Add `\path\to\XexUtils\lib` to `Configuration Properties > Linker > General > Additional Libary Directories`.
    - Add `XexUtils.lib` (or `XexUtilsd.lib` for the debug version) to `Configuration Properties > Linker > Input > Additional Dependencies`.
    - Add `\path\to\XexUtils\include` to `Configuration Properties > C/C++ > General > Additional Include Directories`.

### Compiling from source

- Clone the repository with its submodule. XexUtils depends on [BearSSL](https://bearssl.org/).
    ```
    git clone --recursive https://github.com/ClementDreptin/XexUtils.git
    ```
- Add XexUtils as a project in Visual Studio:&nbsp;
  Right click on the solution name in the solution explorer then `Add > Existing Project...` and select `XexUtils.vcxproj` in `\path\to\XexUtils`.
- Add it as a reference to your main project:&nbsp;
  Right click on your main project in the solution explorer then `Add > Reference...`, tick `XexUtils` and click OK.
- Add BearSSL as a project in Visual Studio:&nbsp;
  Right click on the solution name in the solution explorer then `Add > Existing Project...` and select `BearSSL.vcxproj` in `\path\to\XexUtils\deps\BearSSL.vcxproj`.

## Documentation

You can look at the [examples](./examples) directory, which will show you a basic usage of every public function. If you want a detailed API reference, you can look at the Doxygen comments in the [source header files](./src), which should display on hover in your editor if it's modern enough.

## Running the tests

The tests are an app that runs **on the console** and is deployed to the `devkit:\XexUtilsTests` directory (same as `hdd:\DEVKIT\XexUtilsTests`).

### Visual Studio 2010

Open `test\Tests.sln` in Visual Studio.

**Note**: Using Visual Studio 2010 is the only way to run the test app in a debugger (sadly).

### Visual Studio 2022 (or any environment)

You can't build with the 64-bit version of MSBuild so you'll need to run the 32-bit version manually. Open PowerShell (which can be done in `View > Terminal` in Visual Studio) and run the following command:

```PS1
# Create an alias to the 32-bit version of MSBuild named msbuild
# The default installation path of VS2022 is C:\Program Files\Microsoft Visual Studio\2022\Community
Set-Alias msbuild "<path_vs2022>\MSBuild\Current\Bin\MSBuild.exe"
```

Now run `msbuild` to compile the test app and deploy it to your console.

## Acknowledgements

- [Xbox 360 Detours](https://gist.github.com/iMoD1998/4aa48d5c990535767a3fc3251efc0348) - What served as a reference for the `Detour` implementation.
- [BearSSL](https://bearssl.org/) - The TLS implementation used in sockets.
- [XboxTLS](https://github.com/JakobRangel/XboxTLS) - What inspired and showed how to integrate BearSSL in an Xbox 360 environment.
