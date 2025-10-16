savedcmd_passing_arguments.mod := printf '%s\n'   passing_arguments.o | awk '!x[$$0]++ { print("./"$$0) }' > passing_arguments.mod
