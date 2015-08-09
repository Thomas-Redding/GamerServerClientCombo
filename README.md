# GamerServerClientCombo
A basic template to create a multiplayer game app using SFML


Whenever you launch the application, it launches both a server and a client (each in a different thread). When creating your game, you should only have to look and edit the Client and Server classes (both of which are already instantiated for you as be singletons). Each consists of a bunch of helpful methods for you including many events for you to implement.

The Client and Server classes are unlikely to change much in the future (except for commenting). The other classes might change later to increase clarity and efficiency while solving any bugs that might show up; however, such changes shouldn't affect any implementation of Client or Server.
