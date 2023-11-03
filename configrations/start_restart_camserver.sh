tmux kill-session -t PilatusCamServer
tmux new -d -s PilatusCamServer
tmux send-keys -t PilatusCamServer "ssh det@10.3.3.8" ENTER
tmux send-keys -t PilatusCamServer "camserver" ENTER

