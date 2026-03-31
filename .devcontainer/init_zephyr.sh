#!/bin/bash
source /home/vscode/zephyrproject/.venv/bin/activate

if [ ! -d ../.west ]; then
    echo "Initializing Zephyr workspace..."
    west init -l
    west update
    west zephyr-export
    west packages pip --install
    west sdk install
else
    echo "Zephyr workspace already initialized. Skipping initialization."
fi
