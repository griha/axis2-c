#!/bin/bash

CLIENT_REPO="$HOME/client_repo"
echo "Start creating a client repository at $CLIENT_REPO"

if [ -d  $CLIENT_REPO ]; 
then
    echo "$CLIENT_REPO exists. "
else
    #Create client repo
    echo "Creating a new directory for client repo"
    mkdir $CLIENT_REPO
fi


#copy [client]axis2.xml to CLIENT_REPO
echo "Copying axis2.xml to client_repo"
cp data/client.enc.axis2.xml $CLIENT_REPO/axis2.xml

#copy [server]axis2.xml to AXIS2C_HOME
echo "Copying axis2.xml to AXIS2C_HOME"
cp data/server.enc.axis2.xml $AXIS2C_HOME/axis2.xml

#copy libs to client_repo
echo "Copying libraries to client_repo"
cp -rr $AXIS2C_HOME/lib $CLIENT_REPO/

#INSTALL MODULES to make sure that both server and client have the same module.
echo "Copying latest modules to client_repo"
cp -r $AXIS2C_HOME/modules $CLIENT_REPO/

