# Hashes a file, ignoring all whitespace and comments. 
# Usage: source hash.sh < file.cpp
cpp -dD -P -fpreprocessed | tr -d '[:space:]'| md5sum |cut -c-6
