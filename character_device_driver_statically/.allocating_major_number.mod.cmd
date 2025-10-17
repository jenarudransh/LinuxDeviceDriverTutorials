savedcmd_allocating_major_number.mod := printf '%s\n'   allocating_major_number.o | awk '!x[$$0]++ { print("./"$$0) }' > allocating_major_number.mod
