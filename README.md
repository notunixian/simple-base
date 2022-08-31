## simple-base - base for c++ VRChat clients
[![HitCount](https://hits.dwyl.com/notunixian/simple-base.svg?style=flat-square)](http://hits.dwyl.com/notunixian/simple-base)

Confirmed working for latest VRC update (build 1229) on 8/31/22.

A extremely simple base for VRChat clients made in C++, using the data of a modified build of [Il2CppInspector.](https://github.com/djkaty/Il2CppInspector)\
You are free to do anything you want with this base, aslong as you are following [the license of Il2CppInspector.](https://github.com/djkaty/Il2CppInspector/blob/master/LICENSE)

This repository also includes other data exported by Il2CppInspector, if you want to access any of this data you are free to by going into the il2cppinspector_resources folder.

If this is your first time using Il2CppInspector injecton projects, you should read up on [the writeups on using code inside of them.](https://katyscode.wordpress.com/2021/01/14/il2cppinspector-tutorial-working-with-code-in-il2cpp-dll-injection-projects/)

### This base contains:

* All the data exported from Il2CppInspector. This including **all** types, methods, etc.
* Fully working version of [ocornut's Dear ImGui](https://github.com/ocornut/imgui) using [Rebzzel's kiero](https://github.com/Rebzzel/kiero).
* Example hooking of methods inside of VRChat.
* Example tracers, names, and playerlist using methods inside of Unity and ImGui drawing.

### Using this base:
* Launch up your favorite IDE that can use msbuild (VSCode, VS, CLion, etc.)
* Unpack the 7z file inside of the appdata folder (this is to get past github's 100 mb per file limit.).
* Build, and use your favorite injector for EAC (do some googling, example: [face injector](https://github.com/Vazzupov/face-injector-fixed))
* Any errors relating to linker errors are most likely due to you not having the [DirectX SDK installed.](https://www.microsoft.com/en-us/download/details.aspx?id=6812)

### Updating this base:
This base will break whenever VRChat decides to update their game, I'll try to update this repo as often as possible when VRChat updates to provide the smoothest experience possible.

But, instructions on how to update this:
* Grab the source to Il2CppInspector
* Head over to Il2CppInspector.Common/IL2CPP/Il2CppBinaryClasses.cs
* Modify the data to properly match being able to read IL2CPP version 24.4.
* Run your modified version and create a C++ scaffolding project and point it to the directory that contains simple-base.
* Let it run, and now change any method names that VRChat may have changed due to the updates.
