# GamerServerClientCombo
A project to create a real-time tactics multiplayer game in C++ using SFML


Whenever you launch the application, it launches both a server and a client (each in a different thread). When creating your game, you should only have to look and edit the Client and Server classes (both of which are already instantiated for you as be singletons). Each consists of a bunch of helpful methods for you including many events for you to implement.

On a Windows machine, "ResourcePath.cpp" is also needed. On a Mac machine, "ResourcePath.mm" is also needed. If you are developing with this repository, do NOT add these files to the public repository. These files are OS-specific and should be kept only on your local version. Feel free to contact Thomas-Redding for these files.
