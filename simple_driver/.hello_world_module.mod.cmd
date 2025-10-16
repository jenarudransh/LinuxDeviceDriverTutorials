savedcmd_hello_world_module.mod := printf '%s\n'   hello_world_module.o | awk '!x[$$0]++ { print("./"$$0) }' > hello_world_module.mod
