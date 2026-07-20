#!/usr/bin/env bash
#
# cristop-by-name.sh  — Stop a running CRI-O / containerd container by name.
#
#   Usage: ./cristop-by-name.sh my-app
#   You can also chmod +x it and put it in your path.

set -euo pipefail

############################
# CONFIGURE THESE TWO LINES
############################
SUDO_USER=control          # ← the Linux user that will run the script
SUDO_PASS='sesamems$$$'       # ← that user’s password (plaintext!)
############################

if [[ $# -ne 1 ]]; then
  echo "Usage: $0 <container-name>" >&2
  exit 1
fi
NAME="$1"

# Look up the (first) running container ID that matches the exact name
ID=$(printf '%s\n' "$SUDO_PASS" |
     sudo -S -u "$SUDO_USER" \
       crictl ps --name "^${NAME}$" -q | head -n1)

if [[ -z "$ID" ]]; then
  echo "No running container found with the exact name: $NAME"
  exit 1
fi

# Stop it
printf '%s\n' "$SUDO_PASS" |
  sudo -S -u "$SUDO_USER" crictl stop "$ID"

echo "Container $NAME (ID $ID) stopped."

