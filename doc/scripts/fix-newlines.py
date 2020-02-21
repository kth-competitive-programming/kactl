import glob

for fname in glob.glob('content/*/*.h'):
    fname = fname.strip()
    with open(fname) as f:
        cont = list(f)
    prline = -1
    for i, line in enumerate(cont):
        if line.startswith('#pragma once'):
            prline = i
    if prline == -1:
        continue
    print(fname)
    while not cont[prline-1].strip():
        del cont[prline-1]
        prline -= 1
    while not cont[prline+1].strip():
        del cont[prline+1]
    cont[prline+1:prline+1] = ['\n']
    cont = ''.join(cont)
    # print(cont)
    # print()
    with open(fname, 'w') as f:
        f.write(cont)
