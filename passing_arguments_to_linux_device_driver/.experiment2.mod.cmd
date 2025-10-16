savedcmd_experiment2.mod := printf '%s\n'   experiment2.o | awk '!x[$$0]++ { print("./"$$0) }' > experiment2.mod
