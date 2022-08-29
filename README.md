## simple-base - base for c++ VRChat clients
[![HitCount](https://hits.dwyl.com/notunixian/simple-base.svg?style=flat-square)](http://hits.dwyl.com/notunixian/simple-base)

A extremely simple base for VRChat clients made in C++, using the data of a modified build of [Il2CppInspector.](https://github.com/djkaty/Il2CppInspector)\
You are free to do anything you want with this base, aslong as you are following [the license of Il2CppInspector.](https://github.com/djkaty/Il2CppInspector/blob/master/LICENSE)

If this is your first time using Il2CppInspector injecton projects, you should read up on [Il2CppInspector's developers writeups on using code inside of them.](https://katyscode.wordpress.com/2021/01/14/il2cppinspector-tutorial-working-with-code-in-il2cpp-dll-injection-projects/)

### This base contains:

* All the data exported from Il2CppInspector. This including **all** types, methods, etc.
* Fully working version of [ocornut's Dear ImGui](https://github.com/ocornut/imgui) using [Rebzzel's kiero](https://github.com/Rebzzel/kiero).
* Example hooking of methods inside of VRChat.
* Example tracers and names using methods inside of Unity and ImGui drawing.

### Using this base:
* Launch up your favorite IDE that can use msbuild (VSCode, VS, CLion, etc.)
* Build, and use your favorite injector for EAC (there are many that exist that are free & open source, do some googling.)
* Any errors relating to linker errors are most likely due to you not having the [DirectX SDK installed.](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

### Casing & Formatting:
Most of the code that I have placed myself in here are in snake_case and are formatted using clang-format.
You are free to change this to whatever you like.
