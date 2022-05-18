# Quick start

1. Clone this repository to `Plugins/NearLinker` in your project directory
2. Open your project in the Unreal Editor
3. Go to project settings and enable the plugin
4. Restart the Unreal Editor
5. Go to project settings > Plugins > Nearlinker
6. Set the "Integration server" "Executable path" to the location of node.exe
7. Set the "Integration server" "Working directory" to the location of the nl-api-server directory from the NearLinker git repository
8. If the integration server runs locally, create a "Certificates" folder in your project's "Content" directory, and copy the integration server CA to "Content/Certificates/cacert.pem" (see how to generate certificates in the nl-api-server documentation)
9. Use the plugin in blueprints. See BP_NearMenu for an example of how to use it.


#Source code

In the Source directory, you will find the following files

## Settings

This adds a "Nearlinker" section in the project settings. In particular, it allows you to set the integration server url from the editor.

## WalletComponent

This defines an ActorComponent which can load, store, and save credentials for modifying requests to the integration server. It can also request creation of new credentials and save them.

## FunctionLibrary

This defines functions to interact with the integration server.

