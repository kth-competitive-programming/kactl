# For interactive problems
mkfifo fifo
(./solution < fifo) | (./interactor > fifo)