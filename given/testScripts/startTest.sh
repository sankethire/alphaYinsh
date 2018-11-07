pw_dir="/media/yashmalviya98/0FE212980FE21298/1/Assignments/COL333/A2/Yinsh-AI/"
env_dir="../yinshEnv/bin/activate"

xterm -hold -e "cd $pw_dir ; source $env_dir ; bash server.sh" &
xterm -hold -e "cd $pw_dir ; source $env_dir ; bash client1.sh" &
xterm -hold -e "cd $pw_dir ; source $env_dir ; bash client2.sh"