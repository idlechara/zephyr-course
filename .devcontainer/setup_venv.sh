#!/bin/bash

python3 -m venv ~/zephyrproject/.venv
source ~/zephyrproject/.venv/bin/activate
pip install west

echo "source /home/vscode/zephyrproject/.venv/bin/activate" >> ~/.zshrc
echo "source /home/vscode/zephyrproject/.venv/bin/activate" >> ~/.bashrc
source /home/vscode/zephyrproject/.venv/bin/activate
sudo mkdir -p /workspaces
sudo chown vscode:vscode /workspaces
