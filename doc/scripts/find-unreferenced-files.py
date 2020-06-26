import os

for (dirpath, dirnames, filenames) in os.walk('content'):
    try:
        with open(os.path.join(dirpath, 'chapter.tex')) as f:
            chapter_tex = f.read()
    except:
        continue

    for fname in filenames:
        if not fname.endswith('.h') or '-codeforces' in fname:
            continue
        if f'{{{fname}}}' in chapter_tex:
            continue
        print(os.path.join(dirpath, fname))
