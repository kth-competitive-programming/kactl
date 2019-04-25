# Hashes a file, ignoring all whitespace and comments. Use for
# verifying that code was correctly typed.
cpp -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c1-6
