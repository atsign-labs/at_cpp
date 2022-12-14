# at_client_cpp

This project builds a library and a demo executable that implements the
atProtocol. The library will be `libat_client_cpp.a` and the exe is
`at_client_cpp_demo.exe`. 

## Supported platforms

Currently, the project builds using CLion in Windows with the `g++`
compiler toolchain, but should be possible to extend to other platforms
by tweaking the `CMakeLists.txt` file.

## Building

Run cmake:

```shell
cmake.exe --build ./cmake-build-debug --target at_client_cpp_demo
```

## Running the demo client

The exe requires a `config.json` file as an argument. Sample contents
are shown below.

```json
{
  "rootServerHost"    : "root.atsign.wtf",
  "rootServerPort"    : "64",
  "atSign"            : "<your atsign>",
  "pkamPemFile"       : "<path of your pem file>"
}
```

### Sample command line (assuming config file name is config.json)

```shell
at_client_cpp_demo.exe config.json
```

### Demo client flow

The demo client exe first looks up the secondary server for the given atSign.  
Then it does a `from` for the given atSign to get the challenge (this is
required to do `pkam` authentication).  
Next, `pkam` authentication is executed, followed by `scan` and `lookup`.  
In the demo, `llookup` is used instead of `lookup` since it is looking up
properties of the local atsign.  
