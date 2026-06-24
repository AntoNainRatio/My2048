#!/bin/bash

set -e

sudo apt update

sudo apt install -y build-essential pkg-config

sudo apt install -y libgtk-3-dev

sudo apt install -y libcriterion-dev

make all
