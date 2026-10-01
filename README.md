Full disclosure: I smashed this template together with an unholy fusion of Bing, then Claude when I ran out of tokens, and then finally copilot in VSCode when I discovered it could read through all my code and make suggestions. I'm not aware of templates for building plugins on Linux, so I thought I'd do it myself. If anyone is aware of resources from people who actually know what they're doing, please let me know.

I used resources from the Linux cross-compiling in [alandtse/CommonLibSSE-NG](https://github.com/alandtse/CommonLibSSE-NG/blob/ng/examples/linux-cross-compile/README.md), [mrowrpurr's Logging SKSE Template](https://github.com/SkyrimScripting/SKSE_Template_Logging), and this [commonlibsse-ng-template](https://github.com/libxse/commonlibsse-ng-template). It's somehow working. Please God forgive me.

## Building
```sh
cmake --preset build-release-linux-clangcl-vcpkg-all
cmake --build --preset release-linux-clangcl-vcpkg-all
```

## Intellisense
For IntelliSense, install clangd in VS Code.

## Testing
This is AI Generated, haven't personally test this:
Tests are disabled by default. To enable them, add the `tests` feature to
`default-features` in `vcpkg.json`:

```json
"default-features": [
	"tests"
]
```

Then change `BUILD_TESTS` in `CMakeLists.txt` from `OFF` to `ON` and re-run the
configure and build commands above.
