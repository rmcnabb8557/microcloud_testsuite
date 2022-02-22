# MicroCloud Testsuite readme.md by @rmcnabb8557 
Don't touch anything, these things are sensitive, currently the system creates 3 child processes which communicate linearly via pipelines
#   view<-control->model

Eventually I want it to act as such:
#   view<->control<->model
Where view connects to GUI which is created by teammate, and model connects to node_web which is created by @szechu4n
