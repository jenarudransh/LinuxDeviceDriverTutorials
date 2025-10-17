savedcmd_allocating_major_number_dynamically.mod := printf '%s\n'   allocating_major_number_dynamically.o | awk '!x[$$0]++ { print("./"$$0) }' > allocating_major_number_dynamically.mod
