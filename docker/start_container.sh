#!/bin/bash
if [ "$1" == "" ]; then
  echo "please input container_name to start
  usage: $0 [container_name]
"
  exit 0
fi

container_name=$1
sudo docker start  ${container_name}
sudo docker exec -it  ${container_name} /bin/bash