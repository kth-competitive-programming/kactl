KACTL stands for KTH ACM Contest Template Library and it contains a lot of useful tips and code. We use Mercurial revision control system for KACTL. The first step is to install it on your system. There are even a few graphical applications (see e.g. http://en.wikipedia.org/wiki/Mercurial#Related_software) but this Howto is written for the official console client. To build KACTL, you will need Python, make and LaTeX.

When you've got Mercurial installed on your computer, you should check that you can access Mercurial on the KTH computers without a login shell. Try running
$ ssh <nada-username>@my.nada.kth.se hg --version
If you get back the Mercurial version, then you are all set. However, we had some problems with this because the KTH module system won't load when you ssh without a login shell, so we had to add the following lines to our .bashrc (on nada's system):
export PATH=$PATH:/pkg/mercurial/1.4.2/os/bin;
export PYTHONPATH=$PYTHONPATH:/pkg/mercurial/1.4.2/os/lib/python/;

Mercurial is a distributed revision control system, which means that you will have a complete local copy of the entire project history. You perform commits to your local repository, and then push/pull the changesets to our central repository. Notice the following concepts:
working space      - The files you have currently visible on your computer.
local repository   - The entire history of the repository, stored on your computer, in the hidden .hg folder under the project.
central repository - The entire history of the repository, stored on KTH's network.
changeset          - A group of file changes in the repository.
Thus, a common working flow is to first update your working space to the latest version from the central repository (hg pull, hg update). Then edit some files in your working space, you can use any text editor for this. When you are done, check that you haven't changed anything by mistake (hg status, hg diff), and then commit the changes to the local repository (hg commit), this creates a new changeset. If you have added a new file, then you need to run 'hg add' before committing, and if you want to move or remove a file, use 'hg move' and 'hg remove'. Finally, you need to synchronize your changes back to the central repository. Start by checking if someone else has made any changes while you were working (hg incoming, hg pull), in the worst case, you need to merge (hg merge). Then, push your changesets to the central repository (hg outgoing, hg push).

Now we are ready to start, check out your local copy of the repository by typing:
$ hg clone ssh://<nada-username>@my.nada.kth.se//misc/projects/contest/newKACTL <local-directory>
Also ask Håkan <hakante@kth.se> to give you permissions to write to the repository.

Before committing for the first time, you should create a .hgrc file in your home folder (on the computer where you make the commits, i.e., your own computer) with the name you want to be visible when you commit, e.g.:
[ui]
username = Håkan Terelius <hakante@kth.se>

These are the commands you will use most of the time:
hg status          - Shows you any local changes you have made to the repository. Use this all the time, especially before committing!!
hg diff            - See exactly which lines that have been modified. Can be used on single files, and between any two revisions.
hg commit          - Commits your changes to your LOCAL repository
hg pull            - Downloads any new changesets from the central repository to your local repository.
hg incoming        - Checks if there is anything to pull.
hg push            - Uploads any new changesets from your local repository to the central repository.
hg outgoing        - Checks if there is anything to push.
hg update          - Updates your working space to the lates changeset (used after 'pull')
hg add             - Signals that a file should be under version control. Commit to actually save it.
hg remove          - Removes that file, and signals that the file should be removed from the repository.
hg move            - Moves that file, and signals that the file has moved, so that Mercurial can keep it's history.
hg revert          - Go back to an earlier version of a file, or an entire changeset.
hg merge           - If you have made any changes to a file that has also been modified on the central repository.

Consult "hg add --help" for help or read a tutorial
http://mercurial.selenic.com/wiki/Tutorial

For further information and guidelines about committing content to KACTl, read the file doc/README in the repository.
