
for fname in open('todo'):
    fname = fname.strip()
    print(fname)
    with open(fname) as f:
        cont = list(f)
    beforeline = -1
    for i, line in enumerate(cont):
        if line.startswith(' * Author:') or line.startswith(' * Date:'):
            beforeline = i+1
    cont[beforeline:beforeline] = [' * License: CC0\n']
    cont = ''.join(cont)
    with open(fname, 'w') as f:
        f.write(cont)
