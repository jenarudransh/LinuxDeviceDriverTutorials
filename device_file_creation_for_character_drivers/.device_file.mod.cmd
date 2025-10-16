savedcmd_device_file.mod := printf '%s\n'   device_file.o | awk '!x[$$0]++ { print("./"$$0) }' > device_file.mod
