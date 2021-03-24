#!/bin/bash

set -euo pipefail

if [[ $# -eq 0 ]] ; then
    >&2 echo "Usage: ./run_server.sh <IP>"
    >&2 echo "<IP> is the IP of the instance being connected to"
    exit 1
fi

# Finds ssh key
KEY=$(echo *.pem)
echo "${KEY}"

# Error checking
if [[ -z "${KEY}" ]] ; then
  >&2 echo "Error: No ssh permission file could be found in directory"
  >&2 echo "       Please include the permission file to ssh into the desired instance"
  exit 1
fi

WS=" "
if [[ ${KEY} =~ $WS ]]; then
  >&2 echo "Error: Multiple ssh permission files found in directory"
  >&2 echo "       Please have only 1 permission file for the desired instance"
  exit 1
fi

echo "###########################"
echo "Connecting to server instance"
ssh -A -i ${KEY} ubuntu@${1} << EOF
  set -euo pipefail
  echo "Connection successful"

  echo "###########################"
  echo "Installing packages"
  sudo apt update
  sudo apt -y install g++
  sudo apt -y install make
  sudo apt -y install flex
  echo "Packages installed successfully"

  echo "###########################"
  echo "Building project"
  if [ -d "InfoProc_Project" ]
  then
    cd InfoProc_Project
    git pull origin master
    cd
  else
    git clone git@github.com:sts219/InfoProc_Project.git
  fi
  echo "Most recent version obtained"

  echo "###########################"
  echo "Launching TCP server"
  g++ InfoProc_Project/TCP/CppC/TCPServer.cpp -o server
  ./server

  echo "###########################"
  echo "Cleaning"
  rm server
EOF
